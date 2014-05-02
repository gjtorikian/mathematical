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

#ifndef LSM_STR_H
#define LSM_STR_H

#include <lsmtypes.h>

G_BEGIN_DECLS

gboolean 	lsm_str_is_uri 		(const char *str);
char *   	lsm_str_to_uri 		(const char *str);

gboolean 	lsm_str_parse_double 		(char **str, double *x);
unsigned int 	lsm_str_parse_double_list 	(char **str, unsigned int n_values, double *values);

void		lsm_str_point_list_exents	(const char *point_list, LsmExtents *extents);

static inline void
lsm_str_skip_spaces (char **str)
{
	while (g_ascii_isspace (**str))
		(*str)++;
}

static inline void
lsm_str_skip_char (char **str, char c)
{
	while (**str == c)
		(*str)++;
}

static inline void
lsm_str_skip_comma_and_spaces (char **str)
{
	while (g_ascii_isspace (**str) || **str == ',')
		(*str)++;
}

static inline void
lsm_str_skip_semicolon_and_spaces (char **str)
{
	while (g_ascii_isspace (**str) || **str == ';')
		(*str)++;
}

static inline void
lsm_str_skip_colon_and_spaces (char **str)
{
	while (g_ascii_isspace (**str) || **str == ':')
		(*str)++;
}

/**
 * lsm_str_consolidate:
 * @str: a utf8 string
 *
 * Removes trailing and heading ascii spaces from str, and reduce consecutive spaces to one space.
 */

static inline void
lsm_str_consolidate (char *str)
{
	char *to_ptr;
	char *from_ptr;

	if (str == NULL)
		return;

	from_ptr = str;
	to_ptr = str;
	while (*from_ptr != '\0') {
		if (g_ascii_isspace (*from_ptr)) {
			if (to_ptr != str &&
			    *(to_ptr - 1) != ' ') {
				*to_ptr = ' ';
				to_ptr++;
			}
		} else {
			*to_ptr = *from_ptr;
			to_ptr++;
		}
		from_ptr++;
	}

	if (to_ptr != str && *(to_ptr - 1) == ' ')
		*(to_ptr - 1) = '\0';
	else
		*to_ptr = '\0';
}

G_END_DECLS

#endif
