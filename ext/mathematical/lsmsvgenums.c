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

#include <lsmsvgenums.h>
#include <lsmtraits.h>
#include <string.h>

static const char *lsm_svg_blending_mode_strings[] = {
	"normal",
	"multiply",
	"screen",
	"darken",
	"lighten",
	"over",
	"in",
	"out",
	"atop",
	"xor"
};

const char *
lsm_svg_blending_mode_to_string (LsmSvgBlendingMode blending_mode)
{
	if (blending_mode < 0 || blending_mode > LSM_SVG_BLENDING_MODE_XOR)
		return NULL;

	return lsm_svg_blending_mode_strings[blending_mode];
}

LsmSvgBlendingMode
lsm_svg_blending_mode_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_blending_mode_strings,
					   G_N_ELEMENTS (lsm_svg_blending_mode_strings));
}

static const char *lsm_svg_enable_background_strings[] = {
	"accumulate",
	"new"
};

const char *
lsm_svg_enable_background_to_string (LsmSvgEnableBackground enable_background)
{
	if (enable_background < 0 || enable_background > LSM_SVG_ENABLE_BACKGROUND_NEW)
		return NULL;

	return lsm_svg_enable_background_strings[enable_background];
}

LsmSvgEnableBackground
lsm_svg_enable_background_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_enable_background_strings,
					   G_N_ELEMENTS (lsm_svg_enable_background_strings));
}

static const char *lsm_svg_length_type_strings[] = {
	"",
	"%",
	"em",
	"ex",
	"px",
	"cm",
	"mm",
	"in",
	"pt",
	"pc"
};

const char *
lsm_svg_length_type_to_string (LsmSvgLengthType length_type)
{
	if (length_type < 0 || length_type > LSM_SVG_LENGTH_TYPE_PC)
		return NULL;

	return lsm_svg_length_type_strings[length_type];
}

LsmSvgLengthType
lsm_svg_length_type_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_length_type_strings,
					   G_N_ELEMENTS (lsm_svg_length_type_strings));
}

static const char *lsm_svg_fill_rule_strings[] = {
	"nonzero",
	"evenodd"
};

const char *
lsm_svg_fill_rule_to_string (LsmSvgFillRule fill_rule)
{
	if (fill_rule < 0 || fill_rule > LSM_SVG_FILL_RULE_EVEN_ODD)
		return NULL;

	return lsm_svg_fill_rule_strings[fill_rule];
}

LsmSvgFillRule
lsm_svg_fill_rule_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_fill_rule_strings,
					   G_N_ELEMENTS (lsm_svg_fill_rule_strings));
}

static const char *lsm_svg_line_join_strings[] = {
	"miter",
	"round",
	"bevel"
};

const char *
lsm_svg_line_join_to_string (LsmSvgLineJoin line_join)
{
	if (line_join < 0 || line_join > LSM_SVG_LINE_JOIN_BEVEL)
		return NULL;

	return lsm_svg_line_join_strings[line_join];
}

LsmSvgLineJoin
lsm_svg_line_join_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_line_join_strings,
					   G_N_ELEMENTS (lsm_svg_line_join_strings));
}

static const char *lsm_svg_line_cap_strings[] = {
	"butt",
	"round",
	"square"
};

const char *
lsm_svg_line_cap_to_string (LsmSvgLineCap line_cap)
{
	if (line_cap < 0 || line_cap > LSM_SVG_LINE_CAP_SQUARE)
		return NULL;

	return lsm_svg_line_cap_strings[line_cap];
}

LsmSvgLineCap
lsm_svg_line_cap_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_line_cap_strings,
					   G_N_ELEMENTS (lsm_svg_line_cap_strings));
}

static const char *lsm_svg_overflow_strings[] = {
	"visible",
	"hidden",
	"scroll",
	"auto"
};

const char *
lsm_svg_overflow_to_string (LsmSvgOverflow overflow)
{
	if (overflow < 0 || overflow > LSM_SVG_OVERFLOW_AUTO)
		return NULL;

	return lsm_svg_overflow_strings[overflow];
}

LsmSvgOverflow
lsm_svg_overflow_from_string (const char *string)
{
	LsmSvgOverflow overflow = lsm_enum_value_from_string (string, lsm_svg_overflow_strings,
							      G_N_ELEMENTS (lsm_svg_overflow_strings));

	return overflow;
}

static const char *lsm_svg_pattern_units_strings[] = {
	"userSpaceOnUse",
	"objectBoundingBox"
};

const char *
lsm_svg_pattern_units_to_string (LsmSvgPatternUnits units)
{
	if (units < 0 || units > LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX)
		return NULL;

	return lsm_svg_pattern_units_strings[units];
}

LsmSvgPatternUnits
lsm_svg_pattern_units_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_pattern_units_strings,
					   G_N_ELEMENTS (lsm_svg_pattern_units_strings));
}

static const char *lsm_svg_marker_units_strings[] = {
	"strokeWidth",
	"userSpaceOnUse"
};

const char *
lsm_svg_marker_units_to_string (LsmSvgMarkerUnits units)
{
	if (units < 0 || units > LSM_SVG_MARKER_UNITS_STROKE_WIDTH)
		return NULL;

	return lsm_svg_marker_units_strings[units];
}

LsmSvgMarkerUnits
lsm_svg_marker_units_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_marker_units_strings,
					   G_N_ELEMENTS (lsm_svg_marker_units_strings));
}

static const char *lsm_svg_spread_method_strings[] = {
	"pad",
	"reflect",
	"repeat"
};

const char *
lsm_svg_spread_method_to_string (LsmSvgSpreadMethod units)
{
	if (units < 0 || units > LSM_SVG_SPREAD_METHOD_REPEAT)
		return NULL;

	return lsm_svg_spread_method_strings[units];
}

LsmSvgSpreadMethod
lsm_svg_spread_method_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_spread_method_strings,
					 G_N_ELEMENTS (lsm_svg_spread_method_strings));
}

static const char *lsm_svg_align_strings[] = {
	"none",
	"xMinYMin",
	"xMidYMin",
	"xMaxYMin",
	"xMinYMid",
	"xMidYMid",
	"xMaxYMid",
	"xMinYMax",
	"xMidYMax",
	"xMaxYMax"
};

const char *
lsm_svg_align_to_string (LsmSvgAlign align)
{
	if (align < 0 || align > LSM_SVG_ALIGN_X_MAX_Y_MAX)
		return NULL;

	return lsm_svg_align_strings[align];
}

LsmSvgAlign
lsm_svg_align_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_align_strings,
					   G_N_ELEMENTS (lsm_svg_align_strings));
}

static const char *lsm_svg_meet_or_slice_strings[] = {
	"meet",
	"slice"
};

const char *
lsm_svg_meet_or_slice_to_string (LsmSvgMeetOrSlice meet_or_slice)
{
	if (meet_or_slice < 0 || meet_or_slice > LSM_SVG_MEET_OR_SLICE_SLICE)
		return NULL;

	return lsm_svg_meet_or_slice_strings[meet_or_slice];
}

LsmSvgMeetOrSlice
lsm_svg_meet_or_slice_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_meet_or_slice_strings,
					  G_N_ELEMENTS (lsm_svg_meet_or_slice_strings));
}

static const char *lsm_svg_comp_op_strings[] = {
	"clear",
	"src",
	"dst",
	"src-over",
	"dst-over",
	"src-in",
	"dst-in",
	"src-out",
	"dst-out",
	"src-atop",
	"dst-atop",
	"xor",
	"plus",
	"multiply",
	"screen",
	"overlay",
	"darken",
	"lighten",
	"color-dodge",
	"color-burn",
	"hard-light",
	"soft-light",
	"difference",
	"exclusion"
};

const char *
lsm_svg_comp_op_to_string (LsmSvgCompOp comp_op)
{
	if (comp_op < 0 || comp_op > LSM_SVG_COMP_OP_EXCLUSION)
		return NULL;

	return lsm_svg_comp_op_strings[comp_op];
}

LsmSvgCompOp
lsm_svg_comp_op_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_comp_op_strings,
					  G_N_ELEMENTS (lsm_svg_comp_op_strings));
}

static const char *lsm_svg_font_stretch_strings[] = {
	"normal",
	"ultra-condensed",
	"extra-condensed",
	"condensed",
	"semi-condensed",
	"semi-expanded",
	"expanded",
	"extra-expanded",
	"ultra-expanded"
};

const char *
lsm_svg_font_stretch_to_string (LsmSvgFontStretch font_stretch)
{
	if (font_stretch < 0 || font_stretch > LSM_SVG_FONT_STRETCH_ULTRA_EXPANDED)
		return NULL;

	return lsm_svg_font_stretch_strings[font_stretch];
}

LsmSvgFontStretch
lsm_svg_font_stretch_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_font_stretch_strings,
					  G_N_ELEMENTS (lsm_svg_font_stretch_strings));
}

static const char *lsm_svg_font_style_strings[] = {
	"normal",
	"oblique",
	"italic"
};

const char *
lsm_svg_font_style_to_string (LsmSvgFontStyle font_style)
{
	if (font_style < 0 || font_style > LSM_SVG_FONT_STYLE_ITALIC)
		return NULL;

	return lsm_svg_font_style_strings[font_style];
}

LsmSvgFontStyle
lsm_svg_font_style_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_font_style_strings,
					  G_N_ELEMENTS (lsm_svg_font_style_strings));
}

static const char *lsm_svg_font_weight_strings[] = {
	"normal",
	"bold"
};

const char *
lsm_svg_font_weight_to_string (LsmSvgFontWeight font_weight)
{
	switch (font_weight) {
		case LSM_SVG_FONT_WEIGHT_NORMAL:
			return lsm_svg_font_weight_strings[0];
		case LSM_SVG_FONT_WEIGHT_BOLD:
			return lsm_svg_font_weight_strings[1];
		default:
			return NULL;
	}
}

LsmSvgFontWeight
lsm_svg_font_weight_from_string (const char *string)
{
	int index;

	index = lsm_enum_value_from_string (string, lsm_svg_font_weight_strings,
					   G_N_ELEMENTS (lsm_svg_font_weight_strings));

	switch (index) {
		case 0:
			return LSM_SVG_FONT_WEIGHT_NORMAL;
		case 1:
			return LSM_SVG_FONT_WEIGHT_BOLD;
		default:
			return -1;
	}
}

static const char *lsm_svg_text_anchor_strings[] = {
	"start",
	"middle",
	"end"
};

const char *
lsm_svg_text_anchor_to_string (LsmSvgTextAnchor text_anchor)
{
	if (text_anchor < 0 || text_anchor > LSM_SVG_TEXT_ANCHOR_MIDDLE)
		return NULL;

	return lsm_svg_text_anchor_strings[text_anchor];
}

LsmSvgTextAnchor
lsm_svg_text_anchor_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_text_anchor_strings,
					   G_N_ELEMENTS (lsm_svg_text_anchor_strings));
}

static const char *lsm_svg_display_strings[] = {
	"none",
	"inline",
	"block",
	"list-item",
	"run-in",
	"compact",
	"marker",
	"table",
	"inline-table",
	"table-row-group",
	"table-header-group",
	"table-footer-group",
	"table-row",
	"table-column-group",
	"table-column",
	"table-cell",
	"table-caption",
};

const char *
lsm_svg_display_to_string (LsmSvgDisplay display)
{
	if (display < 0 || display > LSM_SVG_DISPLAY_TABLE_CAPTION)
		return NULL;

	return lsm_svg_display_strings[display];
}

LsmSvgDisplay
lsm_svg_display_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_display_strings,
					   G_N_ELEMENTS (lsm_svg_display_strings));
}

static const char *lsm_svg_visibility_strings[] = {
	"visible",
	"hidden",
	"collapse"
};

const char *
lsm_svg_visibility_to_string (LsmSvgVisibility visibility)
{
	if (visibility < 0 || visibility > LSM_SVG_VISIBILITY_HIDDEN)
		return NULL;

	return lsm_svg_visibility_strings[visibility];
}

LsmSvgVisibility
lsm_svg_visibility_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_visibility_strings,
					   G_N_ELEMENTS (lsm_svg_visibility_strings));
}

static const char *lsm_svg_writing_mode_strings[] = {
	"lr-tb",
	"rl-tb",
	"tb-rl",
	"lr",
	"rl",
	"tb"
};

const char *
lsm_svg_writing_mode_to_string (LsmSvgWritingMode writing_mode)
{
	if (writing_mode < 0 || writing_mode > LSM_SVG_WRITING_MODE_TB)
		return NULL;

	return lsm_svg_writing_mode_strings[writing_mode];
}

LsmSvgWritingMode
lsm_svg_writing_mode_from_string (const char *string)
{
	return lsm_enum_value_from_string (string, lsm_svg_writing_mode_strings,
					   G_N_ELEMENTS (lsm_svg_writing_mode_strings));
}

