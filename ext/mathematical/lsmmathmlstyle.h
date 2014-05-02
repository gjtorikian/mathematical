/* Lasem
 *
 * Copyright © 2007-2009 Emmanuel Pacaud
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

#ifndef LSM_MATHML_STYLE_H
#define LSM_MATHML_STYLE_H

#include <lsmmathmltypes.h>
#include <lsmmathmlattributes.h>

G_BEGIN_DECLS

GType lsm_mathml_style_get_type (void);

#define LSM_TYPE_MATHML_STYLE (lsm_mathml_style_get_type())

struct _LsmMathmlStyle {
	/* mstyle */
	LsmMathmlDisplay display;

	int script_level;
	double script_size_multiplier;
	double script_min_size;

	double very_very_thin_math_space;
	double very_thin_math_space;
	double thin_math_space;
	double medium_math_space;
	double thick_math_space;
	double very_thick_math_space;
	double very_very_thick_math_space;
	/* tokens */
	char *math_family;
	LsmMathmlVariant math_variant;
	double math_size;
	LsmMathmlColor math_color;
	LsmMathmlColor math_background;
	/* mfrac */
	gboolean bevelled;
	/* msubsup */
	double subscript_shift;
	double superscript_shift;
	/* mfrac */
	double line_thickness;
};

LsmMathmlStyle *	lsm_mathml_style_new 			(void);
void			lsm_mathml_style_free 			(LsmMathmlStyle *style);
LsmMathmlStyle *	lsm_mathml_style_duplicate 		(const LsmMathmlStyle *from);

void 			lsm_mathml_style_change_script_level 	(LsmMathmlStyle *style, int increment);

void 			lsm_mathml_style_set_math_size_pt 	(LsmMathmlStyle *style, double math_size);
void 			lsm_mathml_style_set_script_min_size_pt	(LsmMathmlStyle *style, double script_min_size);
void 			lsm_mathml_style_set_math_family 	(LsmMathmlStyle *style, const char *math_family);
void 			lsm_mathml_style_set_math_variant	(LsmMathmlStyle *style, LsmMathmlVariant math_variant);
void 			lsm_mathml_style_set_math_color 	(LsmMathmlStyle *style,
								 double red, double green, double blue, double alpha);

G_END_DECLS

#endif
