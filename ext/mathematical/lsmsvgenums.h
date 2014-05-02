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

#ifndef LSM_SVG_ENUMS_H
#define LSM_SVG_ENUMS_H

#include <glib-object.h>
#include <lsmtypes.h>

G_BEGIN_DECLS

typedef enum {
	LSM_SVG_ANGLE_TYPE_ERROR = -1,
	LSM_SVG_ANGLE_TYPE_AUTO,
	LSM_SVG_ANGLE_TYPE_FIXED
} LsmSvgAngleType;

typedef enum {
	LSM_SVG_BLENDING_MODE_ERROR = -1,
	LSM_SVG_BLENDING_MODE_NORMAL,
	LSM_SVG_BLENDING_MODE_MULTIPLY,
	LSM_SVG_BLENDING_MODE_SCREEN,
	LSM_SVG_BLENDING_MODE_DARKEN,
	LSM_SVG_BLENDING_MODE_LIGHTEN,
	LSM_SVG_BLENDING_MODE_OVER,
	LSM_SVG_BLENDING_MODE_IN,
	LSM_SVG_BLENDING_MODE_OUT,
	LSM_SVG_BLENDING_MODE_ATOP,
	LSM_SVG_BLENDING_MODE_XOR
} LsmSvgBlendingMode;

const char * 		lsm_svg_blending_mode_to_string 	(LsmSvgBlendingMode blending_mode);
LsmSvgBlendingMode	lsm_svg_blending_mode_from_string 	(const char *string);

typedef enum {
	LSM_SVG_ENABLE_BACKGROUND_ERROR = -1,
	LSM_SVG_ENABLE_BACKGROUND_ACCUMULATE,
	LSM_SVG_ENABLE_BACKGROUND_NEW
} LsmSvgEnableBackground;

const char * 		lsm_svg_enable_background_to_string 	(LsmSvgEnableBackground enable_background);
LsmSvgEnableBackground	lsm_svg_enable_background_from_string 	(const char *string);

typedef enum {
	LSM_SVG_PAINT_TYPE_ERROR = -1,
	LSM_SVG_PAINT_TYPE_UNKNOWN = 0,
	LSM_SVG_PAINT_TYPE_RGB_COLOR,
	LSM_SVG_PAINT_TYPE_RGB_COLOR_ICC_COLOR,
	LSM_SVG_PAINT_TYPE_NONE = 101,
	LSM_SVG_PAINT_TYPE_CURRENT_COLOR,
	LSM_SVG_PAINT_TYPE_URI_NONE,
	LSM_SVG_PAINT_TYPE_URI_CURRENT_COLOR,
	LSM_SVG_PAINT_TYPE_URI_RGB_COLOR,
	LSM_SVG_PAINT_TYPE_URI_RGB_COLOR_ICC_COLOR,
	LSM_SVG_PAINT_TYPE_URI
} LsmSvgPaintType;

typedef enum {
	LSM_SVG_LENGTH_DIRECTION_ERROR = -1,
	LSM_SVG_LENGTH_DIRECTION_HORIZONTAL,
	LSM_SVG_LENGTH_DIRECTION_VERTICAL,
	LSM_SVG_LENGTH_DIRECTION_DIAGONAL
} LsmSvgLengthDirection;

typedef enum {
	LSM_SVG_LENGTH_TYPE_ERROR = -1,
	LSM_SVG_LENGTH_TYPE_NUMBER,
	LSM_SVG_LENGTH_TYPE_PERCENTAGE,
	LSM_SVG_LENGTH_TYPE_EMS,
	LSM_SVG_LENGTH_TYPE_EXS,
	LSM_SVG_LENGTH_TYPE_PX,
	LSM_SVG_LENGTH_TYPE_CM,
	LSM_SVG_LENGTH_TYPE_MM,
	LSM_SVG_LENGTH_TYPE_IN,
	LSM_SVG_LENGTH_TYPE_PT,
	LSM_SVG_LENGTH_TYPE_PC
} LsmSvgLengthType;

const char * 		lsm_svg_length_type_to_string 		(LsmSvgLengthType length_type);
LsmSvgLengthType	lsm_svg_length_type_from_string 	(const char *string);

typedef enum {
	LSM_SVG_FILL_RULE_ERROR = -1,
	LSM_SVG_FILL_RULE_NON_ZERO,
	LSM_SVG_FILL_RULE_EVEN_ODD
} LsmSvgFillRule;

const char * 		lsm_svg_fill_rule_to_string 		(LsmSvgFillRule fill_rule);
LsmSvgFillRule 		lsm_svg_fill_rule_from_string 		(const char *string);

typedef enum {
	LSM_SVG_LINE_JOIN_ERROR = -1,
	LSM_SVG_LINE_JOIN_MITER,
	LSM_SVG_LINE_JOIN_ROUND,
	LSM_SVG_LINE_JOIN_BEVEL
} LsmSvgLineJoin;

const char * 		lsm_svg_line_join_to_string 		(LsmSvgLineJoin line_join);
LsmSvgLineJoin 		lsm_svg_line_join_from_string 		(const char *string);

typedef enum {
	LSM_SVG_LINE_CAP_ERROR = -1,
	LSM_SVG_LINE_CAP_BUTT,
	LSM_SVG_LINE_CAP_ROUND,
	LSM_SVG_LINE_CAP_SQUARE
} LsmSvgLineCap;

const char * 		lsm_svg_line_cap_to_string 		(LsmSvgLineCap line_cap);
LsmSvgLineCap		lsm_svg_line_cap_from_string 		(const char *string);

typedef enum {
	LSM_SVG_TRANSFORM_TYPE_ERROR = -1,
	LSM_SVG_TRANSFORM_TYPE_MATRIX,
	LSM_SVG_TRANSFORM_TYPE_TRANSLATE,
	LSM_SVG_TRANSFORM_TYPE_SCALE,
	LSM_SVG_TRANSFORM_TYPE_ROTATE,
	LSM_SVG_TRANSFORM_TYPE_SKEW_X,
	LSM_SVG_TRANSFORM_TYPE_SKEW_Y
} LsmSvgTransformType;

typedef enum {
	LSM_SVG_OVERFLOW_ERROR = -1,
	LSM_SVG_OVERFLOW_VISIBLE,
	LSM_SVG_OVERFLOW_HIDDEN,
	LSM_SVG_OVERFLOW_SCROLL,
	LSM_SVG_OVERFLOW_AUTO
} LsmSvgOverflow;

const char * 		lsm_svg_overflow_to_string 		(LsmSvgOverflow overflow);
LsmSvgOverflow		lsm_svg_overflow_from_string		(const char *string);

typedef enum {
	LSM_SVG_PATTERN_UNITS_ERROR = -1,
	LSM_SVG_PATTERN_UNITS_USER_SPACE_ON_USE,
	LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX
} LsmSvgPatternUnits;

const char * 		lsm_svg_pattern_units_to_string 		(LsmSvgPatternUnits units);
LsmSvgPatternUnits	lsm_svg_pattern_units_from_string		(const char *string);

typedef enum {
	LSM_SVG_MARKER_UNITS_ERROR = -1,
	LSM_SVG_MARKER_UNITS_STROKE_WIDTH,
	LSM_SVG_MARKER_UNITS_USER_SPACE_ON_USE
} LsmSvgMarkerUnits;

const char * 		lsm_svg_marker_units_to_string 			(LsmSvgMarkerUnits units);
LsmSvgMarkerUnits	lsm_svg_marker_units_from_string		(const char *string);

typedef enum {
	LSM_SVG_SPREAD_METHOD_ERROR = -1,
	LSM_SVG_SPREAD_METHOD_PAD,
	LSM_SVG_SPREAD_METHOD_REFLECT,
	LSM_SVG_SPREAD_METHOD_REPEAT
} LsmSvgSpreadMethod;

const char * 		lsm_svg_spread_method_to_string 		(LsmSvgSpreadMethod method);
LsmSvgSpreadMethod	lsm_svg_spread_method_from_string		(const char *string);

typedef enum {
	LSM_SVG_ALIGN_ERROR = -1,
	LSM_SVG_ALIGN_NONE,
	LSM_SVG_ALIGN_X_MIN_Y_MIN,
	LSM_SVG_ALIGN_X_MID_Y_MIN,
	LSM_SVG_ALIGN_X_MAX_Y_MIN,
	LSM_SVG_ALIGN_X_MIN_Y_MID,
	LSM_SVG_ALIGN_X_MID_Y_MID,
	LSM_SVG_ALIGN_X_MAX_Y_MID,
	LSM_SVG_ALIGN_X_MIN_Y_MAX,
	LSM_SVG_ALIGN_X_MID_Y_MAX,
	LSM_SVG_ALIGN_X_MAX_Y_MAX
} LsmSvgAlign;

const char * 		lsm_svg_align_to_string 		(LsmSvgAlign align);
LsmSvgAlign		lsm_svg_align_from_string		(const char *string);

typedef enum {
	LSM_SVG_MEET_OR_SLICE_ERROR = -1,
	LSM_SVG_MEET_OR_SLICE_MEET,
	LSM_SVG_MEET_OR_SLICE_SLICE
} LsmSvgMeetOrSlice;

const char * 		lsm_svg_meet_or_slice_to_string 	(LsmSvgMeetOrSlice meet_or_slice);
LsmSvgMeetOrSlice	lsm_svg_meet_or_slice_from_string	(const char *string);

typedef enum {
	LSM_SVG_COMP_OP_ERROR = -1,
	LSM_SVG_COMP_OP_CLEAR,
	LSM_SVG_COMP_OP_SRC,
	LSM_SVG_COMP_OP_DST,
	LSM_SVG_COMP_OP_SRC_OVER,
	LSM_SVG_COMP_OP_DST_OVER,
	LSM_SVG_COMP_OP_SRC_IN,
	LSM_SVG_COMP_OP_DST_IN,
	LSM_SVG_COMP_OP_SRC_OUT,
	LSM_SVG_COMP_OP_DST_OUT,
	LSM_SVG_COMP_OP_SRC_ATOP,
	LSM_SVG_COMP_OP_DST_ATOP,
	LSM_SVG_COMP_OP_XOR,
	LSM_SVG_COMP_OP_PLUS,
	LSM_SVG_COMP_OP_MULTIPLY,
	LSM_SVG_COMP_OP_SCREEN,
	LSM_SVG_COMP_OP_OVERLAY,
	LSM_SVG_COMP_OP_DARKEN,
	LSM_SVG_COMP_OP_LIGHTEN,
	LSM_SVG_COMP_OP_COLOR_DODGE,
	LSM_SVG_COMP_OP_COLOR_BURN,
	LSM_SVG_COMP_OP_HARD_LIGHT,
	LSM_SVG_COMP_OP_SOFT_LIGHT,
	LSM_SVG_COMP_OP_DIFFERENCE,
	LSM_SVG_COMP_OP_EXCLUSION
} LsmSvgCompOp;

const char * 		lsm_svg_comp_op_to_string 	(LsmSvgCompOp comp_op);
LsmSvgCompOp		lsm_svg_comp_op_from_string	(const char *string);

typedef enum {
	LSM_SVG_FONT_STRETCH_ERROR = -1,
	LSM_SVG_FONT_STRETCH_NORMAL,
	LSM_SVG_FONT_STRETCH_ULTRA_CONDENSED,
	LSM_SVG_FONT_STRETCH_EXTRA_CONDENSED,
	LSM_SVG_FONT_STRETCH_CONDENSED,
	LSM_SVG_FONT_STRETCH_SEMI_CONDENSED,
	LSM_SVG_FONT_STRETCH_SEMI_EXPANDED,
	LSM_SVG_FONT_STRETCH_EXPANDED,
	LSM_SVG_FONT_STRETCH_EXTRA_EXPANDED,
	LSM_SVG_FONT_STRETCH_ULTRA_EXPANDED
} LsmSvgFontStretch;

const char * 		lsm_svg_font_stretch_to_string 		(LsmSvgFontStretch font_stretch);
LsmSvgFontStretch	lsm_svg_font_stretch_from_string	(const char *string);

typedef enum {
	LSM_SVG_FONT_STYLE_ERROR = -1,
	LSM_SVG_FONT_STYLE_NORMAL,
	LSM_SVG_FONT_STYLE_OBLIQUE,
	LSM_SVG_FONT_STYLE_ITALIC
} LsmSvgFontStyle;

const char * 		lsm_svg_font_style_to_string 		(LsmSvgFontStyle font_style);
LsmSvgFontStyle		lsm_svg_font_style_from_string		(const char *string);

typedef enum {
	LSM_SVG_FONT_WEIGHT_ERROR = -1,
	LSM_SVG_FONT_WEIGHT_NORMAL = 400,
	LSM_SVG_FONT_WEIGHT_BOLD = 700
} LsmSvgFontWeight;

const char * 		lsm_svg_font_weight_to_string 	(LsmSvgFontWeight font_weight);
LsmSvgFontWeight	lsm_svg_font_weight_from_string	(const char *string);

typedef enum {
	LSM_SVG_TEXT_ANCHOR_ERROR = -1,
	LSM_SVG_TEXT_ANCHOR_START,
	LSM_SVG_TEXT_ANCHOR_MIDDLE,
	LSM_SVG_TEXT_ANCHOR_END
} LsmSvgTextAnchor;

const char * 		lsm_svg_text_anchor_to_string 		(LsmSvgTextAnchor text_anchor);
LsmSvgTextAnchor	lsm_svg_text_anchor_from_string		(const char *string);

typedef enum {
	LSM_SVG_FILTER_INPUT_ERROR = -1,
	LSM_SVG_FILTER_INPUT_SOURCE_GRAPHIC,
	LSM_SVG_FILTER_INPUT_SOURCE_ALPHA,
	LSM_SVG_FILTER_INPUT_BACKGROUND_IMAGE,
	LSM_SVG_FILTER_INPUT_BACKGROUND_ALPHA,
	LSM_SVG_FILTER_INPUT_FILL_PAINT,
	LSM_SVG_FILTER_INPUT_STROKE_PAINT
} LsmSvgFilterInput;

typedef enum {
	LSM_SVG_DISPLAY_ERROR = -1,
	LSM_SVG_DISPLAY_NONE,
	LSM_SVG_DISPLAY_INLINE,
	LSM_SVG_DISPLAY_BLOCK,
	LSM_SVG_DISPLAY_LIST_ITEM,
	LSM_SVG_DISPLAY_RUN_IN,
	LSM_SVG_DISPLAY_COMPACT,
	LSM_SVG_DISPLAY_MARKER,
	LSM_SVG_DISPLAY_TABLE,
	LSM_SVG_DISPLAY_INLINE_TABLE,
	LSM_SVG_DISPLAY_TABLE_ROW_GROUP,
	LSM_SVG_DISPLAY_TABLE_HEADER_GROUP,
	LSM_SVG_DISPLAY_TABLE_FOOTER_GROUP,
	LSM_SVG_DISPLAY_TABLE_ROW,
	LSM_SVG_DISPLAY_TABLE_COLUMN_GROUP,
	LSM_SVG_DISPLAY_TABLE_COLUMN,
	LSM_SVG_DISPLAY_TABLE_CELL,
	LSM_SVG_DISPLAY_TABLE_CAPTION
} LsmSvgDisplay;

const char * 		lsm_svg_display_to_string 		(LsmSvgDisplay display);
LsmSvgDisplay		lsm_svg_display_from_string		(const char *string);

typedef enum {
	LSM_SVG_VISIBILITY_ERROR = -1,
	LSM_SVG_VISIBILITY_VISIBLE,
	LSM_SVG_VISIBILITY_HIDDEN,
	LSM_SVG_VISIBILITY_COLLAPSE
} LsmSvgVisibility;

const char * 		lsm_svg_visibility_to_string 		(LsmSvgVisibility visibility);
LsmSvgVisibility	lsm_svg_visibility_from_string		(const char *string);

typedef enum {
	LSM_SVG_ELEMENT_CATEGORY_NONE			= 1 << 0,
	LSM_SVG_ELEMENT_CATEGORY_DESCRIPTIVE		= 1 << 1,
	LSM_SVG_ELEMENT_CATEGORY_CONTAINER		= 1 << 2,
	LSM_SVG_ELEMENT_CATEGORY_STRUCTURAL		= 1 << 3,
	LSM_SVG_ELEMENT_CATEGORY_GRAPHICS_REFERENCING	= 1 << 4,
	LSM_SVG_ELEMENT_CATEGORY_GRAPHICS		= 1 << 5,
	LSM_SVG_ELEMENT_CATEGORY_SHAPE			= 1 << 6,
	LSM_SVG_ELEMENT_CATEGORY_BASIC_SHAPE		= 1 << 7,
	LSM_SVG_ELEMENT_CATEGORY_TEXT_CONTENT		= 1 << 8,
	LSM_SVG_ELEMENT_CATEGORY_TEXT_CONTENT_CHILD	= 1 << 9,
	LSM_SVG_ELEMENT_CATEGORY_GRADIENT		= 1 << 10,
	LSM_SVG_ELEMENT_CATEGORY_FILTER_PRIMITIVE	= 1 << 11,
	LSM_SVG_ELEMENT_CATEGORY_ANIMATION		= 1 << 12
} LsmSvgElementCategory;

typedef enum {
	LSM_SVG_WRITING_MODE_ERROR = -1,
	LSM_SVG_WRITING_MODE_LR_TB,
	LSM_SVG_WRITING_MODE_RL_TB,
	LSM_SVG_WRITING_MODE_TB_RL,
	LSM_SVG_WRITING_MODE_LR,
	LSM_SVG_WRITING_MODE_RL,
	LSM_SVG_WRITING_MODE_TB
} LsmSvgWritingMode;

const char * 		lsm_svg_writing_mode_to_string 		(LsmSvgWritingMode writing_mode);
LsmSvgWritingMode	lsm_svg_writing_mode_from_string	(const char *string);

G_END_DECLS

#endif
