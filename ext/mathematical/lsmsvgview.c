/* Lasem
 *
 * Copyright © 2009 Emmanuel Pacaud
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Author:
 * 	Emmanuel Pacaud <emmanuel@gnome.org>
 */

#include <lsmdebug.h>
#include <lsmsvgview.h>
#include <lsmsvgdocument.h>
#include <lsmsvgelement.h>
#include <lsmsvgsvgelement.h>
#include <lsmsvgradialgradientelement.h>
#include <lsmsvgfilterelement.h>
#include <lsmsvglineargradientelement.h>
#include <lsmsvgpatternelement.h>
#include <lsmsvgmarkerelement.h>
#include <lsmsvgclippathelement.h>
#include <lsmsvgmaskelement.h>
#include <lsmsvgfiltersurface.h>
#include <lsmcairo.h>
#include <lsmstr.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib/gprintf.h>

#include <math.h>
#include <string.h>

static gboolean lsm_svg_view_circular_reference_check (LsmSvgView *view, LsmSvgElement *element);

static GObjectClass *parent_class;

typedef struct {
	gboolean is_text_path;
	gboolean is_extents_defined;
	LsmExtents extents;
	PangoLayout *pango_layout;
} LsmSvgViewPathInfos;

static LsmSvgViewPathInfos default_path_infos = {
	.is_text_path = FALSE,
	.is_extents_defined = FALSE,
	.extents = {0.0, 0.0, 0.0, 0.0},
	.pango_layout = NULL
};

struct _LsmSvgViewPatternData {
	cairo_t *old_cairo;

	cairo_pattern_t *pattern;

	LsmBox extents;
	LsmBox object_extents;

	double opacity;
};

typedef struct {
	cairo_surface_t *surface;
	double group_opacity;
	gboolean enable_background;
} LsmSvgViewBackground;

cairo_operator_t cairo_operators[] = {
	CAIRO_OPERATOR_CLEAR,
	CAIRO_OPERATOR_SOURCE,
	CAIRO_OPERATOR_DEST,
	CAIRO_OPERATOR_OVER,
	CAIRO_OPERATOR_DEST_OVER,
	CAIRO_OPERATOR_IN,
	CAIRO_OPERATOR_DEST_IN,
	CAIRO_OPERATOR_OUT,
	CAIRO_OPERATOR_DEST_OUT,
	CAIRO_OPERATOR_ATOP,
	CAIRO_OPERATOR_DEST_ATOP,
	CAIRO_OPERATOR_XOR,
	CAIRO_OPERATOR_ADD,
	CAIRO_OPERATOR_MULTIPLY,
	CAIRO_OPERATOR_SCREEN,
	CAIRO_OPERATOR_OVERLAY,
	CAIRO_OPERATOR_DARKEN,
	CAIRO_OPERATOR_LIGHTEN,
	CAIRO_OPERATOR_COLOR_DODGE,
	CAIRO_OPERATOR_COLOR_BURN,
	CAIRO_OPERATOR_HARD_LIGHT,
	CAIRO_OPERATOR_SOFT_LIGHT,
	CAIRO_OPERATOR_DIFFERENCE,
	CAIRO_OPERATOR_EXCLUSION
};

void
lsm_cairo_set_comp_op (cairo_t *cairo, LsmSvgCompOp comp_op)
{
	if (G_LIKELY (cairo != NULL && comp_op >= LSM_SVG_COMP_OP_CLEAR && comp_op <= LSM_SVG_COMP_OP_EXCLUSION)) {
		lsm_log_render ("[lsmSvgView::set_comp_op] Set comp-op to %s", lsm_svg_comp_op_to_string (comp_op));
		cairo_set_operator (cairo, cairo_operators[comp_op]);
	}
}

double
lsm_svg_view_normalize_length (LsmSvgView *view, const LsmSvgLength *length, LsmSvgLengthDirection direction)
{
	g_return_val_if_fail (LSM_IS_SVG_VIEW (view), 0.0);

	return lsm_svg_length_normalize (length, view->viewbox_stack->data, view->style->font_size_px, direction);
}

static void
_start_pattern (LsmSvgView *view, const LsmBox *extents, const LsmBox *object_extents, double opacity)
{
	lsm_debug_render ("[LsmSvgView::start_pattern]");

	view->pattern_stack = g_slist_prepend (view->pattern_stack, view->pattern_data);

	view->pattern_data = g_new (LsmSvgViewPatternData, 1);
	view->pattern_data->old_cairo = view->dom_view.cairo;
	view->pattern_data->pattern = NULL;
	view->pattern_data->extents = *extents;
	view->pattern_data->opacity = opacity;
	view->pattern_data->object_extents = *object_extents;

	view->dom_view.cairo = NULL;
}

static void
_end_pattern (LsmSvgView *view)
{
	g_return_if_fail (view->pattern_data != NULL);

	if (view->pattern_data->pattern != NULL)
		cairo_pattern_destroy (view->pattern_data->pattern);
	if (view->dom_view.cairo != NULL)
		cairo_destroy (view->dom_view.cairo);

	view->dom_view.cairo = view->pattern_data->old_cairo;

	g_free (view->pattern_data);

	if (view->pattern_stack != NULL) {
		view->pattern_data = view->pattern_stack->data;
		view->pattern_stack = g_slist_delete_link (view->pattern_stack, view->pattern_stack);
	} else
		view->pattern_data = NULL;

	lsm_debug_render ("[LsmSvgView::end_pattern]");
}

static void
_set_pattern (LsmSvgView *view, cairo_pattern_t *pattern)
{
	g_return_if_fail (view->pattern_data != NULL);
	g_return_if_fail (view->pattern_data->pattern == NULL);

	view->pattern_data->pattern = pattern;
	view->last_stop_offset = 0.0;
}

void
lsm_svg_view_create_radial_gradient (LsmSvgView *view,
				     double cx, double cy,
				     double r,
				     double fx, double fy)
{
	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	_set_pattern (view, cairo_pattern_create_radial (fx, fy, 0, cx, cy, r));
}

void
lsm_svg_view_create_linear_gradient (LsmSvgView *view,
				     double x1, double y1,
				     double x2, double y2)
{
	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	_set_pattern (view, cairo_pattern_create_linear (x1, y1, x2, y2));
}

void
lsm_svg_view_add_gradient_color_stop (LsmSvgView *view, double offset)
{
	const LsmSvgStyle *style;
	const LsmSvgColor *color;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (view->pattern_data != NULL);
	g_return_if_fail (view->pattern_data->pattern != NULL);

	if (offset > 1.0)
		offset = 1.0;

	if (offset < view->last_stop_offset)
		offset = view->last_stop_offset;
	else
		view->last_stop_offset = offset;

	style = view->style;

	lsm_debug_render ("[LsmSvgView::add_gradient_color_stop] opacity = %g", style->stop_opacity->value);

	color = &style->stop_color->value;

	if (color->red < 0.0 || color->blue < 0.0 || color->green < 0.0)
		color = &style->color->value;

	lsm_debug_render ("[LsmSvgView::add_gradient_color_stop] color = %2x%2x%2x",
		   (int) (255.0 * color->red),
		   (int) (255.0 * color->green),
		   (int) (255.0 * color->blue));

	cairo_pattern_add_color_stop_rgba (view->pattern_data->pattern, offset,
					   color->red,
					   color->green,
					   color->blue,
					   style->stop_opacity->value * view->pattern_data->opacity);
}

gboolean
lsm_svg_view_set_gradient_properties (LsmSvgView *view,
				      LsmSvgSpreadMethod method,
				      LsmSvgPatternUnits units,
				      const LsmSvgMatrix *gradient_matrix)
{
	cairo_matrix_t matrix;
	cairo_matrix_t inv_matrix;
	cairo_status_t status;

	g_return_val_if_fail (LSM_IS_SVG_VIEW (view), FALSE);
	g_return_val_if_fail (view->pattern_data != NULL, FALSE);
	g_return_val_if_fail (view->pattern_data->pattern != NULL, FALSE);

	switch (method) {
		case LSM_SVG_SPREAD_METHOD_REFLECT:
			cairo_pattern_set_extend (view->pattern_data->pattern, CAIRO_EXTEND_REFLECT);
			break;
		case LSM_SVG_SPREAD_METHOD_REPEAT:
			cairo_pattern_set_extend (view->pattern_data->pattern, CAIRO_EXTEND_REPEAT);
			break;
		default:
			cairo_pattern_set_extend (view->pattern_data->pattern, CAIRO_EXTEND_PAD);
	}

	if (gradient_matrix != NULL) {
		cairo_matrix_init (&matrix,
				   gradient_matrix->a, gradient_matrix->b,
				   gradient_matrix->c, gradient_matrix->d,
				   gradient_matrix->e, gradient_matrix->f);
		cairo_matrix_invert (&matrix);
	} else
		cairo_matrix_init_identity (&matrix);

	if (units == LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX &&
	    view->pattern_data->extents.width > 0.0 &&
	    view->pattern_data->extents.height > 0.0) {
		cairo_matrix_scale (&matrix,
				    1.0 / view->pattern_data->extents.width,
				    1.0 / view->pattern_data->extents.height);
		cairo_matrix_translate (&matrix,
					-view->pattern_data->extents.x,
					-view->pattern_data->extents.y);

	}

	inv_matrix = matrix;
	status = cairo_matrix_invert (&inv_matrix);

	if (status != CAIRO_STATUS_SUCCESS) {
		lsm_debug_render ("[LsmSvgView::set_gradient_properties] Not invertible matrix");
		return FALSE;
	}

	cairo_pattern_set_matrix (view->pattern_data->pattern, &matrix);

	return TRUE;
}

gboolean
lsm_svg_view_create_surface_pattern (LsmSvgView *view,
				     const LsmBox *viewport,
				     const LsmSvgMatrix *pattern_matrix,
				     LsmSvgViewSurfaceType surface_type)
{
	cairo_surface_t *surface;
	cairo_pattern_t *pattern;
	cairo_matrix_t matrix;
	cairo_matrix_t inv_matrix;
	cairo_status_t status;
	double x1, y1, x2, y2;
	double device_width, device_height;
	double x_scale, y_scale;

	g_return_val_if_fail (LSM_IS_SVG_VIEW (view), FALSE);
	g_return_val_if_fail (viewport != NULL, FALSE);
	g_return_val_if_fail (view->pattern_data != NULL, FALSE);
	g_return_val_if_fail (view->dom_view.cairo == NULL, FALSE);

	x1 = viewport->x;
	y1 = viewport->y;
	x2 = viewport->x + viewport->width;
	y2 = viewport->y;

	cairo_user_to_device (view->pattern_data->old_cairo, &x1, &y1);
	cairo_user_to_device (view->pattern_data->old_cairo, &x2, &y2);

	device_width = sqrt ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));

	x2 = viewport->x;
	y2 = viewport->y + viewport->height;

	cairo_user_to_device (view->pattern_data->old_cairo, &x2, &y2);

	device_height = sqrt ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));

	if (surface_type == LSM_SVG_VIEW_SURFACE_TYPE_IMAGE) {
		device_height = ceil (device_height);
		device_width = ceil (device_width);
	}

	x_scale = device_width / viewport->width;
	y_scale = device_height / viewport->height;

	lsm_debug_render ("[LsmSvgView::create_surface_pattern] pattern size = %g ,%g at %g, %g (scale %g x %g)",
		   device_width, device_height, viewport->x, viewport->y, x_scale, y_scale);

	switch (surface_type) {
		case LSM_SVG_VIEW_SURFACE_TYPE_AUTO:
			surface = cairo_surface_create_similar (cairo_get_target (view->pattern_data->old_cairo),
								CAIRO_CONTENT_COLOR_ALPHA,
								device_width, device_height);
			break;
		default:
		case LSM_SVG_VIEW_SURFACE_TYPE_IMAGE:
			surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, device_width, device_height);
			break;
	}

	pattern = cairo_pattern_create_for_surface (surface);
	view->dom_view.cairo = cairo_create (surface);
	cairo_surface_destroy (surface);

	cairo_scale (view->dom_view.cairo, x_scale, y_scale);
	cairo_translate (view->dom_view.cairo, -viewport->x, -viewport->y);

	_set_pattern (view, pattern);

	if (pattern_matrix != NULL) {
		cairo_matrix_init (&matrix,
				   pattern_matrix->a, pattern_matrix->b,
				   pattern_matrix->c, pattern_matrix->d,
				   pattern_matrix->e + viewport->x, pattern_matrix->f + viewport->y);
		cairo_matrix_scale (&matrix, 1.0 / x_scale, 1.0 / y_scale);
		cairo_matrix_invert (&matrix);
	} else {
		cairo_matrix_init_scale (&matrix, x_scale, y_scale);
		cairo_matrix_translate (&matrix, -viewport->x, -viewport->y);
	}

	inv_matrix = matrix;
	status = cairo_matrix_invert (&inv_matrix);

	if (status != CAIRO_STATUS_SUCCESS) {
		lsm_debug_render ("[LsmSvgView::create_surface_pattern] Not invertible matrix");
		return FALSE;
	}

	cairo_pattern_set_matrix (view->pattern_data->pattern, &matrix);
	cairo_pattern_set_extend (view->pattern_data->pattern, CAIRO_EXTEND_REPEAT);

	lsm_debug_render ("[LsmSvgView::create_surface_pattern] Pattern matrix %g, %g, %g, %g, %g, %g",
			  matrix.xx, matrix.xy, matrix.yx, matrix.yy,
			  matrix.x0, matrix.y0);

	return TRUE;
}

typedef enum {
	LSM_SVG_VIEW_PAINT_OPERATION_FILL,
	LSM_SVG_VIEW_PAINT_OPERATION_STROKE
} LsmSvgViewPaintOperation;

static void
_paint_url (LsmSvgView *view,
	    LsmSvgViewPathInfos *path_infos,
	    LsmSvgViewPaintOperation operation,
	    const char *url, double opacity)
{
	cairo_t *cairo;
	LsmSvgElement *element;
	LsmBox extents;

	element = lsm_svg_document_get_element_by_url (LSM_SVG_DOCUMENT (view->dom_view.document), url);
	if ((!LSM_IS_SVG_RADIAL_GRADIENT_ELEMENT (element) &&
	     !LSM_IS_SVG_LINEAR_GRADIENT_ELEMENT (element) &&
	     !LSM_IS_SVG_PATTERN_ELEMENT (element)) ||
	    lsm_svg_view_circular_reference_check (view, element)) {

		cairo_set_source_rgba (view->dom_view.cairo, 0, 0, 0, 0);

		lsm_warning_render ("[LsmSvgView::_paint_url] Paint url not found: %s", url);

		return;
	}

	lsm_debug_render ("[LsmSvgView::_paint_url] Paint using '%s'", url);

	if (!path_infos->is_extents_defined) {
		cairo_path_extents (view->dom_view.cairo,
				    &path_infos->extents.x1,
				    &path_infos->extents.y1,
				    &path_infos->extents.x2,
				    &path_infos->extents.y2);
		path_infos->is_extents_defined = TRUE;
	}

	extents.x = path_infos->extents.x1;
	extents.y = path_infos->extents.y1;
	extents.width =  path_infos->extents.x2 - extents.x;
	extents.height = path_infos->extents.y2 - extents.y;

	lsm_debug_render ("[LsmSvgView::_paint_url] Pattern extents x = %g, y = %g, w = %g, h = %g",
		   extents.x, extents.y, extents.width, extents.height);

	_start_pattern (view, &extents, &extents, opacity);

	lsm_svg_element_force_render (LSM_SVG_ELEMENT (element), view);

	cairo = view->pattern_data->old_cairo;

	if (view->pattern_data->pattern) {
		if (view->debug_pattern && view->dom_view.cairo) {
			char *filename;

			filename = g_strdup_printf ("pattern-%s).png", url);
			cairo_surface_write_to_png (cairo_get_target (view->dom_view.cairo), filename);
			g_free (filename);
		}

		cairo_set_source (cairo, view->pattern_data->pattern);
	} else
		cairo_set_source_rgba (cairo, 0.0, 0.0, 0.0, 0.0);

	_end_pattern (view);
}

static gboolean
_set_color (LsmSvgView *view,
	    LsmSvgViewPathInfos *path_infos,
	    LsmSvgViewPaintOperation operation,
	    const LsmSvgPaint *paint, double opacity)
{
	cairo_t *cairo = view->dom_view.cairo;

	switch (paint->type) {
		case LSM_SVG_PAINT_TYPE_NONE:
			return FALSE;
		case LSM_SVG_PAINT_TYPE_RGB_COLOR:
			cairo_set_source_rgba (cairo,
					       paint->color.red,
					       paint->color.green,
					       paint->color.blue,
					       opacity);
			break;
		case LSM_SVG_PAINT_TYPE_CURRENT_COLOR:
			cairo_set_source_rgba (cairo,
					       view->style->color->value.red,
					       view->style->color->value.green,
					       view->style->color->value.blue,
					       opacity);
			break;
		case LSM_SVG_PAINT_TYPE_URI:
		case LSM_SVG_PAINT_TYPE_URI_RGB_COLOR:
		case LSM_SVG_PAINT_TYPE_URI_CURRENT_COLOR:
		case LSM_SVG_PAINT_TYPE_URI_NONE:
			_paint_url (view, path_infos, operation, paint->url, opacity);
			break;
		default:
			return FALSE;
	}

	return TRUE;
}

static void
paint_markers (LsmSvgView *view)
{
	const LsmSvgStyle *style;
	LsmSvgElement *marker;
	LsmSvgElement *marker_start;
	LsmSvgElement *marker_mid;
	LsmSvgElement *marker_end;
	cairo_t *cairo;
	cairo_path_t *path;
	cairo_path_data_t *data;
	cairo_path_data_t *next_data;
	double stroke_width;
	double prev_x, prev_y;
	double x = 0;
	double y = 0;
	double next_x, next_y;
	cairo_path_data_type_t type;
	cairo_path_data_type_t next_type;
	double angle;
	int i;

	style = view->style;

	if ((style->marker->value == NULL ||       strcmp (style->marker->value, "none") == 0) &&
	    (style->marker_mid->value == NULL ||   strcmp (style->marker_mid->value, "none") == 0) &&
	    (style->marker_end->value == NULL ||   strcmp (style->marker_end->value, "none") == 0) &&
	    (style->marker_start->value == NULL || strcmp (style->marker_start->value, "none") == 0))
		return;

	cairo = view->dom_view.cairo;

	marker = lsm_svg_document_get_element_by_url (LSM_SVG_DOCUMENT (view->dom_view.document),
						      style->marker->value);
	marker_start = lsm_svg_document_get_element_by_url (LSM_SVG_DOCUMENT (view->dom_view.document),
							    style->marker_start->value);
	marker_mid = lsm_svg_document_get_element_by_url (LSM_SVG_DOCUMENT (view->dom_view.document),
							  style->marker_mid->value);
	marker_end = lsm_svg_document_get_element_by_url (LSM_SVG_DOCUMENT (view->dom_view.document),
							  style->marker_end->value);
	stroke_width = lsm_svg_view_normalize_length (view, &view->style->stroke_width->length,
						      LSM_SVG_LENGTH_DIRECTION_DIAGONAL);

	if (marker != NULL && lsm_svg_view_circular_reference_check (view, marker))
		return;
	if (marker_start != NULL && lsm_svg_view_circular_reference_check (view, marker_start))
		return;
	if (marker_mid != NULL && lsm_svg_view_circular_reference_check (view, marker_mid))
		return;
	if (marker_end != NULL && lsm_svg_view_circular_reference_check (view, marker_end))
		return;

	if (marker_start == NULL)
		marker_start = marker;
	if (marker_mid == NULL)
		marker_mid = marker;
	if (marker_end == NULL)
		marker_end = marker;

	path = cairo_copy_path (cairo);
	cairo_new_path (cairo);

	if (path->num_data > 0) {
		next_data = &path->data[0];
		next_type = next_data->header.type;

		if (next_type == CAIRO_PATH_CURVE_TO) {
			next_x = next_data[3].point.x;
			next_y = next_data[3].point.y;
		} else {
			next_x = next_data[1].point.x;
			next_y = next_data[1].point.y;
		}

		for (i = 0; i < path->num_data; i += path->data[i].header.length) {
			data = next_data;

			prev_x = x;
			prev_y = y;
			x = next_x;
			y = next_y;
			type = next_type;

			if (i + path->data[i].header.length < path->num_data) {
				next_data = &path->data[i + path->data[i].header.length];
				next_type = next_data->header.type;

				if (next_type == CAIRO_PATH_CURVE_TO) {
					next_x = next_data[3].point.x;
					next_y = next_data[3].point.y;
				} else {
					next_x = next_data[1].point.x;
					next_y = next_data[1].point.y;
				}
			} else {
				next_data = NULL;
				next_type = CAIRO_PATH_MOVE_TO;
				next_x = 0.0;
				next_y = 0.0;
			}

			if (data->header.type == CAIRO_PATH_CLOSE_PATH) {
				marker = NULL;
			} else if (next_data == NULL ||
				   next_data->header.type == CAIRO_PATH_MOVE_TO) {
				marker = marker_end;
				if (type == CAIRO_PATH_CURVE_TO) {
					if (y != data[2].point.y ||
					    x != data[2].point.x)
						angle = atan2 (y - data[2].point.y,
							       x - data[2].point.x);
					else
						angle = atan2 (y - data[1].point.y,
							       x - data[1].point.x);
				} else
					angle = atan2 (y - prev_y, x - prev_x);
			} else if (data->header.type == CAIRO_PATH_MOVE_TO) {
				marker = marker_start;
				if (next_type == CAIRO_PATH_CURVE_TO) {
					if (next_data[1].point.y != y ||
					    next_data[1].point.x != x)
						angle = atan2 (next_data[1].point.y - y,
							       next_data[1].point.x - x);
					else
						angle = atan2 (next_data[2].point.y - y,
							       next_data[2].point.x - x);
				} else
					angle = atan2 (next_y - y, next_x - x);
			} else {
				double xdifin, ydifin, xdifout, ydifout, intot, outtot;

				marker = marker_mid;

				if (type == CAIRO_PATH_CURVE_TO) {
					if (x != data[2].point.x ||
					    y != data[2].point.y) {
						xdifin = x - data[2].point.x;
						ydifin = y - data[2].point.y;
					} else {
						xdifin = x - data[1].point.x;
						ydifin = y - data[1].point.y;
					}
				} else {
					xdifin = x - prev_x;
					ydifin = y - prev_y;
				}
				if (next_type == CAIRO_PATH_CURVE_TO) {
					if (next_data[1].point.x != x ||
					    next_data[1].point.y != y) {
						xdifout = next_data[1].point.x - x;
						ydifout = next_data[1].point.y - y;
					} else {
						xdifout = next_data[2].point.x - x;
						ydifout = next_data[2].point.y - y;
					}
				} else {
					xdifout = next_x - x;
					ydifout = next_y - y;
				}

				intot = sqrt (xdifin * xdifin + ydifin * ydifin);
				outtot = sqrt (xdifout * xdifout + ydifout * ydifout);

				xdifin /= intot;
				ydifin /= intot;
				xdifout /= outtot;
				ydifout /= outtot;

				angle = atan2 ((ydifin + ydifout) / 2, (xdifin + xdifout) / 2);
			}

			if (marker != NULL) {
				cairo_save (cairo);
				cairo_translate (cairo, x, y);
				lsm_svg_marker_element_render (LSM_SVG_MARKER_ELEMENT (marker), view,
							       stroke_width, angle);
				cairo_restore (cairo);
			}
		}

		cairo_path_destroy (path);
	}
}

static void
paint (LsmSvgView *view, LsmSvgViewPathInfos *path_infos)
{
	const LsmSvgStyle *style;
	LsmSvgElement *element;
	cairo_t *cairo;
	gboolean use_group;
	double group_opacity;

	element = view->element_stack->data;

	g_return_if_fail (LSM_IS_SVG_ELEMENT (element));

	cairo = view->dom_view.cairo;
	style = view->style;

	if ((style->opacity != NULL ||
	     style->comp_op->value != LSM_SVG_COMP_OP_SRC_OVER ) &&
	    style->ignore_group_opacity &&
	    g_strcmp0 (style->filter->value, "none") == 0) {
		group_opacity = style->opacity->value;

		use_group = ((style->fill->paint.type != LSM_SVG_PAINT_TYPE_NONE &&
			      style->stroke->paint.type != LSM_SVG_PAINT_TYPE_NONE) ||
			     style->stroke->paint.type == LSM_SVG_PAINT_TYPE_URI ||
			     style->stroke->paint.type == LSM_SVG_PAINT_TYPE_URI_RGB_COLOR ||
			     style->fill->paint.type == LSM_SVG_PAINT_TYPE_URI_RGB_COLOR ||
			     style->fill->paint.type == LSM_SVG_PAINT_TYPE_URI) &&
			(group_opacity < 1.0 || style->comp_op->value != LSM_SVG_COMP_OP_SRC_OVER );
	} else {
		use_group = FALSE;
		group_opacity = 1.0;
	}

	/* Instead of push_group, we should restrict to the current path bounding box */
	if (use_group) {
		cairo_push_group (cairo);
	} else if (style->comp_op->value != LSM_SVG_COMP_OP_SRC_OVER)
		lsm_cairo_set_comp_op (cairo, style->comp_op->value);

	if (_set_color (view,
			path_infos,
			LSM_SVG_VIEW_PAINT_OPERATION_FILL,
			&style->fill->paint,
			style->fill_opacity->value * (use_group ? 1.0 : group_opacity))) {

		if (path_infos->is_text_path) {
			pango_cairo_show_layout (cairo, path_infos->pango_layout);
		} else {
			cairo_set_fill_rule (cairo, style->fill_rule->value == LSM_SVG_FILL_RULE_EVEN_ODD ?
					     CAIRO_FILL_RULE_EVEN_ODD : CAIRO_FILL_RULE_WINDING);
			cairo_fill_preserve (cairo);
		}
	}

	if (_set_color (view,
			path_infos,
			LSM_SVG_VIEW_PAINT_OPERATION_STROKE,
			&style->stroke->paint,
			style->stroke_opacity->value * (use_group ? 1.0 : group_opacity))) {
		double line_width;

		if (path_infos->is_text_path) {
			pango_cairo_layout_path (cairo, path_infos->pango_layout);
		}

		switch (style->stroke_line_join->value) {
			case LSM_SVG_LINE_JOIN_MITER:
				cairo_set_line_join (cairo, CAIRO_LINE_JOIN_MITER);
				break;
			case LSM_SVG_LINE_JOIN_ROUND:
				cairo_set_line_join (cairo,CAIRO_LINE_JOIN_ROUND);
				break;
			default:
				cairo_set_line_join (cairo,CAIRO_LINE_JOIN_BEVEL);
		}

		switch (style->stroke_line_cap->value) {
			case LSM_SVG_LINE_CAP_BUTT:
				cairo_set_line_cap (cairo, CAIRO_LINE_CAP_BUTT);
				break;
			case LSM_SVG_LINE_CAP_ROUND:
				cairo_set_line_cap (cairo, CAIRO_LINE_CAP_ROUND);
				break;
			default:
				cairo_set_line_cap (cairo, CAIRO_LINE_CAP_SQUARE);
		}

		line_width = lsm_svg_view_normalize_length (view, &style->stroke_width->length,
							    LSM_SVG_LENGTH_DIRECTION_DIAGONAL);

		cairo_set_miter_limit (cairo, style->stroke_miter_limit->value);
		cairo_set_line_width (cairo, line_width);

		if (style->stroke_dash_array->value.n_dashes > 0) {
			double dash_offset;
			double *dashes;
			unsigned int i;

			dash_offset = lsm_svg_view_normalize_length (view, &style->stroke_dash_offset->length,
								     LSM_SVG_LENGTH_DIRECTION_DIAGONAL);
			dashes = g_new (double, style->stroke_dash_array->value.n_dashes);
			for (i = 0; i < style->stroke_dash_array->value.n_dashes; i++)
				dashes[i] = lsm_svg_view_normalize_length (view,
									   &style->stroke_dash_array->value.dashes[i],
									   LSM_SVG_LENGTH_DIRECTION_DIAGONAL);

			cairo_set_dash (cairo, dashes, style->stroke_dash_array->value.n_dashes, dash_offset);
			g_free (dashes);
		} else
			cairo_set_dash (cairo, NULL, 0, 0.0);

		cairo_stroke_preserve (cairo);
	}

	paint_markers (view);

	cairo_new_path (cairo);

	if (use_group) {
		cairo_pop_group_to_source (cairo);
		if (G_UNLIKELY (style->comp_op->value != LSM_SVG_COMP_OP_SRC_OVER))
			lsm_cairo_set_comp_op (cairo, style->comp_op->value);
		cairo_paint_with_alpha (cairo, group_opacity);
	}

	if (view->style->comp_op->value != LSM_SVG_COMP_OP_SRC_OVER)
		lsm_cairo_set_comp_op (cairo, LSM_SVG_COMP_OP_SRC_OVER);
}

static void
process_path (LsmSvgView *view, LsmSvgViewPathInfos *path_infos)
{
	g_return_if_fail (view->style != NULL);

	if (view->is_clipping) {
		if (path_infos->is_text_path)
			pango_cairo_layout_path (view->dom_view.cairo, path_infos->pango_layout);
		cairo_set_fill_rule (view->dom_view.cairo, view->style->clip_rule->value);
	} else
		paint (view, path_infos);
}

void
lsm_svg_view_show_viewport (LsmSvgView*view, const LsmBox *viewport)
{
	LsmSvgPaint *paint;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (viewport != NULL);

	paint = &view->style->viewport_fill->paint;

	switch (paint->type) {
		case LSM_SVG_PAINT_TYPE_RGB_COLOR:
			cairo_set_source_rgba (view->dom_view.cairo,
					       paint->color.red,
					       paint->color.green,
					       paint->color.blue,
					       view->style->viewport_fill_opacity->value);
			break;
		case LSM_SVG_PAINT_TYPE_CURRENT_COLOR:
			cairo_set_source_rgba (view->dom_view.cairo,
					       view->style->color->value.red,
					       view->style->color->value.green,
					       view->style->color->value.blue,
					       view->style->viewport_fill_opacity->value);
		default:
			return;
	}

	cairo_rectangle (view->dom_view.cairo, viewport->x, viewport->y, 0, 0);
	cairo_paint (view->dom_view.cairo);
}

/*
 * Code for show_rectangle and show ellipse is inspired from
 * the librsvg library (rsvg-shapes.c)
 *
 * Copyright (C) 2000 Eazel, Inc.
 * Copyright (C) 2002 Dom Lachowicz <cinamod@hotmail.com>
 *
 * Authors: Raph Levien <raph@artofcode.com>,
 *          Dom Lachowicz <cinamod@hotmail.com>,
 *          Caleb Moore <c.moore@student.unsw.edu.au>
 */

void
lsm_svg_view_show_rectangle (LsmSvgView *view,
			     double x, double y,
			     double w, double h,
			     double rx, double ry)
{
	LsmSvgViewPathInfos path_infos = default_path_infos;
	cairo_t *cairo;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	cairo = view->dom_view.cairo;

	if (rx <= 0.0 || ry <= 0.0)
		cairo_rectangle (cairo, x, y, w, h);
	else {

		if (rx > fabs (w / 2.))
			rx = fabs (w / 2.);
		if (ry > fabs (h / 2.))
			ry = fabs (h / 2.);

		cairo_move_to (cairo, x + rx, y);
		cairo_line_to (cairo, x + w - rx, y);
		lsm_cairo_elliptical_arc (cairo, rx, ry, 0.0, FALSE, TRUE, x + w, y + ry);
		cairo_line_to (cairo, x + w, y + h -ry);
		lsm_cairo_elliptical_arc (cairo, rx, ry, 0.0, FALSE, TRUE, x + w - rx, y + h);
		cairo_line_to (cairo, x + rx, y + h);
		lsm_cairo_elliptical_arc (cairo, rx, ry, 0.0, FALSE, TRUE, x, y + h - ry);
		cairo_line_to (cairo, x, y + ry);
		lsm_cairo_elliptical_arc (cairo, rx, ry, 0.0, FALSE, TRUE, x + rx, y);
		cairo_close_path (cairo);
	}

	process_path (view, &path_infos);
}

void
lsm_svg_view_show_circle (LsmSvgView *view, double cx, double cy, double r)
{
	LsmSvgViewPathInfos path_infos = default_path_infos;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	cairo_arc (view->dom_view.cairo, cx, cy, r, 0, 2 * M_PI);

	process_path (view, &path_infos);
}

#define LSM_SVG_ARC_MAGIC ((double) 0.5522847498) /* 4/3 * (1-cos 45)/sin 45 = 4/3 * sqrt(2) - 1 */

void
lsm_svg_view_show_ellipse (LsmSvgView *view, double cx, double cy, double rx, double ry)
{
	LsmSvgViewPathInfos path_infos = default_path_infos;
	cairo_t *cairo;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	if (rx <= 0 || ry <= 0)
		return;

	cairo = view->dom_view.cairo;

	cairo_move_to (cairo, cx + rx, cy);
	cairo_curve_to (cairo, cx + rx, cy + LSM_SVG_ARC_MAGIC * ry, cx + LSM_SVG_ARC_MAGIC * rx, cy + ry, cx, cy + ry);
	cairo_curve_to (cairo, cx - LSM_SVG_ARC_MAGIC * rx, cy + ry, cx - rx, cy + LSM_SVG_ARC_MAGIC * ry, cx - rx, cy);
	cairo_curve_to (cairo, cx - rx, cy - LSM_SVG_ARC_MAGIC * ry, cx - LSM_SVG_ARC_MAGIC * rx, cy - ry, cx, cy - ry);
	cairo_curve_to (cairo, cx + LSM_SVG_ARC_MAGIC * rx, cy - ry, cx + rx, cy - LSM_SVG_ARC_MAGIC * ry, cx + rx, cy);
	cairo_close_path (cairo);

	process_path (view, &path_infos);
}

void
lsm_svg_view_show_path (LsmSvgView *view,
		     const char *d)
{
	LsmSvgViewPathInfos path_infos = default_path_infos;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	lsm_cairo_emit_svg_path (view->dom_view.cairo, d);

	process_path (view, &path_infos);
}

void
lsm_svg_view_path_extents (LsmSvgView *view,
			   const char *path,
			   LsmExtents *extents)
{
	double x1, y1, x2, y2;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (extents != NULL);

	cairo_new_path (view->dom_view.cairo);
	lsm_cairo_emit_svg_path (view->dom_view.cairo, path);
	cairo_path_extents (view->dom_view.cairo, &x1, &y1, &x2, &y2);
	cairo_new_path (view->dom_view.cairo);

	extents->x1 = x1;
	extents->x2 = x2;
	extents->y1 = y1;
	extents->y2 = y2;
}

void
lsm_svg_view_show_line (LsmSvgView *view, double x1, double y1, double x2, double y2)
{
	LsmSvgViewPathInfos path_infos = default_path_infos;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	cairo_move_to (view->dom_view.cairo, x1, y1);
	cairo_line_to (view->dom_view.cairo, x2, y2);

	process_path (view, &path_infos);
}

static void
_show_points (LsmSvgView *view, const char *points, gboolean close_path)
{
	LsmSvgViewPathInfos path_infos = default_path_infos;
	char *str;
	double values[2];
	unsigned int n_values;
	unsigned int count = 0;

	if (points == NULL)
		return;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	str = (char *) points;

	do {
		n_values = lsm_str_parse_double_list (&str, 2, values);
		if (n_values == 2) {
			if (count == 0)
				cairo_move_to (view->dom_view.cairo, values[0], values[1]);
			else
				cairo_line_to (view->dom_view.cairo, values[0], values[1]);
		} else if (n_values != 0) {
			cairo_new_path (view->dom_view.cairo);
			return;
		}
		count++;
	} while (n_values == 2);

	if (close_path)
		cairo_close_path (view->dom_view.cairo);

	process_path (view, &path_infos);
}

void
lsm_svg_view_show_polyline (LsmSvgView *view, const char *points)
{
	_show_points (view, points, FALSE);
}

void
lsm_svg_view_show_polygon (LsmSvgView *view, const char *points)
{
	_show_points (view, points, TRUE);
}

static void
_update_pango_layout (LsmSvgView *view, char const *string, double x, double y, LsmSvgViewPathInfos *path_infos)
{
	const LsmSvgStyle *style;
	PangoLayout *pango_layout;
	PangoFontDescription *font_description;
	PangoStretch font_stretch;
	PangoStyle font_style;
	PangoLayoutIter *iter;
	PangoRectangle rectangle;
	int baseline;
	double x1, y1;

	style = view->style;

	pango_layout = view->pango_layout;
	font_description = view->dom_view.font_description;

	pango_font_description_set_family (font_description, style->font_family->value);
	pango_font_description_set_size (font_description, PANGO_SCALE * style->font_size_px);
	pango_font_description_set_weight (font_description, style->font_weight->value);

	switch (style->font_stretch->value) {
		case LSM_SVG_FONT_STRETCH_ULTRA_CONDENSED:
			font_stretch = PANGO_STRETCH_ULTRA_CONDENSED;
			break;
		case LSM_SVG_FONT_STRETCH_EXTRA_CONDENSED:
			font_stretch = PANGO_STRETCH_EXTRA_CONDENSED;
			break;
		case LSM_SVG_FONT_STRETCH_CONDENSED:
			font_stretch = PANGO_STRETCH_CONDENSED;
			break;
		case LSM_SVG_FONT_STRETCH_SEMI_CONDENSED:
			font_stretch = PANGO_STRETCH_SEMI_CONDENSED;
			break;
		case LSM_SVG_FONT_STRETCH_SEMI_EXPANDED:
			font_stretch = PANGO_STRETCH_SEMI_EXPANDED;
			break;
		case LSM_SVG_FONT_STRETCH_EXPANDED:
			font_stretch = PANGO_STRETCH_EXPANDED;
			break;
		case LSM_SVG_FONT_STRETCH_EXTRA_EXPANDED:
			font_stretch = PANGO_STRETCH_EXTRA_EXPANDED;
			break;
		case LSM_SVG_FONT_STRETCH_ULTRA_EXPANDED:
			font_stretch = PANGO_STRETCH_ULTRA_EXPANDED;
			break;
		case LSM_SVG_FONT_STRETCH_NORMAL:
		default:
			font_stretch = PANGO_STRETCH_NORMAL;
			break;
	}
	pango_font_description_set_stretch (font_description, font_stretch);

	switch (style->font_style->value) {
		case LSM_SVG_FONT_STYLE_OBLIQUE:
			font_style = PANGO_STYLE_OBLIQUE;
			break;
		case LSM_SVG_FONT_STYLE_ITALIC:
			font_style = PANGO_STYLE_ITALIC;
			break;
		case LSM_SVG_FONT_STYLE_NORMAL:
		default:
			font_style = PANGO_STYLE_NORMAL;
			break;
	}
	pango_font_description_set_style (font_description, font_style);

	pango_layout_set_text (pango_layout, string, -1);
	pango_layout_set_font_description (pango_layout, font_description);
	pango_layout_get_extents (pango_layout, &rectangle, NULL);

	iter = pango_layout_get_iter (pango_layout);
	baseline = pango_layout_iter_get_baseline (iter);
	pango_layout_iter_free (iter);

	x1 = x - pango_units_to_double (rectangle.x);
	y1 = y - pango_units_to_double (baseline);

	switch (style->text_anchor->value) {
		case LSM_SVG_TEXT_ANCHOR_END:
			x1 -= pango_units_to_double (rectangle.width);
			break;
		case LSM_SVG_TEXT_ANCHOR_MIDDLE:
			x1 -= pango_units_to_double (rectangle.width) / 2.0;
			break;
		case LSM_SVG_TEXT_ANCHOR_START:
		default:
			break;
	}

	path_infos->is_text_path = TRUE;
	path_infos->is_extents_defined = TRUE;
	path_infos->extents.x1 = x1;
	path_infos->extents.y1 = y1;
	path_infos->extents.x2 = x1 + pango_units_to_double (rectangle.width);
	path_infos->extents.y2 = y1 + pango_units_to_double (rectangle.height);
	path_infos->pango_layout = pango_layout;
}

static gboolean
_lock_pango_layout (LsmSvgView *view)
{
	/* A text may be painted with a text based pattern. In this case,
	 * we take care to create a new pango layout if the current one is in use. */
	if (view->is_pango_layout_in_use) {
		PangoContext *pango_context;

		pango_context = pango_layout_get_context (view->pango_layout);
		view->pango_layout_stack = g_slist_prepend (view->pango_layout_stack, view->pango_layout);
		view->pango_layout = pango_layout_new (pango_context);

		lsm_debug_render ("[LsmSvgView::show_text] Create a new pango layout");

		return TRUE;
	}

	view->is_pango_layout_in_use = TRUE;

	return FALSE;
}

static void
_unlock_pango_layout (LsmSvgView *view, gboolean need_pop)
{

	if (need_pop) {
		lsm_debug_render ("[LsmSvgView::show_text] Free the child pango layout");

		if (view->pango_layout != NULL) {
			g_object_unref (view->pango_layout);

			view->pango_layout = view->pango_layout_stack->data;
			view->pango_layout_stack = g_slist_delete_link (view->pango_layout_stack,
									view->pango_layout_stack);
		} else
			g_warning ("[LsmSvgView::show_text] Pango layout stack empty");
	}

	view->is_pango_layout_in_use = FALSE;
}

void
lsm_svg_view_show_text (LsmSvgView *view, char const *string, double x, double y)
{
	LsmSvgViewPathInfos path_infos = default_path_infos;
	const LsmSvgStyle *style;
	gboolean need_pop;

	if (string == NULL || string[0] == '\0')
		return;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	style = view->style;

	lsm_debug_render ("[LsmSvgView::show_text] Show '%s' at %g,%g (%g px)", string, x, y, style->font_size_px);

	need_pop = _lock_pango_layout (view);

	_update_pango_layout (view, string, x, y, &path_infos);

	if (style->writing_mode->value == LSM_SVG_WRITING_MODE_TB ||
	    style->writing_mode->value == LSM_SVG_WRITING_MODE_TB_RL) {

		cairo_save (view->dom_view.cairo);
		cairo_rotate (view->dom_view.cairo, M_PI / 2.0);
		cairo_move_to (view->dom_view.cairo, path_infos.extents.x1, path_infos.extents.y1);

		process_path (view, &path_infos);

		cairo_restore (view->dom_view.cairo);
	} else {
		cairo_move_to (view->dom_view.cairo, path_infos.extents.x1, path_infos.extents.y1);
		process_path (view, &path_infos);
	}

	_unlock_pango_layout (view, need_pop);
}

void
lsm_svg_view_text_extents (LsmSvgView *view, char const *string, double x, double y, LsmExtents *extents)
{
	LsmSvgViewPathInfos path_infos = default_path_infos;
	gboolean need_pop;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (extents != NULL);

	if (string == NULL ||
	    string[0] == '\0') {
		extents->x1 = 0;
		extents->y1 = 0;
		extents->y1 = 0;
		extents->y2 = 0;
	}

	need_pop = _lock_pango_layout (view);

	_update_pango_layout (view, string, x, y, &path_infos);

	_unlock_pango_layout (view, need_pop);

	*extents = path_infos.extents;
}

void
lsm_svg_view_show_pixbuf (LsmSvgView *view, GdkPixbuf *pixbuf)
{
	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (GDK_IS_PIXBUF (pixbuf));

	lsm_cairo_set_source_pixbuf (view->dom_view.cairo, pixbuf, 0, 0);
	cairo_paint (view->dom_view.cairo);
}

void
lsm_svg_view_push_viewbox (LsmSvgView *view, const LsmBox *viewbox)
{
	LsmSvgViewbox *svg_viewbox;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	lsm_debug_render ("[LsmSvgView::push_viewbox] viewbox = %g, %g, %g, %g",
		   viewbox->x, viewbox->y, viewbox->width, viewbox->height);

	svg_viewbox = lsm_svg_viewbox_new (view->resolution_ppi, viewbox);

	view->viewbox_stack = g_slist_prepend (view->viewbox_stack, svg_viewbox);
}

void
lsm_svg_view_pop_viewbox (LsmSvgView *view)
{
	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (view->viewbox_stack != NULL);

	lsm_debug_render ("[LsmSvgView::pop_viewbox]");

	lsm_svg_viewbox_free (view->viewbox_stack->data);
	view->viewbox_stack = g_slist_delete_link (view->viewbox_stack, view->viewbox_stack);
}

static const LsmBox *
_compute_viewbox_scale (const LsmBox *viewport, const LsmBox *viewbox,
			const LsmSvgPreserveAspectRatio *aspect_ratio,
			double *x_offset, double *y_offset,
			double *x_scale, double *y_scale)
{
	if (viewbox != NULL) {
		double x, y;
		double x_ratio;
		double y_ratio;

		x_ratio = viewbox->width  > 0.0 ? viewport->width  / viewbox->width  : 0.0;
		y_ratio = viewbox->height > 0.0 ? viewport->height / viewbox->height : 0.0;

		if (aspect_ratio != NULL && aspect_ratio->align > LSM_SVG_ALIGN_NONE) {
			if (aspect_ratio->meet_or_slice == LSM_SVG_MEET_OR_SLICE_MEET) {
				*x_scale = MIN (x_ratio, y_ratio);
				*y_scale = *x_scale;
			} else {
				*x_scale = MAX (x_ratio, y_ratio);
				*y_scale = *x_scale;
			}

			x = -viewbox->x * *x_scale;
			y = -viewbox->y * *y_scale;

			switch (aspect_ratio->align) {
				case LSM_SVG_ALIGN_X_MIN_Y_MIN:
					break;
				case LSM_SVG_ALIGN_X_MIN_Y_MID:
					y += (viewport->height- viewbox->height * *y_scale) * 0.5;
					break;
				case LSM_SVG_ALIGN_X_MIN_Y_MAX:
					y += (viewport->height - viewbox->height * *y_scale);
					break;
				case LSM_SVG_ALIGN_X_MID_Y_MIN:
					x += (viewport->width - viewbox->width * *x_scale) * 0.5;
					break;
				case LSM_SVG_ALIGN_X_MID_Y_MID:
					x += (viewport->width - viewbox->width * *x_scale) * 0.5;
					y += (viewport->height- viewbox->height * *y_scale) * 0.5;
					break;
				case LSM_SVG_ALIGN_X_MID_Y_MAX:
					x += (viewport->width - viewbox->width * *x_scale) * 0.5;
					y += (viewport->height - viewbox->height * *y_scale);
					break;
				case LSM_SVG_ALIGN_X_MAX_Y_MIN:
					x += (viewport->width - viewbox->width * *x_scale);
					break;
				case LSM_SVG_ALIGN_X_MAX_Y_MID:
					x += (viewport->width - viewbox->width * *x_scale);
					y += (viewport->height- viewbox->height * *y_scale) * 0.5;
					break;
				case LSM_SVG_ALIGN_X_MAX_Y_MAX:
					x += (viewport->width - viewbox->width * *x_scale);
					y += (viewport->height - viewbox->height * *y_scale);
					break;
				default:
					break;
			}

			*x_offset = x;
			*y_offset = y;

		} else {
			*x_scale = x_ratio;
			*y_scale = y_ratio;

			*x_offset = -viewbox->x * *x_scale;
			*y_offset = -viewbox->y * *y_scale;
		}

		lsm_debug_render ("[LsmSvgView::_compute_viewbox_scale] scale = %g, %g", *x_scale, *y_scale);

		return viewbox;
	}

	*x_scale = *y_scale = 1.0;
	*x_offset = 0.0;
	*y_offset = 0.0;

	return viewport;
}

void
lsm_svg_view_push_viewport (LsmSvgView *view, const LsmBox *viewport, const LsmBox *viewbox,
			    const LsmSvgPreserveAspectRatio *aspect_ratio,
			    LsmSvgOverflow overflow)
{
	cairo_t *cairo;
	const LsmBox *actual_viewbox;
	double x_offset, y_offset;
	double x_scale, y_scale;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (viewport != NULL);

	actual_viewbox = _compute_viewbox_scale (viewport, viewbox, aspect_ratio,
						 &x_offset, &y_offset, &x_scale, &y_scale);
	lsm_svg_view_push_viewbox (view, actual_viewbox);

	cairo = view->dom_view.cairo;

	cairo_save (cairo);

	if (lsm_debug_check (&lsm_debug_category_viewport, LSM_DEBUG_LEVEL_LOG)) {
		cairo_save (cairo);
		cairo_set_line_width (cairo, 1.0);
		cairo_set_source_rgb (cairo, 0.0, 0.0, 0.0);
		cairo_rectangle (cairo, viewport->x, viewport->y, viewport->width, viewport->height);
		cairo_stroke (cairo);
		cairo_restore (cairo);
	}

	if (overflow == LSM_SVG_OVERFLOW_HIDDEN) {
		cairo_rectangle (cairo, viewport->x, viewport->y, viewport->width, viewport->height);
		cairo_clip (cairo);
	}

	cairo_translate (cairo, viewport->x + x_offset, viewport->y + y_offset);
	cairo_scale (cairo, x_scale, y_scale);
}

void
lsm_svg_view_pop_viewport (LsmSvgView *view)
{
	cairo_restore (view->dom_view.cairo);

	lsm_svg_view_pop_viewbox (view);
}

void
lsm_svg_view_viewbox_to_viewport (LsmSvgView *view, const LsmBox *viewport, const LsmBox *viewbox,
				  const LsmSvgPreserveAspectRatio *aspect_ratio,
				  double *x, double *y)
{
	double x_offset, y_offset;
	double x_scale, y_scale;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (viewport != NULL);

	_compute_viewbox_scale (viewport, viewbox, aspect_ratio,
				&x_offset, &y_offset, &x_scale, &y_scale);

	if (x != NULL)
		*x = *x * x_scale + x_offset;

	if (y != NULL)
		*y = *y * y_scale + y_offset;
}

gboolean
lsm_svg_view_push_matrix (LsmSvgView *view, const LsmSvgMatrix *matrix)
{
	cairo_matrix_t cr_matrix;
	cairo_matrix_t cr_inv_matrix;
	cairo_matrix_t *ctm;
	cairo_status_t status;

	g_return_val_if_fail (LSM_IS_SVG_VIEW (view), FALSE);

	ctm = g_new (cairo_matrix_t, 1);
	cairo_get_matrix (view->dom_view.cairo, ctm);

	view->matrix_stack = g_slist_prepend (view->matrix_stack, ctm);

	lsm_debug_render ("[LsmSvgView::push_matrix] New transform %g, %g, %g, %g, %g, %g",
		   matrix->a, matrix->b, matrix->c, matrix->d, matrix->e, matrix->f);

	cairo_matrix_init (&cr_matrix, matrix->a, matrix->b, matrix->c, matrix->d, matrix->e, matrix->f);
	cr_inv_matrix = cr_matrix;
	status = cairo_matrix_invert (&cr_inv_matrix) == CAIRO_STATUS_SUCCESS;

	if (status == CAIRO_STATUS_SUCCESS) {
		lsm_debug_render ("[LsmSvgView::push_matrix] Not invertible matrix");
       		return FALSE;
	}

	cairo_transform (view->dom_view.cairo, &cr_matrix);

	{
		cairo_matrix_t current_ctm;
		cairo_get_matrix (view->dom_view.cairo, &current_ctm);

		lsm_debug_render ("[LsmSvgView::push_matrix] Current ctm %g, %g, %g, %g, %g, %g",
			   current_ctm.xx, current_ctm.xy, current_ctm.yx, current_ctm.yy,
			   current_ctm.x0, current_ctm.y0);
	}

	return TRUE;
}

void
lsm_svg_view_pop_matrix (LsmSvgView *view)
{
	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	if (view->matrix_stack != NULL) {
		cairo_matrix_t *ctm;

		ctm = view->matrix_stack->data;

		cairo_set_matrix (view->dom_view.cairo, ctm);

		lsm_debug_render ("[LsmSvgView::pop_matrix] Restore ctm %g, %g, %g, %g, %g, %g",
			   ctm->xx, ctm->xy, ctm->yx, ctm->yy,
			   ctm->x0, ctm->y0);

		g_free (ctm);
		view->matrix_stack = g_slist_delete_link (view->matrix_stack, view->matrix_stack);
	}
}

static void
lsm_svg_view_push_clip (LsmSvgView *view)
{
	LsmSvgElement *element;
	LsmExtents extents;
	char *url;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (!view->is_clipping);

	lsm_svg_element_get_extents (view->element_stack->data, view, &extents);

	url = view->style->clip_path->value;

	lsm_debug_render ("[LsmSvgView::push_clip] Using '%s'", url);

	cairo_save (view->dom_view.cairo);

	view->clip_extents.x = extents.x1;
	view->clip_extents.y = extents.y1;
	view->clip_extents.width  = extents.x2 - extents.x1;
	view->clip_extents.height = extents.y2 - extents.y1;

	lsm_debug_render ("[LsmSvgView::push_clip] x=%g y=%g w=%g h=%g",
			  view->clip_extents.x,
			  view->clip_extents.y,
			  view->clip_extents.width,
			  view->clip_extents.height);

	element = lsm_svg_document_get_element_by_url (LSM_SVG_DOCUMENT (view->dom_view.document), url);
	if (LSM_IS_SVG_CLIP_PATH_ELEMENT (element) &&
	    !lsm_svg_view_circular_reference_check (view, element)) {
		view->is_clipping = TRUE;
		lsm_svg_element_force_render (LSM_SVG_ELEMENT (element), view);
		cairo_clip (view->dom_view.cairo);
		view->is_clipping = FALSE;
	} else
		lsm_warning_render ("[LsmSvgView::push_clip] Clip path not found: %s", view->style->clip_path->value);
}

static void
lsm_svg_view_pop_clip (LsmSvgView *view)
{
	lsm_debug_render ("[LsmSvgView::pop_clip");

	cairo_restore (view->dom_view.cairo);
}

static void
lsm_svg_view_push_mask (LsmSvgView *view)
{
	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	cairo_push_group (view->dom_view.cairo);
}

static void
lsm_svg_view_pop_mask (LsmSvgView *view)
{
	LsmSvgElement *mask_element;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	mask_element = lsm_svg_document_get_element_by_url (LSM_SVG_DOCUMENT (view->dom_view.document),
							    view->style->mask->value);

	if (LSM_IS_SVG_MASK_ELEMENT (mask_element) &&
	    !lsm_svg_view_circular_reference_check (view, mask_element)) {
		LsmExtents extents;
		LsmBox mask_extents;
		cairo_t *cairo;

		lsm_svg_element_get_extents (view->element_stack->data, view, &extents);

		mask_extents.x = extents.x1;
		mask_extents.y = extents.y1;
		mask_extents.width = extents.x2 - extents.x1;
		mask_extents.height = extents.y2 - extents.y1;

		cairo = view->dom_view.cairo;

		_start_pattern (view, &mask_extents, &mask_extents, 1.0);

		lsm_svg_element_force_render (LSM_SVG_ELEMENT (mask_element), view);

		cairo_pop_group_to_source (cairo);
		if (view->pattern_data->pattern != NULL) {
			cairo_surface_t *surface;
			int width, height, row, i, stride;
			unsigned char *pixels;

			cairo_pattern_get_surface (view->pattern_data->pattern, &surface);
			pixels = cairo_image_surface_get_data (surface);
			height = cairo_image_surface_get_height (surface);
			width = cairo_image_surface_get_width (surface);
			stride = cairo_image_surface_get_stride (surface);

			for (row = 0; row < height; row++) {
				guint8 *row_data = (pixels + (row * stride));
				for (i = 0; i < width; i++) {
					guint32 *pixel = (guint32 *) row_data + i;
					*pixel = ((((*pixel & 0x00ff0000) >> 16) * 13817 +
						   ((*pixel & 0x0000ff00) >> 8) * 46518 +
						   ((*pixel & 0x000000ff)) * 4688) * 0xff
						  /* * opacity */);
				}
			}

			cairo_pattern_set_extend (view->pattern_data->pattern, CAIRO_EXTEND_NONE);

			if (view->debug_mask && view->dom_view.cairo != NULL) {
				char *filename;

				filename = g_strdup_printf ("mask-%s.png", view->style->mask->value);
				cairo_surface_write_to_png (cairo_get_target (view->dom_view.cairo), filename);
				g_free (filename);
			}

			cairo_mask (cairo, view->pattern_data->pattern);
		} else {
			cairo_paint (cairo);
		}

		_end_pattern (view);
	} else {
		lsm_warning_render ("[LsmSvgView::pop_mask] Mask url nout found: %s", view->style->mask->value);

		cairo_pop_group_to_source (view->dom_view.cairo);
		cairo_paint (view->dom_view.cairo);
	}
}

void
lsm_svg_view_push_filter (LsmSvgView *view)
{
	LsmExtents extents;
	LsmBox object_extents;
	LsmBox effect_viewport;
	LsmSvgElement *filter_element;
	gboolean success;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (view->element_stack != NULL);

	lsm_svg_element_get_extents (view->element_stack->data, view, &extents);

	object_extents.x = extents.x1;
	object_extents.y = extents.y1;
	object_extents.width = extents.x2 - extents.x1;
	object_extents.height = extents.y2 - extents.y1;

	filter_element = lsm_svg_document_get_element_by_url (LSM_SVG_DOCUMENT (view->dom_view.document),
							      view->style->filter->value);

	if (LSM_IS_SVG_FILTER_ELEMENT (filter_element)) {
		effect_viewport = lsm_svg_filter_element_get_effect_viewport (LSM_SVG_FILTER_ELEMENT (filter_element),
									      &object_extents, view);

		_start_pattern (view, &effect_viewport, &object_extents,
				view->style->opacity != NULL ? view->style->opacity->value : 1.0);

		success = lsm_svg_view_create_surface_pattern (view,
							      &effect_viewport,
							      NULL,
							      LSM_SVG_VIEW_SURFACE_TYPE_IMAGE);
	} else {
		lsm_warning_render ("LsmSvgView::push_filter] Filter not found: %s", view->style->filter->value);

		_start_pattern (view, &object_extents, &object_extents, 0.0);

		success = lsm_svg_view_create_surface_pattern (view,
							       &object_extents,
							       NULL,
							       LSM_SVG_VIEW_SURFACE_TYPE_IMAGE);
	}

	if (!success)
		lsm_warning_render ("LsmSvgView::push_filter] Failed to create subsurface");
}

void
lsm_svg_view_pop_filter (LsmSvgView *view)
{
	LsmSvgElement *filter_element;
	LsmSvgFilterSurface *filter_surface;
	cairo_surface_t *surface;
	GSList *iter;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	filter_element = lsm_svg_document_get_element_by_url (LSM_SVG_DOCUMENT (view->dom_view.document),
							      view->style->filter->value);

	if (LSM_IS_SVG_FILTER_ELEMENT (filter_element) &&
	    view->pattern_data->pattern != NULL) {
		cairo_matrix_t matrix;
		LsmBox subregion;

		view->filter_surfaces = NULL;

		cairo_pattern_get_surface (view->pattern_data->pattern, &surface);

		subregion.x = 0;
		subregion.y = 0;
		subregion.width = cairo_image_surface_get_width (surface);
		subregion.height = cairo_image_surface_get_height (surface);

		filter_surface = lsm_svg_filter_surface_new_with_content ("SourceGraphic", surface, &subregion);
		cairo_pattern_get_matrix (view->pattern_data->pattern, &matrix);

		view->filter_surfaces = g_slist_prepend (view->filter_surfaces, filter_surface);

		lsm_svg_element_force_render (filter_element, view);

		if (view->debug_filter) {
			GSList *iter;
			char *filename;
			static int count = 0;

			for (iter = view->filter_surfaces; iter != NULL; iter = iter->next) {
				LsmSvgFilterSurface *surface = iter->data;

				filename = g_strdup_printf ("filter-%04d-%s-%s.png", count++,
							    view->style->filter->value,
							    lsm_svg_filter_surface_get_name (surface));
				cairo_surface_write_to_png (lsm_svg_filter_surface_get_cairo_surface (surface), filename);
				g_free (filename);
			}
		}

		if (view->filter_surfaces->next != NULL) {
			cairo_pattern_t *pattern;
			cairo_surface_t *surface;

			surface = lsm_svg_filter_surface_get_cairo_surface (view->filter_surfaces->data);
			pattern = cairo_pattern_create_for_surface (surface);
			cairo_pattern_set_extend (pattern, CAIRO_EXTEND_NONE);
			cairo_pattern_set_matrix (pattern, &matrix);
			cairo_set_source (view->pattern_data->old_cairo, pattern);
			cairo_pattern_destroy (pattern);
			cairo_paint_with_alpha (view->pattern_data->old_cairo, view->style->opacity->value);
		}

		for (iter = view->filter_surfaces; iter != NULL; iter = iter->next)
			lsm_svg_filter_surface_unref (iter->data);
		g_slist_free (view->filter_surfaces);
		view->filter_surfaces = NULL;
	}

	_end_pattern (view);
}

static LsmSvgFilterSurface *
_get_filter_surface (LsmSvgView *view, const char *input)
{
	GSList *iter;
	LsmSvgFilterSurface *source_surface = NULL;

	if (input == NULL)
		return view->filter_surfaces->data;

	for (iter = view->filter_surfaces; iter != NULL; iter = iter->next) {
		LsmSvgFilterSurface *surface = iter->data;

		if (g_strcmp0 (input, lsm_svg_filter_surface_get_name (surface)) == 0)
			return surface;

		source_surface = surface;
	}

	if (g_strcmp0 (input, "SourceAlpha") == 0 && source_surface != NULL) {
		LsmSvgFilterSurface *surface;

		surface = lsm_svg_filter_surface_new_similar ("SourceAlpha", source_surface, NULL);
		lsm_svg_filter_surface_alpha (source_surface, surface);
		view->filter_surfaces = g_slist_prepend (view->filter_surfaces, surface);

		return surface;
	} else if (g_strcmp0 (input, "BackgroundImage") == 0) {
		LsmSvgFilterSurface *surface;
		LsmSvgViewBackground *background;
		gboolean background_processing = FALSE;
		cairo_matrix_t matrix;
		cairo_matrix_t pattern_matrix;
		cairo_t *cairo;
		GList *iter;

		for (iter = view->background_stack; iter != NULL; iter = iter->next) {
			background = iter->data;

			if (background->enable_background) {
				background_processing = TRUE;
				break;
			}
		}

		if (!background_processing) {
			lsm_debug_render ("[LsmSvgView::_get_filter_surface] Background processing not enabled");
			return NULL;
		}

		surface = lsm_svg_filter_surface_new_similar ("BackgroundImage", source_surface, NULL);
		view->filter_surfaces = g_slist_prepend (view->filter_surfaces, surface);

		cairo_get_matrix (view->pattern_data->old_cairo, &matrix);
		cairo_pattern_get_matrix (view->pattern_data->pattern, &pattern_matrix);

		cairo_matrix_invert (&matrix);
		cairo_matrix_multiply (&matrix, &matrix, &pattern_matrix);

		lsm_debug_render ("[LsmSvgView::_get_filter_surface] Background image matrix %g, %g, %g, %g, %g, %g",
				  matrix.xx, matrix.xy, matrix.yx, matrix.yy,
				  matrix.x0, matrix.y0);

		cairo = cairo_create (lsm_svg_filter_surface_get_cairo_surface (surface));
		cairo_set_matrix (cairo, &matrix);

		for (; iter != NULL; iter = iter->prev) {
			background = iter->data;

			cairo_set_source_surface (cairo, background->surface, 0, 0);
			cairo_paint_with_alpha (cairo, background->group_opacity);
		}

		cairo_destroy (cairo);

		return surface;
	} else if (g_strcmp0 (input, "BackgroundAlpha") == 0) {
		LsmSvgFilterSurface *surface;
		LsmSvgFilterSurface *background_surface;

		if (view->background_stack == NULL)
			return NULL;

		background_surface = _get_filter_surface (view, "BackgroundImage");

		surface = lsm_svg_filter_surface_new_similar ("BackgroundAlpha", background_surface, NULL);
		lsm_svg_filter_surface_alpha (background_surface, surface);
		view->filter_surfaces = g_slist_prepend (view->filter_surfaces, surface);

		return surface;
	}

	return NULL;
}

static LsmSvgFilterSurface *
_create_filter_surface (LsmSvgView *view, const char *output, LsmSvgFilterSurface *input_surface, const LsmBox *subregion)
{
	LsmSvgFilterSurface *surface;

	surface = lsm_svg_filter_surface_new_similar (output, input_surface, subregion);

	view->filter_surfaces = g_slist_prepend (view->filter_surfaces, surface);

	return surface;
}

LsmBox
lsm_svg_view_get_filter_surface_extents (LsmSvgView *view, const char *name)
{
	static LsmBox null_extents = {.x = 0.0, .y = 0.0, .width = 0.0, .height = 0.0};
	LsmSvgFilterSurface *surface;
	LsmBox extents;

	g_return_val_if_fail (LSM_IS_SVG_VIEW (view), null_extents);

	surface = _get_filter_surface (view, name);
	if (surface == NULL)
		return null_extents;

	lsm_cairo_box_device_to_user (view->dom_view.cairo, &extents, lsm_svg_filter_surface_get_subregion (surface));

	return extents;
}

void
lsm_svg_view_apply_blend (LsmSvgView *view, const char *input_1, const char*input_2, const char *output,
			  const LsmBox *subregion, LsmSvgBlendingMode mode)
{
	LsmSvgFilterSurface *output_surface;
	LsmSvgFilterSurface *input_1_surface;
	LsmSvgFilterSurface *input_2_surface;
	LsmBox subregion_px;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	input_1_surface = _get_filter_surface (view, input_1);
	input_2_surface = _get_filter_surface (view, input_2);

	if (input_1_surface == NULL || input_2_surface == NULL) {
		lsm_warning_render ("[SvgView::apply_blend] Inputs '%s' or '%s' not found", input_1, input_2);
		return;
	}

	lsm_cairo_box_user_to_device (view->dom_view.cairo, &subregion_px, subregion);
	output_surface = _create_filter_surface (view, output, input_1_surface, &subregion_px);

	lsm_log_render ("[SvgView::blend] mode = %s", lsm_svg_blending_mode_to_string (mode));

	lsm_svg_filter_surface_blend (input_1_surface, input_2_surface, output_surface, mode);
}

void
lsm_svg_view_apply_flood (LsmSvgView *view, const char *output, const LsmBox *subregion)
{
	LsmSvgFilterSurface *output_surface;
	LsmSvgFilterSurface *input_surface;
	LsmBox subregion_px;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	input_surface = _get_filter_surface (view, NULL);

	lsm_cairo_box_user_to_device (view->dom_view.cairo, &subregion_px, subregion);
	output_surface = _create_filter_surface (view, output, input_surface, &subregion_px);

	lsm_log_render ("[SvgView::apply_flood] subregion %gx%g px at %g,%g px",
		        subregion_px.width, subregion_px.height,
		        subregion_px.x, subregion_px.y);

	lsm_svg_filter_surface_flood (output_surface,
				  view->style->flood_color->value.red,
				  view->style->flood_color->value.green,
				  view->style->flood_color->value.blue,
				  view->style->flood_opacity->value);
}

void
lsm_svg_view_apply_gaussian_blur (LsmSvgView *view, const char *input, const char *output,
				  const LsmBox *subregion, double std_x, double std_y)
{
	LsmSvgFilterSurface *input_surface;
	LsmSvgFilterSurface *output_surface;
	LsmBox subregion_px;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	input_surface = _get_filter_surface (view, input);

	if (input_surface == NULL) {
		lsm_debug_render ("[SvgView::apply_gaussian_blur] Input '%s' not found", input);
		return;
	}

	lsm_cairo_box_user_to_device (view->dom_view.cairo, &subregion_px, subregion);
	output_surface = _create_filter_surface (view, output, input_surface, &subregion_px);

	lsm_log_render ("[SvgView::apply_gaussian_blur] %s -> %s (%g,%g)",
			input != NULL ? input : "previous",
			output != NULL ? output : "next",
			std_x, std_y);

	cairo_user_to_device_distance (view->dom_view.cairo, &std_x, &std_y);

	lsm_log_render ("[SvgView::apply_gaussian_blur] %g px,%g px",
			std_x, std_y);

	lsm_svg_filter_surface_fast_blur (input_surface, output_surface, std_x, std_y);
}

void
lsm_svg_view_apply_offset (LsmSvgView *view, const char *input, const char *output,
			   const LsmBox *subregion, double dx, double dy)
{
	LsmSvgFilterSurface *input_surface;
	LsmSvgFilterSurface *output_surface;
	LsmBox subregion_px;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	input_surface = _get_filter_surface (view, input);

	if (input_surface == NULL) {
		lsm_debug_render ("[SvgView::apply_offset] Input '%s' not found", input);
		return;
	}

	lsm_cairo_box_user_to_device (view->dom_view.cairo, &subregion_px, subregion);
	output_surface = _create_filter_surface (view, output, input_surface, &subregion_px);

	lsm_log_render ("[SvgView::apply_offset] %s -> %s (dx:%g,dy:%g)", input, output, dx, dy);

	cairo_user_to_device_distance (view->dom_view.cairo, &dx, &dy);

	lsm_log_render ("[SvgView::apply_offset] %g px,%g px", dx, dy);

	lsm_svg_filter_surface_offset (input_surface, output_surface, dx, dy);
}

void
lsm_svg_view_apply_merge (LsmSvgView *view, const char *input, const char *output, const LsmBox *subregion)
{
	LsmSvgFilterSurface *input_surface;
	LsmSvgFilterSurface *output_surface;
	LsmBox subregion_px;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));

	input_surface = _get_filter_surface (view, input);

	if (input_surface == NULL) {
		lsm_debug_render ("[SvgView::apply_offset] Input '%s' not found", input);
		return;
	}

	output_surface = _get_filter_surface (view, output);
	lsm_cairo_box_user_to_device (view->dom_view.cairo, &subregion_px, subregion);
	if (output_surface == NULL)
		output_surface = _create_filter_surface (view, output, input_surface, &subregion_px);

	if (output_surface != NULL)
		lsm_svg_filter_surface_merge (input_surface, output_surface);
}

void
lsm_svg_view_apply_tile (LsmSvgView *view, const char *input, const char *output, const LsmBox *subregion)
{
	LsmSvgFilterSurface *input_surface;
	LsmSvgFilterSurface *output_surface;
	LsmBox subregion_px;

	input_surface = _get_filter_surface (view, input);

	if (input_surface == NULL) {
		lsm_debug_render ("[SvgView::apply_offset] Input '%s' not found", input);
		return;
	}

	lsm_cairo_box_user_to_device (view->dom_view.cairo, &subregion_px, subregion);
	output_surface = _create_filter_surface (view, output, input_surface, &subregion_px);

	lsm_svg_filter_surface_tile (input_surface, output_surface);
}

void
lsm_svg_view_push_element (LsmSvgView *view, const LsmSvgElement *element)
{
	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (LSM_IS_SVG_ELEMENT (element));

	view->element_stack = g_slist_prepend (view->element_stack, (void *) element);
}

void
lsm_svg_view_pop_element (LsmSvgView *view)
{
	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (view->element_stack != NULL);

	view->element_stack = g_slist_delete_link (view->element_stack, view->element_stack);
}

static gboolean
lsm_svg_view_circular_reference_check (LsmSvgView *view, LsmSvgElement *element)
{
	GSList *iter;

	for (iter = view->element_stack; iter != NULL; iter = iter->next)
		if (iter->data == element) {
			lsm_debug_render ("[LsmSvgView::circular_reference_check] "
				   "Circular reference to %s (id = %s)",
				   lsm_dom_element_get_tag_name (LSM_DOM_ELEMENT (element)),
				   lsm_dom_element_get_attribute (LSM_DOM_ELEMENT (element), "id"));
			return TRUE;
		}

	return FALSE;
}

void
lsm_svg_view_push_style (LsmSvgView *view, LsmSvgStyle *style)
{
	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (style != NULL);

	lsm_log_render ("[SvgView::push_style]");

	if (view->style == NULL || (style->font_size != view->style->font_size)) {
		LsmSvgViewbox font_viewbox;
		LsmSvgViewbox *viewbox;
		double current_font_size_px;

		if (view->style != NULL)
			current_font_size_px = view->style->font_size_px;
		else
			current_font_size_px = 0.0;

		viewbox = view->viewbox_stack->data;
		font_viewbox.resolution_ppi = viewbox->resolution_ppi;
		font_viewbox.viewbox.x = 0;
		font_viewbox.viewbox.y = 0;
		font_viewbox.viewbox.width = current_font_size_px;
		font_viewbox.viewbox.height = current_font_size_px;

		style->font_size_px = lsm_svg_length_normalize (&style->font_size->length, &font_viewbox,
								current_font_size_px, LSM_SVG_LENGTH_DIRECTION_VERTICAL);

		if (style->font_size_px < 0.0)
			style->font_size_px = 0.0;
		lsm_log_render ("[SvgView::push_style] Font size = %g pixels", style->font_size_px);
	} else
		style->font_size_px = view->style->font_size_px;

	view->style_stack = g_slist_prepend (view->style_stack, (void *) style);
	view->style = style;

}

void
lsm_svg_view_push_composition (LsmSvgView *view, LsmSvgStyle *style)
{
	gboolean do_filter;
	gboolean do_mask;
	gboolean do_clip;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (style != NULL);

	lsm_svg_view_push_style (view, style);

	lsm_log_render ("[SvgView::push_composition]");

	do_clip = (g_strcmp0 (style->clip_path->value, "none") != 0);
	do_mask = (g_strcmp0 (style->mask->value, "none") != 0);
	do_filter = (g_strcmp0 (style->filter->value, "none") != 0);

	if (G_UNLIKELY((view->style->opacity->value < 1.0 ||
			view->style->enable_background->value == LSM_SVG_ENABLE_BACKGROUND_NEW ||
			view->style->comp_op->value != LSM_SVG_COMP_OP_SRC_OVER) &&
		       !do_filter &&
		       !view->is_clipping &&
		       !view->style->ignore_group_opacity &&
		       view->dom_view.cairo != NULL)) {
		LsmSvgViewBackground *background;

		lsm_debug_render ("[LsmSvgView::push_composition] Push group");
		cairo_push_group (view->dom_view.cairo);

		background = g_slice_new (LsmSvgViewBackground);
		background->surface = cairo_get_group_target (view->dom_view.cairo);
		background->group_opacity = view->style->opacity->value;
		background->enable_background = view->style->enable_background->value == LSM_SVG_ENABLE_BACKGROUND_NEW;

		view->background_stack = g_list_prepend (view->background_stack, background);
	}

	if (G_UNLIKELY (do_clip)) {
		lsm_debug_render ("[LsmSvgView::push_style] Start clip '%s'", style->clip_path->value);
		lsm_svg_view_push_clip (view);
	}

	if (G_UNLIKELY (do_mask)) {
		lsm_debug_render ("[LsmSvgView::push_style] Start mask '%s'", style->mask->value);
		lsm_svg_view_push_mask (view);
	}

	/* Don't do filtering during a clipping operation, as filter will
	 * create a new subsurface, where clipping should occur with the path
	 * of the clip-path element. */
	if (G_UNLIKELY (do_filter && !view->is_clipping)) {
		lsm_debug_render ("[LsmSvgView::push_style] Start filter '%s'", style->filter->value);
		lsm_svg_view_push_filter (view);
	}
}

void lsm_svg_view_pop_style (LsmSvgView *view)
{
	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (view->style_stack != NULL);

	view->style_stack = g_slist_delete_link (view->style_stack, view->style_stack);
	view->style = view->style_stack != NULL ? view->style_stack->data : NULL;

	lsm_log_render ("[SvgView::pop_style]");
}

void lsm_svg_view_pop_composition (LsmSvgView *view)
{
	gboolean do_filter;
	gboolean do_mask;
	gboolean do_clip;
	cairo_t *cairo;

	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (view->style != NULL);

	lsm_log_render ("[SvgView::pop_composition]");

	do_clip = (g_strcmp0 (view->style->clip_path->value, "none") != 0);
	do_mask = (g_strcmp0 (view->style->mask->value, "none") != 0);
	do_filter = (g_strcmp0 (view->style->filter->value, "none") != 0);

	/* Don't do filtering during a clipping operation, as filter will
	 * create a new subsurface, where clipping should occur with the path
	 * of the clip-path element. */
	if (G_UNLIKELY (do_filter && !view->is_clipping))
		lsm_svg_view_pop_filter (view);

	if (G_UNLIKELY (do_mask))
		lsm_svg_view_pop_mask (view);

	if (G_UNLIKELY (do_clip))
		lsm_svg_view_pop_clip (view);

	cairo = view->dom_view.cairo;

	if (G_UNLIKELY ((view->style->opacity->value < 1.0 ||
			 view->style->enable_background->value == LSM_SVG_ENABLE_BACKGROUND_NEW ||
			 view->style->comp_op->value != LSM_SVG_COMP_OP_SRC_OVER) &&
			!do_filter &&
			!view->is_clipping &&
			!view->style->ignore_group_opacity &&
			cairo != NULL)) {
		g_slice_free (LsmSvgViewBackground, view->background_stack->data);
		view->background_stack = g_list_delete_link (view->background_stack, view->background_stack);

		cairo_pop_group_to_source (view->dom_view.cairo);
		if (G_UNLIKELY (view->style->comp_op->value != LSM_SVG_COMP_OP_SRC_OVER))
			lsm_cairo_set_comp_op (cairo, view->style->comp_op->value);
		cairo_paint_with_alpha (cairo, view->style->opacity->value);
		if (G_UNLIKELY (view->style->comp_op->value != LSM_SVG_COMP_OP_SRC_OVER))
			lsm_cairo_set_comp_op (cairo, LSM_SVG_COMP_OP_SRC_OVER);
		lsm_debug_render ("[LsmSvgView::pop_composition] Pop group");
	}

	lsm_svg_view_pop_style (view);
}

LsmSvgStyle *
lsm_svg_view_get_current_style (LsmSvgView *view)
{
	g_return_val_if_fail (LSM_IS_SVG_VIEW (view), NULL);

	return (LsmSvgStyle *) view->style;
}

const LsmBox *
lsm_svg_view_get_pattern_extents (LsmSvgView *view)
{
	static LsmBox null_extents = {.x = 0.0, .y = 0.0, .width = 0.0, .height = 0.0};

	g_return_val_if_fail (LSM_IS_SVG_VIEW (view), &null_extents);
	g_return_val_if_fail (view->pattern_data != NULL, &null_extents);

	return &view->pattern_data->extents;
}

const LsmBox *
lsm_svg_view_get_object_extents (LsmSvgView *view)
{
	static LsmBox null_extents = {.x = 0.0, .y = 0.0, .width = 0.0, .height = 0.0};

	g_return_val_if_fail (LSM_IS_SVG_VIEW (view), &null_extents);
	g_return_val_if_fail (view->pattern_data != NULL, &null_extents);

	return &view->pattern_data->object_extents;
}

const LsmBox *
lsm_svg_view_get_clip_extents (LsmSvgView *view)
{
	static LsmBox null_extents = {.x = 0.0, .y = 0.0, .width = 0.0, .height = 0.0};

	g_return_val_if_fail (LSM_IS_SVG_VIEW (view), &null_extents);
	g_return_val_if_fail (view->is_clipping, &null_extents);

	return &view->clip_extents;
}

static void
lsm_svg_view_measure (LsmDomView *view, double *width, double *height, double *baseline)
{
	LsmSvgSvgElement *svg_element;

	svg_element = lsm_svg_document_get_root_element (LSM_SVG_DOCUMENT (view->document));
	if (svg_element == NULL)
		return;

	lsm_svg_svg_element_measure (svg_element, LSM_SVG_VIEW (view), width, height);
	if (baseline)
		*baseline = *height;
}

static void
lsm_svg_view_render (LsmDomView *view)
{
	LsmSvgView *svg_view;
	LsmSvgSvgElement *svg_element;

	svg_view = LSM_SVG_VIEW (view);

	svg_element = lsm_svg_document_get_root_element (LSM_SVG_DOCUMENT (view->document));
	if (svg_element == NULL)
		return;

	svg_view->style_stack = NULL;
	svg_view->element_stack = NULL;
	svg_view->viewbox_stack = NULL;
	svg_view->matrix_stack = NULL;
	svg_view->pango_layout_stack = NULL;
	svg_view->background_stack = NULL;

	svg_view->is_clipping = FALSE;
	svg_view->is_pango_layout_in_use = FALSE;
	svg_view->pango_layout = view->pango_layout;

	svg_view->resolution_ppi = lsm_dom_view_get_resolution (view);

	lsm_svg_svg_element_render  (svg_element, svg_view);

	if (svg_view->is_pango_layout_in_use)
		g_warning ("[LsmSvgView::render] Unfinished text redenring");

	if (svg_view->is_clipping)
		g_warning ("[LsmSvgView::render] Unfinished clipping");

	if (svg_view->pango_layout_stack != NULL) {
		g_warning ("[LsmSvgView::render] Dangling pango_layout in stack");
		g_slist_free (svg_view->pango_layout_stack);
		svg_view->pango_layout_stack = NULL;
	}

	if (svg_view->matrix_stack != NULL) {
		g_warning ("[LsmSvgView::render] Dangling matrix in stack");
		g_slist_free (svg_view->matrix_stack);
		svg_view->matrix_stack = NULL;
	}
	if (svg_view->viewbox_stack != NULL) {
		g_warning ("[LsmSvgView::render] Dangling viewport in stack");
		g_slist_free (svg_view->viewbox_stack);
		svg_view->viewbox_stack = NULL;
	}
	if (svg_view->element_stack != NULL) {
		g_warning ("[LsmSvgView::render] Dangling element in stack");
		g_slist_free (svg_view->element_stack);
		svg_view->element_stack = NULL;
	}
	if (svg_view->style_stack != NULL) {
		g_warning ("[LsmSvgView::render] Dangling style in stack");
		g_slist_free (svg_view->style_stack);
		svg_view->style_stack = NULL;
	}
	if (svg_view->background_stack != NULL) {
		g_warning ("[LsmSvgView::render] Dangling background in stack");
		g_list_free (svg_view->background_stack);
		svg_view->background_stack = NULL;
	}
}

static void
lsm_svg_view_set_debug (LsmDomView *view, const char *feature, gboolean enable)
{
	LsmSvgView *svg_view = LSM_SVG_VIEW (view);

	if (g_strcmp0 (feature, "filter") == 0)
		svg_view->debug_filter = enable;
	else if (g_strcmp0 (feature, "mask") == 0)
		svg_view->debug_mask = enable;
	else if (g_strcmp0 (feature, "pattern") == 0)
		svg_view->debug_pattern = enable;
}

LsmSvgView *
lsm_svg_view_new (LsmSvgDocument *document)
{
	LsmSvgView *view;

	view = g_object_new (LSM_TYPE_SVG_VIEW, NULL);

	lsm_dom_view_set_document (LSM_DOM_VIEW (view), LSM_DOM_DOCUMENT (document));

	return view;
}

static void
lsm_svg_view_init (LsmSvgView *view)
{
	view->debug_mask = FALSE;
	view->debug_filter = FALSE;
	view->debug_pattern = FALSE;
}

static void
lsm_svg_view_finalize (GObject *object)
{
	parent_class->finalize (object);
}

static void
lsm_svg_view_class_init (LsmSvgViewClass *view_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (view_class);
	LsmDomViewClass *d_view_class = LSM_DOM_VIEW_CLASS (view_class);

	parent_class = g_type_class_peek_parent (view_class);

	object_class->finalize = lsm_svg_view_finalize;

	d_view_class->measure = lsm_svg_view_measure;
	d_view_class->render = lsm_svg_view_render;
	d_view_class->set_debug = lsm_svg_view_set_debug;
}

G_DEFINE_TYPE (LsmSvgView, lsm_svg_view, LSM_TYPE_DOM_VIEW)
