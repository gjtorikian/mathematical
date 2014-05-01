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

#include <lsmmathmlenums.h>
#include <lsmtraits.h>
#include <string.h>

static const char *lsm_mathml_mode_strings[] = {
	"display",
	"inline"
};

const char *
lsm_mathml_mode_to_string (LsmMathmlMode mode)
{
	if (mode < 0 || mode > LSM_MATHML_MODE_INLINE)
		return NULL;

	return lsm_mathml_mode_strings[mode];
}

LsmMathmlMode
lsm_mathml_mode_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_mathml_mode_strings,
					   G_N_ELEMENTS (lsm_mathml_mode_strings));
}

static const char *lsm_mathml_display_strings[] = {
	"block",
	"inline"
};

const char *
lsm_mathml_display_to_string (LsmMathmlDisplay display)
{
	if (display < 0 || display > LSM_MATHML_DISPLAY_INLINE)
		return NULL;

	return lsm_mathml_display_strings[display];
}

LsmMathmlDisplay
lsm_mathml_display_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_mathml_display_strings,
					   G_N_ELEMENTS (lsm_mathml_display_strings));
}

static const char *lsm_mathml_space_name_strings[] = {
	"veryverythinmathspace",
	"verythinmathspace",
	"thinmathspace",
	"mediummathspace",
	"thickmathspace",
	"verythickmathspace",
	"veryverythickmathspace",
	"infinity"
};

const char *
lsm_mathml_space_name_to_string (LsmMathmlSpaceName space_name)
{
	if (space_name < 0 || space_name > LSM_MATHML_SPACE_NAME_INFINITY)
		return NULL;

	return lsm_mathml_space_name_strings[space_name];
}

LsmMathmlSpaceName
lsm_mathml_space_name_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_mathml_space_name_strings,
					   G_N_ELEMENTS (lsm_mathml_space_name_strings));
}

static const char *lsm_mathml_unit_strings[] = {
	"",
	"em",
	"ex",
	"in",
	"cm",
	"mm",
	"pt",
	"px",
	"pc",
	"%"
};

const char *
lsm_mathml_unit_to_string (LsmMathmlUnit unit)
{
	if (unit < 0 || unit > LSM_MATHML_UNIT_PERCENT)
		return NULL;

	return lsm_mathml_unit_strings[unit];
}

LsmMathmlUnit
lsm_mathml_unit_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_mathml_unit_strings,
					   G_N_ELEMENTS (lsm_mathml_unit_strings));
}

static const char *lsm_mathml_font_style_strings[] = {
	"normal",
	"italic"
};

const char *
lsm_mathml_font_style_to_string (LsmMathmlFontStyle font_style)
{
	if (font_style < 0 || font_style > LSM_MATHML_FONT_STYLE_ITALIC)
		return NULL;

	return lsm_mathml_font_style_strings[font_style];
}

LsmMathmlFontStyle
lsm_mathml_font_style_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_mathml_font_style_strings,
					   G_N_ELEMENTS (lsm_mathml_font_style_strings));
}

static const char *lsm_mathml_font_weight_strings[] = {
	"normal",
	"bold"
};

const char *
lsm_mathml_font_weight_to_string (LsmMathmlFontWeight font_weight)
{
	if (font_weight < 0 || font_weight > LSM_MATHML_FONT_WEIGHT_BOLD)
		return NULL;

	return lsm_mathml_font_weight_strings[font_weight];
}

LsmMathmlFontWeight
lsm_mathml_font_weight_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_mathml_font_weight_strings,
					   G_N_ELEMENTS (lsm_mathml_font_weight_strings));
}

static const char *lsm_mathml_variant_strings[] = {
	"normal",
	"bold",
	"italic",
	"bold-italic",
	"double-struck",
	"bold-fraktur",
	"script",
	"bold-script",
	"fraktur",
	"sans-serif",
	"bold-sans-serif",
	"sans-serif-italic",
	"sans-serif-bold-italic",
	"monospace"
};

const char *
lsm_mathml_variant_to_string (LsmMathmlVariant variant)
{
	if (variant < 0 || variant > LSM_MATHML_VARIANT_MONOSPACE)
		return NULL;

	return lsm_mathml_variant_strings[variant];
}

LsmMathmlVariant
lsm_mathml_variant_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_mathml_variant_strings,
					   G_N_ELEMENTS (lsm_mathml_variant_strings));
}

void
lsm_mathml_variant_set_font_style (LsmMathmlVariant *variant, LsmMathmlFontStyle style)
{
	if (variant == NULL)
		return;

	switch (style) {
		case LSM_MATHML_FONT_STYLE_ITALIC:
			switch (*variant) {
				case LSM_MATHML_VARIANT_NORMAL:
					*variant = LSM_MATHML_VARIANT_ITALIC;
					return;
				case LSM_MATHML_VARIANT_BOLD:
					*variant = LSM_MATHML_VARIANT_BOLD_ITALIC;
					return;
				case LSM_MATHML_VARIANT_SANS_SERIF:
					*variant = LSM_MATHML_VARIANT_SANS_SERIF_ITALIC;
					return;
				case LSM_MATHML_VARIANT_SANS_SERIF_BOLD:
					*variant = LSM_MATHML_VARIANT_SANS_SERIF_BOLD_ITALIC;
					return;
				case LSM_MATHML_VARIANT_ITALIC:
				case LSM_MATHML_VARIANT_BOLD_ITALIC:
				case LSM_MATHML_VARIANT_DOUBLE_STRUCK:
				case LSM_MATHML_VARIANT_FRAKTUR_BOLD:
				case LSM_MATHML_VARIANT_SCRIPT:
				case LSM_MATHML_VARIANT_SCRIPT_BOLD:
				case LSM_MATHML_VARIANT_FRAKTUR:
				case LSM_MATHML_VARIANT_SANS_SERIF_ITALIC:
				case LSM_MATHML_VARIANT_SANS_SERIF_BOLD_ITALIC:
				case LSM_MATHML_VARIANT_MONOSPACE:
				case LSM_MATHML_VARIANT_ERROR:
					return;
			}
		case LSM_MATHML_FONT_WEIGHT_NORMAL:
			switch (*variant) {
				case LSM_MATHML_VARIANT_ITALIC:
					*variant = LSM_MATHML_VARIANT_NORMAL;
					return;
				case LSM_MATHML_VARIANT_BOLD_ITALIC:
					*variant = LSM_MATHML_VARIANT_BOLD;
					return;
				case LSM_MATHML_VARIANT_SANS_SERIF_ITALIC:
					*variant = LSM_MATHML_VARIANT_SANS_SERIF;
					return;
				case LSM_MATHML_VARIANT_SANS_SERIF_BOLD_ITALIC:
					*variant = LSM_MATHML_VARIANT_SANS_SERIF_BOLD;
					return;
				case LSM_MATHML_VARIANT_BOLD:
				case LSM_MATHML_VARIANT_NORMAL:
				case LSM_MATHML_VARIANT_SANS_SERIF:
				case LSM_MATHML_VARIANT_SANS_SERIF_BOLD:
				case LSM_MATHML_VARIANT_DOUBLE_STRUCK:
				case LSM_MATHML_VARIANT_FRAKTUR_BOLD:
				case LSM_MATHML_VARIANT_SCRIPT:
				case LSM_MATHML_VARIANT_SCRIPT_BOLD:
				case LSM_MATHML_VARIANT_FRAKTUR:
				case LSM_MATHML_VARIANT_MONOSPACE:
				case LSM_MATHML_VARIANT_ERROR:
					return;
			}
		default:
			return;
	}
}

void
lsm_mathml_variant_set_font_weight (LsmMathmlVariant *variant, LsmMathmlFontWeight weight)
{
	if (variant == NULL)
		return;

	switch (weight) {
		case LSM_MATHML_FONT_WEIGHT_BOLD:
			switch (*variant) {
				case LSM_MATHML_VARIANT_NORMAL:
					*variant = LSM_MATHML_VARIANT_BOLD;
					return;
				case LSM_MATHML_VARIANT_ITALIC:
					*variant = LSM_MATHML_VARIANT_BOLD_ITALIC;
					return;
				case LSM_MATHML_VARIANT_SANS_SERIF:
					*variant = LSM_MATHML_VARIANT_SANS_SERIF_BOLD;
					return;
				case LSM_MATHML_VARIANT_SANS_SERIF_ITALIC:
					*variant = LSM_MATHML_VARIANT_SANS_SERIF_BOLD_ITALIC;
					return;
				case LSM_MATHML_VARIANT_SCRIPT:
					*variant = LSM_MATHML_VARIANT_SCRIPT_BOLD;
					return;
				case LSM_MATHML_VARIANT_FRAKTUR:
					*variant = LSM_MATHML_VARIANT_FRAKTUR_BOLD;
					return;
				case LSM_MATHML_VARIANT_BOLD:
				case LSM_MATHML_VARIANT_BOLD_ITALIC:
				case LSM_MATHML_VARIANT_DOUBLE_STRUCK:
				case LSM_MATHML_VARIANT_FRAKTUR_BOLD:
				case LSM_MATHML_VARIANT_SCRIPT_BOLD:
				case LSM_MATHML_VARIANT_SANS_SERIF_BOLD:
				case LSM_MATHML_VARIANT_SANS_SERIF_BOLD_ITALIC:
				case LSM_MATHML_VARIANT_MONOSPACE:
				case LSM_MATHML_VARIANT_ERROR:
					return;
			}
		case LSM_MATHML_FONT_WEIGHT_NORMAL:
			switch (*variant) {
				case LSM_MATHML_VARIANT_BOLD:
					*variant = LSM_MATHML_VARIANT_NORMAL;
					return;
				case LSM_MATHML_VARIANT_BOLD_ITALIC:
					*variant = LSM_MATHML_VARIANT_ITALIC;
					return;
				case LSM_MATHML_VARIANT_SANS_SERIF_BOLD:
					*variant = LSM_MATHML_VARIANT_SANS_SERIF;
					return;
				case LSM_MATHML_VARIANT_SANS_SERIF_BOLD_ITALIC:
					*variant = LSM_MATHML_VARIANT_SANS_SERIF_ITALIC;
					return;
				case LSM_MATHML_VARIANT_FRAKTUR_BOLD:
					*variant = LSM_MATHML_VARIANT_FRAKTUR;
					return;
				case LSM_MATHML_VARIANT_SCRIPT_BOLD:
					*variant = LSM_MATHML_VARIANT_SCRIPT;
					return;
				case LSM_MATHML_VARIANT_ITALIC:
				case LSM_MATHML_VARIANT_NORMAL:
				case LSM_MATHML_VARIANT_SANS_SERIF:
				case LSM_MATHML_VARIANT_SANS_SERIF_ITALIC:
				case LSM_MATHML_VARIANT_DOUBLE_STRUCK:
				case LSM_MATHML_VARIANT_SCRIPT:
				case LSM_MATHML_VARIANT_FRAKTUR:
				case LSM_MATHML_VARIANT_MONOSPACE:
				case LSM_MATHML_VARIANT_ERROR:
					return;
			}
		default:
			return;
	}
}

static const char *lsm_mathml_form_strings[] = {
	"prefix",
	"postfix",
	"infix"
};

const char *
lsm_mathml_form_to_string (LsmMathmlForm form)
{
	if (form < 0 || form > LSM_MATHML_FORM_INFIX)
		return NULL;

	return lsm_mathml_form_strings[form];
}

LsmMathmlForm
lsm_mathml_form_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_mathml_form_strings,
					   G_N_ELEMENTS (lsm_mathml_form_strings));
}

static const char *lsm_mathml_row_align_strings[] = {
	"baseline",
	"top",
	"bottom",
	"center",
	"axis"
};

const char *
lsm_mathml_row_align_to_string (LsmMathmlRowAlign row_align)
{
	if (row_align < 0 || row_align > LSM_MATHML_ROW_ALIGN_AXIS)
		return NULL;

	return lsm_mathml_row_align_strings[row_align];
}

LsmMathmlRowAlign
lsm_mathml_row_align_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_mathml_row_align_strings,
					   G_N_ELEMENTS (lsm_mathml_row_align_strings));
}

static const char *lsm_mathml_column_align_strings[] = {
	"center",
	"left",
	"right"
};

const char *
lsm_mathml_column_align_to_string (LsmMathmlColumnAlign column_align)
{
	if (column_align < 0 || column_align > LSM_MATHML_COLUMN_ALIGN_RIGHT)
		return NULL;

	return lsm_mathml_column_align_strings[column_align];
}

LsmMathmlColumnAlign
lsm_mathml_column_align_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_mathml_column_align_strings,
					   G_N_ELEMENTS (lsm_mathml_column_align_strings));
}

static const char *lsm_mathml_line_strings[] = {
	"none",
	"solid",
	"dashed"
};

const char *
lsm_mathml_line_to_string (LsmMathmlLine line)
{
	if (line < 0 || line > LSM_MATHML_LINE_DASHED)
		return NULL;

	return lsm_mathml_line_strings [line];
}

LsmMathmlLine
lsm_mathml_line_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_mathml_line_strings,
					   G_N_ELEMENTS (lsm_mathml_line_strings));
}
