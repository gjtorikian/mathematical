/* Lasem - SVG and Mathml library
 *
 * Copyright © 2009-2010  Emmanuel Pacaud
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

#ifndef LSM_TRAITS_H
#define LSM_TRAITS_H

#include <lsmtypes.h>

G_BEGIN_DECLS

typedef void LsmTrait;

typedef struct {
	size_t		size;
	void 		(*init)			(LsmTrait *abstract_trait, const LsmTrait *trait_default);
	void 		(*finalize)		(LsmTrait *abstract_trait);
	gboolean	(*from_string)		(LsmTrait *abstract_trait, char *string);
	char * 		(*to_string)		(LsmTrait *abstract_trait);
} LsmTraitClass;

extern const LsmTraitClass lsm_null_trait_class;
extern const LsmTraitClass lsm_double_trait_class;
extern const LsmTraitClass lsm_box_trait_class;

int 	lsm_enum_value_from_string 	(const char *string, const char **strings, unsigned int n_strings);

G_END_DECLS

#endif
