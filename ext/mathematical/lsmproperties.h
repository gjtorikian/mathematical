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

#ifndef LSM_PROPERTIES_H
#define LSM_PROPERTIES_H

#include <lsmtypes.h>
#include <lsmtraits.h>

G_BEGIN_DECLS

#define LSM_PROPERTY_OFFSET_TO_ID(structure,member) (offsetof (structure, member) / sizeof (void *))
#define LSM_PROPERTY_ID_TO_OFFSET(id) ((id) * sizeof (void *))

typedef struct {
	guint16	id;
	guint16	flags;
	char *	value;
} LsmProperty;

typedef struct {
	char const *		name;
	guint16			id;
	const LsmTraitClass *	trait_class;
	const char *		trait_default;
} LsmPropertyInfos;

typedef struct {
	GSList *properties;
} LsmPropertyBag;

typedef struct _LsmPropertyManager LsmPropertyManager;

#define LSM_TYPE_PROPERTY_MANAGER (lsm_property_manager_get_type())

GType lsm_property_manager_get_type (void);

LsmPropertyManager *	lsm_property_manager_new	(unsigned int n_properties,
							 const LsmPropertyInfos *property_infos);
LsmPropertyManager *	lsm_property_manager_ref	(LsmPropertyManager *manager);
void			lsm_property_manager_unref	(LsmPropertyManager *manager);

gboolean 	lsm_property_manager_set_property 	(LsmPropertyManager *manager,
							 LsmPropertyBag *property_bag,
							 const char *name,
							 const char *value);
const char *	lsm_property_manager_get_property 	(LsmPropertyManager *manager,
							 LsmPropertyBag *property_bag,
							 const char *name);
void		lsm_property_manager_clean_properties	(LsmPropertyManager *manager,
							 LsmPropertyBag *property_bag);
char * 		lsm_property_manager_serialize 		(LsmPropertyManager *property_manager,
							 LsmPropertyBag *property_bag);
void		lsm_property_manager_apply_property_bag (LsmPropertyManager *property_manager,
							 LsmPropertyBag *property_bag,
							 void *style,
							 const void *parent_style);
void		lsm_property_manager_init_default_style (LsmPropertyManager *property_manager,
							 void *style);

void		lsm_property_bag_init			(LsmPropertyBag *bag);

G_END_DECLS

#endif
