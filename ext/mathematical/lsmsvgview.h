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

#ifndef LSM_SVG_VIEW_H
#define LSM_SVG_VIEW_H

#include <lsmdom.h>
#include <lsmsvgtypes.h>
#include <lsmsvgelement.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

G_BEGIN_DECLS

typedef enum {
	LSM_SVG_VIEW_SURFACE_TYPE_AUTO,
	LSM_SVG_VIEW_SURFACE_TYPE_IMAGE
} LsmSvgViewSurfaceType;

#define LSM_TYPE_SVG_VIEW             (lsm_svg_view_get_type ())
#define LSM_SVG_VIEW(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_SVG_VIEW, LsmSvgView))
#define LSM_SVG_VIEW_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_SVG_VIEW, LsmSvgViewClass))
#define LSM_IS_SVG_VIEW(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_SVG_VIEW))
#define LSM_IS_SVG_VIEW_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_SVG_VIEW))
#define LSM_SVG_VIEW_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_SVG_VIEW, LsmSvgViewClass))

typedef struct _LsmSvgViewClass LsmSvgViewClass;
typedef struct _LsmSvgViewPrivate LsmSvgViewPrivate;

typedef struct _LsmSvgViewPatternData LsmSvgViewPatternData;

struct _LsmSvgView {
	LsmDomView dom_view;

	double resolution_ppi;

	const LsmSvgStyle *style;

	GSList *style_stack;
	GSList *element_stack;
	GSList *viewbox_stack;
	GSList *matrix_stack;
	GSList *pango_layout_stack;
	GList *background_stack;

	gboolean is_pango_layout_in_use;

	LsmSvgViewPatternData *pattern_data;
	PangoLayout *pango_layout;

	GSList *pattern_stack;

	gboolean is_clipping;
	LsmBox clip_extents;

	double last_stop_offset;

	GSList *filter_surfaces;

	gboolean debug_filter;
	gboolean debug_mask;
	gboolean debug_pattern;
	gboolean debug_group;
	gboolean debug_text;
};

struct _LsmSvgViewClass {
	LsmDomViewClass parent_class;
};

GType lsm_svg_view_get_type (void);

LsmSvgView *	lsm_svg_view_new 			(LsmSvgDocument *document);

double 		lsm_svg_view_normalize_length 		(LsmSvgView *view, const LsmSvgLength *length,
							 LsmSvgLengthDirection direction);
double * 	lsm_svg_view_normalize_length_list 	(LsmSvgView *view, const LsmSvgLengthList *list, LsmSvgLengthDirection direction,
							 unsigned int *n_data);

const LsmBox *	lsm_svg_view_get_pattern_extents	(LsmSvgView *view);
const LsmBox * 	lsm_svg_view_get_object_extents 	(LsmSvgView *view);
const LsmBox *	lsm_svg_view_get_clip_extents		(LsmSvgView *view);

void		lsm_svg_view_path_extents		(LsmSvgView *view, const char *path, LsmExtents *extents);

void 		lsm_svg_view_create_radial_gradient 	(LsmSvgView *view, double cx, double cy,
							                   double r, double fx, double fy);
void 		lsm_svg_view_create_linear_gradient 	(LsmSvgView *view, double x1, double y1,
							                   double x2, double y2);
void 		lsm_svg_view_add_gradient_color_stop	(LsmSvgView *view, double offset);
G_GNUC_WARN_UNUSED_RESULT gboolean 	
		lsm_svg_view_set_gradient_properties	(LsmSvgView *view,
							 LsmSvgSpreadMethod method,
							 LsmSvgPatternUnits units,
							 const LsmSvgMatrix *matrix);

G_GNUC_WARN_UNUSED_RESULT gboolean
		lsm_svg_view_create_surface_pattern	(LsmSvgView *view, const LsmBox *viewport,
							 const LsmSvgMatrix *matrix,
							 LsmSvgViewSurfaceType surface_type) G_GNUC_WARN_UNUSED_RESULT;

void 		lsm_svg_view_show_viewport 	(LsmSvgView*view, const LsmBox *viewport);
void 		lsm_svg_view_show_rectangle 	(LsmSvgView *view, double x, double y,
						                   double width, double height,
								   double rx, double ry);
void 		lsm_svg_view_show_circle	(LsmSvgView *view, double cx, double cy, double r);
void 		lsm_svg_view_show_ellipse	(LsmSvgView *view, double cx, double cy, double rx, double ry);
void		lsm_svg_view_show_path		(LsmSvgView *view, const char *d);
void 		lsm_svg_view_show_line 		(LsmSvgView *view, double x1, double y1, double x2, double y2);
void 		lsm_svg_view_show_polyline	(LsmSvgView *view, const char *points);
void 		lsm_svg_view_show_polygon	(LsmSvgView *view, const char *points);
void 		lsm_svg_view_start_text 	(LsmSvgView *view);
void 		lsm_svg_view_end_text 		(LsmSvgView *view);
void 		lsm_svg_view_show_text 		(LsmSvgView *view, char const *string, 
						 unsigned int n_x, double *x, unsigned int n_y, double *y,
						 unsigned int n_dx, double *dx, unsigned int n_dy, double *dy);
void 		lsm_svg_view_text_extents 	(LsmSvgView *view, char const *string,
						 double x, double y,
						 unsigned int n_dx, double *dx, unsigned int n_dy, double *dy,
						 LsmExtents *extents);
void		lsm_svg_view_show_pixbuf	(LsmSvgView *view, GdkPixbuf *pixbuf);

void 		lsm_svg_view_push_viewbox 		(LsmSvgView *view, const LsmBox *viewbox);
void 		lsm_svg_view_pop_viewbox 		(LsmSvgView *view);
void 		lsm_svg_view_push_viewport 		(LsmSvgView *view, const LsmBox *viewport,
							 const LsmBox *viewbox,
							 const LsmSvgPreserveAspectRatio *aspect_ratio,
							 LsmSvgOverflow overflow);
void 		lsm_svg_view_pop_viewport 		(LsmSvgView *view);
void 		lsm_svg_view_viewbox_to_viewport 	(LsmSvgView *view,
							 const LsmBox *viewport, const LsmBox *viewbox,
							 const LsmSvgPreserveAspectRatio *aspect_ratio,
							 double *x, double *y);
gboolean	lsm_svg_view_push_matrix		(LsmSvgView *view, const LsmSvgMatrix *matrix);
void 		lsm_svg_view_pop_matrix			(LsmSvgView *view);

void		lsm_svg_view_push_element		(LsmSvgView *view, const LsmSvgElement *element);
void		lsm_svg_view_pop_element		(LsmSvgView *view);

void		lsm_svg_view_push_style			(LsmSvgView *view, LsmSvgStyle *style);
void		lsm_svg_view_pop_style			(LsmSvgView *view);
LsmSvgStyle *	lsm_svg_view_get_current_style		(LsmSvgView *view);

void		lsm_svg_view_push_composition		(LsmSvgView *view, LsmSvgStyle *style);
void		lsm_svg_view_pop_composition		(LsmSvgView *view);

LsmBox 		lsm_svg_view_get_filter_surface_extents (LsmSvgView *view, const char *name);
void 		lsm_svg_view_apply_blend 		(LsmSvgView *view, const char *input_1, const char*input_2, const char *output,
							 const LsmBox *subregion, LsmSvgBlendingMode mode);
void 		lsm_svg_view_apply_flood 		(LsmSvgView *view, const char *output, const LsmBox *subregion);
void		lsm_svg_view_apply_gaussian_blur 	(LsmSvgView *view, const char *input, const char *output, const LsmBox *subregion,
							 double std_x, double std_y);
void 		lsm_svg_view_apply_offset 		(LsmSvgView *view, const char *input, const char *output, const LsmBox *subregion,
							 double dx, double dy);
void 		lsm_svg_view_apply_merge 		(LsmSvgView *view, const char *input, const char *output, const LsmBox *subregion);
void 		lsm_svg_view_apply_tile 		(LsmSvgView *view, const char *input, const char *output, const LsmBox *subregion);

G_END_DECLS

#endif
