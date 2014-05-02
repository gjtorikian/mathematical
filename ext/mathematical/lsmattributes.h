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

#ifndef LSM_ATTRIBUTES_H
#define LSM_ATTRIBUTES_H

#include <lsmtypes.h>
#include <lsmtraits.h>

G_BEGIN_DECLS

typedef struct {
	char *value;
} LsmAttribute;

gboolean	lsm_attribute_is_defined			(const LsmAttribute *attribute);

typedef struct {
	char const *		name;
	int 			attribute_offset;
	const LsmTraitClass *	trait_class;
	const void *		trait_default;
} LsmAttributeInfos;

typedef struct _LsmAttributeManager LsmAttributeManager;

#define LSM_TYPE_ATTRIBUTE_MANAGER (lsm_attribute_manager_get_type())

GType lsm_attribute_manager_get_type (void);

LsmAttributeManager *	lsm_attribute_manager_new 		(unsigned int n_attributes,
								 const LsmAttributeInfos *attribute_infos);
LsmAttributeManager * 	lsm_attribute_manager_duplicate 	(const LsmAttributeManager *origin);
LsmAttributeManager *	lsm_attribute_manager_ref		(LsmAttributeManager *manager);
void			lsm_attribute_manager_unref		(LsmAttributeManager *manager);

void 			lsm_attribute_manager_add_attributes 	(LsmAttributeManager *manager,
								 unsigned int n_attributes,
								 const LsmAttributeInfos *attribute_infos);

gboolean	lsm_attribute_manager_set_attribute		(LsmAttributeManager *manager,
								 void *instance,
								 char const *name,
								 char const *value);
char const *	lsm_attribute_manager_get_attribute		(LsmAttributeManager *manager,
								 void *instance,
								 char const *name);
void		lsm_attribute_manager_clean_attributes 		(LsmAttributeManager *manager,
								 void *instance);
char *		lsm_attribute_manager_serialize			(LsmAttributeManager *manager,
								 void *instance);

G_END_DECLS

#endif
