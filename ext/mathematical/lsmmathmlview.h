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

#ifndef LSM_MATHML_VIEW_H
#define LSM_MATHML_VIEW_H

#include <lsmdomview.h>
#include <lsmmathmltypes.h>
#include <lsmmathmlutils.h>
#include <lsmmathmlelement.h>
#include <lsmmathmlpresentationtoken.h>

G_BEGIN_DECLS

typedef enum {
	LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL =	1 << 0,
	LSM_MATHML_GLYPH_FLAG_STRETCH_HORIZONTAL =	1 << 1,
	LSM_MATHML_GLYPH_FLAG_TYPE_SIZED =		1 << 2,
	LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS =		1 << 3,
	LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION =	1 << 4,
	LSM_MATHML_GLYPH_FLAG_INTEGRAL_SLANT =	1 << 5
} LsmMathmlGlyphFlags;

typedef enum {
	LSM_MATHML_FONT_ERROR,
	LSM_MATHML_FONT_DEFAULT,
	LSM_MATHML_FONT_CMR10,
	LSM_MATHML_FONT_CMMI10,
	LSM_MATHML_FONT_CMEX10,
	LSM_MATHML_FONT_CMSY10,
	LSM_MATHML_FONT_SYMBOL
} LsmMathmlFont;

typedef struct {
	LsmMathmlFont 	font;
	const char 	utf8[4];
} LsmMathmlGlyph;

typedef struct {
	const char		*utf8;
	LsmMathmlGlyphFlags	flags;
	LsmMathmlGlyph		start_glyph;
	LsmMathmlGlyph		middle_glyph;
	LsmMathmlGlyph		stop_glyph;
	LsmMathmlGlyph		glue_glyph;
	unsigned int		n_sized_glyphs;
	LsmMathmlGlyph		sized_glyphs[5];
} LsmMathmlOperatorGlyph;

#define LSM_TYPE_MATHML_VIEW             (lsm_mathml_view_get_type ())
#define LSM_MATHML_VIEW(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_MATHML_VIEW, LsmMathmlView))
#define LSM_MATHML_VIEW_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_MATHML_VIEW, LsmMathmlViewClass))
#define LSM_IS_MATHML_VIEW(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_MATHML_VIEW))
#define LSM_IS_MATHML_VIEW_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_MATHML_VIEW))
#define LSM_MATHML_VIEW_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_MATHML_VIEW, LsmMathmlViewClass))

typedef struct _LsmMathmlViewClass LsmMathmlViewClass;
typedef struct _LsmMathmlViewPrivate LsmMathmlViewPrivate;

struct _LsmMathmlView {
	LsmDomView dom_view;
};

struct _LsmMathmlViewClass {
	LsmDomViewClass dom_view_class;
};

GType lsm_mathml_view_get_type (void);

LsmMathmlView *		lsm_mathml_view_new 		(LsmMathmlDocument *document);

/* Internal API */

double 		lsm_mathml_view_measure_axis_offset	(LsmMathmlView *view, double math_size);

void 		lsm_mathml_view_get_font_metrics 	(LsmMathmlView *view,
							 const LsmMathmlElementStyle *style,
							 double *ascent,
							 double *descent);

void 		lsm_mathml_view_measure_text 		(LsmMathmlView *view,
							 const LsmMathmlElementStyle *style,
							 char const *text,
							 LsmMathmlBbox *bbox);
void 		lsm_mathml_view_show_text 		(LsmMathmlView *view,
							 const LsmMathmlElementStyle *style,
							 double x, double y, const char *text);

void 		lsm_mathml_view_measure_operator 	(LsmMathmlView *view,
							 const LsmMathmlElementStyle *style,
							 char const *text,
							 gboolean large, gboolean symmetric,
							 double axis_offset,
							 const LsmMathmlBbox *stretch_bbox,
							 LsmMathmlBbox *bbox);
void 		lsm_mathml_view_show_operator 		(LsmMathmlView *view,
							 const LsmMathmlElementStyle *style,
							 double x, double y, char const *text,
							 gboolean large,
							 const LsmMathmlBbox *stretch_bbox);
double 		lsm_mathml_view_get_operator_slant 	(LsmMathmlView *view,
							 const LsmMathmlElementStyle *style,
							 const char *text);

void 		lsm_mathml_view_measure_radical 	(LsmMathmlView *view,
							 const LsmMathmlElementStyle *style,
							 const LsmMathmlBbox *stretch_bbox,
							 LsmMathmlBbox *bbox,
							 double *x_offset, double *y_offset);
void 		lsm_mathml_view_show_radical		(LsmMathmlView *view,
							 const LsmMathmlElementStyle *style,
							 double x, double y, double width,
							 const LsmMathmlBbox *stretch_bbox);

void 		lsm_mathml_view_show_background 	(LsmMathmlView *view,
							 const LsmMathmlElementStyle *style,
							 double x, double y,
							 const LsmMathmlBbox *bbox);
void 		lsm_mathml_view_show_rectangle 		(LsmMathmlView *view,
							 const LsmMathmlElementStyle *style,
							 double x, double y, double width, double height,
							 LsmMathmlLine line, double line_width);
void 		lsm_mathml_view_show_line 		(LsmMathmlView *view,
							 const LsmMathmlElementStyle *style,
							 double x0, double y0, double x1, double y1,
							 LsmMathmlLine line, double line_width);
void 		lsm_mathml_view_show_fraction_line	(LsmMathmlView *view,
							 const LsmMathmlElementStyle *style,
							 double x, double y,
							 double width, double thickness);

void 		lsm_mathml_view_show_bbox 		(LsmMathmlView *view, double x, double y,
							 const LsmMathmlBbox *bbox);

void		lsm_mathml_view_draw_root		(LsmMathmlView *view,
							 double x, double y,
							 double width, double height,
							 double top_width,
							 double thickness,
							 LsmMathmlColor *color);

G_END_DECLS

#endif
