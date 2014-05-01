/* Lasem
 *
 * Copyright © 2010-2012 Emmanuel Pacaud
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

#include <lsmdebug.h>
#include <glib/gprintf.h>
#include <stdlib.h>

LsmDebugCategory lsm_debug_category_dom =
{
	.name = "dom",
	.level = -1
};

LsmDebugCategory lsm_debug_category_measure =
{
	.name = "measure",
	.level = -1
};

LsmDebugCategory lsm_debug_category_update =
{
	.name = "update",
	.level = -1
};

LsmDebugCategory lsm_debug_category_render =
{
	.name = "render",
	.level = -1
};

LsmDebugCategory lsm_debug_category_viewport =
{
	.name = "viewport",
	.level = -1
};

static GHashTable *lsm_debug_categories = NULL;

static void
lsm_debug_category_free (LsmDebugCategory *category)
{
	if (category != NULL) {
		g_free (category->name);
		g_free (category);
	}
}

static void
lsm_debug_initialize (const char *debug_var)
{
	if (lsm_debug_categories != NULL)
		return;

	lsm_debug_categories = g_hash_table_new_full (g_str_hash, g_str_equal,
						      (GDestroyNotify) lsm_debug_category_free, NULL);

	if (debug_var != NULL) {
		char **categories;
		int i;

		categories = g_strsplit (debug_var, ",", -1);
		for (i = 0; categories[i] != NULL; i++) {
			LsmDebugCategory *category;
			char **infos;

			category = g_new0 (LsmDebugCategory, 1);

			infos = g_strsplit (categories[i], ":", -1);
			if (infos[0] != NULL) {
				category->name = g_strdup (infos[0]);
				if (infos[1] != NULL)
					category->level = atoi (infos[1]);
				else
					category->level = LSM_DEBUG_LEVEL_DEBUG;

				g_hash_table_insert (lsm_debug_categories, category->name, category);
			} else
				g_free (category);

			g_strfreev (infos);
		}
		g_strfreev (categories);
	}
}

gboolean
lsm_debug_check	(LsmDebugCategory *category, LsmDebugLevel level)
{
	LsmDebugCategory *configured_category;

	if (category == NULL)
		return FALSE;

	if ((int) level <= (int) category->level)
		return TRUE;

	if ((int) category->level >= 0)
		return FALSE;

	lsm_debug_initialize (g_getenv ("LSM_DEBUG"));

	configured_category = g_hash_table_lookup (lsm_debug_categories, category->name);
	if (configured_category == NULL)
		configured_category = g_hash_table_lookup (lsm_debug_categories, "all");
	if (configured_category != NULL)
		category->level = configured_category->level;
	else
		category->level = 0;


	return (int) level <= (int) category->level;
}

static void
lsm_debug_with_level (LsmDebugCategory *category, LsmDebugLevel level, const char *format, va_list args)
{
	if (!lsm_debug_check (category, level))
		return;

	g_vprintf (format, args);
	g_printf ("\n");
}

void
lsm_warning (LsmDebugCategory *category, const char *format, ...)
{
	va_list args;

	va_start (args, format);
	lsm_debug_with_level (category, LSM_DEBUG_LEVEL_WARNING, format, args);
	va_end (args);
}

void
lsm_debug (LsmDebugCategory *category, const char *format, ...)
{
	va_list args;

	va_start (args, format);
	lsm_debug_with_level (category, LSM_DEBUG_LEVEL_DEBUG, format, args);
	va_end (args);
}

void
lsm_log (LsmDebugCategory *category, const char *format, ...)
{
	va_list args;

	va_start (args, format);
	lsm_debug_with_level (category, LSM_DEBUG_LEVEL_LOG, format, args);
	va_end (args);
}

void
lsm_debug_enable (const char *categories)
{
	lsm_debug_initialize (categories);
}
