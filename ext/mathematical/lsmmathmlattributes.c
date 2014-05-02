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

#include <lsmmathmlattributes.h>
#include <lsmmathmlstyle.h>

gboolean
lsm_mathml_boolean_attribute_inherit (LsmMathmlBooleanAttribute *attribute, gboolean value)
{
	if (attribute->base.value == NULL)
		attribute->value = value;

	return attribute->value;
}

unsigned int
lsm_mathml_enum_attribute_inherit (LsmMathmlEnumAttribute *attribute, unsigned int value)
{
	if (attribute->base.value == NULL)
		attribute->value = value;

	return attribute->value;
}

double
lsm_mathml_double_attribute_inherit (LsmMathmlDoubleAttribute *attribute, double value)
{
	if (attribute->base.value == NULL)
		attribute->value = value;

	return attribute->value;
}

LsmMathmlColor
lsm_mathml_color_attribute_inherit (LsmMathmlColorAttribute *attribute, LsmMathmlColor value)
{
	if (attribute->base.value == NULL)
		attribute->color = value;

	return attribute->color;
}

const char *
lsm_mathml_string_attribute_inherit (LsmMathmlStringAttribute *attribute, const char *string)
{
	if (attribute->base.value == NULL) {
		g_free (attribute->value);
		attribute->value = g_strdup (string);
	}

	return attribute->value;
}

int
lsm_mathml_script_level_attribute_apply	(LsmMathmlScriptLevelAttribute *attribute,
					 int script_level)
{
	if (attribute->base.value == NULL) {
		attribute->value.level = script_level;
		attribute->value.sign = LSM_MATHML_SCRIPT_LEVEL_SIGN_NONE;

		return script_level;
	}

	if (attribute->value.sign == LSM_MATHML_SCRIPT_LEVEL_SIGN_NONE)
		return attribute->value.level;

	return script_level + attribute->value.level;
}

double
lsm_mathml_length_attribute_normalize (LsmMathmlLengthAttribute *attribute,
				       double base,
				       const LsmMathmlLength *default_value,
				       const LsmMathmlStyle *style)
{
	const LsmMathmlLength *length;

	g_return_val_if_fail (attribute != NULL, 0.0);
	g_return_val_if_fail (style != NULL, 0.0);

	length = attribute->base.value != NULL ? &attribute->length : default_value;

	g_return_val_if_fail (length != NULL, 0.0);

	attribute->value = lsm_mathml_length_normalize (length, base, style->math_size);

	return attribute->value;
}

double
lsm_mathml_space_attribute_normalize (LsmMathmlSpaceAttribute *attribute,
				      double base,
				      const LsmMathmlSpace *default_value,
				      const LsmMathmlStyle *style)
{
	const LsmMathmlSpace *space;

	g_return_val_if_fail (attribute != NULL, 0.0);
	g_return_val_if_fail (style != NULL, 0.0);

	space = attribute->base.value != NULL ?	&attribute->space : default_value;

	g_return_val_if_fail (space != NULL, 0.0);

	switch (space->name) {
		case LSM_MATHML_SPACE_NAME_VERY_VERY_THIN:
			attribute->value = style->very_very_thin_math_space;
			break;
		case LSM_MATHML_SPACE_NAME_VERY_THIN:
			attribute->value = style->very_thin_math_space;
			break;
		case LSM_MATHML_SPACE_NAME_THIN:
			attribute->value = style->thin_math_space;
			break;
		case LSM_MATHML_SPACE_NAME_MEDIUM:
			attribute->value = style->medium_math_space;
			break;
		case LSM_MATHML_SPACE_NAME_THICK:
			attribute->value = style->thick_math_space;
			break;
		case LSM_MATHML_SPACE_NAME_VERY_THICK:
			attribute->value = style->very_thick_math_space;
			break;
		case LSM_MATHML_SPACE_NAME_VERY_VERY_THICK:
			attribute->value = style->very_very_thick_math_space;
			break;
		case LSM_MATHML_SPACE_NAME_INFINITY:
			attribute->value = G_MAXDOUBLE;
			break;
		default:
			attribute->value = lsm_mathml_length_normalize (&space->length,
									base,
									style->math_size);
	}

	return attribute->value;
}

void
lsm_mathml_space_list_attribute_normalize (LsmMathmlSpaceListAttribute *attribute,
					   double base,
					   const LsmMathmlSpaceList *default_value,
					   const LsmMathmlStyle *style)
{
	LsmMathmlSpaceAttribute space_attribute;
	const LsmMathmlSpaceList *space_list;
	unsigned int i;

	g_return_if_fail (attribute != NULL);
	g_return_if_fail (style != NULL);

	space_list = attribute->base.value != NULL ? &attribute->space_list : default_value;

	g_return_if_fail (space_list != NULL);

	g_free (attribute->values);
	attribute->values = NULL;
	attribute->n_values = 0;

	if (space_list->n_spaces == 0) {
		attribute->values = g_new (double, 1);
		attribute->values[0] = 0.0;
		return;
	}

	space_attribute.base.value = "";

	attribute->values = g_new (double, space_list->n_spaces);
	attribute->n_values = space_list->n_spaces;

	for (i = 0; i < space_list->n_spaces; i++) {
		space_attribute.space = space_list->spaces[i];
		lsm_mathml_space_attribute_normalize (&space_attribute, base, NULL, style);
		attribute->values[i] = space_attribute.value;
	}
}
