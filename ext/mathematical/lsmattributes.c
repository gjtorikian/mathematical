/* Lasem
 *
 * Copyright © 2007-2009  Emmanuel Pacaud
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

#include <lsmattributes.h>
#include <lsmdebug.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

gboolean
lsm_attribute_is_defined (const LsmAttribute *attribute)
{
	g_return_val_if_fail (attribute != NULL, FALSE);

	return attribute->value != NULL;
}

#define ATTRIBUTE_TRAIT(attribute) ((void *) (((char *) attribute) + sizeof (LsmAttribute)))

struct _LsmAttributeManager {
	GHashTable *			hash_by_name;

	gint ref_count;
};

G_DEFINE_BOXED_TYPE (LsmAttributeManager, lsm_attribute_manager, lsm_attribute_manager_ref, lsm_attribute_manager_unref)

static LsmAttributeManager *
lsm_attribute_manager_create (void)
{
	LsmAttributeManager *manager;

	manager = g_new0 (LsmAttributeManager, 1);
	manager->hash_by_name = g_hash_table_new_full (g_str_hash, g_str_equal, NULL, NULL);
	manager->ref_count = 1;

	return manager;
}

LsmAttributeManager *
lsm_attribute_manager_new (unsigned int n_attributes, const LsmAttributeInfos *attribute_infos)
{
	LsmAttributeManager *manager;

	manager = lsm_attribute_manager_create ();

	lsm_attribute_manager_add_attributes (manager, n_attributes, attribute_infos);

	return manager;
}

LsmAttributeManager *
lsm_attribute_manager_duplicate (const LsmAttributeManager *origin)
{
	LsmAttributeManager *manager;
	GHashTableIter iter;
	gpointer key, value;

	g_return_val_if_fail (origin != NULL, NULL);

	manager = lsm_attribute_manager_create ();

	g_hash_table_iter_init (&iter, origin->hash_by_name);
	while (g_hash_table_iter_next (&iter, &key, &value))
		g_hash_table_insert (manager->hash_by_name, key, value);

	return manager;
}

void
lsm_attribute_manager_add_attributes (LsmAttributeManager *manager,
				      unsigned int n_attributes,
				      const LsmAttributeInfos *attribute_infos)
{
	unsigned int i;

	g_return_if_fail (n_attributes > 0);
	g_return_if_fail (attribute_infos != NULL);

	for (i = 0; i < n_attributes; i++) {
		g_assert (attribute_infos[i].name != NULL);
		g_assert (attribute_infos[i].attribute_offset >= 0);
		g_assert (attribute_infos[i].trait_class != NULL);

		g_hash_table_insert (manager->hash_by_name,
				     (void *) attribute_infos[i].name,
				     (void *) &attribute_infos[i]);
	}

}

LsmAttributeManager *
lsm_attribute_manager_ref (LsmAttributeManager *manager)
{
	g_return_val_if_fail (manager != NULL, NULL);

	g_atomic_int_inc (&manager->ref_count);

	return manager;
}

void
lsm_attribute_manager_unref (LsmAttributeManager *manager)
{
	g_return_if_fail (manager != NULL);

	if (g_atomic_int_dec_and_test (&manager->ref_count)) {
		g_hash_table_unref (manager->hash_by_name);
		g_free (manager);
	}
}

gboolean
lsm_attribute_manager_set_attribute (LsmAttributeManager *manager,
				     void *instance,
				     const char *name,
				     const char *value)
{
	LsmAttribute *attribute;
	LsmAttributeInfos *attribute_infos;
	const LsmTraitClass *trait_class;

	g_return_val_if_fail (manager != NULL, FALSE);

	attribute_infos = g_hash_table_lookup (manager->hash_by_name, name);
	if (attribute_infos == NULL)
		return FALSE;

	attribute = (void *)(((char *) instance) + attribute_infos->attribute_offset);
	g_return_val_if_fail (attribute != NULL, FALSE);

	trait_class = attribute_infos->trait_class;

	g_free (attribute->value);
	attribute->value = g_strdup (value);

	if (attribute->value != NULL) {
		if (trait_class->from_string) {
			gboolean success;

			success = trait_class->from_string (ATTRIBUTE_TRAIT (attribute), (char *) value);
			if (success)
				return TRUE;

			if (trait_class->finalize)
				trait_class->finalize (ATTRIBUTE_TRAIT (attribute));
			g_free (attribute->value);
			attribute->value = NULL;

			lsm_debug_dom ("[LsmAttributeManager::set_attribute] Invalid attribute value %s='%s'",
				   name, value);
		} else
			return TRUE;
	}

	if (trait_class->init)
		trait_class->init (ATTRIBUTE_TRAIT (attribute), attribute_infos->trait_default);
	else
		/* Simple memcpy for default init implementation, discarded by a NULL default value. */
		if (attribute_infos->trait_default != NULL)
			memcpy (ATTRIBUTE_TRAIT (attribute),
				attribute_infos->trait_default,
				trait_class->size);

	return TRUE;
}

char const *
lsm_attribute_manager_get_attribute (LsmAttributeManager *manager,
				     void *instance,
				     const char *name)
{
	LsmAttributeInfos *attribute_infos;
	LsmAttribute *attribute;

	g_return_val_if_fail (manager != NULL, NULL);

	attribute_infos = g_hash_table_lookup (manager->hash_by_name, name);
	if (attribute_infos == NULL)
		return NULL;

	attribute = (void *)(((char *)instance) + attribute_infos->attribute_offset);
	g_return_val_if_fail (attribute != NULL, NULL);

	return attribute->value;
}

void
lsm_attribute_manager_clean_attributes (LsmAttributeManager *manager,
					void *instance)
{
	LsmAttributeInfos *attribute_infos;
	LsmAttribute *attribute;
	const LsmTraitClass *trait_class;
	GHashTableIter iter;
	gpointer key, value;

	g_return_if_fail (manager != NULL);

	g_hash_table_iter_init (&iter, manager->hash_by_name);
	while (g_hash_table_iter_next (&iter, &key, &value)) {
		attribute_infos = value;
		trait_class = attribute_infos->trait_class;

		attribute = (void *)(((char *)instance) + attribute_infos->attribute_offset);
		g_free (attribute->value);
		attribute->value = NULL;

		if (trait_class->finalize) {
			trait_class->finalize (ATTRIBUTE_TRAIT (attribute));
		}
	}
}

char *
lsm_attribute_manager_serialize	(LsmAttributeManager *manager,
				 void *instance)
{
	LsmAttributeInfos *attribute_infos;
	LsmAttribute *attribute;
	GString *string;
	GHashTableIter iter;
	char *c_string;
	gpointer key, value;
	gboolean attribute_found = FALSE;

	g_return_val_if_fail (manager != NULL, NULL);

	string = g_string_new ("");

	g_hash_table_iter_init (&iter, manager->hash_by_name);
	while (g_hash_table_iter_next (&iter, &key, &value)) {
		attribute_infos = value;
		attribute = (void *)(((char *)instance) + attribute_infos->attribute_offset);

		if (attribute->value != NULL) {
			if (!attribute_found) {
				g_string_append_printf (string, "%s=\"%s\"",
							attribute_infos->name,
							attribute->value);
				attribute_found = TRUE;
			} else {
				g_string_append_printf (string, " %s=\"%s\"",
							attribute_infos->name,
							attribute->value);
			}
		}
	}

	if (!attribute_found) {
		g_string_free (string, TRUE);
		return NULL;
	}

	c_string = string->str;
	g_string_free (string, FALSE);

	return c_string;
}
