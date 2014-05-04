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

#include <lsmsvgtraits.h>
#include <lsmstr.h>
#include <lsmsvgcolors.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

const LsmSvgColor lsm_svg_color_null = {0.0, 0.0, 0.0};
const LsmSvgDashArray lsm_svg_dash_array_null = {0, NULL};

static gboolean
lsm_svg_blending_mode_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgBlendingMode *trait = (LsmSvgBlendingMode *) abstract_trait;

	*trait = lsm_svg_blending_mode_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_blending_mode_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgBlendingMode *trait = (LsmSvgBlendingMode *) abstract_trait;

	return g_strdup (lsm_svg_blending_mode_to_string (*trait));
}

const LsmTraitClass lsm_svg_blending_mode_trait_class = {
	.size = sizeof (LsmSvgBlendingMode),
	.from_string = lsm_svg_blending_mode_trait_from_string,
	.to_string = lsm_svg_blending_mode_trait_to_string
};

static gboolean
lsm_svg_comp_op_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgCompOp *trait = (LsmSvgCompOp *) abstract_trait;

	*trait = lsm_svg_comp_op_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_comp_op_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgCompOp *trait = (LsmSvgCompOp *) abstract_trait;

	return g_strdup (lsm_svg_comp_op_to_string (*trait));
}

const LsmTraitClass lsm_svg_comp_op_trait_class = {
	.size = sizeof (LsmSvgCompOp),
	.from_string = lsm_svg_comp_op_trait_from_string,
	.to_string = lsm_svg_comp_op_trait_to_string
};

static gboolean
lsm_svg_enable_background_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgEnableBackground *trait = (LsmSvgEnableBackground *) abstract_trait;

	*trait = lsm_svg_enable_background_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_enable_background_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgEnableBackground *trait = (LsmSvgEnableBackground *) abstract_trait;

	return g_strdup (lsm_svg_enable_background_to_string (*trait));
}

const LsmTraitClass lsm_svg_enable_background_trait_class = {
	.size = sizeof (LsmSvgEnableBackground),
	.from_string = lsm_svg_enable_background_trait_from_string,
	.to_string = lsm_svg_enable_background_trait_to_string
};

static gboolean
lsm_svg_length_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgLength *svg_length = (LsmSvgLength *) abstract_trait;
	char *length_type_str;

	svg_length->value_unit = g_ascii_strtod (string, &length_type_str);
	svg_length->type = lsm_svg_length_type_from_string (length_type_str);

	return length_type_str != string && svg_length->type >= 0;
}

static char *
lsm_svg_length_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgLength *svg_length = (LsmSvgLength *) abstract_trait;

	return g_strdup_printf ("%g%s",
				svg_length->value_unit,
				lsm_svg_length_type_to_string (svg_length->type));
}

const LsmTraitClass lsm_svg_length_trait_class = {
	.size = sizeof (LsmSvgLength),
	.from_string = lsm_svg_length_trait_from_string,
	.to_string = lsm_svg_length_trait_to_string
};

static gboolean
lsm_svg_length_list_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgLengthList *length_list = (LsmSvgLengthList *) abstract_trait;
	unsigned int n_lengths = 1;
	unsigned int i;
	gboolean success = FALSE;
	char *iter = (char *) string;

	g_free (length_list->lengths);
	length_list->n_lengths = 0;
	length_list->lengths = NULL;

	while (*iter != '\0') {
		if (*iter == ',' ||
		    *iter == ' ') {
			n_lengths++;
			do {
				iter++;
			} while (*iter == ',' ||
				 *iter == ' ');
		} else
			iter++;
	}

	length_list->lengths = g_new (LsmSvgLength, n_lengths);
	length_list->n_lengths = n_lengths;
	iter = (char *)string;
	lsm_str_skip_spaces (&iter);

	for (i = 0; i < n_lengths; i++) {
		success = lsm_svg_parse_length (&iter, &length_list->lengths[i]);

		if (!success)
			break;
		lsm_str_skip_comma_and_spaces (&iter);
	}

	if (!success) {
		g_free (length_list->lengths);
		length_list->lengths = NULL;
		length_list->n_lengths = 0;
	}

	return TRUE;
}

static char *
lsm_svg_length_list_trait_to_string (LsmTrait *abstract_trait)
{
	g_assert_not_reached ();

	return NULL;
}

static void
lsm_svg_length_list_trait_finalize (LsmTrait *abstract_trait)
{
	LsmSvgLengthList *svg_length_list = (LsmSvgLengthList *) abstract_trait;

	g_free (svg_length_list->lengths);
	svg_length_list->n_lengths = 0;
	svg_length_list->lengths = NULL;
}

const LsmTraitClass lsm_svg_length_list_trait_class = {
	.size = sizeof (LsmSvgLengthList),
	.from_string = lsm_svg_length_list_trait_from_string,
	.to_string = lsm_svg_length_list_trait_to_string,
	.finalize = lsm_svg_length_list_trait_finalize
};

static void
_init_matrix (LsmSvgMatrix *matrix, LsmSvgTransformType transform, unsigned int n_values, double values[])
{
	switch (transform) {
		case LSM_SVG_TRANSFORM_TYPE_SCALE:
			if (n_values == 1) {
				lsm_svg_matrix_init_scale (matrix, values[0], values[0]);
				return;
			} else if (n_values == 2) {
				lsm_svg_matrix_init_scale (matrix, values[0], values[1]);
				return;
			}
			break;
		case LSM_SVG_TRANSFORM_TYPE_TRANSLATE:
			if (n_values == 1) {
				lsm_svg_matrix_init_translate (matrix, values[0], values[0]);
				return;
			} else if (n_values == 2) {
				lsm_svg_matrix_init_translate (matrix, values[0], values[1]);
				return;
			}
			break;
		case LSM_SVG_TRANSFORM_TYPE_MATRIX:
			if (n_values == 6) {
				lsm_svg_matrix_init (matrix,
						  values[0], values[1],
						  values[2], values[3],
						  values[4], values[5]);
				return;
			}
			break;
		case LSM_SVG_TRANSFORM_TYPE_ROTATE:
			if (n_values == 1) {
				lsm_svg_matrix_init_rotate (matrix, values[0] * M_PI / 180.0);
				return;
			} else if (n_values == 3) {
				LsmSvgMatrix matrix_b;

				lsm_svg_matrix_init_translate (matrix, values[1], values[2]);
				lsm_svg_matrix_init_rotate (&matrix_b, values[0] * M_PI / 180.0);
				lsm_svg_matrix_multiply (matrix, &matrix_b, matrix);
				lsm_svg_matrix_init_translate (&matrix_b, -values[1], -values[2]);
				lsm_svg_matrix_multiply (matrix, &matrix_b, matrix);
				return;
			}
			break;
		case LSM_SVG_TRANSFORM_TYPE_SKEW_X:
			if (n_values == 1) {
				lsm_svg_matrix_init_skew_x (matrix, values[0] * M_PI / 180.0);
				return;
			}
			break;
		case LSM_SVG_TRANSFORM_TYPE_SKEW_Y:
			if (n_values == 1) {
				lsm_svg_matrix_init_skew_y (matrix, values[0] * M_PI / 180.0);
				return;
			}
		default:
			break;
	}

	lsm_svg_matrix_init_identity (matrix);
}

static gboolean
lsm_svg_matrix_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgMatrix *matrix = (LsmSvgMatrix *) abstract_trait;

	lsm_svg_matrix_init_identity (matrix);

	while (*string != '\0') {
		LsmSvgTransformType transform;
		double values[6];

		lsm_str_skip_spaces (&string);

		if (strncmp (string, "translate", 9) == 0) {
			transform = LSM_SVG_TRANSFORM_TYPE_TRANSLATE;
			string += 9;
		} else if (strncmp (string, "scale", 5) == 0) {
			transform = LSM_SVG_TRANSFORM_TYPE_SCALE;
			string += 5;
		} else if (strncmp (string, "rotate", 6) == 0) {
			transform = LSM_SVG_TRANSFORM_TYPE_ROTATE;
			string += 6;
		} else if (strncmp (string, "matrix", 6) == 0) {
			transform = LSM_SVG_TRANSFORM_TYPE_MATRIX;
			string += 6;
		} else if (strncmp (string, "skewX", 5) == 0) {
			transform = LSM_SVG_TRANSFORM_TYPE_SKEW_X;
			string += 5;
		} else if (strncmp (string, "skewY", 5) == 0) {
			transform = LSM_SVG_TRANSFORM_TYPE_SKEW_Y;
			string += 5;
		} else
			return FALSE;

		lsm_str_skip_spaces (&string);

		if (*string == '(') {
			unsigned int n_values = 0;

			string++;

			while (*string != ')' && *string != '\0' && n_values < 6) {
				lsm_str_skip_comma_and_spaces (&string);

				if (!lsm_str_parse_double (&string, &values[n_values]))
					break;

				n_values++;
			}

			lsm_str_skip_comma_and_spaces (&string);

			if (*string == ')') {
				LsmSvgMatrix new_matrix;

				string++;

				_init_matrix (&new_matrix, transform, n_values, values);

				lsm_svg_matrix_multiply (matrix, &new_matrix, matrix);
			} else
				return FALSE;
		} else
			return FALSE;
	}

	return TRUE;
}

static char *
lsm_svg_matrix_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgMatrix *matrix = (LsmSvgMatrix *) abstract_trait;

	/* TODO smarter serialization, checking for zeros */
	return g_strdup_printf ("matrix(%g,%g,%g,%g,%g,%g)",
				matrix->a,
				matrix->b,
				matrix->c,
				matrix->d,
				matrix->e,
				matrix->f);
}

const LsmTraitClass lsm_svg_matrix_trait_class = {
	.size = sizeof (LsmSvgMatrix),
	.from_string = lsm_svg_matrix_trait_from_string,
	.to_string = lsm_svg_matrix_trait_to_string
};

static double
_hue_to_rgb (double m1, double m2, double h)
{
	if (h < 0)
		h = h + 1.0;
	if (h > 1)
		h = h - 1.0;
	if (h * 6.0 < 1.0)
		return  m1 + (m2 - m1 ) * h * 6.0;
	if (h * 2.0 < 1.0)
		return m2;
       	if (h * 3.0 < 2.0)
		return m1 + (m2 - m1) * (2.0 / 3.0 - h) * 6.0;

	return m1;
}

static char *
_parse_color (char *string,
	      LsmSvgColor *svg_color,
	      LsmSvgPaintType *paint_type)
{
	unsigned int color = 0;

	lsm_str_skip_spaces (&string);

	if (g_strcmp0 (string, "currentColor") == 0) {
		svg_color->red = -1.0;
		svg_color->green = -1.0;
		svg_color->blue = -1.0;

		*paint_type = LSM_SVG_PAINT_TYPE_CURRENT_COLOR;

		string += 12; /* strlen ("current_color") */

		return string;
	}

	if (*string == '#') {
		int value, i;
		string++;

		for (i = 0; i < 6; i++) {
			if (*string >= '0' && *string <= '9')
				value = *string - '0';
			else if (*string >= 'A' && *string <= 'F')
				value = *string - 'A' + 10;
			else if (*string >= 'a' && *string <= 'f')
				value = *string - 'a' + 10;
			else
				break;

			color = (color << 4) + value;
			string++;
		}

		if (i == 3) {
			color = ((color & 0xf00) << 8) | ((color & 0x0f0) << 4) | (color & 0x00f);
			color |= color << 4;
		} else if (i != 6)
			color = 0;

		*paint_type = LSM_SVG_PAINT_TYPE_RGB_COLOR;
	} else if (strncmp (string, "rgb(", 4) == 0) {
		int i;
		double value;


		string += 4; /* strlen ("rgb(") */

		lsm_str_skip_spaces (&string);

		for (i = 0; i < 3; i++) {
			if (!lsm_str_parse_double (&string, &value))
				break;

			if (*string == '%') {
				value = value * 255.0 / 100.0;
				string++;
			}

			if (i < 2)
				lsm_str_skip_comma_and_spaces (&string);

			color = (color << 8) + (int) (0.5 + CLAMP (value, 0.0, 255.0));
		}

		lsm_str_skip_spaces (&string);

		if (*string != ')' || i != 3)
			color = 0;

		*paint_type = LSM_SVG_PAINT_TYPE_RGB_COLOR;
	} else if (strncmp (string, "hsl(", 4) == 0) {
		double value[3];
		int i;

		string += 4; /* strlen ("hsl(") */

		lsm_str_skip_spaces (&string);

		for (i = 0; i < 3; i++) {
			if (!lsm_str_parse_double (&string, &value[i]))
				break;

			if (i > 0) {
			       if (*string != '%')
				break;
			       string++;
			}

			lsm_str_skip_comma_and_spaces (&string);
		}

		lsm_str_skip_spaces (&string);

		if (*string == ')' && i == 3) {
			double m1, m2;
			double h,s,l;

			h = value[0] / 360.0;
			s = value[1] / 100.0; 
			l = value[2] / 100.0;

			if (l <= 0.5)
				m2 = l*(s + 1.0);
			else
				m2 = l + s - l * s;
			m1 = l * 2.0 - m2;

			svg_color->red = _hue_to_rgb (m1, m2, h + 1.0/3.0);
			svg_color->green  = _hue_to_rgb (m1, m2, h);		
			svg_color->blue = _hue_to_rgb (m1, m2, h - 1.0/3.0);

			*paint_type = LSM_SVG_PAINT_TYPE_RGB_COLOR;

			return string;
		}
	} else if (g_strcmp0 (string, "none") != 0) {
		color = lsm_svg_color_from_string (string);

		*paint_type = LSM_SVG_PAINT_TYPE_RGB_COLOR;
	} else {
		*paint_type = LSM_SVG_PAINT_TYPE_NONE;
	}

	svg_color->red = (double) ((color & 0xff0000) >> 16) / 255.0;
	svg_color->green = (double) ((color & 0x00ff00) >> 8) / 255.0;
	svg_color->blue = (double) (color & 0x0000ff) / 255.0;

	return string;
}

static gboolean
lsm_svg_paint_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgPaint *paint = (LsmSvgPaint *) abstract_trait;
	LsmSvgPaintType paint_type;

	g_free (paint->url);

	if (strncmp (string, "url(#", 5) == 0) {
		unsigned int length;

		length = 5;
		while (string[length] != ')')
			length++;
		length++;

		paint->url = g_new (char, length);
		if (paint->url != NULL) {
			memcpy (paint->url, string, length - 1);
			paint->url[length - 1] = '\0';
		}
		string += length;
	} else {
		paint->url = NULL;
	}

	string = _parse_color (string, &paint->color, &paint_type);

	if (paint->url != NULL)
		switch (paint_type) {
			case LSM_SVG_PAINT_TYPE_RGB_COLOR:
				paint_type = LSM_SVG_PAINT_TYPE_URI_RGB_COLOR;
				break;
			case LSM_SVG_PAINT_TYPE_CURRENT_COLOR:
				paint_type = LSM_SVG_PAINT_TYPE_URI_CURRENT_COLOR;
				break;
			case LSM_SVG_PAINT_TYPE_NONE:
				paint_type = LSM_SVG_PAINT_TYPE_URI;
				break;
			case LSM_SVG_PAINT_TYPE_RGB_COLOR_ICC_COLOR:
				paint_type = LSM_SVG_PAINT_TYPE_URI_RGB_COLOR_ICC_COLOR;
				break;
			default:
				paint_type = LSM_SVG_PAINT_TYPE_URI;
				break;
		}

	paint->type = paint_type;

	/* TODO better syntax error check */

	return TRUE;
}

static char *
lsm_svg_paint_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgPaint *paint = (LsmSvgPaint *) abstract_trait;

	if (paint->color.red < 0.0 || paint->color.green < 0.0 || paint->color.blue < 0.0)
		return g_strdup ("currentColor");

	/* FIXME */
	if (paint->url != NULL)
		return g_strdup (paint->url);

	return g_strdup_printf ("rgb(%g%%,%g%%,%g%%)",
				100.0 * paint->color.red,
				100.0 * paint->color.green,
				100.0 * paint->color.blue);
}

const LsmTraitClass lsm_svg_paint_trait_class = {
	.size = sizeof (LsmSvgPaint),
	.from_string = lsm_svg_paint_trait_from_string,
	.to_string = lsm_svg_paint_trait_to_string
};

static gboolean
lsm_svg_fill_rule_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgFillRule *trait = (LsmSvgFillRule *) abstract_trait;

	*trait = lsm_svg_fill_rule_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_fill_rule_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgFillRule *trait = (LsmSvgFillRule *) abstract_trait;

	return g_strdup (lsm_svg_fill_rule_to_string (*trait));
}

const LsmTraitClass lsm_svg_fill_rule_trait_class = {
	.size = sizeof (LsmSvgFillRule),
	.from_string = lsm_svg_fill_rule_trait_from_string,
	.to_string = lsm_svg_fill_rule_trait_to_string
};

static gboolean
lsm_svg_font_style_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgFontStyle *trait = (LsmSvgFontStyle *) abstract_trait;

	*trait = lsm_svg_font_style_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_font_style_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgFontStyle *trait = (LsmSvgFontStyle *) abstract_trait;

	return g_strdup (lsm_svg_font_style_to_string (*trait));
}

const LsmTraitClass lsm_svg_font_style_trait_class = {
	.size = sizeof (LsmSvgFontStyle),
	.from_string = lsm_svg_font_style_trait_from_string,
	.to_string = lsm_svg_font_style_trait_to_string
};

static gboolean
lsm_svg_font_stretch_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgFontStretch *trait = (LsmSvgFontStretch *) abstract_trait;

	*trait = lsm_svg_font_stretch_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_font_stretch_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgFontStretch *trait = (LsmSvgFontStretch *) abstract_trait;

	return g_strdup (lsm_svg_font_stretch_to_string (*trait));
}

const LsmTraitClass lsm_svg_font_stretch_trait_class = {
	.size = sizeof (LsmSvgFontStretch),
	.from_string = lsm_svg_font_stretch_trait_from_string,
	.to_string = lsm_svg_font_stretch_trait_to_string
};

static gboolean
lsm_svg_font_weight_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgFontWeight *trait = (LsmSvgFontWeight *) abstract_trait;

	*trait = lsm_svg_font_weight_from_string (string);

	if (*trait < 0)
		*trait = strtol (string, NULL, 10);

	return *trait >= 100 && *trait <= 1000;
}

static char *
lsm_svg_font_weight_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgFontWeight *trait = (LsmSvgFontWeight *) abstract_trait;
	const char *string;

	string = lsm_svg_font_weight_to_string (*trait);

	if (string != NULL)
		return g_strdup (string);

	return g_strdup_printf ("%d", *trait);
}

const LsmTraitClass lsm_svg_font_weight_trait_class = {
	.size = sizeof (LsmSvgFontWeight),
	.from_string = lsm_svg_font_weight_trait_from_string,
	.to_string = lsm_svg_font_weight_trait_to_string
};

static gboolean
lsm_svg_line_join_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgLineJoin *trait = (LsmSvgLineJoin *) abstract_trait;

	*trait = lsm_svg_line_join_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_line_join_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgLineJoin *trait = (LsmSvgLineJoin *) abstract_trait;

	return g_strdup (lsm_svg_line_join_to_string (*trait));
}

const LsmTraitClass lsm_svg_line_join_trait_class = {
	.size = sizeof (LsmSvgLineJoin),
	.from_string = lsm_svg_line_join_trait_from_string,
	.to_string = lsm_svg_line_join_trait_to_string
};

static gboolean
lsm_svg_line_cap_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgLineCap *trait = (LsmSvgLineCap *) abstract_trait;

	*trait = lsm_svg_line_cap_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_line_cap_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgLineCap *trait = (LsmSvgLineCap *) abstract_trait;

	return g_strdup (lsm_svg_line_cap_to_string (*trait));
}

const LsmTraitClass lsm_svg_line_cap_trait_class = {
	.size = sizeof (LsmSvgLineCap),
	.from_string = lsm_svg_line_cap_trait_from_string,
	.to_string = lsm_svg_line_cap_trait_to_string
};

LsmSvgDashArray *
lsm_svg_dash_array_new (unsigned int n_dashes)
{
	LsmSvgDashArray *array;

	g_return_val_if_fail (n_dashes > 0, (LsmSvgDashArray *) &lsm_svg_dash_array_null);

	array = g_new (LsmSvgDashArray, 1);
	array->n_dashes = n_dashes;
	array->dashes = g_new (LsmSvgLength, n_dashes);

	return array;
}

void
lsm_svg_dash_array_free (LsmSvgDashArray *array)
{
	if (array == NULL || array == &lsm_svg_dash_array_null)
		return;

	g_free (array->dashes);
	g_free (array);
}

LsmSvgDashArray *
lsm_svg_dash_array_duplicate (const LsmSvgDashArray *origin)
{
	LsmSvgDashArray *duplicate;

	if (origin == NULL || origin == &lsm_svg_dash_array_null)
		return (LsmSvgDashArray *) &lsm_svg_dash_array_null;

	duplicate = lsm_svg_dash_array_new (origin->n_dashes);

	if (duplicate != &lsm_svg_dash_array_null)
		memcpy (duplicate->dashes, origin->dashes, sizeof (LsmSvgLength) * origin->n_dashes);

	return duplicate;
}

static gboolean
lsm_svg_dash_array_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgDashArray *dash_array = (LsmSvgDashArray *) abstract_trait;
	unsigned int n_dashes = 1;
	double value;
	double sum = 0.0;
	gboolean is_error = FALSE;

	g_free (dash_array->dashes);
	dash_array->n_dashes = 0;
	dash_array->dashes = NULL;

	if (strcmp (string, "none") != 0 &&
	    strcmp (string, "inherit")) {
		char *iter = (char *) string;
		unsigned int i;

		while (*iter != '\0') {
			if (*iter == ',' ||
			    *iter == ' ') {
				n_dashes++;
				do {
					iter++;
				} while (*iter == ',' ||
					 *iter == ' ');
			} else
				iter++;
		}

		if (n_dashes > 0) {
			LsmSvgLength length;

			dash_array->n_dashes = n_dashes;
			dash_array->dashes = g_new (LsmSvgLength, n_dashes);

			iter = (char *)string;
			lsm_str_skip_spaces (&iter);

			for (i = 0; i < n_dashes; i++) {
				if (lsm_str_parse_double (&iter, &length.value_unit)) {
					length.type = lsm_svg_length_type_from_string (iter);
					dash_array->dashes[i] = length;
					while (*iter != '\0' && *iter != ' ' && *iter != ',')
						iter ++;
				} else {
					dash_array->dashes[i].value_unit = 0.0;
					dash_array->dashes[i].type = LSM_SVG_LENGTH_TYPE_NUMBER;
				}
				lsm_str_skip_comma_and_spaces (&iter);

				value = dash_array->dashes[i].value_unit;
				if (value < 0.0) {
					is_error = TRUE;
					break;
				}
				sum += value;
			}
		}

		if (is_error || sum <= 0.0) {
			g_free (dash_array->dashes);
			dash_array->n_dashes = 0;
			dash_array->dashes = NULL;

			return !is_error;
		}
	}

	return TRUE;
}

static char *
lsm_svg_dash_array_trait_to_string (LsmTrait *abstract_trait)
{
	g_assert_not_reached ();

	return NULL;
}

static void
lsm_svg_dash_array_trait_finalize (LsmTrait *abstract_trait)
{
	LsmSvgDashArray *dash_array = (LsmSvgDashArray *) abstract_trait;

	g_free (dash_array->dashes);
	dash_array->n_dashes = 0;
	dash_array->dashes = NULL;
}

const LsmTraitClass lsm_svg_dash_array_trait_class = {
	.size = sizeof (LsmSvgDashArray),
	.from_string = lsm_svg_dash_array_trait_from_string,
	.to_string = lsm_svg_dash_array_trait_to_string,
	.finalize = lsm_svg_dash_array_trait_finalize
};

static gboolean
lsm_svg_display_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgDisplay *trait = (LsmSvgDisplay *) abstract_trait;

	*trait = lsm_svg_display_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_display_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgDisplay *trait = (LsmSvgDisplay *) abstract_trait;

	return g_strdup (lsm_svg_display_to_string (*trait));
}

const LsmTraitClass lsm_svg_display_trait_class = {
	.size = sizeof (LsmSvgDisplay),
	.from_string = lsm_svg_display_trait_from_string,
	.to_string = lsm_svg_display_trait_to_string
};

static gboolean
lsm_svg_color_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgColor *color = (LsmSvgColor *) abstract_trait;
	LsmSvgPaintType paint_type;

	_parse_color (string, color, &paint_type);

	/* TODO Better error check */

	return TRUE;
}

static char *
lsm_svg_color_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgColor *color = (LsmSvgColor *) abstract_trait;

	if (color->red < 0.0 || color->green < 0.0 || color->blue < 0.0)
		return g_strdup ("currentColor");

	return g_strdup_printf ("rgb(%g%%,%g%%,%g%%)",
				100.0 * color->red,
				100.0 * color->green,
				100.0 * color->blue);
}

const LsmTraitClass lsm_svg_color_trait_class = {
	.size = sizeof (LsmSvgColor),
	.from_string = lsm_svg_color_trait_from_string,
	.to_string = lsm_svg_color_trait_to_string
};

static gboolean
lsm_svg_marker_units_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgMarkerUnits *trait = (LsmSvgMarkerUnits *) abstract_trait;

	*trait = lsm_svg_marker_units_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_marker_units_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgMarkerUnits *trait = (LsmSvgMarkerUnits *) abstract_trait;

	return g_strdup (lsm_svg_marker_units_to_string (*trait));
}

const LsmTraitClass lsm_svg_marker_units_trait_class = {
	.size = sizeof (LsmSvgMarkerUnits),
	.from_string = lsm_svg_marker_units_trait_from_string,
	.to_string = lsm_svg_marker_units_trait_to_string
};

static gboolean
lsm_svg_pattern_units_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgPatternUnits *trait = (LsmSvgPatternUnits *) abstract_trait;

	*trait = lsm_svg_pattern_units_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_pattern_units_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgPatternUnits *trait = (LsmSvgPatternUnits *) abstract_trait;

	return g_strdup (lsm_svg_pattern_units_to_string (*trait));
}

const LsmTraitClass lsm_svg_pattern_units_trait_class = {
	.size = sizeof (LsmSvgPatternUnits),
	.from_string = lsm_svg_pattern_units_trait_from_string,
	.to_string = lsm_svg_pattern_units_trait_to_string
};

static gboolean
lsm_svg_preserve_aspect_ratio_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgPreserveAspectRatio *trait = (LsmSvgPreserveAspectRatio *) abstract_trait;

	char **tokens;
	unsigned int i = 0;

	tokens = g_strsplit (string, " ", -1);

	if (tokens[i] != NULL && strcmp (tokens[i], "defer") == 0) {
		trait->defer = TRUE;
		i++;
	} else
		trait->defer = FALSE;

	if (tokens[i] != NULL) {
		trait->align = lsm_svg_align_from_string (tokens[i]);
		i++;
		if (tokens[i] != NULL)
			trait->meet_or_slice = lsm_svg_meet_or_slice_from_string (tokens[i]);
		else
			trait->meet_or_slice = LSM_SVG_MEET_OR_SLICE_MEET;
	} else trait->align = LSM_SVG_ALIGN_X_MID_Y_MID;

	g_strfreev (tokens);

	/* TODO Better error check */

	return TRUE;
}

static char *
lsm_svg_preserve_aspect_ratio_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgPreserveAspectRatio *trait = (LsmSvgPreserveAspectRatio *) abstract_trait;

	return g_strdup_printf ("%s%s %s", trait->defer ? "defer " : "",
				lsm_svg_align_to_string (trait->align),
				lsm_svg_meet_or_slice_to_string (trait->meet_or_slice));
}

const LsmTraitClass lsm_svg_preserve_aspect_ratio_trait_class = {
	.size = sizeof (LsmSvgPreserveAspectRatio),
	.from_string = lsm_svg_preserve_aspect_ratio_trait_from_string,
	.to_string = lsm_svg_preserve_aspect_ratio_trait_to_string
};

static gboolean
lsm_svg_spread_method_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgSpreadMethod *trait = (LsmSvgSpreadMethod *) abstract_trait;

	*trait = lsm_svg_spread_method_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_spread_method_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgSpreadMethod *trait = (LsmSvgSpreadMethod *) abstract_trait;

	return g_strdup (lsm_svg_spread_method_to_string (*trait));
}

const LsmTraitClass lsm_svg_spread_method_trait_class = {
	.size = sizeof (LsmSvgSpreadMethod),
	.from_string = lsm_svg_spread_method_trait_from_string,
	.to_string = lsm_svg_spread_method_trait_to_string
};

static gboolean
lsm_svg_angle_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgAngle *trait = (LsmSvgAngle *) abstract_trait;
	char *end_ptr;

	if (g_strcmp0 (string, "auto") == 0) {
		trait->type = LSM_SVG_ANGLE_TYPE_AUTO;
		trait->angle = 0.0;

		return TRUE;
	}

	trait->type = LSM_SVG_ANGLE_TYPE_FIXED;
	trait->angle = g_ascii_strtod (string, &end_ptr);

	return end_ptr != string;
}

static char *
lsm_svg_angle_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgAngle *trait = (LsmSvgAngle *) abstract_trait;

	if (trait->type == LSM_SVG_ANGLE_TYPE_AUTO)
		return g_strdup ("auto");

	return g_strdup_printf ("%g", trait->angle);
}

const LsmTraitClass lsm_svg_angle_trait_class = {
	.size = sizeof (LsmSvgAngle),
	.from_string = lsm_svg_angle_trait_from_string,
	.to_string = lsm_svg_angle_trait_to_string
};

static gboolean
lsm_svg_text_anchor_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgTextAnchor *trait = (LsmSvgTextAnchor *) abstract_trait;

	*trait = lsm_svg_text_anchor_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_text_anchor_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgTextAnchor *trait = (LsmSvgTextAnchor *) abstract_trait;

	return g_strdup (lsm_svg_text_anchor_to_string (*trait));
}

const LsmTraitClass lsm_svg_text_anchor_trait_class = {
	.size = sizeof (LsmSvgTextAnchor),
	.from_string = lsm_svg_text_anchor_trait_from_string,
	.to_string = lsm_svg_text_anchor_trait_to_string
};

static gboolean
lsm_svg_visibility_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgVisibility *trait = (LsmSvgVisibility *) abstract_trait;

	*trait = lsm_svg_visibility_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_visibility_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgVisibility *trait = (LsmSvgVisibility *) abstract_trait;

	return g_strdup (lsm_svg_visibility_to_string (*trait));
}

const LsmTraitClass lsm_svg_visibility_trait_class = {
	.size = sizeof (LsmSvgVisibility),
	.from_string = lsm_svg_visibility_trait_from_string,
	.to_string = lsm_svg_visibility_trait_to_string
};

static gboolean
lsm_svg_one_or_two_double_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgOneOrTwoDouble *trait = (LsmSvgOneOrTwoDouble *) abstract_trait;
	char *end_ptr;

	trait->a = g_ascii_strtod (string, &end_ptr);
	if (end_ptr == string) {
		trait->b = 0.0;
		return FALSE;
	}

	string = end_ptr;

	lsm_str_skip_spaces (&string);

	if (string[0] == '\0') {
		trait->b = trait->a;
		return TRUE;
	}

	trait->b = g_ascii_strtod (string, &end_ptr);

	return end_ptr != string;
}

static char *
lsm_svg_one_or_two_double_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgOneOrTwoDouble *trait = (LsmSvgOneOrTwoDouble *) abstract_trait;

	if (trait->a == trait->b)
		return g_strdup_printf ("%g", trait->a);

	return g_strdup_printf ("%g %g", trait->a, trait->b);
}

const LsmTraitClass lsm_svg_one_or_two_double_trait_class = {
	.size = sizeof (double),
	.from_string = lsm_svg_one_or_two_double_trait_from_string,
	.to_string = lsm_svg_one_or_two_double_trait_to_string
};

static gboolean
lsm_svg_overflow_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgOverflow *trait = (LsmSvgOverflow *) abstract_trait;

	*trait = lsm_svg_overflow_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_overflow_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgOverflow *trait = (LsmSvgOverflow *) abstract_trait;

	return g_strdup (lsm_svg_overflow_to_string (*trait));
}

const LsmTraitClass lsm_svg_overflow_trait_class = {
	.size = sizeof (LsmSvgOverflow),
	.from_string = lsm_svg_overflow_trait_from_string,
	.to_string = lsm_svg_overflow_trait_to_string
};

static gboolean
lsm_svg_writing_mode_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmSvgWritingMode *trait = (LsmSvgWritingMode *) abstract_trait;

	*trait = lsm_svg_writing_mode_from_string (string);

	return *trait >= 0;
}

static char *
lsm_svg_writing_mode_trait_to_string (LsmTrait *abstract_trait)
{
	LsmSvgWritingMode *trait = (LsmSvgWritingMode *) abstract_trait;

	return g_strdup (lsm_svg_writing_mode_to_string (*trait));
}

const LsmTraitClass lsm_svg_writing_mode_trait_class = {
	.size = sizeof (LsmSvgWritingMode),
	.from_string = lsm_svg_writing_mode_trait_from_string,
	.to_string = lsm_svg_writing_mode_trait_to_string
};

