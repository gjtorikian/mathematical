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

#include <lsmutils.h>

LsmExtents *
lsm_extents_duplicate (const LsmExtents *from)
{
	LsmExtents *extents;

	g_return_val_if_fail (from != NULL, NULL);

	extents = g_new (LsmExtents, 1);
	*extents = *from;

	return extents;
}

G_DEFINE_BOXED_TYPE (LsmExtents, lsm_extents, lsm_extents_duplicate, g_free)

LsmBox *
lsm_box_duplicate (const LsmBox *from)
{
	LsmBox *box;

	g_return_val_if_fail (from != NULL, NULL);

	box = g_new (LsmBox, 1);
	*box = *from;

	return box;
}

G_DEFINE_BOXED_TYPE (LsmBox, lsm_box, lsm_box_duplicate, g_free)
