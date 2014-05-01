
/* Generated data (by glib-mkenums) */

#include "lsmmathmlenumtypes.h"

/* enumerations from "lsmmathmlenums.h" */
#include "lsmmathmlenums.h"

GType
lsm_mathml_css_type_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_CSS_TYPE_USER,
			  "LSM_MATHML_CSS_TYPE_USER",
			  "user" },
			{ LSM_MATHML_CSS_TYPE_AUTHOR,
			  "LSM_MATHML_CSS_TYPE_AUTHOR",
			  "author" },
			{ LSM_MATHML_CSS_TYPE_AUTHOR_IMPORTANT,
			  "LSM_MATHML_CSS_TYPE_AUTHOR_IMPORTANT",
			  "author-important" },
			{ LSM_MATHML_CSS_TYPE_USER_IMPORTANT,
			  "LSM_MATHML_CSS_TYPE_USER_IMPORTANT",
			  "user-important" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlCssType"),
				values);
	}
	return the_type;
}

GType
lsm_mathml_mode_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_MODE_ERROR,
			  "LSM_MATHML_MODE_ERROR",
			  "error" },
			{ LSM_MATHML_MODE_DISPLAY,
			  "LSM_MATHML_MODE_DISPLAY",
			  "display" },
			{ LSM_MATHML_MODE_INLINE,
			  "LSM_MATHML_MODE_INLINE",
			  "inline" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlMode"),
				values);
	}
	return the_type;
}

GType
lsm_mathml_display_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_DISPLAY_ERROR,
			  "LSM_MATHML_DISPLAY_ERROR",
			  "error" },
			{ LSM_MATHML_DISPLAY_BLOCK,
			  "LSM_MATHML_DISPLAY_BLOCK",
			  "block" },
			{ LSM_MATHML_DISPLAY_INLINE,
			  "LSM_MATHML_DISPLAY_INLINE",
			  "inline" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlDisplay"),
				values);
	}
	return the_type;
}

GType
lsm_mathml_space_name_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_SPACE_NAME_ERROR,
			  "LSM_MATHML_SPACE_NAME_ERROR",
			  "error" },
			{ LSM_MATHML_SPACE_NAME_VERY_VERY_THIN,
			  "LSM_MATHML_SPACE_NAME_VERY_VERY_THIN",
			  "very-very-thin" },
			{ LSM_MATHML_SPACE_NAME_VERY_THIN,
			  "LSM_MATHML_SPACE_NAME_VERY_THIN",
			  "very-thin" },
			{ LSM_MATHML_SPACE_NAME_THIN,
			  "LSM_MATHML_SPACE_NAME_THIN",
			  "thin" },
			{ LSM_MATHML_SPACE_NAME_MEDIUM,
			  "LSM_MATHML_SPACE_NAME_MEDIUM",
			  "medium" },
			{ LSM_MATHML_SPACE_NAME_THICK,
			  "LSM_MATHML_SPACE_NAME_THICK",
			  "thick" },
			{ LSM_MATHML_SPACE_NAME_VERY_THICK,
			  "LSM_MATHML_SPACE_NAME_VERY_THICK",
			  "very-thick" },
			{ LSM_MATHML_SPACE_NAME_VERY_VERY_THICK,
			  "LSM_MATHML_SPACE_NAME_VERY_VERY_THICK",
			  "very-very-thick" },
			{ LSM_MATHML_SPACE_NAME_INFINITY,
			  "LSM_MATHML_SPACE_NAME_INFINITY",
			  "infinity" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlSpaceName"),
				values);
	}
	return the_type;
}

GType
lsm_mathml_unit_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_UNIT_ERROR,
			  "LSM_MATHML_UNIT_ERROR",
			  "error" },
			{ LSM_MATHML_UNIT_NONE,
			  "LSM_MATHML_UNIT_NONE",
			  "none" },
			{ LSM_MATHML_UNIT_EM,
			  "LSM_MATHML_UNIT_EM",
			  "em" },
			{ LSM_MATHML_UNIT_EX,
			  "LSM_MATHML_UNIT_EX",
			  "ex" },
			{ LSM_MATHML_UNIT_IN,
			  "LSM_MATHML_UNIT_IN",
			  "in" },
			{ LSM_MATHML_UNIT_CM,
			  "LSM_MATHML_UNIT_CM",
			  "cm" },
			{ LSM_MATHML_UNIT_MM,
			  "LSM_MATHML_UNIT_MM",
			  "mm" },
			{ LSM_MATHML_UNIT_PT,
			  "LSM_MATHML_UNIT_PT",
			  "pt" },
			{ LSM_MATHML_UNIT_PX,
			  "LSM_MATHML_UNIT_PX",
			  "px" },
			{ LSM_MATHML_UNIT_PC,
			  "LSM_MATHML_UNIT_PC",
			  "pc" },
			{ LSM_MATHML_UNIT_PERCENT,
			  "LSM_MATHML_UNIT_PERCENT",
			  "percent" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlUnit"),
				values);
	}
	return the_type;
}

GType
lsm_mathml_font_style_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_FONT_STYLE_ERROR,
			  "LSM_MATHML_FONT_STYLE_ERROR",
			  "error" },
			{ LSM_MATHML_FONT_STYLE_NORMAL,
			  "LSM_MATHML_FONT_STYLE_NORMAL",
			  "normal" },
			{ LSM_MATHML_FONT_STYLE_ITALIC,
			  "LSM_MATHML_FONT_STYLE_ITALIC",
			  "italic" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlFontStyle"),
				values);
	}
	return the_type;
}

GType
lsm_mathml_font_weight_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_FONT_WEIGHT_ERROR,
			  "LSM_MATHML_FONT_WEIGHT_ERROR",
			  "error" },
			{ LSM_MATHML_FONT_WEIGHT_NORMAL,
			  "LSM_MATHML_FONT_WEIGHT_NORMAL",
			  "normal" },
			{ LSM_MATHML_FONT_WEIGHT_BOLD,
			  "LSM_MATHML_FONT_WEIGHT_BOLD",
			  "bold" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlFontWeight"),
				values);
	}
	return the_type;
}

GType
lsm_mathml_variant_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_VARIANT_ERROR,
			  "LSM_MATHML_VARIANT_ERROR",
			  "error" },
			{ LSM_MATHML_VARIANT_NORMAL,
			  "LSM_MATHML_VARIANT_NORMAL",
			  "normal" },
			{ LSM_MATHML_VARIANT_BOLD,
			  "LSM_MATHML_VARIANT_BOLD",
			  "bold" },
			{ LSM_MATHML_VARIANT_ITALIC,
			  "LSM_MATHML_VARIANT_ITALIC",
			  "italic" },
			{ LSM_MATHML_VARIANT_BOLD_ITALIC,
			  "LSM_MATHML_VARIANT_BOLD_ITALIC",
			  "bold-italic" },
			{ LSM_MATHML_VARIANT_DOUBLE_STRUCK,
			  "LSM_MATHML_VARIANT_DOUBLE_STRUCK",
			  "double-struck" },
			{ LSM_MATHML_VARIANT_FRAKTUR_BOLD,
			  "LSM_MATHML_VARIANT_FRAKTUR_BOLD",
			  "fraktur-bold" },
			{ LSM_MATHML_VARIANT_SCRIPT,
			  "LSM_MATHML_VARIANT_SCRIPT",
			  "script" },
			{ LSM_MATHML_VARIANT_SCRIPT_BOLD,
			  "LSM_MATHML_VARIANT_SCRIPT_BOLD",
			  "script-bold" },
			{ LSM_MATHML_VARIANT_FRAKTUR,
			  "LSM_MATHML_VARIANT_FRAKTUR",
			  "fraktur" },
			{ LSM_MATHML_VARIANT_SANS_SERIF,
			  "LSM_MATHML_VARIANT_SANS_SERIF",
			  "sans-serif" },
			{ LSM_MATHML_VARIANT_SANS_SERIF_BOLD,
			  "LSM_MATHML_VARIANT_SANS_SERIF_BOLD",
			  "sans-serif-bold" },
			{ LSM_MATHML_VARIANT_SANS_SERIF_ITALIC,
			  "LSM_MATHML_VARIANT_SANS_SERIF_ITALIC",
			  "sans-serif-italic" },
			{ LSM_MATHML_VARIANT_SANS_SERIF_BOLD_ITALIC,
			  "LSM_MATHML_VARIANT_SANS_SERIF_BOLD_ITALIC",
			  "sans-serif-bold-italic" },
			{ LSM_MATHML_VARIANT_MONOSPACE,
			  "LSM_MATHML_VARIANT_MONOSPACE",
			  "monospace" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlVariant"),
				values);
	}
	return the_type;
}

GType
lsm_mathml_form_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_FORM_ERROR,
			  "LSM_MATHML_FORM_ERROR",
			  "error" },
			{ LSM_MATHML_FORM_PREFIX,
			  "LSM_MATHML_FORM_PREFIX",
			  "prefix" },
			{ LSM_MATHML_FORM_POSTFIX,
			  "LSM_MATHML_FORM_POSTFIX",
			  "postfix" },
			{ LSM_MATHML_FORM_INFIX,
			  "LSM_MATHML_FORM_INFIX",
			  "infix" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlForm"),
				values);
	}
	return the_type;
}

GType
lsm_mathml_row_align_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_ROW_ALIGN_ERROR,
			  "LSM_MATHML_ROW_ALIGN_ERROR",
			  "error" },
			{ LSM_MATHML_ROW_ALIGN_BASELINE,
			  "LSM_MATHML_ROW_ALIGN_BASELINE",
			  "baseline" },
			{ LSM_MATHML_ROW_ALIGN_TOP,
			  "LSM_MATHML_ROW_ALIGN_TOP",
			  "top" },
			{ LSM_MATHML_ROW_ALIGN_BOTTOM,
			  "LSM_MATHML_ROW_ALIGN_BOTTOM",
			  "bottom" },
			{ LSM_MATHML_ROW_ALIGN_CENTER,
			  "LSM_MATHML_ROW_ALIGN_CENTER",
			  "center" },
			{ LSM_MATHML_ROW_ALIGN_AXIS,
			  "LSM_MATHML_ROW_ALIGN_AXIS",
			  "axis" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlRowAlign"),
				values);
	}
	return the_type;
}

GType
lsm_mathml_column_align_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_COLUMN_ALIGN_ERROR,
			  "LSM_MATHML_COLUMN_ALIGN_ERROR",
			  "error" },
			{ LSM_MATHML_COLUMN_ALIGN_CENTER,
			  "LSM_MATHML_COLUMN_ALIGN_CENTER",
			  "center" },
			{ LSM_MATHML_COLUMN_ALIGN_LEFT,
			  "LSM_MATHML_COLUMN_ALIGN_LEFT",
			  "left" },
			{ LSM_MATHML_COLUMN_ALIGN_RIGHT,
			  "LSM_MATHML_COLUMN_ALIGN_RIGHT",
			  "right" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlColumnAlign"),
				values);
	}
	return the_type;
}

GType
lsm_mathml_line_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_LINE_ERROR,
			  "LSM_MATHML_LINE_ERROR",
			  "error" },
			{ LSM_MATHML_LINE_NONE,
			  "LSM_MATHML_LINE_NONE",
			  "none" },
			{ LSM_MATHML_LINE_SOLID,
			  "LSM_MATHML_LINE_SOLID",
			  "solid" },
			{ LSM_MATHML_LINE_DASHED,
			  "LSM_MATHML_LINE_DASHED",
			  "dashed" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlLine"),
				values);
	}
	return the_type;
}

GType
lsm_mathml_script_level_sign_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_SCRIPT_LEVEL_SIGN_ERROR,
			  "LSM_MATHML_SCRIPT_LEVEL_SIGN_ERROR",
			  "error" },
			{ LSM_MATHML_SCRIPT_LEVEL_SIGN_NONE,
			  "LSM_MATHML_SCRIPT_LEVEL_SIGN_NONE",
			  "none" },
			{ LSM_MATHML_SCRIPT_LEVEL_SIGN_PLUS,
			  "LSM_MATHML_SCRIPT_LEVEL_SIGN_PLUS",
			  "plus" },
			{ LSM_MATHML_SCRIPT_LEVEL_SIGN_MINUS,
			  "LSM_MATHML_SCRIPT_LEVEL_SIGN_MINUS",
			  "minus" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlScriptLevelSign"),
				values);
	}
	return the_type;
}

/* enumerations from "lsmmathmltablerowelement.h" */
#include "lsmmathmltablerowelement.h"

GType
lsm_mathml_table_row_element_type_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_TABLE_ROW_ELEMENT_TYPE_ROW,
			  "LSM_MATHML_TABLE_ROW_ELEMENT_TYPE_ROW",
			  "row" },
			{ LSM_MATHML_TABLE_ROW_ELEMENT_TYPE_LABELED_ROW,
			  "LSM_MATHML_TABLE_ROW_ELEMENT_TYPE_LABELED_ROW",
			  "labeled-row" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlTableRowElementType"),
				values);
	}
	return the_type;
}

/* enumerations from "lsmmathmlradicalelement.h" */
#include "lsmmathmlradicalelement.h"

GType
lsm_mathml_radical_element_type_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_RADICAL_ELEMENT_TYPE_SQRT,
			  "LSM_MATHML_RADICAL_ELEMENT_TYPE_SQRT",
			  "sqrt" },
			{ LSM_MATHML_RADICAL_ELEMENT_TYPE_ROOT,
			  "LSM_MATHML_RADICAL_ELEMENT_TYPE_ROOT",
			  "root" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlRadicalElementType"),
				values);
	}
	return the_type;
}

/* enumerations from "lsmmathmlscriptelement.h" */
#include "lsmmathmlscriptelement.h"

GType
lsm_mathml_script_element_type_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUB,
			  "LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUB",
			  "sub" },
			{ LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUP,
			  "LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUP",
			  "sup" },
			{ LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUB_SUP,
			  "LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUB_SUP",
			  "sub-sup" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlScriptElementType"),
				values);
	}
	return the_type;
}

/* enumerations from "lsmmathmlunderoverelement.h" */
#include "lsmmathmlunderoverelement.h"

GType
lsm_mathml_under_over_element_type_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_UNDER,
			  "LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_UNDER",
			  "under" },
			{ LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_OVER,
			  "LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_OVER",
			  "over" },
			{ LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_UNDER_OVER,
			  "LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_UNDER_OVER",
			  "under-over" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlUnderOverElementType"),
				values);
	}
	return the_type;
}

/* enumerations from "lsmmathmlpresentationtoken.h" */
#include "lsmmathmlpresentationtoken.h"

GType
lsm_mathml_presentation_token_type_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_PRESENTATION_TOKEN_TYPE_NUMBER,
			  "LSM_MATHML_PRESENTATION_TOKEN_TYPE_NUMBER",
			  "number" },
			{ LSM_MATHML_PRESENTATION_TOKEN_TYPE_IDENTIFIER,
			  "LSM_MATHML_PRESENTATION_TOKEN_TYPE_IDENTIFIER",
			  "identifier" },
			{ LSM_MATHML_PRESENTATION_TOKEN_TYPE_TEXT,
			  "LSM_MATHML_PRESENTATION_TOKEN_TYPE_TEXT",
			  "text" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlPresentationTokenType"),
				values);
	}
	return the_type;
}

/* enumerations from "lsmmathmlview.h" */
#include "lsmmathmlview.h"

GType
lsm_mathml_glyph_flags_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GFlagsValue values[] = {
			{ LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL,
			  "LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL",
			  "stretch-vertical" },
			{ LSM_MATHML_GLYPH_FLAG_STRETCH_HORIZONTAL,
			  "LSM_MATHML_GLYPH_FLAG_STRETCH_HORIZONTAL",
			  "stretch-horizontal" },
			{ LSM_MATHML_GLYPH_FLAG_TYPE_SIZED,
			  "LSM_MATHML_GLYPH_FLAG_TYPE_SIZED",
			  "type-sized" },
			{ LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS,
			  "LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS",
			  "align-axis" },
			{ LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION,
			  "LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION",
			  "has-large-version" },
			{ LSM_MATHML_GLYPH_FLAG_INTEGRAL_SLANT,
			  "LSM_MATHML_GLYPH_FLAG_INTEGRAL_SLANT",
			  "integral-slant" },
			{ 0, NULL, NULL }
		};
		the_type = g_flags_register_static (
				g_intern_static_string ("LsmMathmlGlyphFlags"),
				values);
	}
	return the_type;
}

GType
lsm_mathml_font_get_type (void)
{
	static GType the_type = 0;

	if (the_type == 0)
	{
		static const GEnumValue values[] = {
			{ LSM_MATHML_FONT_ERROR,
			  "LSM_MATHML_FONT_ERROR",
			  "error" },
			{ LSM_MATHML_FONT_DEFAULT,
			  "LSM_MATHML_FONT_DEFAULT",
			  "default" },
			{ LSM_MATHML_FONT_CMR10,
			  "LSM_MATHML_FONT_CMR10",
			  "cmr10" },
			{ LSM_MATHML_FONT_CMMI10,
			  "LSM_MATHML_FONT_CMMI10",
			  "cmmi10" },
			{ LSM_MATHML_FONT_CMEX10,
			  "LSM_MATHML_FONT_CMEX10",
			  "cmex10" },
			{ LSM_MATHML_FONT_CMSY10,
			  "LSM_MATHML_FONT_CMSY10",
			  "cmsy10" },
			{ LSM_MATHML_FONT_SYMBOL,
			  "LSM_MATHML_FONT_SYMBOL",
			  "symbol" },
			{ 0, NULL, NULL }
		};
		the_type = g_enum_register_static (
				g_intern_static_string ("LsmMathmlFont"),
				values);
	}
	return the_type;
}


/* Generated data ends here */

