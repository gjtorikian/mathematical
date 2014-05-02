/* Lasem
 *
 * Copyright © 2007-2008 Emmanuel Pacaud
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

#ifndef LSM_MATHML_ENUMS_H
#define LSM_MATHML_ENUMS_H

#include <glib-object.h>

G_BEGIN_DECLS

typedef enum {
	LSM_MATHML_CSS_TYPE_USER,
	LSM_MATHML_CSS_TYPE_AUTHOR,
	LSM_MATHML_CSS_TYPE_AUTHOR_IMPORTANT,
	LSM_MATHML_CSS_TYPE_USER_IMPORTANT
} LsmMathmlCssType;

typedef enum {
	LSM_MATHML_MODE_ERROR = -1,
	LSM_MATHML_MODE_DISPLAY,
	LSM_MATHML_MODE_INLINE
} LsmMathmlMode;

const char *		lsm_mathml_mode_to_string		(LsmMathmlMode mode);
LsmMathmlMode		lsm_mathml_mode_from_string		(const char *string);

typedef enum {
	LSM_MATHML_DISPLAY_ERROR = -1,
	LSM_MATHML_DISPLAY_BLOCK,
	LSM_MATHML_DISPLAY_INLINE
} LsmMathmlDisplay;

const char *		lsm_mathml_display_to_string		(LsmMathmlDisplay display);
LsmMathmlDisplay	lsm_mathml_display_from_string		(const char *string);

typedef enum {
	LSM_MATHML_SPACE_NAME_ERROR = -1,
	LSM_MATHML_SPACE_NAME_VERY_VERY_THIN,
	LSM_MATHML_SPACE_NAME_VERY_THIN,
	LSM_MATHML_SPACE_NAME_THIN,
	LSM_MATHML_SPACE_NAME_MEDIUM,
	LSM_MATHML_SPACE_NAME_THICK,
	LSM_MATHML_SPACE_NAME_VERY_THICK,
	LSM_MATHML_SPACE_NAME_VERY_VERY_THICK,
	LSM_MATHML_SPACE_NAME_INFINITY
} LsmMathmlSpaceName;

const char * 		lsm_mathml_space_name_to_string 		(LsmMathmlSpaceName name);
LsmMathmlSpaceName 	lsm_mathml_space_name_from_string 		(const char *string);

typedef enum {
	LSM_MATHML_UNIT_ERROR = -1,
	LSM_MATHML_UNIT_NONE,
	LSM_MATHML_UNIT_EM,
	LSM_MATHML_UNIT_EX,
	LSM_MATHML_UNIT_IN,
	LSM_MATHML_UNIT_CM,
	LSM_MATHML_UNIT_MM,
	LSM_MATHML_UNIT_PT,
	LSM_MATHML_UNIT_PX,
	LSM_MATHML_UNIT_PC,
	LSM_MATHML_UNIT_PERCENT
} LsmMathmlUnit;

const char * 		lsm_mathml_unit_to_string 		(LsmMathmlUnit unit);
LsmMathmlUnit 		lsm_mathml_unit_from_string 		(const char *string);

typedef enum {
	LSM_MATHML_FONT_STYLE_ERROR = -1,
	LSM_MATHML_FONT_STYLE_NORMAL,
	LSM_MATHML_FONT_STYLE_ITALIC
} LsmMathmlFontStyle;

const char * 		lsm_mathml_font_style_to_string 	(LsmMathmlFontStyle font_style);
LsmMathmlFontStyle 	lsm_mathml_font_style_from_string 	(const char *string);

typedef enum {
	LSM_MATHML_FONT_WEIGHT_ERROR = -1,
	LSM_MATHML_FONT_WEIGHT_NORMAL,
	LSM_MATHML_FONT_WEIGHT_BOLD
} LsmMathmlFontWeight;

const char * 		lsm_mathml_font_weight_to_string 	(LsmMathmlFontWeight font_weight);
LsmMathmlFontWeight 	lsm_mathml_font_weight_from_string 	(const char *string);

/* Keep in sync with lsm_mathml_pango_options in lsm_mathml_view */
typedef enum {
	LSM_MATHML_VARIANT_ERROR = -1,
	LSM_MATHML_VARIANT_NORMAL,
	LSM_MATHML_VARIANT_BOLD,
	LSM_MATHML_VARIANT_ITALIC,
	LSM_MATHML_VARIANT_BOLD_ITALIC,
	LSM_MATHML_VARIANT_DOUBLE_STRUCK,
	LSM_MATHML_VARIANT_FRAKTUR_BOLD,
	LSM_MATHML_VARIANT_SCRIPT,
	LSM_MATHML_VARIANT_SCRIPT_BOLD,
	LSM_MATHML_VARIANT_FRAKTUR,
	LSM_MATHML_VARIANT_SANS_SERIF,
	LSM_MATHML_VARIANT_SANS_SERIF_BOLD,
	LSM_MATHML_VARIANT_SANS_SERIF_ITALIC,
	LSM_MATHML_VARIANT_SANS_SERIF_BOLD_ITALIC,
	LSM_MATHML_VARIANT_MONOSPACE
} LsmMathmlVariant;

const char * 		lsm_mathml_variant_to_string 		(LsmMathmlVariant variant);
LsmMathmlVariant 	lsm_mathml_variant_from_string 		(const char *string);
void	 		lsm_mathml_variant_set_font_style	(LsmMathmlVariant *variant, LsmMathmlFontStyle style);
void 			lsm_mathml_variant_set_font_weight	(LsmMathmlVariant *variant, LsmMathmlFontWeight weight);

typedef enum {
	LSM_MATHML_FORM_ERROR = -1,
	LSM_MATHML_FORM_PREFIX,
	LSM_MATHML_FORM_POSTFIX,
	LSM_MATHML_FORM_INFIX
} LsmMathmlForm;

const char *		lsm_mathml_form_to_string 			(LsmMathmlForm form);
LsmMathmlForm 		lsm_mathml_form_from_string 		(const char *string);

typedef enum {
	LSM_MATHML_ROW_ALIGN_ERROR = -1,
	LSM_MATHML_ROW_ALIGN_BASELINE,
	LSM_MATHML_ROW_ALIGN_TOP,
	LSM_MATHML_ROW_ALIGN_BOTTOM,
	LSM_MATHML_ROW_ALIGN_CENTER,
	LSM_MATHML_ROW_ALIGN_AXIS
} LsmMathmlRowAlign;

const char *		lsm_mathml_row_align_to_string		(LsmMathmlRowAlign row_align);
LsmMathmlRowAlign		lsm_mathml_row_align_from_string		(const char *string);

typedef enum {
	LSM_MATHML_COLUMN_ALIGN_ERROR = -1,
	LSM_MATHML_COLUMN_ALIGN_CENTER,
	LSM_MATHML_COLUMN_ALIGN_LEFT,
	LSM_MATHML_COLUMN_ALIGN_RIGHT
} LsmMathmlColumnAlign;

const char *		lsm_mathml_column_align_to_string		(LsmMathmlColumnAlign column_align);
LsmMathmlColumnAlign	lsm_mathml_column_align_from_string	(const char *string);

typedef enum {
	LSM_MATHML_LINE_ERROR = -1,
	LSM_MATHML_LINE_NONE,
	LSM_MATHML_LINE_SOLID,
	LSM_MATHML_LINE_DASHED
} LsmMathmlLine;

const char *		lsm_mathml_line_to_string			(LsmMathmlLine line);
LsmMathmlLine		lsm_mathml_line_from_string		(const char *string);

typedef enum {
	LSM_MATHML_SCRIPT_LEVEL_SIGN_ERROR = -1,
	LSM_MATHML_SCRIPT_LEVEL_SIGN_NONE,
	LSM_MATHML_SCRIPT_LEVEL_SIGN_PLUS,
	LSM_MATHML_SCRIPT_LEVEL_SIGN_MINUS
} LsmMathmlScriptLevelSign;

G_END_DECLS

#endif

