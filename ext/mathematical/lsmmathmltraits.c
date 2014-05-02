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

#include <pango/pango-attributes.h>
#include <lsmmathmltraits.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

static gboolean
lsm_mathml_boolean_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	gboolean *value = (gboolean *) abstract_trait;

	if (g_strcmp0 (string, "true") == 0) {
		*value = TRUE;
		return TRUE;
	} else if (g_strcmp0 (string, "false") == 0) {
		*value = FALSE;
		return TRUE;
	}

	*value = FALSE;
	return FALSE;
}

static char *
lsm_mathml_boolean_trait_to_string (LsmTrait *abstract_trait)
{
	gboolean *value = (gboolean *) abstract_trait;

	return g_strdup_printf ("%s", *value ? "true" : "false");
}

const LsmTraitClass lsm_mathml_boolean_trait_class = {
	.size = sizeof (gboolean),
	.from_string = lsm_mathml_boolean_trait_from_string,
	.to_string = lsm_mathml_boolean_trait_to_string
};

static gboolean
lsm_mathml_unsigned_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	unsigned int *value = (unsigned int *) abstract_trait;
	char *end_ptr;

	*value = strtol (string, &end_ptr, 10);

	return end_ptr != string;
}

static char *
lsm_mathml_unsigned_trait_to_string (LsmTrait *abstract_trait)
{
	unsigned int *value = (unsigned int *) abstract_trait;

	return g_strdup_printf ("%u", *value);
}

const LsmTraitClass lsm_mathml_unsigned_trait_class = {
	.size = sizeof (unsigned),
	.from_string = lsm_mathml_unsigned_trait_from_string,
	.to_string = lsm_mathml_unsigned_trait_to_string
};

static gboolean
lsm_mathml_display_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmMathmlDisplay *value = (LsmMathmlDisplay *) abstract_trait;

	*value = lsm_mathml_display_from_string (string);

	return *value >= 0;
}

static char *
lsm_mathml_display_trait_to_string (LsmTrait *abstract_trait)
{
	LsmMathmlDisplay *value = (LsmMathmlDisplay *) abstract_trait;

	return g_strdup (lsm_mathml_display_to_string (*value));
}

const LsmTraitClass lsm_mathml_display_trait_class = {
	.size = sizeof (int),
	.from_string = lsm_mathml_display_trait_from_string,
	.to_string = lsm_mathml_display_trait_to_string
};

static gboolean
lsm_mathml_mode_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmMathmlMode *value = (LsmMathmlMode *) abstract_trait;

	*value = lsm_mathml_mode_from_string (string);

	return *value >= 0;
}

static char *
lsm_mathml_mode_trait_to_string (LsmTrait *abstract_trait)
{
	LsmMathmlMode *value = (LsmMathmlMode *) abstract_trait;

	return g_strdup (lsm_mathml_mode_to_string (*value));
}

const LsmTraitClass lsm_mathml_mode_trait_class = {
	.size = sizeof (int),
	.from_string = lsm_mathml_mode_trait_from_string,
	.to_string = lsm_mathml_mode_trait_to_string
};

static gboolean
lsm_mathml_line_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmMathmlLine *value = (LsmMathmlLine *) abstract_trait;

	*value = lsm_mathml_line_from_string (string);

	return *value >= 0;
}

static char *
lsm_mathml_line_trait_to_string (LsmTrait *abstract_trait)
{
	LsmMathmlLine *value = (LsmMathmlLine *) abstract_trait;

	return g_strdup (lsm_mathml_line_to_string (*value));
}

const LsmTraitClass lsm_mathml_line_trait_class = {
	.size = sizeof (int),
	.from_string = lsm_mathml_line_trait_from_string,
	.to_string = lsm_mathml_line_trait_to_string
};

static gboolean
lsm_mathml_font_style_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmMathmlFontStyle *value = (LsmMathmlFontStyle *) abstract_trait;

	*value = lsm_mathml_font_style_from_string (string);

	return *value >= 0;
}

static char *
lsm_mathml_font_style_trait_to_string (LsmTrait *abstract_trait)
{
	LsmMathmlFontStyle *value = (LsmMathmlFontStyle *) abstract_trait;

	return g_strdup (lsm_mathml_font_style_to_string (*value));
}

const LsmTraitClass lsm_mathml_font_style_trait_class = {
	.size = sizeof (int),
	.from_string = lsm_mathml_font_style_trait_from_string,
	.to_string = lsm_mathml_font_style_trait_to_string
};

static gboolean
lsm_mathml_font_weight_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmMathmlFontWeight *value = (LsmMathmlFontWeight *) abstract_trait;

	*value = lsm_mathml_font_weight_from_string (string);

	return *value >= 0;
}

static char *
lsm_mathml_font_weight_trait_to_string (LsmTrait *abstract_trait)
{
	LsmMathmlFontWeight *value = (LsmMathmlFontWeight *) abstract_trait;

	return g_strdup (lsm_mathml_font_weight_to_string (*value));
}

const LsmTraitClass lsm_mathml_font_weight_trait_class = {
	.size = sizeof (int),
	.from_string = lsm_mathml_font_weight_trait_from_string,
	.to_string = lsm_mathml_font_weight_trait_to_string
};

static gboolean
lsm_mathml_variant_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmMathmlVariant *value = (LsmMathmlVariant *) abstract_trait;

	*value = lsm_mathml_variant_from_string (string);

	return *value >= 0;
}

static char *
lsm_mathml_variant_trait_to_string (LsmTrait *abstract_trait)
{
	LsmMathmlVariant *value = (LsmMathmlVariant *) abstract_trait;

	return g_strdup (lsm_mathml_variant_to_string (*value));
}

const LsmTraitClass lsm_mathml_variant_trait_class = {
	.size = sizeof (int),
	.from_string = lsm_mathml_variant_trait_from_string,
	.to_string = lsm_mathml_variant_trait_to_string
};

static gboolean
lsm_mathml_form_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmMathmlForm *value = (LsmMathmlForm *) abstract_trait;

	*value = lsm_mathml_form_from_string (string);

	return *value >= 0;
}

static char *
lsm_mathml_form_trait_to_string (LsmTrait *abstract_trait)
{
	LsmMathmlForm *value = (LsmMathmlForm *) abstract_trait;

	return g_strdup (lsm_mathml_form_to_string (*value));
}

const LsmTraitClass lsm_mathml_form_trait_class = {
	.size = sizeof (int),
	.from_string = lsm_mathml_form_trait_from_string,
	.to_string = lsm_mathml_form_trait_to_string
};

typedef int (*LsmMathmlEnumFromString) (const char *string);
typedef char * (*LsmMathmlEnumToString) (unsigned int value);

static gboolean
lsm_mathml_enum_list_trait_from_string (LsmMathmlEnumList *enum_list,
					LsmMathmlEnumFromString from_string,
					char *string)
{
	char **items;
	unsigned int i;
	int enum_value;

	g_free (enum_list->values);

	items = g_strsplit_set (string, " ", -1);
	enum_list->n_values = g_strv_length (items);

	enum_list->values = g_new (int, enum_list->n_values);
	for (i = 0; i < enum_list->n_values; i++) {
		enum_value = from_string (items[i]);
		if (enum_value < 0) {
			g_free (enum_list->values);
			enum_list->values = NULL;
			enum_list->n_values = 0;
			g_strfreev (items);

			return FALSE;
		}
		enum_list->values[i] = enum_value;
	}

	g_strfreev (items);

	return TRUE;
}

static char *
lsm_mathml_enum_list_trait_to_string (LsmMathmlEnumList *enum_list,
				      LsmMathmlEnumToString to_string)
{
	return g_strdup ("FIXME");
}

static void
lsm_mathml_enum_list_trait_init (LsmTrait *abstract_trait,
				 const LsmTrait *abstract_default)
{
	LsmMathmlEnumList *enum_list = (LsmMathmlEnumList *) abstract_trait;
	LsmMathmlEnumList *enum_list_defaut = (LsmMathmlEnumList *) abstract_default;

	enum_list->n_values = enum_list_defaut->n_values;
	if (enum_list->n_values == 0)
		enum_list->values = NULL;
	else {
		enum_list->values = g_new (int, enum_list->n_values);
		memcpy (enum_list->values, enum_list_defaut->values, sizeof (int) * enum_list->n_values);
	}
}

void
lsm_mathml_enum_list_init (LsmMathmlEnumList *enum_list, const LsmMathmlEnumList *enum_list_default)
{
	g_return_if_fail (enum_list != NULL);
	g_return_if_fail (enum_list_default != NULL);

	lsm_mathml_enum_list_trait_init (enum_list, enum_list_default);
}

static void
lsm_mathml_enum_list_trait_finalize (LsmTrait *abstract_trait)
{
	LsmMathmlEnumList *enum_list = (LsmMathmlEnumList *) abstract_trait;

	g_free (enum_list->values);
	enum_list->values = NULL;
	enum_list->n_values = 0;
}

static gboolean
lsm_mathml_row_align_list_trait_from_string (LsmTrait *abstract_trait,
					     char *string)
{
	return lsm_mathml_enum_list_trait_from_string ((LsmMathmlEnumList *) abstract_trait,
						       (LsmMathmlEnumFromString) lsm_mathml_row_align_from_string,
						       string);
}

static char *
lsm_mathml_row_align_list_trait_to_string (LsmTrait *abstract_trait)
{
	return lsm_mathml_enum_list_trait_to_string ((LsmMathmlEnumList *) abstract_trait,
						     (LsmMathmlEnumToString) lsm_mathml_row_align_to_string);
}

const LsmTraitClass lsm_mathml_row_align_list_trait_class = {
	.size = sizeof (LsmMathmlEnumList),
	.from_string = lsm_mathml_row_align_list_trait_from_string,
	.to_string = lsm_mathml_row_align_list_trait_to_string,
	.init = lsm_mathml_enum_list_trait_init,
	.finalize = lsm_mathml_enum_list_trait_finalize
};

static gboolean
lsm_mathml_column_align_list_trait_from_string (LsmTrait *abstract_trait,
					     char *string)
{
	return lsm_mathml_enum_list_trait_from_string ((LsmMathmlEnumList *) abstract_trait,
						       (LsmMathmlEnumFromString) lsm_mathml_column_align_from_string,
						       string);
}

static char *
lsm_mathml_column_align_list_trait_to_string (LsmTrait *abstract_trait)
{
	return lsm_mathml_enum_list_trait_to_string ((LsmMathmlEnumList *) abstract_trait,
						     (LsmMathmlEnumToString) lsm_mathml_column_align_to_string);
}

const LsmTraitClass lsm_mathml_column_align_list_trait_class = {
	.size = sizeof (LsmMathmlEnumList),
	.from_string = lsm_mathml_column_align_list_trait_from_string,
	.to_string = lsm_mathml_column_align_list_trait_to_string,
	.init = lsm_mathml_enum_list_trait_init,
	.finalize = lsm_mathml_enum_list_trait_finalize
};

static gboolean
lsm_mathml_line_list_trait_from_string (LsmTrait *abstract_trait,
					     char *string)
{
	return lsm_mathml_enum_list_trait_from_string ((LsmMathmlEnumList *) abstract_trait,
						       (LsmMathmlEnumFromString) lsm_mathml_line_from_string,
						       string);
}

static char *
lsm_mathml_line_list_trait_to_string (LsmTrait *abstract_trait)
{
	return lsm_mathml_enum_list_trait_to_string ((LsmMathmlEnumList *) abstract_trait,
						     (LsmMathmlEnumToString) lsm_mathml_line_to_string);
}

const LsmTraitClass lsm_mathml_line_list_trait_class = {
	.size = sizeof (LsmMathmlEnumList),
	.from_string = lsm_mathml_line_list_trait_from_string,
	.to_string = lsm_mathml_line_list_trait_to_string,
	.init = lsm_mathml_enum_list_trait_init,
	.finalize = lsm_mathml_enum_list_trait_finalize
};

static gboolean
lsm_mathml_script_level_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmMathmlScriptLevel *value = (LsmMathmlScriptLevel *) abstract_trait;
	char *end_ptr;

	value->level = strtol (string, &end_ptr, 10);

	if (string[0] == '+')
		value->sign = LSM_MATHML_SCRIPT_LEVEL_SIGN_PLUS;
	else if (string[0] == '-')
		value->sign = LSM_MATHML_SCRIPT_LEVEL_SIGN_MINUS;
	else
		value->sign = LSM_MATHML_SCRIPT_LEVEL_SIGN_NONE;

	return end_ptr != string;
}

static char *
lsm_mathml_script_level_trait_to_string (LsmTrait *abstract_trait)
{
	LsmMathmlScriptLevel *value = (LsmMathmlScriptLevel *) abstract_trait;

	if (value->sign == LSM_MATHML_SCRIPT_LEVEL_SIGN_PLUS)
			return g_strdup_printf ("+%d", value->level);

	return g_strdup_printf ("%d", value->level);
}

const LsmTraitClass lsm_mathml_script_level_trait_class = {
	.size = sizeof (int),
	.from_string = lsm_mathml_script_level_trait_from_string,
	.to_string = lsm_mathml_script_level_trait_to_string
};

static gboolean
lsm_mathml_double_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	double *value = (double *) abstract_trait;
	char *end_ptr;

	*value = g_ascii_strtod (string, &end_ptr);

	return end_ptr != string;
}

static char *
lsm_mathml_double_trait_to_string (LsmTrait *abstract_trait)
{
	double *value = (double *) abstract_trait;

	return g_strdup_printf ("%g", *value);
}

const LsmTraitClass lsm_mathml_double_trait_class = {
	.size = sizeof (double),
	.from_string = lsm_mathml_double_trait_from_string,
	.to_string = lsm_mathml_double_trait_to_string
};

static LsmMathmlColor *
lsm_mathml_color_copy (LsmMathmlColor *color)
{
	LsmMathmlColor *copy;

	copy = g_new (LsmMathmlColor, 1);
	memcpy (copy, color, sizeof (LsmMathmlColor));

	return copy;
}

GType
lsm_mathml_color_get_type (void)
{
	static GType our_type = 0;
	if (our_type == 0)
		our_type = g_boxed_type_register_static
			("LsmMathmlColor",
			 (GBoxedCopyFunc) lsm_mathml_color_copy,
			 (GBoxedFreeFunc) g_free);
	return our_type;
}

static gboolean
lsm_mathml_color_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmMathmlColor *color = (LsmMathmlColor *) abstract_trait;
	PangoColor pango_color;
	gboolean result;

	if (strcmp (string, "transparent") == 0) {
		color->red = 0.0;
		color->green = 0.0;
		color->blue = 0.0;
		color->alpha = 0.0;

		return TRUE;
	}

	result = pango_color_parse (&pango_color, string);
	color->alpha = 1.0;
	color->red = pango_color.red / 65535.0;
	color->green = pango_color.green / 65535.0;
	color->blue = pango_color.blue / 65535.0;

	return result;
}

static char *
lsm_mathml_color_trait_to_string (LsmTrait *abstract_trait)
{
	LsmMathmlColor *color = (LsmMathmlColor *) abstract_trait;
	PangoColor pango_color;

	if (color->alpha <= 0.0)
		return g_strdup ("transparent");

	pango_color.red = ((int) ((double) 0.5 + 65535.0 * color->red));
	pango_color.blue = ((int) ((double) 0.5 + 65535.0 * color->blue));
	pango_color.green = ((int) ((double) 0.5 + 65535.0 * color->green));

	return pango_color_to_string (&pango_color);
}

const LsmTraitClass lsm_mathml_color_trait_class = {
	.size = sizeof (LsmMathmlColor),
	.from_string = lsm_mathml_color_trait_from_string,
	.to_string = lsm_mathml_color_trait_to_string
};

static gboolean
lsm_mathml_string_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	char **value = (char **) abstract_trait;

	g_free (*value);
	*value = g_strdup (string);

	return TRUE;
}

static char *
lsm_mathml_string_trait_to_string (LsmTrait *abstract_trait)
{
	char **value = (char **) abstract_trait;

	return g_strdup (*value);
}

static void
lsm_mathml_string_trait_init (LsmTrait *abstract_trait,
			      const LsmTrait *abstract_default)
{
	char **value = (char **) abstract_trait;
	char **default_value = (char **) abstract_default;

	*value = g_strdup (*default_value);
}

static void
lsm_mathml_string_trait_finalize (LsmTrait *abstract_trait)
{
	char **value = (char **) abstract_trait;

	g_free (*value);
	*value = NULL;
}

const LsmTraitClass lsm_mathml_string_trait_class = {
	.size = sizeof (char *),
	.from_string = lsm_mathml_string_trait_from_string,
	.to_string = lsm_mathml_string_trait_to_string,
	.init = lsm_mathml_string_trait_init,
	.finalize = lsm_mathml_string_trait_finalize
};

static LsmMathmlLength *
lsm_mathml_length_copy (LsmMathmlLength *length)
{
	LsmMathmlLength *copy;

	copy = g_new (LsmMathmlLength, 1);
	memcpy (copy, length, sizeof (LsmMathmlLength));

	return copy;
}

GType
lsm_mathml_length_get_type (void)
{
	static GType our_type = 0;

	if (our_type == 0)
		our_type = g_boxed_type_register_static
			("LsmMathmlLength",
			 (GBoxedCopyFunc) lsm_mathml_length_copy,
			 (GBoxedFreeFunc) g_free);
	return our_type;
}

static gboolean
lsm_mathml_length_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmMathmlLength *length = (LsmMathmlLength *) abstract_trait;
	char *unit_str;

	length->value = g_ascii_strtod (string, &unit_str);
	length->unit = lsm_mathml_unit_from_string (unit_str);

	/* TODO Handle "big", "small", normal" sizes */

	return unit_str != string && length->unit >= 0;
}

static char *
lsm_mathml_length_trait_to_string (LsmTrait *abstract_trait)
{
	LsmMathmlLength *length = (LsmMathmlLength *) abstract_trait;

	return g_strdup_printf ("%g %s", length->value,
				lsm_mathml_unit_to_string (length->unit));
}

const LsmTraitClass lsm_mathml_length_trait_class = {
	.size = sizeof (char *),
	.from_string = lsm_mathml_length_trait_from_string,
	.to_string = lsm_mathml_length_trait_to_string
};

double
lsm_mathml_length_normalize (const LsmMathmlLength *length,
			     double base,
			     double font_size)
{
	double value;

	g_return_val_if_fail (length != NULL, 0.0);

	switch (length->unit) {
		case LSM_MATHML_UNIT_PX:
		case LSM_MATHML_UNIT_PT:
			value = length->value;
			break;
		case LSM_MATHML_UNIT_PC:
			value = length->value * 72.0 / 6.0;
			break;
		case LSM_MATHML_UNIT_CM:
			value = length->value * 72.0 / 2.54;
			break;
		case LSM_MATHML_UNIT_MM:
			value = length->value * 72.0 / 25.4;
			break;
		case LSM_MATHML_UNIT_IN:
			value = length->value * 72.0;
			break;
		case LSM_MATHML_UNIT_EM:
			value = length->value * font_size;
			break;
		case LSM_MATHML_UNIT_EX:
			value = length->value * font_size * 0.5;
			break;
		case LSM_MATHML_UNIT_PERCENT:
			value = length->value * base / 100.0;
			break;
		case LSM_MATHML_UNIT_NONE:
			value = length->value * base;
			break;
		default:
			value = 0;
	}

	return value;
}

static LsmMathmlSpace *
lsm_mathml_space_copy (LsmMathmlSpace *space)
{
	LsmMathmlSpace *copy;

	copy = g_new (LsmMathmlSpace, 1);
	memcpy (copy, space, sizeof (LsmMathmlSpace));

	return copy;
}

GType
lsm_mathml_space_get_type (void)
{
	static GType our_type = 0;

	if (our_type == 0)
		our_type = g_boxed_type_register_static
			("LsmMathmlSpace",
			 (GBoxedCopyFunc) lsm_mathml_space_copy,
			 (GBoxedFreeFunc) g_free);
	return our_type;
}

static gboolean
lsm_mathml_space_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmMathmlSpace *space = (LsmMathmlSpace *) abstract_trait;
	char *unit_str;

	space->name = lsm_mathml_space_name_from_string (string);

	if (space->name < 0) {
		space->length.value = g_ascii_strtod (string, &unit_str);
		space->length.unit = lsm_mathml_unit_from_string (unit_str);

		return unit_str != string && space->length.unit >= 0;
	}

	space->length.value = 0.0;
	space->length.unit = LSM_MATHML_UNIT_PX;

	return TRUE;
}

static char *
lsm_mathml_space_trait_to_string (LsmTrait *abstract_trait)
{
	LsmMathmlSpace *space = (LsmMathmlSpace *) abstract_trait;
	const char *string;

	string = lsm_mathml_space_name_to_string (space->name);
	if (string != NULL)
		return g_strdup (string);

	return g_strdup_printf ("%g %s", space->length.value,
				lsm_mathml_unit_to_string (space->length.unit));
}

const LsmTraitClass lsm_mathml_space_trait_class = {
	.size = sizeof (char *),
	.from_string = lsm_mathml_space_trait_from_string,
	.to_string = lsm_mathml_space_trait_to_string
};

gboolean
lsm_mathml_space_list_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmMathmlSpaceList *space_list = (LsmMathmlSpaceList *) abstract_trait;
	char **items;
	unsigned int i;

	g_free (space_list->spaces);

	items = g_strsplit_set (string, " ", -1);
	space_list->n_spaces = g_strv_length (items);

	space_list->spaces = g_new (LsmMathmlSpace, space_list->n_spaces);
	for (i = 0; i < space_list->n_spaces; i++) {
		if (!lsm_mathml_space_trait_from_string (&space_list->spaces[i], items[i])) {
			g_free (space_list->spaces);
			space_list->spaces = NULL;
			space_list->n_spaces = 0;
			g_strfreev (items);

			return FALSE;
		}
	}

	g_strfreev (items);

	return TRUE;
}

static char *
lsm_mathml_space_list_trait_to_string (LsmTrait *abstract_trait)
{
	return g_strdup ("FIXME");
}

static void
lsm_mathml_space_list_trait_init (LsmTrait *abstract_trait,
				  const LsmTrait *abstract_default)
{
	LsmMathmlSpaceList *space_list = (LsmMathmlSpaceList *) abstract_trait;
	LsmMathmlSpaceList *space_list_defaut = (LsmMathmlSpaceList *) abstract_default;

	space_list->n_spaces = space_list_defaut->n_spaces;
	if (space_list->n_spaces == 0)
		space_list->spaces = NULL;
	else {
		space_list->spaces = g_new (LsmMathmlSpace, space_list->n_spaces);
		memcpy (space_list->spaces, space_list_defaut->spaces, sizeof (LsmMathmlSpace) * space_list->n_spaces);
	}
}

static void
lsm_mathml_space_list_trait_finalize (LsmTrait *abstract_trait)
{
	LsmMathmlSpaceList *space_list = (LsmMathmlSpaceList *) abstract_trait;

	g_free (space_list->spaces);
	space_list->spaces = NULL;
	space_list->n_spaces = 0;
}

void
lsm_mathml_space_list_init (LsmMathmlSpaceList *space_list, const LsmMathmlSpaceList *space_list_default)
{
	g_return_if_fail (space_list != NULL);
	g_return_if_fail (space_list_default != NULL);

	lsm_mathml_space_list_trait_init (space_list, space_list_default);
}

const LsmTraitClass lsm_mathml_space_list_trait_class = {
	.size = sizeof (LsmMathmlSpaceList),
	.from_string = lsm_mathml_space_list_trait_from_string,
	.to_string = lsm_mathml_space_list_trait_to_string,
	.init = lsm_mathml_space_list_trait_init,
	.finalize = lsm_mathml_space_list_trait_finalize
};
