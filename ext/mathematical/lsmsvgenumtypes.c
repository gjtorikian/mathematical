
/* Generated data (by glib-mkenums) */

#include "lsmsvgenumtypes.h"

/* enumerations from "lsmsvgenums.h" */
#include "lsmsvgenums.h"

GType
lsm_svg_angle_type_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_ANGLE_TYPE_ERROR,
			  "LSM_SVG_ANGLE_TYPE_ERROR",
			  "error" },
			{ LSM_SVG_ANGLE_TYPE_AUTO,
			  "LSM_SVG_ANGLE_TYPE_AUTO",
			  "auto" },
			{ LSM_SVG_ANGLE_TYPE_FIXED,
			  "LSM_SVG_ANGLE_TYPE_FIXED",
			  "fixed" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgAngleType"),
				values);
	}
	return the_type;
}

GType
lsm_svg_blending_mode_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_BLENDING_MODE_ERROR,
			  "LSM_SVG_BLENDING_MODE_ERROR",
			  "error" },
			{ LSM_SVG_BLENDING_MODE_NORMAL,
			  "LSM_SVG_BLENDING_MODE_NORMAL",
			  "normal" },
			{ LSM_SVG_BLENDING_MODE_MULTIPLY,
			  "LSM_SVG_BLENDING_MODE_MULTIPLY",
			  "multiply" },
			{ LSM_SVG_BLENDING_MODE_SCREEN,
			  "LSM_SVG_BLENDING_MODE_SCREEN",
			  "screen" },
			{ LSM_SVG_BLENDING_MODE_DARKEN,
			  "LSM_SVG_BLENDING_MODE_DARKEN",
			  "darken" },
			{ LSM_SVG_BLENDING_MODE_LIGHTEN,
			  "LSM_SVG_BLENDING_MODE_LIGHTEN",
			  "lighten" },
			{ LSM_SVG_BLENDING_MODE_OVER,
			  "LSM_SVG_BLENDING_MODE_OVER",
			  "over" },
			{ LSM_SVG_BLENDING_MODE_IN,
			  "LSM_SVG_BLENDING_MODE_IN",
			  "in" },
			{ LSM_SVG_BLENDING_MODE_OUT,
			  "LSM_SVG_BLENDING_MODE_OUT",
			  "out" },
			{ LSM_SVG_BLENDING_MODE_ATOP,
			  "LSM_SVG_BLENDING_MODE_ATOP",
			  "atop" },
			{ LSM_SVG_BLENDING_MODE_XOR,
			  "LSM_SVG_BLENDING_MODE_XOR",
			  "xor" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgBlendingMode"),
				values);
	}
	return the_type;
}

GType
lsm_svg_enable_background_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_ENABLE_BACKGROUND_ERROR,
			  "LSM_SVG_ENABLE_BACKGROUND_ERROR",
			  "error" },
			{ LSM_SVG_ENABLE_BACKGROUND_ACCUMULATE,
			  "LSM_SVG_ENABLE_BACKGROUND_ACCUMULATE",
			  "accumulate" },
			{ LSM_SVG_ENABLE_BACKGROUND_NEW,
			  "LSM_SVG_ENABLE_BACKGROUND_NEW",
			  "new" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgEnableBackground"),
				values);
	}
	return the_type;
}

GType
lsm_svg_paint_type_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_PAINT_TYPE_ERROR,
			  "LSM_SVG_PAINT_TYPE_ERROR",
			  "error" },
			{ LSM_SVG_PAINT_TYPE_UNKNOWN,
			  "LSM_SVG_PAINT_TYPE_UNKNOWN",
			  "unknown" },
			{ LSM_SVG_PAINT_TYPE_RGB_COLOR,
			  "LSM_SVG_PAINT_TYPE_RGB_COLOR",
			  "rgb-color" },
			{ LSM_SVG_PAINT_TYPE_RGB_COLOR_ICC_COLOR,
			  "LSM_SVG_PAINT_TYPE_RGB_COLOR_ICC_COLOR",
			  "rgb-color-icc-color" },
			{ LSM_SVG_PAINT_TYPE_NONE,
			  "LSM_SVG_PAINT_TYPE_NONE",
			  "none" },
			{ LSM_SVG_PAINT_TYPE_CURRENT_COLOR,
			  "LSM_SVG_PAINT_TYPE_CURRENT_COLOR",
			  "current-color" },
			{ LSM_SVG_PAINT_TYPE_URI_NONE,
			  "LSM_SVG_PAINT_TYPE_URI_NONE",
			  "uri-none" },
			{ LSM_SVG_PAINT_TYPE_URI_CURRENT_COLOR,
			  "LSM_SVG_PAINT_TYPE_URI_CURRENT_COLOR",
			  "uri-current-color" },
			{ LSM_SVG_PAINT_TYPE_URI_RGB_COLOR,
			  "LSM_SVG_PAINT_TYPE_URI_RGB_COLOR",
			  "uri-rgb-color" },
			{ LSM_SVG_PAINT_TYPE_URI_RGB_COLOR_ICC_COLOR,
			  "LSM_SVG_PAINT_TYPE_URI_RGB_COLOR_ICC_COLOR",
			  "uri-rgb-color-icc-color" },
			{ LSM_SVG_PAINT_TYPE_URI,
			  "LSM_SVG_PAINT_TYPE_URI",
			  "uri" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgPaintType"),
				values);
	}
	return the_type;
}

GType
lsm_svg_length_direction_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_LENGTH_DIRECTION_ERROR,
			  "LSM_SVG_LENGTH_DIRECTION_ERROR",
			  "error" },
			{ LSM_SVG_LENGTH_DIRECTION_HORIZONTAL,
			  "LSM_SVG_LENGTH_DIRECTION_HORIZONTAL",
			  "horizontal" },
			{ LSM_SVG_LENGTH_DIRECTION_VERTICAL,
			  "LSM_SVG_LENGTH_DIRECTION_VERTICAL",
			  "vertical" },
			{ LSM_SVG_LENGTH_DIRECTION_DIAGONAL,
			  "LSM_SVG_LENGTH_DIRECTION_DIAGONAL",
			  "diagonal" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgLengthDirection"),
				values);
	}
	return the_type;
}

GType
lsm_svg_length_type_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_LENGTH_TYPE_ERROR,
			  "LSM_SVG_LENGTH_TYPE_ERROR",
			  "error" },
			{ LSM_SVG_LENGTH_TYPE_NUMBER,
			  "LSM_SVG_LENGTH_TYPE_NUMBER",
			  "number" },
			{ LSM_SVG_LENGTH_TYPE_PERCENTAGE,
			  "LSM_SVG_LENGTH_TYPE_PERCENTAGE",
			  "percentage" },
			{ LSM_SVG_LENGTH_TYPE_EMS,
			  "LSM_SVG_LENGTH_TYPE_EMS",
			  "ems" },
			{ LSM_SVG_LENGTH_TYPE_EXS,
			  "LSM_SVG_LENGTH_TYPE_EXS",
			  "exs" },
			{ LSM_SVG_LENGTH_TYPE_PX,
			  "LSM_SVG_LENGTH_TYPE_PX",
			  "px" },
			{ LSM_SVG_LENGTH_TYPE_CM,
			  "LSM_SVG_LENGTH_TYPE_CM",
			  "cm" },
			{ LSM_SVG_LENGTH_TYPE_MM,
			  "LSM_SVG_LENGTH_TYPE_MM",
			  "mm" },
			{ LSM_SVG_LENGTH_TYPE_IN,
			  "LSM_SVG_LENGTH_TYPE_IN",
			  "in" },
			{ LSM_SVG_LENGTH_TYPE_PT,
			  "LSM_SVG_LENGTH_TYPE_PT",
			  "pt" },
			{ LSM_SVG_LENGTH_TYPE_PC,
			  "LSM_SVG_LENGTH_TYPE_PC",
			  "pc" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgLengthType"),
				values);
	}
	return the_type;
}

GType
lsm_svg_fill_rule_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_FILL_RULE_ERROR,
			  "LSM_SVG_FILL_RULE_ERROR",
			  "error" },
			{ LSM_SVG_FILL_RULE_NON_ZERO,
			  "LSM_SVG_FILL_RULE_NON_ZERO",
			  "non-zero" },
			{ LSM_SVG_FILL_RULE_EVEN_ODD,
			  "LSM_SVG_FILL_RULE_EVEN_ODD",
			  "even-odd" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgFillRule"),
				values);
	}
	return the_type;
}

GType
lsm_svg_line_join_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_LINE_JOIN_ERROR,
			  "LSM_SVG_LINE_JOIN_ERROR",
			  "error" },
			{ LSM_SVG_LINE_JOIN_MITER,
			  "LSM_SVG_LINE_JOIN_MITER",
			  "miter" },
			{ LSM_SVG_LINE_JOIN_ROUND,
			  "LSM_SVG_LINE_JOIN_ROUND",
			  "round" },
			{ LSM_SVG_LINE_JOIN_BEVEL,
			  "LSM_SVG_LINE_JOIN_BEVEL",
			  "bevel" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgLineJoin"),
				values);
	}
	return the_type;
}

GType
lsm_svg_line_cap_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_LINE_CAP_ERROR,
			  "LSM_SVG_LINE_CAP_ERROR",
			  "error" },
			{ LSM_SVG_LINE_CAP_BUTT,
			  "LSM_SVG_LINE_CAP_BUTT",
			  "butt" },
			{ LSM_SVG_LINE_CAP_ROUND,
			  "LSM_SVG_LINE_CAP_ROUND",
			  "round" },
			{ LSM_SVG_LINE_CAP_SQUARE,
			  "LSM_SVG_LINE_CAP_SQUARE",
			  "square" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgLineCap"),
				values);
	}
	return the_type;
}

GType
lsm_svg_transform_type_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_TRANSFORM_TYPE_ERROR,
			  "LSM_SVG_TRANSFORM_TYPE_ERROR",
			  "error" },
			{ LSM_SVG_TRANSFORM_TYPE_MATRIX,
			  "LSM_SVG_TRANSFORM_TYPE_MATRIX",
			  "matrix" },
			{ LSM_SVG_TRANSFORM_TYPE_TRANSLATE,
			  "LSM_SVG_TRANSFORM_TYPE_TRANSLATE",
			  "translate" },
			{ LSM_SVG_TRANSFORM_TYPE_SCALE,
			  "LSM_SVG_TRANSFORM_TYPE_SCALE",
			  "scale" },
			{ LSM_SVG_TRANSFORM_TYPE_ROTATE,
			  "LSM_SVG_TRANSFORM_TYPE_ROTATE",
			  "rotate" },
			{ LSM_SVG_TRANSFORM_TYPE_SKEW_X,
			  "LSM_SVG_TRANSFORM_TYPE_SKEW_X",
			  "skew-x" },
			{ LSM_SVG_TRANSFORM_TYPE_SKEW_Y,
			  "LSM_SVG_TRANSFORM_TYPE_SKEW_Y",
			  "skew-y" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgTransformType"),
				values);
	}
	return the_type;
}

GType
lsm_svg_overflow_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_OVERFLOW_ERROR,
			  "LSM_SVG_OVERFLOW_ERROR",
			  "error" },
			{ LSM_SVG_OVERFLOW_VISIBLE,
			  "LSM_SVG_OVERFLOW_VISIBLE",
			  "visible" },
			{ LSM_SVG_OVERFLOW_HIDDEN,
			  "LSM_SVG_OVERFLOW_HIDDEN",
			  "hidden" },
			{ LSM_SVG_OVERFLOW_SCROLL,
			  "LSM_SVG_OVERFLOW_SCROLL",
			  "scroll" },
			{ LSM_SVG_OVERFLOW_AUTO,
			  "LSM_SVG_OVERFLOW_AUTO",
			  "auto" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgOverflow"),
				values);
	}
	return the_type;
}

GType
lsm_svg_pattern_units_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_PATTERN_UNITS_ERROR,
			  "LSM_SVG_PATTERN_UNITS_ERROR",
			  "error" },
			{ LSM_SVG_PATTERN_UNITS_USER_SPACE_ON_USE,
			  "LSM_SVG_PATTERN_UNITS_USER_SPACE_ON_USE",
			  "user-space-on-use" },
			{ LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX,
			  "LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX",
			  "object-bounding-box" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgPatternUnits"),
				values);
	}
	return the_type;
}

GType
lsm_svg_marker_units_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_MARKER_UNITS_ERROR,
			  "LSM_SVG_MARKER_UNITS_ERROR",
			  "error" },
			{ LSM_SVG_MARKER_UNITS_STROKE_WIDTH,
			  "LSM_SVG_MARKER_UNITS_STROKE_WIDTH",
			  "stroke-width" },
			{ LSM_SVG_MARKER_UNITS_USER_SPACE_ON_USE,
			  "LSM_SVG_MARKER_UNITS_USER_SPACE_ON_USE",
			  "user-space-on-use" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgMarkerUnits"),
				values);
	}
	return the_type;
}

GType
lsm_svg_spread_method_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_SPREAD_METHOD_ERROR,
			  "LSM_SVG_SPREAD_METHOD_ERROR",
			  "error" },
			{ LSM_SVG_SPREAD_METHOD_PAD,
			  "LSM_SVG_SPREAD_METHOD_PAD",
			  "pad" },
			{ LSM_SVG_SPREAD_METHOD_REFLECT,
			  "LSM_SVG_SPREAD_METHOD_REFLECT",
			  "reflect" },
			{ LSM_SVG_SPREAD_METHOD_REPEAT,
			  "LSM_SVG_SPREAD_METHOD_REPEAT",
			  "repeat" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgSpreadMethod"),
				values);
	}
	return the_type;
}

GType
lsm_svg_align_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_ALIGN_ERROR,
			  "LSM_SVG_ALIGN_ERROR",
			  "error" },
			{ LSM_SVG_ALIGN_NONE,
			  "LSM_SVG_ALIGN_NONE",
			  "none" },
			{ LSM_SVG_ALIGN_X_MIN_Y_MIN,
			  "LSM_SVG_ALIGN_X_MIN_Y_MIN",
			  "x-min-y-min" },
			{ LSM_SVG_ALIGN_X_MID_Y_MIN,
			  "LSM_SVG_ALIGN_X_MID_Y_MIN",
			  "x-mid-y-min" },
			{ LSM_SVG_ALIGN_X_MAX_Y_MIN,
			  "LSM_SVG_ALIGN_X_MAX_Y_MIN",
			  "x-max-y-min" },
			{ LSM_SVG_ALIGN_X_MIN_Y_MID,
			  "LSM_SVG_ALIGN_X_MIN_Y_MID",
			  "x-min-y-mid" },
			{ LSM_SVG_ALIGN_X_MID_Y_MID,
			  "LSM_SVG_ALIGN_X_MID_Y_MID",
			  "x-mid-y-mid" },
			{ LSM_SVG_ALIGN_X_MAX_Y_MID,
			  "LSM_SVG_ALIGN_X_MAX_Y_MID",
			  "x-max-y-mid" },
			{ LSM_SVG_ALIGN_X_MIN_Y_MAX,
			  "LSM_SVG_ALIGN_X_MIN_Y_MAX",
			  "x-min-y-max" },
			{ LSM_SVG_ALIGN_X_MID_Y_MAX,
			  "LSM_SVG_ALIGN_X_MID_Y_MAX",
			  "x-mid-y-max" },
			{ LSM_SVG_ALIGN_X_MAX_Y_MAX,
			  "LSM_SVG_ALIGN_X_MAX_Y_MAX",
			  "x-max-y-max" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgAlign"),
				values);
	}
	return the_type;
}

GType
lsm_svg_meet_or_slice_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_MEET_OR_SLICE_ERROR,
			  "LSM_SVG_MEET_OR_SLICE_ERROR",
			  "error" },
			{ LSM_SVG_MEET_OR_SLICE_MEET,
			  "LSM_SVG_MEET_OR_SLICE_MEET",
			  "meet" },
			{ LSM_SVG_MEET_OR_SLICE_SLICE,
			  "LSM_SVG_MEET_OR_SLICE_SLICE",
			  "slice" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgMeetOrSlice"),
				values);
	}
	return the_type;
}

GType
lsm_svg_comp_op_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_COMP_OP_ERROR,
			  "LSM_SVG_COMP_OP_ERROR",
			  "error" },
			{ LSM_SVG_COMP_OP_CLEAR,
			  "LSM_SVG_COMP_OP_CLEAR",
			  "clear" },
			{ LSM_SVG_COMP_OP_SRC,
			  "LSM_SVG_COMP_OP_SRC",
			  "src" },
			{ LSM_SVG_COMP_OP_DST,
			  "LSM_SVG_COMP_OP_DST",
			  "dst" },
			{ LSM_SVG_COMP_OP_SRC_OVER,
			  "LSM_SVG_COMP_OP_SRC_OVER",
			  "src-over" },
			{ LSM_SVG_COMP_OP_DST_OVER,
			  "LSM_SVG_COMP_OP_DST_OVER",
			  "dst-over" },
			{ LSM_SVG_COMP_OP_SRC_IN,
			  "LSM_SVG_COMP_OP_SRC_IN",
			  "src-in" },
			{ LSM_SVG_COMP_OP_DST_IN,
			  "LSM_SVG_COMP_OP_DST_IN",
			  "dst-in" },
			{ LSM_SVG_COMP_OP_SRC_OUT,
			  "LSM_SVG_COMP_OP_SRC_OUT",
			  "src-out" },
			{ LSM_SVG_COMP_OP_DST_OUT,
			  "LSM_SVG_COMP_OP_DST_OUT",
			  "dst-out" },
			{ LSM_SVG_COMP_OP_SRC_ATOP,
			  "LSM_SVG_COMP_OP_SRC_ATOP",
			  "src-atop" },
			{ LSM_SVG_COMP_OP_DST_ATOP,
			  "LSM_SVG_COMP_OP_DST_ATOP",
			  "dst-atop" },
			{ LSM_SVG_COMP_OP_XOR,
			  "LSM_SVG_COMP_OP_XOR",
			  "xor" },
			{ LSM_SVG_COMP_OP_PLUS,
			  "LSM_SVG_COMP_OP_PLUS",
			  "plus" },
			{ LSM_SVG_COMP_OP_MULTIPLY,
			  "LSM_SVG_COMP_OP_MULTIPLY",
			  "multiply" },
			{ LSM_SVG_COMP_OP_SCREEN,
			  "LSM_SVG_COMP_OP_SCREEN",
			  "screen" },
			{ LSM_SVG_COMP_OP_OVERLAY,
			  "LSM_SVG_COMP_OP_OVERLAY",
			  "overlay" },
			{ LSM_SVG_COMP_OP_DARKEN,
			  "LSM_SVG_COMP_OP_DARKEN",
			  "darken" },
			{ LSM_SVG_COMP_OP_LIGHTEN,
			  "LSM_SVG_COMP_OP_LIGHTEN",
			  "lighten" },
			{ LSM_SVG_COMP_OP_COLOR_DODGE,
			  "LSM_SVG_COMP_OP_COLOR_DODGE",
			  "color-dodge" },
			{ LSM_SVG_COMP_OP_COLOR_BURN,
			  "LSM_SVG_COMP_OP_COLOR_BURN",
			  "color-burn" },
			{ LSM_SVG_COMP_OP_HARD_LIGHT,
			  "LSM_SVG_COMP_OP_HARD_LIGHT",
			  "hard-light" },
			{ LSM_SVG_COMP_OP_SOFT_LIGHT,
			  "LSM_SVG_COMP_OP_SOFT_LIGHT",
			  "soft-light" },
			{ LSM_SVG_COMP_OP_DIFFERENCE,
			  "LSM_SVG_COMP_OP_DIFFERENCE",
			  "difference" },
			{ LSM_SVG_COMP_OP_EXCLUSION,
			  "LSM_SVG_COMP_OP_EXCLUSION",
			  "exclusion" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgCompOp"),
				values);
	}
	return the_type;
}

GType
lsm_svg_font_stretch_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_FONT_STRETCH_ERROR,
			  "LSM_SVG_FONT_STRETCH_ERROR",
			  "error" },
			{ LSM_SVG_FONT_STRETCH_NORMAL,
			  "LSM_SVG_FONT_STRETCH_NORMAL",
			  "normal" },
			{ LSM_SVG_FONT_STRETCH_ULTRA_CONDENSED,
			  "LSM_SVG_FONT_STRETCH_ULTRA_CONDENSED",
			  "ultra-condensed" },
			{ LSM_SVG_FONT_STRETCH_EXTRA_CONDENSED,
			  "LSM_SVG_FONT_STRETCH_EXTRA_CONDENSED",
			  "extra-condensed" },
			{ LSM_SVG_FONT_STRETCH_CONDENSED,
			  "LSM_SVG_FONT_STRETCH_CONDENSED",
			  "condensed" },
			{ LSM_SVG_FONT_STRETCH_SEMI_CONDENSED,
			  "LSM_SVG_FONT_STRETCH_SEMI_CONDENSED",
			  "semi-condensed" },
			{ LSM_SVG_FONT_STRETCH_SEMI_EXPANDED,
			  "LSM_SVG_FONT_STRETCH_SEMI_EXPANDED",
			  "semi-expanded" },
			{ LSM_SVG_FONT_STRETCH_EXPANDED,
			  "LSM_SVG_FONT_STRETCH_EXPANDED",
			  "expanded" },
			{ LSM_SVG_FONT_STRETCH_EXTRA_EXPANDED,
			  "LSM_SVG_FONT_STRETCH_EXTRA_EXPANDED",
			  "extra-expanded" },
			{ LSM_SVG_FONT_STRETCH_ULTRA_EXPANDED,
			  "LSM_SVG_FONT_STRETCH_ULTRA_EXPANDED",
			  "ultra-expanded" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgFontStretch"),
				values);
	}
	return the_type;
}

GType
lsm_svg_font_style_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_FONT_STYLE_ERROR,
			  "LSM_SVG_FONT_STYLE_ERROR",
			  "error" },
			{ LSM_SVG_FONT_STYLE_NORMAL,
			  "LSM_SVG_FONT_STYLE_NORMAL",
			  "normal" },
			{ LSM_SVG_FONT_STYLE_OBLIQUE,
			  "LSM_SVG_FONT_STYLE_OBLIQUE",
			  "oblique" },
			{ LSM_SVG_FONT_STYLE_ITALIC,
			  "LSM_SVG_FONT_STYLE_ITALIC",
			  "italic" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgFontStyle"),
				values);
	}
	return the_type;
}

GType
lsm_svg_font_weight_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_FONT_WEIGHT_ERROR,
			  "LSM_SVG_FONT_WEIGHT_ERROR",
			  "error" },
			{ LSM_SVG_FONT_WEIGHT_NORMAL,
			  "LSM_SVG_FONT_WEIGHT_NORMAL",
			  "normal" },
			{ LSM_SVG_FONT_WEIGHT_BOLD,
			  "LSM_SVG_FONT_WEIGHT_BOLD",
			  "bold" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgFontWeight"),
				values);
	}
	return the_type;
}

GType
lsm_svg_text_anchor_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_TEXT_ANCHOR_ERROR,
			  "LSM_SVG_TEXT_ANCHOR_ERROR",
			  "error" },
			{ LSM_SVG_TEXT_ANCHOR_START,
			  "LSM_SVG_TEXT_ANCHOR_START",
			  "start" },
			{ LSM_SVG_TEXT_ANCHOR_MIDDLE,
			  "LSM_SVG_TEXT_ANCHOR_MIDDLE",
			  "middle" },
			{ LSM_SVG_TEXT_ANCHOR_END,
			  "LSM_SVG_TEXT_ANCHOR_END",
			  "end" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgTextAnchor"),
				values);
	}
	return the_type;
}

GType
lsm_svg_filter_input_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_FILTER_INPUT_ERROR,
			  "LSM_SVG_FILTER_INPUT_ERROR",
			  "error" },
			{ LSM_SVG_FILTER_INPUT_SOURCE_GRAPHIC,
			  "LSM_SVG_FILTER_INPUT_SOURCE_GRAPHIC",
			  "source-graphic" },
			{ LSM_SVG_FILTER_INPUT_SOURCE_ALPHA,
			  "LSM_SVG_FILTER_INPUT_SOURCE_ALPHA",
			  "source-alpha" },
			{ LSM_SVG_FILTER_INPUT_BACKGROUND_IMAGE,
			  "LSM_SVG_FILTER_INPUT_BACKGROUND_IMAGE",
			  "background-image" },
			{ LSM_SVG_FILTER_INPUT_BACKGROUND_ALPHA,
			  "LSM_SVG_FILTER_INPUT_BACKGROUND_ALPHA",
			  "background-alpha" },
			{ LSM_SVG_FILTER_INPUT_FILL_PAINT,
			  "LSM_SVG_FILTER_INPUT_FILL_PAINT",
			  "fill-paint" },
			{ LSM_SVG_FILTER_INPUT_STROKE_PAINT,
			  "LSM_SVG_FILTER_INPUT_STROKE_PAINT",
			  "stroke-paint" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgFilterInput"),
				values);
	}
	return the_type;
}

GType
lsm_svg_display_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_DISPLAY_ERROR,
			  "LSM_SVG_DISPLAY_ERROR",
			  "error" },
			{ LSM_SVG_DISPLAY_NONE,
			  "LSM_SVG_DISPLAY_NONE",
			  "none" },
			{ LSM_SVG_DISPLAY_INLINE,
			  "LSM_SVG_DISPLAY_INLINE",
			  "inline" },
			{ LSM_SVG_DISPLAY_BLOCK,
			  "LSM_SVG_DISPLAY_BLOCK",
			  "block" },
			{ LSM_SVG_DISPLAY_LIST_ITEM,
			  "LSM_SVG_DISPLAY_LIST_ITEM",
			  "list-item" },
			{ LSM_SVG_DISPLAY_RUN_IN,
			  "LSM_SVG_DISPLAY_RUN_IN",
			  "run-in" },
			{ LSM_SVG_DISPLAY_COMPACT,
			  "LSM_SVG_DISPLAY_COMPACT",
			  "compact" },
			{ LSM_SVG_DISPLAY_MARKER,
			  "LSM_SVG_DISPLAY_MARKER",
			  "marker" },
			{ LSM_SVG_DISPLAY_TABLE,
			  "LSM_SVG_DISPLAY_TABLE",
			  "table" },
			{ LSM_SVG_DISPLAY_INLINE_TABLE,
			  "LSM_SVG_DISPLAY_INLINE_TABLE",
			  "inline-table" },
			{ LSM_SVG_DISPLAY_TABLE_ROW_GROUP,
			  "LSM_SVG_DISPLAY_TABLE_ROW_GROUP",
			  "table-row-group" },
			{ LSM_SVG_DISPLAY_TABLE_HEADER_GROUP,
			  "LSM_SVG_DISPLAY_TABLE_HEADER_GROUP",
			  "table-header-group" },
			{ LSM_SVG_DISPLAY_TABLE_FOOTER_GROUP,
			  "LSM_SVG_DISPLAY_TABLE_FOOTER_GROUP",
			  "table-footer-group" },
			{ LSM_SVG_DISPLAY_TABLE_ROW,
			  "LSM_SVG_DISPLAY_TABLE_ROW",
			  "table-row" },
			{ LSM_SVG_DISPLAY_TABLE_COLUMN_GROUP,
			  "LSM_SVG_DISPLAY_TABLE_COLUMN_GROUP",
			  "table-column-group" },
			{ LSM_SVG_DISPLAY_TABLE_COLUMN,
			  "LSM_SVG_DISPLAY_TABLE_COLUMN",
			  "table-column" },
			{ LSM_SVG_DISPLAY_TABLE_CELL,
			  "LSM_SVG_DISPLAY_TABLE_CELL",
			  "table-cell" },
			{ LSM_SVG_DISPLAY_TABLE_CAPTION,
			  "LSM_SVG_DISPLAY_TABLE_CAPTION",
			  "table-caption" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgDisplay"),
				values);
	}
	return the_type;
}

GType
lsm_svg_visibility_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_VISIBILITY_ERROR,
			  "LSM_SVG_VISIBILITY_ERROR",
			  "error" },
			{ LSM_SVG_VISIBILITY_VISIBLE,
			  "LSM_SVG_VISIBILITY_VISIBLE",
			  "visible" },
			{ LSM_SVG_VISIBILITY_HIDDEN,
			  "LSM_SVG_VISIBILITY_HIDDEN",
			  "hidden" },
			{ LSM_SVG_VISIBILITY_COLLAPSE,
			  "LSM_SVG_VISIBILITY_COLLAPSE",
			  "collapse" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgVisibility"),
				values);
	}
	return the_type;
}

GType
lsm_svg_element_category_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GFlagsValue values[] = {
			{ LSM_SVG_ELEMENT_CATEGORY_NONE,
			  "LSM_SVG_ELEMENT_CATEGORY_NONE",
			  "none" },
			{ LSM_SVG_ELEMENT_CATEGORY_DESCRIPTIVE,
			  "LSM_SVG_ELEMENT_CATEGORY_DESCRIPTIVE",
			  "descriptive" },
			{ LSM_SVG_ELEMENT_CATEGORY_CONTAINER,
			  "LSM_SVG_ELEMENT_CATEGORY_CONTAINER",
			  "container" },
			{ LSM_SVG_ELEMENT_CATEGORY_STRUCTURAL,
			  "LSM_SVG_ELEMENT_CATEGORY_STRUCTURAL",
			  "structural" },
			{ LSM_SVG_ELEMENT_CATEGORY_GRAPHICS_REFERENCING,
			  "LSM_SVG_ELEMENT_CATEGORY_GRAPHICS_REFERENCING",
			  "graphics-referencing" },
			{ LSM_SVG_ELEMENT_CATEGORY_GRAPHICS,
			  "LSM_SVG_ELEMENT_CATEGORY_GRAPHICS",
			  "graphics" },
			{ LSM_SVG_ELEMENT_CATEGORY_SHAPE,
			  "LSM_SVG_ELEMENT_CATEGORY_SHAPE",
			  "shape" },
			{ LSM_SVG_ELEMENT_CATEGORY_BASIC_SHAPE,
			  "LSM_SVG_ELEMENT_CATEGORY_BASIC_SHAPE",
			  "basic-shape" },
			{ LSM_SVG_ELEMENT_CATEGORY_TEXT_CONTENT,
			  "LSM_SVG_ELEMENT_CATEGORY_TEXT_CONTENT",
			  "text-content" },
			{ LSM_SVG_ELEMENT_CATEGORY_TEXT_CONTENT_CHILD,
			  "LSM_SVG_ELEMENT_CATEGORY_TEXT_CONTENT_CHILD",
			  "text-content-child" },
			{ LSM_SVG_ELEMENT_CATEGORY_GRADIENT,
			  "LSM_SVG_ELEMENT_CATEGORY_GRADIENT",
			  "gradient" },
			{ LSM_SVG_ELEMENT_CATEGORY_FILTER_PRIMITIVE,
			  "LSM_SVG_ELEMENT_CATEGORY_FILTER_PRIMITIVE",
			  "filter-primitive" },
			{ LSM_SVG_ELEMENT_CATEGORY_ANIMATION,
			  "LSM_SVG_ELEMENT_CATEGORY_ANIMATION",
			  "animation" },
			{ 0, NULL, NULL }
		};
		the_type = g_flags_register_static (
				g_intern_static_string ("LsmSvgElementCategory"),
				values);
	}
	return the_type;
}

GType
lsm_svg_writing_mode_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_WRITING_MODE_ERROR,
			  "LSM_SVG_WRITING_MODE_ERROR",
			  "error" },
			{ LSM_SVG_WRITING_MODE_LR_TB,
			  "LSM_SVG_WRITING_MODE_LR_TB",
			  "lr-tb" },
			{ LSM_SVG_WRITING_MODE_RL_TB,
			  "LSM_SVG_WRITING_MODE_RL_TB",
			  "rl-tb" },
			{ LSM_SVG_WRITING_MODE_TB_RL,
			  "LSM_SVG_WRITING_MODE_TB_RL",
			  "tb-rl" },
			{ LSM_SVG_WRITING_MODE_LR,
			  "LSM_SVG_WRITING_MODE_LR",
			  "lr" },
			{ LSM_SVG_WRITING_MODE_RL,
			  "LSM_SVG_WRITING_MODE_RL",
			  "rl" },
			{ LSM_SVG_WRITING_MODE_TB,
			  "LSM_SVG_WRITING_MODE_TB",
			  "tb" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgWritingMode"),
				values);
	}
	return the_type;
}

/* enumerations from "lsmsvgview.h" */
#include "lsmsvgview.h"

GType
lsm_svg_view_surface_type_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_SVG_VIEW_SURFACE_TYPE_AUTO,
			  "LSM_SVG_VIEW_SURFACE_TYPE_AUTO",
			  "auto" },
			{ LSM_SVG_VIEW_SURFACE_TYPE_IMAGE,
			  "LSM_SVG_VIEW_SURFACE_TYPE_IMAGE",
			  "image" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmSvgViewSurfaceType"),
				values);
	}
	return the_type;
}

/* enumerations from "lsmsvgmatrix.h" */
#include "lsmsvgmatrix.h"

GType
lsm_svg_matrix_flags_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GFlagsValue values[] = {
			{ LSM_SVG_MATRIX_FLAGS_IDENTITY,
			  "LSM_SVG_MATRIX_FLAGS_IDENTITY",
			  "identity" },
			{ 0, NULL, NULL }
		};
		the_type = g_flags_register_static (
				g_intern_static_string ("LsmSvgMatrixFlags"),
				values);
	}
	return the_type;
}

/* enumerations from "lsmsvguseelement.h" */
#include "lsmsvguseelement.h"

GType
lsm_svg_use_element_flags_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GFlagsValue values[] = {
			{ LSM_SVG_USE_ELEMENT_FLAGS_IN_USE_FOR_RENDER,
			  "LSM_SVG_USE_ELEMENT_FLAGS_IN_USE_FOR_RENDER",
			  "render" },
			{ LSM_SVG_USE_ELEMENT_FLAGS_IN_USE_FOR_GET_EXTENTS,
			  "LSM_SVG_USE_ELEMENT_FLAGS_IN_USE_FOR_GET_EXTENTS",
			  "get-extents" },
			{ 0, NULL, NULL }
		};
		the_type = g_flags_register_static (
				g_intern_static_string ("LsmSvgUseElementFlags"),
				values);
	}
	return the_type;
}


/* Generated data ends here */

