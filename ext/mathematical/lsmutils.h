/* Lasem
 *
 * Copyright © 2007-2012 Emmanuel Pacaud
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

#ifndef LSM_UTILS_H
#define LSM_UTILS_H

#include <lsmtypes.h>

G_BEGIN_DECLS

struct _LsmExtents {
	double x1;
	double y1;
	double x2;
	double y2;
};

#define LSM_TYPE_EXTENTS (lsm_extents_get_type())

GType lsm_extents_get_type (void);

struct _LsmBox {
	double x;
	double y;
	double width;
	double height;
};

#define LSM_TYPE_BOX (lsm_box_get_type())

GType lsm_box_get_type (void);

G_END_DECLS

#endif

