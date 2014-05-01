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

#ifndef LSM_DEBUG_H
#define LSM_DEBUG_H

#include <glib.h>

G_BEGIN_DECLS

typedef enum {
	LSM_DEBUG_LEVEL_NONE,
	LSM_DEBUG_LEVEL_WARNING,
	LSM_DEBUG_LEVEL_DEBUG,
	LSM_DEBUG_LEVEL_LOG,
	LSM_DEBUG_LEVEL_COUNT
} LsmDebugLevel;

typedef struct {
	char *name;
	LsmDebugLevel level;
} LsmDebugCategory;

extern LsmDebugCategory lsm_debug_category_dom;
extern LsmDebugCategory lsm_debug_category_measure;
extern LsmDebugCategory lsm_debug_category_update;
extern LsmDebugCategory lsm_debug_category_render;
extern LsmDebugCategory lsm_debug_category_viewport;

#define lsm_debug_dom(...) 		lsm_debug (&lsm_debug_category_dom, __VA_ARGS__)
#define lsm_log_dom(...)		lsm_log (&lsm_debug_category_dom, __VA_ARGS__)
#define lsm_warning_dom(...)		lsm_warning (&lsm_debug_category_dom, __VA_ARGS__)

#define lsm_debug_measure(...) 		lsm_debug (&lsm_debug_category_measure, __VA_ARGS__)
#define lsm_log_measure(...)		lsm_log (&lsm_debug_category_measure, __VA_ARGS__)
#define lsm_warning_measure(...)	lsm_warning (&lsm_debug_category_measure, __VA_ARGS__)

#define lsm_debug_update(...) 		lsm_debug (&lsm_debug_category_update, __VA_ARGS__)
#define lsm_log_update(...)		lsm_log (&lsm_debug_category_update, __VA_ARGS__)
#define lsm_warning_update(...)		lsm_warning (&lsm_debug_category_update, __VA_ARGS__)

#define lsm_debug_render(...) 		lsm_debug (&lsm_debug_category_render, __VA_ARGS__)
#define lsm_log_render(...)		lsm_log (&lsm_debug_category_render, __VA_ARGS__)
#define lsm_warning_render(...)		lsm_warning (&lsm_debug_category_render, __VA_ARGS__)

void 		lsm_warning 			(LsmDebugCategory *category, const char *format, ...);
void 		lsm_debug 			(LsmDebugCategory *category, const char *format, ...);
void 		lsm_log 			(LsmDebugCategory *category, const char *format, ...);

gboolean	lsm_debug_check			(LsmDebugCategory *category, LsmDebugLevel level);

void		lsm_debug_enable		(const char *category_selection);

G_END_DECLS

#endif
