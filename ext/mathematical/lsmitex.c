/* Lasem - SVG and Mathml library
 *
 * Copyright © 2013 Emmanuel Pacaud
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

#include <lsmitex.h>
#include <string.h>
#include "itex2MML.h"

/**
 * lsm_itex_to_mathml:
 * @itex: (allow-none): an itex string
 * @size: itex string length, -1 if unknown
 *
 * Converts an itex string to a Mathml representation.
 *
 * Return value: a newly allocated string, NULL on parse error. The returned data must be freed using @lsm_itex_free_mathml_buffer.
 */

char *
lsm_itex_to_mathml (const char *itex, int size)
{
	char *mathml;

	if (itex == NULL)
		return NULL;

	if (size < 0)
		size = strlen (itex);

	mathml = itex2MML_parse (itex, size);
	if (mathml == NULL)
		return NULL;

	if (mathml[0] == '\0') {
		itex2MML_free_string (mathml);
		return NULL;
	}

	return mathml;
}

/**
 * lsm_itex_free_mathml_buffer:
 * @mathml: (allow-none): a mathml buffer
 *
 * Free the buffer returned by @lsm_itex_to_mathml.
 */

void
lsm_itex_free_mathml_buffer (char *mathml)
{
	if (mathml == NULL)
		return;

	itex2MML_free_string (mathml);
}

