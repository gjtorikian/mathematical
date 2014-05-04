/* Lasem - SVG and Mathml library
 *
 * Copyright © 2010 Emmanuel Pacaud
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

#include <lsmtraits.h>
#include <lsmutils.h>
#include <lsmstr.h>
#include <string.h>

const LsmTraitClass lsm_null_trait_class = {
	.size = 0
};

static gboolean
lsm_double_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	double *trait = (double *) abstract_trait;
	char *end_ptr;

	*trait = g_ascii_strtod (string, &end_ptr);

	return end_ptr != string;
}

static char *
lsm_double_trait_to_string (LsmTrait *abstract_trait)
{
	double *trait = (double *) abstract_trait;

	return g_strdup_printf ("%g", *trait);
}

const LsmTraitClass lsm_double_trait_class = {
	.size = sizeof (double),
	.from_string = lsm_double_trait_from_string,
	.to_string = lsm_double_trait_to_string
};

static gboolean
lsm_box_trait_from_string (LsmTrait *abstract_trait, char *string)
{
	LsmBox *trait = (LsmBox *) abstract_trait;
	unsigned int i;
	double value[4];

	for (i = 0; i < 4 && *string != '\0'; i++) {
		lsm_str_skip_comma_and_spaces (&string);

		if (!lsm_str_parse_double (&string, &value[i]))
			break;
	}

	if (i == 4) {
		trait->x = value[0];
		trait->y = value[1];
		trait->width = value[2];
		trait->height = value[3];

		return TRUE;
	}

	trait->x =
	trait->y =
	trait->width =
	trait->height = 0.0;

	return FALSE;
}

static char *
lsm_box_trait_to_string (LsmTrait *abstract_trait)
{
	LsmBox *trait = (LsmBox *) abstract_trait;

	return g_strdup_printf ("%g %g %g %g",
				trait->x, trait->y,
				trait->width, trait->height);
}

const LsmTraitClass lsm_box_trait_class = {
	.size = sizeof (LsmBox),
	.from_string = lsm_box_trait_from_string,
	.to_string = lsm_box_trait_to_string
};

int
lsm_enum_value_from_string (const char *string, const char **strings, unsigned int n_strings)
{
	int i;

	if (string == NULL)
		return -1;

	for (i = 0; i < n_strings; i++)
		if (strcmp (string, strings[i]) == 0)
			return i;

	return -1;
}

