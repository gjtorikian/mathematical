/* Lasem
 *
 * Copyright © 2007-2012 Emmanuel Pacaud
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
#include <lsmmathmlview.h>
#include <lsmmathmldocument.h>
#include <lsmmathmlelement.h>
#include <lsmmathmlmathelement.h>
#include <lsmmathmlstyleelement.h>
#include <lsmmathmlglyphtableams.h>
#include <glib/gprintf.h>

#include <math.h>
#include <string.h>

#define LSM_MATHML_LARGE_OP_SCALE	1.6

static const char *lsm_mathml_font_names[] = {
	"",
	"Sans",
	"cmr10",
	"cmmi10",
	"cmex10",
	"cmsy10",
	"symbol"
};

static const struct {
	const char *font;
	PangoStyle style;
	PangoWeight weight;
} lsm_mathml_pango_options[LSM_MATHML_VARIANT_MONOSPACE + 1] = {
	{NULL,				PANGO_STYLE_NORMAL, 	PANGO_WEIGHT_NORMAL},
	{NULL,  			PANGO_STYLE_NORMAL, 	PANGO_WEIGHT_BOLD},
	{NULL,				PANGO_STYLE_ITALIC, 	PANGO_WEIGHT_NORMAL},
	{NULL,				PANGO_STYLE_ITALIC,	PANGO_WEIGHT_BOLD},
	{LSM_MATHML_FONT_DOUBLE_STRUCK,	PANGO_STYLE_NORMAL,	PANGO_WEIGHT_NORMAL},
	{NULL,				PANGO_STYLE_NORMAL,	PANGO_WEIGHT_NORMAL},
	{LSM_MATHML_FONT_SCRIPT,	PANGO_STYLE_NORMAL,	PANGO_WEIGHT_NORMAL},
	{LSM_MATHML_FONT_SCRIPT,	PANGO_STYLE_NORMAL,	PANGO_WEIGHT_BOLD},
	{NULL,				PANGO_STYLE_NORMAL,	PANGO_WEIGHT_NORMAL},
	{LSM_MATHML_FONT_SANS,		PANGO_STYLE_NORMAL,	PANGO_WEIGHT_NORMAL},
	{LSM_MATHML_FONT_SANS,		PANGO_STYLE_NORMAL,	PANGO_WEIGHT_BOLD},
	{LSM_MATHML_FONT_SANS,		PANGO_STYLE_ITALIC,	PANGO_WEIGHT_NORMAL},
	{LSM_MATHML_FONT_SANS,		PANGO_STYLE_ITALIC,	PANGO_WEIGHT_BOLD},
	{LSM_MATHML_FONT_MONOSPACE,	PANGO_STYLE_NORMAL,	PANGO_WEIGHT_NORMAL}
};

static GObjectClass *parent_class;

static void
lsm_mathml_view_apply_style_to_font_description (PangoFontDescription *font_description,
						 const LsmMathmlElementStyle *style,
						 gboolean set_family)
{
	g_return_if_fail (font_description != NULL);
	g_return_if_fail (style != NULL);

	if (style->math_variant < G_N_ELEMENTS (lsm_mathml_pango_options)) {
		if (set_family) {
			if (lsm_mathml_pango_options[style->math_variant].font == NULL)
				pango_font_description_set_family (font_description, style->math_family);
			else
				pango_font_description_set_family (font_description,
								   lsm_mathml_pango_options[style->math_variant].font);
		}
		pango_font_description_set_style (font_description,
						  lsm_mathml_pango_options[style->math_variant].style);
		pango_font_description_set_weight (font_description,
						   lsm_mathml_pango_options[style->math_variant].weight);
		return;
	}

	if (set_family)
		pango_font_description_set_family (font_description, style->math_family);
	pango_font_description_set_style (font_description, PANGO_STYLE_NORMAL);
	pango_font_description_set_weight (font_description, PANGO_WEIGHT_NORMAL);
}

static void
lsm_mathml_view_update_layout_for_text (LsmMathmlView *view,
					const LsmMathmlElementStyle *style,
					const char *text,
					PangoLayout *pango_layout,
					PangoRectangle *ink_rect,
					PangoRectangle *rect,
					int *baseline)
{
	PangoFontDescription *font_description;

	font_description = view->dom_view.font_description;

	pango_font_description_set_size (font_description, style->math_size * PANGO_SCALE);

	/* Kludge for a nicer latex like rendering */
	if (strcmp (style->math_family, "cmr10") == 0 &&
	    (style->math_variant == LSM_MATHML_VARIANT_ITALIC ||
	     style->math_variant == LSM_MATHML_VARIANT_BOLD_ITALIC)) {
		pango_font_description_set_family (font_description, "cmmi10");
		pango_font_description_set_style (font_description, PANGO_STYLE_NORMAL);
		if (style->math_variant == LSM_MATHML_VARIANT_BOLD_ITALIC)
			pango_font_description_set_weight (font_description, PANGO_WEIGHT_BOLD);
		else
			pango_font_description_set_weight (font_description, PANGO_WEIGHT_NORMAL);
	} else {
		lsm_mathml_view_apply_style_to_font_description (font_description, style, TRUE);
	}
	pango_layout_set_text (pango_layout, text, -1);
	pango_layout_set_font_description (pango_layout, font_description);
	pango_layout_get_extents (pango_layout, ink_rect, rect);

	if (baseline != NULL) {
		PangoLayoutIter *iter;

		iter = pango_layout_get_iter (pango_layout);
		*baseline = pango_layout_iter_get_baseline (iter);
		pango_layout_iter_free (iter);
	}
}

static void
lsm_mathml_view_show_layout (LsmMathmlView *view,
			  double x, double y,
			  int baseline,
			  const PangoRectangle *ink_rect,
			  const PangoRectangle * rect)
{
	if (lsm_debug_check (&lsm_debug_category_render, LSM_DEBUG_LEVEL_DEBUG)) {
		cairo_t *cairo;

		cairo = view->dom_view.cairo;

		cairo_set_line_width (cairo, 0.1);
		cairo_set_source_rgb (cairo, 1,0,0);
		cairo_rectangle (cairo,
				 x + pango_units_to_double (rect->x)
				 - pango_units_to_double (ink_rect->x),
				 y + pango_units_to_double (rect->y) -
				 pango_units_to_double (baseline),
				 pango_units_to_double (rect->width),
				 pango_units_to_double (rect->height));
		cairo_stroke (cairo);
		cairo_set_source_rgb (cairo, 0,1,0);
		cairo_rectangle (cairo,
				 x,
				 y + pango_units_to_double (ink_rect->y) -
				 pango_units_to_double (baseline),
				 pango_units_to_double (ink_rect->width),
				 pango_units_to_double (ink_rect->height));
		cairo_stroke (cairo);
	}

}

double
lsm_mathml_view_measure_axis_offset (LsmMathmlView *view,
				  double math_size)
{
	PangoLayout *pango_layout;
	PangoRectangle ink_rect;
	PangoLayoutIter *iter;
	PangoFontDescription *font_description;
	double axis_offset;
	int baseline;

	g_return_val_if_fail (LSM_IS_MATHML_VIEW (view), 0.0);

	font_description = view->dom_view.font_description;
	pango_layout = view->dom_view.measure_pango_layout;

	pango_font_description_set_family (font_description, LSM_MATHML_FONT_SERIF);
	pango_font_description_set_size (font_description, math_size * PANGO_SCALE);
	pango_font_description_set_style (font_description, PANGO_STYLE_NORMAL);
	pango_font_description_set_weight (font_description, PANGO_WEIGHT_NORMAL);
	pango_layout_set_text (pango_layout, "\xe2\x88\x92", -1);
	pango_layout_set_font_description (pango_layout, font_description);
	pango_layout_get_extents (pango_layout, &ink_rect, NULL);

	iter = pango_layout_get_iter (pango_layout);
	baseline = pango_layout_iter_get_baseline (iter);
	pango_layout_iter_free (iter);

	axis_offset = pango_units_to_double (- 0.5 * ink_rect.height - ink_rect.y + baseline);

	lsm_debug_measure ("[LsmMathmlView::measure_axis_offset] offset = %g (%g %%)",
		   axis_offset, axis_offset / math_size);

	return axis_offset;
}

void
lsm_mathml_view_get_font_metrics (LsmMathmlView *view,
			       const LsmMathmlElementStyle *style,
			       double *ascent,
			       double *descent)
{
	LsmMathmlBbox bbox;

	lsm_mathml_view_measure_text (view, style, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", &bbox);

	if (ascent != NULL)
		*ascent = bbox.height;
	if (descent != NULL)
		*descent = bbox.depth;
}

void
lsm_mathml_view_measure_text (LsmMathmlView *view,
			   const LsmMathmlElementStyle *style,
			   char const *text,
			   LsmMathmlBbox *bbox)
{
	PangoRectangle ink_rect;
	int baseline;

	g_return_if_fail (LSM_IS_MATHML_VIEW (view));
	g_return_if_fail (style != NULL);
	g_return_if_fail (bbox != NULL);

	if (text == NULL) {
		*bbox = lsm_mathml_bbox_null;
		return;
	}

	lsm_mathml_view_update_layout_for_text (view, style, text,
					     view->dom_view.measure_pango_layout, &ink_rect, NULL, &baseline);

	bbox->width = pango_units_to_double (ink_rect.width);
	bbox->height = pango_units_to_double (baseline - ink_rect.y);
	bbox->depth = pango_units_to_double (ink_rect.height + ink_rect.y - baseline);
	bbox->is_defined = TRUE;
}

void
lsm_mathml_view_show_text (LsmMathmlView *view,
			const LsmMathmlElementStyle *style,
			double x, double y, char const *text)
{
	PangoLayout *pango_layout;
	PangoRectangle rect, ink_rect;
	cairo_t *cairo;
	int baseline;

	g_return_if_fail (LSM_IS_MATHML_VIEW (view));
	g_return_if_fail (style != NULL);

	if (text == NULL || strlen (text) < 1)
		return;

	lsm_debug_render ("[LsmMathmlView::show_text] '%s' at %g, %g (size = %g) %s",
		   text, x, y, style->math_size,
		   lsm_mathml_variant_to_string (style->math_variant));

	lsm_mathml_view_update_layout_for_text (view, style, text,
					     view->dom_view.pango_layout, &ink_rect, &rect, &baseline);
	lsm_mathml_view_show_layout (view, x, y, baseline, &ink_rect, &rect);

	if (ink_rect.width <= 0 || ink_rect.height <= 0)
		return;

	cairo = view->dom_view.cairo;
	pango_layout = view->dom_view.pango_layout;

	cairo_save (cairo);

	if (lsm_debug_check (&lsm_debug_category_dom, LSM_DEBUG_LEVEL_DEBUG)) {
		cairo_set_source_rgba (cairo, 1.0, 0.0, 0.0, 0.2);
		cairo_arc (cairo, x, y, 1.0, 0.0, 2.0 * M_PI);
		cairo_fill (cairo);
	}

	cairo_set_source_rgba (cairo,
			       style->math_color.red,
			       style->math_color.green,
			       style->math_color.blue,
			       style->math_color.alpha);

	cairo_move_to (cairo, x - pango_units_to_double (ink_rect.x), y - pango_units_to_double (baseline));
	pango_cairo_show_layout (cairo, pango_layout);

	cairo_restore (cairo);
}

static void
lsm_mathml_view_update_layout_for_operator (LsmMathmlView *view,
					    const LsmMathmlElementStyle *style,
					    const char *text,
					    gboolean large,
					    PangoLayout *pango_layout,
					    PangoRectangle *ink_rect,
					    PangoRectangle *rect,
					    int *baseline)
{
	PangoFontDescription *font_description;

	font_description = view->dom_view.font_description;

	pango_font_description_set_size (font_description,
					 style->math_size * PANGO_SCALE * (large ? LSM_MATHML_LARGE_OP_SCALE : 1.0));
	pango_font_description_set_family (font_description, LSM_MATHML_FONT_SERIF);
	lsm_mathml_view_apply_style_to_font_description (font_description, style, FALSE);
	pango_layout_set_text (pango_layout, text, -1);
	pango_layout_set_font_description (pango_layout, font_description);
	pango_layout_get_extents (pango_layout, ink_rect, rect);

	if (baseline != NULL) {
		PangoLayoutIter *iter;

		iter = pango_layout_get_iter (pango_layout);
		*baseline = pango_layout_iter_get_baseline (iter);
		pango_layout_iter_free (iter);
	}
}

void
lsm_mathml_view_measure_operator (LsmMathmlView *view,
			       const LsmMathmlElementStyle *style,
			       char const *text,
			       gboolean large,
			       gboolean symmetric,
			       double axis_offset,
			       LsmMathmlBbox const *stretch_bbox, LsmMathmlBbox *bbox)
{
	PangoFontDescription *font_description;
	PangoLayout *pango_layout;
	PangoRectangle ink_rect;
	LsmMathmlGlyphFlags flags;
	const LsmMathmlOperatorGlyph *glyph;
	const char *font_name;
	int baseline;
	gboolean is_stretch_bbox_defined;

	g_return_if_fail (LSM_IS_MATHML_VIEW (view));
	g_return_if_fail (style != NULL);
	g_return_if_fail (bbox != NULL);
	g_return_if_fail (stretch_bbox != NULL);

	if (text == NULL) {
		*bbox = lsm_mathml_bbox_null;
		return;
	}

	is_stretch_bbox_defined = stretch_bbox->is_defined;

	font_description = view->dom_view.font_description;
	pango_layout = view->dom_view.measure_pango_layout;

	if (is_stretch_bbox_defined)
		lsm_debug_render ("[LsmMathmlView::measure_operator] Stretch bbox w = %g, h = %g, d = %g",
			   stretch_bbox->width, stretch_bbox->height, stretch_bbox->depth);

	glyph = lsm_mathml_glyph_table_find_operator_glyph (text);
	if (glyph == NULL) {
		lsm_mathml_view_update_layout_for_operator (view, style, text, large,
							 pango_layout, &ink_rect, NULL, &baseline);
		flags = 0;

		lsm_debug_render ("[LsmMathmlView::measure_operator] operator = %s", text);

	} else {
		PangoLayoutIter *iter;
		unsigned int i;
		double width, height;
		gboolean found = FALSE;

		if (large && (glyph->flags & LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION) &&
		    !is_stretch_bbox_defined) {
			pango_font_description_set_size (font_description,
							 style->math_size * PANGO_SCALE);
			i = 1;
		} else {
			pango_font_description_set_size (font_description,
							 style->math_size * PANGO_SCALE *
							 (large ? LSM_MATHML_LARGE_OP_SCALE : 1.0));
			i = 0;
		}

		for (; i < glyph->n_sized_glyphs; i++) {
			font_name = lsm_mathml_font_names [glyph->sized_glyphs[i].font];
			pango_font_description_set_family (font_description, font_name);
			lsm_mathml_view_apply_style_to_font_description (font_description, style, FALSE);
			pango_layout_set_text (pango_layout, glyph->sized_glyphs[i].utf8, -1);
			pango_layout_set_font_description (pango_layout, font_description);
			pango_layout_get_extents (pango_layout, &ink_rect, NULL);

			height = pango_units_to_double (ink_rect.height);
			width = pango_units_to_double (ink_rect.width);

			lsm_debug_render ( "[LsmMathmlView::measure_operator] Glyph #%i -> width = %g, height = %g",
					   i, width, height);

			if (!is_stretch_bbox_defined) {
				found = TRUE;
				break;
			}

			if (glyph->flags & LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL) {
				if (height > (stretch_bbox->height + stretch_bbox->depth))
					found = TRUE;
			}

			if (glyph->flags & LSM_MATHML_GLYPH_FLAG_STRETCH_HORIZONTAL) {
				if (width > stretch_bbox->width)
					found = TRUE;
			}

			if (found)
				break;
		}

		if (found)
			lsm_debug_render ("[LsmMathmlView::measure_operator] Found sized glyph #%i", i);

		iter = pango_layout_get_iter (pango_layout);
		baseline = pango_layout_iter_get_baseline (iter);
		pango_layout_iter_free (iter);

		flags = glyph->flags;
	}

	if (is_stretch_bbox_defined && (flags & LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL) &&
	    (stretch_bbox->height + stretch_bbox->depth) >= 0) {
		bbox->height = stretch_bbox->height;
		bbox->depth = stretch_bbox->depth;
	} else {
		bbox->height = pango_units_to_double (baseline - ink_rect.y);
		bbox->depth = pango_units_to_double (ink_rect.height + ink_rect.y - baseline);
	}

	if (is_stretch_bbox_defined && (flags & LSM_MATHML_GLYPH_FLAG_STRETCH_HORIZONTAL) &&
	    stretch_bbox->width >= 0.0)
		bbox->width = stretch_bbox->width;
	else
		bbox->width = pango_units_to_double (ink_rect.width);

	if (!is_stretch_bbox_defined &&
	    (flags & LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS)) {
		double length = bbox->depth + bbox->height;

		bbox->height = 0.5 * length + axis_offset;
		bbox->depth =  0.5 * length - axis_offset;
	}

	if (is_stretch_bbox_defined && symmetric &&
	    (flags & LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL)) {
		double length = MAX (axis_offset + bbox->depth, bbox->height - axis_offset);

		bbox->height = length + axis_offset;
		bbox->depth =  length - axis_offset;
	}

	bbox->is_defined = TRUE;
}

void
lsm_mathml_view_show_operator (LsmMathmlView *view,
			    const LsmMathmlElementStyle *style,
			    double x, double y, char const *text,
			    gboolean large,
			    LsmMathmlBbox const *stretch_bbox)
{
	PangoFontDescription *font_description;
	PangoLayout *pango_layout;
	PangoRectangle rect, ink_rect;
	cairo_t *cairo;
	const LsmMathmlOperatorGlyph *glyph;
	const char *font_name;
	double scale_x, scale_y;
	int baseline;

	g_return_if_fail (LSM_IS_MATHML_VIEW (view));
	g_return_if_fail (style != NULL);
	g_return_if_fail (stretch_bbox != NULL);

	if (text == NULL || !stretch_bbox->is_defined)
		return;

	font_description = view->dom_view.font_description;
	pango_layout = view->dom_view.measure_pango_layout;

	if (stretch_bbox->is_defined)
		lsm_debug_render ("[LsmMathmlView::show_operator] Stretch bbox w = %g, h = %g, d = %g",
			   stretch_bbox->width, stretch_bbox->height, stretch_bbox->depth);

	glyph = lsm_mathml_glyph_table_find_operator_glyph (text);
	if (glyph == NULL) {
		lsm_mathml_view_update_layout_for_operator (view, style, text, large,
							    pango_layout, &ink_rect, &rect, &baseline);
	} else {
		PangoLayoutIter *iter;
		unsigned int i;
		gboolean found = FALSE;

		if (large && (glyph->flags & LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION)) {
			pango_font_description_set_size (font_description,
							 style->math_size * PANGO_SCALE);
			i = 1;
		} else {
			pango_font_description_set_size (font_description,
							 style->math_size * PANGO_SCALE *
							 (large ? LSM_MATHML_LARGE_OP_SCALE : 1.0));
			i = 0;
		}

		for (; i < glyph->n_sized_glyphs; i++) {
			font_name = lsm_mathml_font_names [glyph->sized_glyphs[i].font];
			pango_font_description_set_family (font_description, font_name);
			lsm_mathml_view_apply_style_to_font_description (font_description, style, FALSE);
			pango_layout_set_text (pango_layout, glyph->sized_glyphs[i].utf8, -1);
			pango_layout_set_font_description (pango_layout, font_description);
			pango_layout_get_extents (pango_layout, &ink_rect, NULL);

			lsm_debug_render ("[LsmMathmlView::show_operator] Glyph #%i -> width = %g, height = %g", i,
				   pango_units_to_double (ink_rect.width),
				   pango_units_to_double (ink_rect.height));

			if (!stretch_bbox->is_defined) {
				found = TRUE;
				break;
			}

			if (glyph->flags & LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL) {
				if (pango_units_to_double (ink_rect.height) >
				    (stretch_bbox->height + stretch_bbox->depth))
					found = TRUE;
			}

			if (glyph->flags & LSM_MATHML_GLYPH_FLAG_STRETCH_HORIZONTAL) {
						if (pango_units_to_double (ink_rect.width) >
						    stretch_bbox->width)
							found = TRUE;
			}

			if (found)
				break;
		}

		if (found)
			lsm_debug_render ("[LsmMathmlView::show_operator] Found sized glyph #%i", i);

		iter = pango_layout_get_iter (pango_layout);
		baseline = pango_layout_iter_get_baseline (iter);
		pango_layout_iter_free (iter);
	}

	lsm_debug_render ("[LsmMathmlView::show_operator] '%s' at %g, %g (size = %g) %s - %s",
		    text, x, y, style->math_size,
		    style->math_family,
		    lsm_mathml_variant_to_string (style->math_variant));

	if (ink_rect.width == 0 || ink_rect.height == 0)
		return;

	scale_x = stretch_bbox->width / pango_units_to_double (ink_rect.width);
	scale_y = (stretch_bbox->height + stretch_bbox->depth) / pango_units_to_double (ink_rect.height);

	cairo = view->dom_view.cairo;

	cairo_save (cairo);

	if (lsm_debug_check (&lsm_debug_category_render, LSM_DEBUG_LEVEL_DEBUG)) {
		cairo_set_source_rgba (cairo, 1.0, 0.0, 0.0, 0.1);
		cairo_arc (cairo, x, y, 1.0, 0.0, 2.0 * M_PI);
		cairo_fill (cairo);
	}

	cairo_move_to (cairo, x , y - stretch_bbox->height);
	cairo_scale (cairo, scale_x, scale_y);
	cairo_rel_move_to (cairo,
			   - pango_units_to_double (ink_rect.x),
			   - pango_units_to_double (ink_rect.y));

	cairo_set_source_rgba (cairo,
			       style->math_color.red,
			       style->math_color.green,
			       style->math_color.blue,
			       style->math_color.alpha);

	pango_cairo_show_layout (cairo, pango_layout);
	cairo_restore (cairo);
}

double
lsm_mathml_view_get_operator_slant (LsmMathmlView *view,
				 const LsmMathmlElementStyle *style,
				 const char *text)
{
	return lsm_mathml_glyph_table_get_operator_slant (text);
}

void
lsm_mathml_view_measure_radical (LsmMathmlView *view,
			      const LsmMathmlElementStyle *style,
			      const LsmMathmlBbox *stretch_bbox,
			      LsmMathmlBbox *bbox, double *x_offset, double *y_offset)
{
	LsmMathmlBbox radical_stretch_bbox;
	double thickness;

	g_return_if_fail (LSM_IS_MATHML_VIEW (view));
	g_return_if_fail (style != NULL);
	g_return_if_fail (bbox != NULL);
	g_return_if_fail (stretch_bbox != NULL);

	radical_stretch_bbox = *stretch_bbox;

	thickness = style->math_size * LSM_MATHML_RADICAL_TOP_LINE_WIDTH;

	radical_stretch_bbox.height += LSM_MATHML_SPACE_EM_THICK * style->math_size + thickness;

	radical_stretch_bbox.depth += LSM_MATHML_SPACE_EM_THICK * style->math_size;

	lsm_mathml_view_measure_operator (view, style, LSM_MATHML_RADICAL_UTF8,
				       FALSE, FALSE, 0.0, &radical_stretch_bbox, bbox);

	if (x_offset != NULL) {
		*x_offset = bbox->width * LSM_MATHML_RADICAL_ORDER_X_OFFSET;
	}

	if (y_offset != NULL) {
		*y_offset = (bbox->height + bbox->depth) * LSM_MATHML_RADICAL_ORDER_Y_OFFSET -
			LSM_MATHML_SPACE_EM_MEDIUM * style->math_size;
	}
}

void
lsm_mathml_view_show_radical (LsmMathmlView *view,
			   const LsmMathmlElementStyle *style,
			   double x, double y, double width,
			   LsmMathmlBbox const *stretch_bbox)
{
	cairo_t *cairo;
	double thickness;
	double y_line;
	double dummy = 0.0;
	double alpha;

	g_return_if_fail (LSM_IS_MATHML_VIEW (view));
	g_return_if_fail (style != NULL);
	g_return_if_fail (stretch_bbox != NULL);

	cairo = view->dom_view.cairo;

	lsm_mathml_view_show_operator (view, style, x, y, LSM_MATHML_RADICAL_UTF8, FALSE, stretch_bbox);

	thickness = style->math_size * LSM_MATHML_RADICAL_TOP_LINE_WIDTH;

	alpha = style->math_color.alpha;

	if (!view->dom_view.is_vector) {
		cairo_user_to_device_distance (cairo, &dummy, &thickness);

		if (thickness < 1.0) {
			alpha *= thickness;
			thickness = 1.0;
		}

		thickness = floor (thickness + 0.5);
		cairo_device_to_user_distance (cairo, &dummy, &thickness);
	}

	cairo_save (cairo);
	cairo_set_line_cap (cairo, CAIRO_LINE_CAP_ROUND);
	cairo_set_line_width (cairo, thickness);

	cairo_set_source_rgba (cairo,
			       style->math_color.red,
			       style->math_color.green,
			       style->math_color.blue,
			       alpha);

	x += stretch_bbox->width;

	y_line = y - stretch_bbox->height;

	if (!view->dom_view.is_vector) {
		cairo_user_to_device (cairo, &dummy, &y_line);

		y_line = floor (y_line);

		cairo_device_to_user (cairo, &dummy, &y_line);
	}

	y_line += 0.5 * thickness;

	cairo_move_to (cairo,
		       x - 0.5 * style->math_size * LSM_MATHML_RADICAL_TOP_LINE_WIDTH,
		       y_line);
	cairo_line_to (cairo,
		       x - thickness * 0.5 + width,
		       y_line);

	cairo_stroke (cairo);

	cairo_restore (cairo);
}

typedef enum {
	_GMATHML_STROKE_WIDTH_EVEN,
	_GMATHML_STROKE_WIDTH_ODD,
	_GMATHML_STROKE_WIDTH_NULL,
	_GMATHML_STROKE_WIDTH_VECTOR
} _LsmMathmlStrokeWidth;

static void
_round_rectangle_coordinates (cairo_t *cairo,
			      _LsmMathmlStrokeWidth stroke_width,
			      double *x0, double *y0,
			      double *x1, double *y1)
{
	if (stroke_width != _GMATHML_STROKE_WIDTH_VECTOR) {
		cairo_user_to_device (cairo, x0, y0);
		cairo_user_to_device (cairo, x1, y1);

		if (stroke_width == _GMATHML_STROKE_WIDTH_EVEN) {
			*x0 = floor (*x0 + 0.5);
			*y0 = floor (*y0 + 0.5);
			*x1 = floor (*x1 + 0.5);
			*y1 = floor (*y1 + 0.5);
		} else {
			*x0 = 0.5 + floor (*x0);
			*y0 = 0.5 + floor (*y0);
			*x1 = 0.5 + floor (*x1);
			*y1 = 0.5 + floor (*y1);
		}

		cairo_device_to_user (cairo, x0, y0);
		cairo_device_to_user (cairo, x1, y1);
	}
}

static _LsmMathmlStrokeWidth
_emit_stroke_attributes (LsmMathmlView *view, LsmMathmlLine line, double line_width,
			 const LsmMathmlColor *color)
{
	_LsmMathmlStrokeWidth stroke_width;
	cairo_t *cairo;
	double dashes[2] = {3.0, 2.0};
	double rounded_width = line_width;
	double dummy = 0;
	double alpha = color->alpha;

	cairo = view->dom_view.cairo;

	switch (line) {
		case LSM_MATHML_LINE_DASHED:
			cairo_set_dash (cairo, dashes, 2, 0.0);
			break;
		case LSM_MATHML_LINE_SOLID:
			cairo_set_dash (cairo, NULL, 0, 0.0);
			break;
		default:
			return _GMATHML_STROKE_WIDTH_NULL;
	}

	if (view->dom_view.is_vector) {
		cairo_set_line_width (cairo, line_width);
		cairo_set_source_rgba (cairo,
				       color->red,
				       color->green,
				       color->blue,
				       color->alpha);
		return _GMATHML_STROKE_WIDTH_VECTOR;
	}

	cairo_user_to_device_distance (cairo, &dummy, &rounded_width);

	if (rounded_width < 1.0) {
		alpha *= rounded_width;
		rounded_width = 1.0;
	}

	rounded_width = floor (rounded_width + 0.5);

	if (((int) rounded_width) % 2 == 0)
		stroke_width = _GMATHML_STROKE_WIDTH_EVEN;
	else
		stroke_width = _GMATHML_STROKE_WIDTH_ODD;

	cairo_device_to_user_distance (cairo, &dummy, &rounded_width);

	cairo_set_line_width (cairo, rounded_width);
	cairo_set_source_rgba (cairo,
			       color->red,
			       color->green,
			       color->blue,
			       alpha);

	return stroke_width;
}

void
lsm_mathml_view_show_background (LsmMathmlView *view,
			      const LsmMathmlElementStyle *style,
			      double x, double y,
			      const LsmMathmlBbox *bbox)
{
	cairo_t *cairo;
	double x0, y0, x1, y1;

	g_return_if_fail (LSM_IS_MATHML_VIEW (view));
	g_return_if_fail (style != NULL);

	cairo = view->dom_view.cairo;

	x0 = x;
	y0 = y - bbox->height;
	x1 = x + bbox->width;
	y1 = y + bbox->depth;

	if (!view->dom_view.is_vector)
		_round_rectangle_coordinates (cairo, _GMATHML_STROKE_WIDTH_EVEN, &x0, &y0, &x1, &y1);

	cairo_set_source_rgba (cairo,
			       style->math_background.red,
			       style->math_background.green,
			       style->math_background.blue,
			       style->math_background.alpha);
	cairo_rectangle (cairo, x0, y0, x1 - x0, y1 - y0);
	cairo_fill (cairo);
}

void
lsm_mathml_view_show_bbox (LsmMathmlView *view, double x, double y, const LsmMathmlBbox *bbox)
{
	cairo_t *cairo;

	g_return_if_fail (LSM_IS_MATHML_VIEW (view));

	cairo = view->dom_view.cairo;

	if (lsm_debug_check (&lsm_debug_category_render, LSM_DEBUG_LEVEL_DEBUG)) {
		cairo_move_to (cairo, x, y);
		cairo_set_source_rgba (cairo, 0,0,1,0.1);
		cairo_rectangle (cairo, x, y, bbox->width, -bbox->height);
		cairo_rectangle (cairo, x, y, bbox->width, bbox->depth);
		cairo_fill (cairo);
	}
}

void
lsm_mathml_view_show_rectangle (LsmMathmlView *view,
			     const LsmMathmlElementStyle *style,
			     double x0, double y0, double width, double height,
			     LsmMathmlLine line, double line_width)
{
	_LsmMathmlStrokeWidth stroke_width;
	cairo_t *cairo;
	double x1, y1;

	g_return_if_fail (LSM_IS_MATHML_VIEW (view));
	g_return_if_fail (style != NULL);

	stroke_width = _emit_stroke_attributes (view, line, line_width, &style->math_color);

	if (stroke_width == _GMATHML_STROKE_WIDTH_NULL)
		return;

	x1 = x0 + width;
	y1 = y0 + height;

	cairo = view->dom_view.cairo;

	_round_rectangle_coordinates (cairo, stroke_width, &x0, &y0, &x1, &y1);

	cairo_rectangle (cairo, x0, y0, x1 - x0, y1 - y0);
	cairo_stroke (cairo);
}

void
lsm_mathml_view_show_line (LsmMathmlView *view,
			const LsmMathmlElementStyle *style,
			double x0, double y0, double x1, double y1,
			LsmMathmlLine line, double line_width)
{
	_LsmMathmlStrokeWidth stroke_width;
	cairo_t *cairo;

	g_return_if_fail (LSM_IS_MATHML_VIEW (view));
	g_return_if_fail (style != NULL);

	stroke_width = _emit_stroke_attributes (view, line, line_width, &style->math_color);

	if (stroke_width == _GMATHML_STROKE_WIDTH_NULL)
		return;

	cairo = view->dom_view.cairo;

	_round_rectangle_coordinates (cairo, stroke_width, &x0, &y0, &x1, &y1);

	cairo_move_to (cairo, x0, y0);
	cairo_line_to (cairo, x1, y1);
	cairo_stroke (cairo);
}

void
lsm_mathml_view_show_fraction_line (LsmMathmlView *view,
				 const LsmMathmlElementStyle *style,
				 double x, double y,
				 double width, double thickness)
{
	_LsmMathmlStrokeWidth stroke_width;
	cairo_t *cairo;
	double x0, y0, x1, y1;

	g_return_if_fail (LSM_IS_MATHML_VIEW (view));
	g_return_if_fail (style != NULL);

	stroke_width = _emit_stroke_attributes (view, LSM_MATHML_LINE_SOLID, thickness, &style->math_color);

	if (stroke_width == _GMATHML_STROKE_WIDTH_NULL)
		return;

	x0 = x;
	y0 = y;
	x1 = x + width;
	y1 = y;

	cairo = view->dom_view.cairo;

	_round_rectangle_coordinates (cairo, stroke_width, &x0, &y0, &x1, &y1);

	cairo_move_to (cairo, x0, y0);
	cairo_line_to (cairo, x1, y1);
	cairo_stroke (cairo);
}

static const LsmMathmlBbox *
_view_measure (LsmMathmlView *view, double *width, double *height, double *baseline)
{
	LsmMathmlMathElement *math_element;
	const LsmMathmlBbox *bbox;

	math_element = lsm_mathml_document_get_root_element (LSM_MATHML_DOCUMENT (view->dom_view.document));
	if (math_element == NULL)
		return NULL;

	lsm_mathml_math_element_update (math_element);

	bbox = lsm_mathml_math_element_measure (math_element, view);

	if (bbox != NULL) {
		if (width != NULL)
			*width = bbox->width;
		if (height != NULL)
			*height = bbox->height + bbox->depth;
		if (baseline != NULL)
			*baseline = bbox->height;
	}

	return bbox;
}

static void
lsm_mathml_view_measure (LsmDomView *dom_view, double *width, double *height, double *baseline)
{
	_view_measure (LSM_MATHML_VIEW (dom_view), width, height, baseline);
}

static void
lsm_mathml_view_render (LsmDomView *dom_view)
{
	LsmMathmlView *view = LSM_MATHML_VIEW (dom_view);
	LsmMathmlMathElement *math_element;
	cairo_t *cairo;
	const LsmMathmlBbox *bbox;
	double resolution_ppi;

	math_element = lsm_mathml_document_get_root_element (LSM_MATHML_DOCUMENT (view->dom_view.document));
	if (math_element == NULL)
		return;

	resolution_ppi = lsm_dom_view_get_resolution (dom_view);

	bbox = _view_measure (view, NULL, NULL, NULL);

	lsm_mathml_math_element_layout (math_element, view, bbox);

	cairo = view->dom_view.cairo;

	cairo_scale (cairo, resolution_ppi / 72.0, resolution_ppi / 72.0);

	cairo_translate (cairo, 0, bbox->height);

	lsm_mathml_math_element_render (math_element, view);

	lsm_debug_render ("[LsmMathmlView::render] cairo status = %s",
		   cairo_status_to_string (cairo_status (cairo)));
}

LsmMathmlView *
lsm_mathml_view_new (LsmMathmlDocument *document)
{
	LsmMathmlView *view;

	view = g_object_new (LSM_TYPE_MATHML_VIEW, NULL);

	lsm_dom_view_set_document (LSM_DOM_VIEW (view), LSM_DOM_DOCUMENT (document));

	return view;
}

static void
lsm_mathml_view_init (LsmMathmlView *view)
{
}

static void
lsm_mathml_view_finalize (GObject *object)
{
	parent_class->finalize (object);
}

static void
lsm_mathml_view_class_init (LsmMathmlViewClass *view_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (view_class);
	LsmDomViewClass *d_view_class = LSM_DOM_VIEW_CLASS (view_class);

	parent_class = g_type_class_peek_parent (view_class);

	object_class->finalize = lsm_mathml_view_finalize;

	d_view_class->measure = lsm_mathml_view_measure;
	d_view_class->render = lsm_mathml_view_render;
}

G_DEFINE_TYPE (LsmMathmlView, lsm_mathml_view, LSM_TYPE_DOM_VIEW)
