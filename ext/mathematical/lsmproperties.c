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

#include <lsmproperties.h>
#include <lsmdebug.h>
#include <lsmstr.h>
#include <string.h>

#define PROPERTY_TRAIT(property) ((void *) (((void *) property) + sizeof (LsmProperty)))
#define PROPERTY_SIZE(trait_class) (trait_class->size + sizeof (LsmProperty))

struct _LsmPropertyManager {
	unsigned int		n_properties;
	const LsmPropertyInfos *property_infos;
	GHashTable *		hash_by_name;

	/* FIXME: Not thread safe */
	unsigned int *		property_check;
	unsigned int		property_check_count;

	gint ref_count;
};

G_DEFINE_BOXED_TYPE (LsmPropertyManager, lsm_property_manager, lsm_property_manager_ref, lsm_property_manager_unref)

LsmPropertyManager *
lsm_property_manager_new (unsigned int n_properties, const LsmPropertyInfos *property_infos)
{
	LsmPropertyManager *manager;
	guint16 i;

	g_return_val_if_fail (n_properties > 0, NULL);
	g_return_val_if_fail (property_infos != NULL, NULL);

	manager = g_new (LsmPropertyManager, 1);
	manager->hash_by_name = g_hash_table_new (g_str_hash, g_str_equal);
	manager->n_properties = n_properties;
	manager->property_infos = property_infos;
	manager->property_check_count = 0;
	manager->property_check = g_new0 (unsigned int, n_properties);
	manager->ref_count = 1;

	for (i = 0; i < n_properties; i++) {

		g_assert (property_infos[i].name != NULL);
		g_assert (property_infos[i].trait_class != NULL);

		g_hash_table_insert (manager->hash_by_name,
				     (void *) property_infos[i].name,
				     (void *) &property_infos[i]);
	}

	return manager;
}

LsmPropertyManager *
lsm_property_manager_ref (LsmPropertyManager *manager)
{
	g_return_val_if_fail (manager != NULL, NULL);

	g_atomic_int_inc (&manager->ref_count);

	return manager;
}

void
lsm_property_manager_unref (LsmPropertyManager *manager)
{
	g_return_if_fail (manager != NULL);

	if (g_atomic_int_dec_and_test (&manager->ref_count)) {
		g_hash_table_unref (manager->hash_by_name);
		g_free (manager->property_check);
		g_free (manager);
	}
}

static void
property_free (LsmProperty *property, const LsmTraitClass *trait_class)
{
	if (trait_class != NULL && trait_class->finalize != NULL)
		trait_class->finalize (PROPERTY_TRAIT (property));

	g_free (property->value);
	g_slice_free1 (PROPERTY_SIZE (trait_class), property);
}

static gboolean
_set_property (LsmPropertyManager *manager,
	       LsmPropertyBag *property_bag,
	       const char *name, const char *value)
{
	LsmProperty *property;
	const LsmPropertyInfos *property_infos;
	const LsmTraitClass *trait_class;

	property_infos = g_hash_table_lookup (manager->hash_by_name, name);
	if (property_infos == NULL)
		return FALSE;

	trait_class = property_infos->trait_class;

	/* We don't check for existing property in the list. The cleanup is done later when 
	 * applying a property bag. */

	property = g_slice_alloc0 (PROPERTY_SIZE (trait_class));
	property->id = property_infos->id;
	property->value = g_strdup (value);

	if (trait_class->init)
		trait_class->init (PROPERTY_TRAIT (property), NULL);

	if (property->value != NULL && trait_class->from_string) {
		gboolean success;

		success = trait_class->from_string (PROPERTY_TRAIT (property), (char *) value);
		if (!success) {
			lsm_debug_dom ("[LsmPropertyManager::set_property] Invalid property value %s='%s'",
				       name, value);
			property_free (property, property_infos->trait_class);

			return FALSE;
		}
	}

	property_bag->properties = g_slist_prepend (property_bag->properties, property);

	return TRUE;
}

gboolean
lsm_property_manager_set_property (LsmPropertyManager *manager,
				   LsmPropertyBag *property_bag,
				   const char *name, const char *value)
{
	gboolean property_found;
	char *inline_style;

	g_return_val_if_fail (property_bag != NULL, FALSE);
	g_return_val_if_fail (manager != NULL, FALSE);
	g_return_val_if_fail (name != NULL, FALSE);

	property_found = _set_property (manager, property_bag, name, value);
	if (property_found)
		return TRUE;

	if (strcmp (name, "style") != 0)
		return FALSE;

	inline_style = g_strdup (value);
	if (inline_style == NULL)
		return FALSE;

	{
		char *end_ptr = inline_style;
		char *name;
		char *value;

		while (*end_ptr != '\0') {

			lsm_str_skip_spaces (&end_ptr);

			name = end_ptr;

			while (*end_ptr != '\0' && *end_ptr != ':' && !g_ascii_isspace (*end_ptr))
				end_ptr++;

			if (*end_ptr != '\0') {
				*end_ptr = '\0';
				end_ptr++;

				lsm_str_skip_colon_and_spaces (&end_ptr);

				if (*end_ptr != '\0') {
					char old_char;

					value = end_ptr;

					while (*end_ptr != ';' && *end_ptr != '\0')
						end_ptr++;

					old_char = *end_ptr;
					*end_ptr = '\0';

					lsm_debug_dom ("[LsmPropertyManager::set_property] inline_style %s = %s",
						       name, value);

					_set_property (manager, property_bag, name, value);

					*end_ptr = old_char;

					lsm_str_skip_char (&end_ptr, ';');
				}
			}
		}
		g_free (inline_style);
	}

	return TRUE;
}

const char *
lsm_property_manager_get_property (LsmPropertyManager *manager,
				   LsmPropertyBag *property_bag,
				   const char *name)
{
	LsmProperty *property = NULL;
	const LsmPropertyInfos *property_infos;
	GSList *iter;

	g_return_val_if_fail (property_bag != NULL, NULL);
	g_return_val_if_fail (manager != NULL, NULL);

	property_infos = g_hash_table_lookup (manager->hash_by_name, name);
	if (property_infos == NULL)
		return NULL;

	g_message ("Get property with name %s (%d)", name, property_infos->id);

	for (iter = property_bag->properties; iter != NULL; iter = iter->next) {
		property = iter->data;
		if (property->id == property_infos->id)
			break;
	}

	if (property == NULL)
		return NULL;

	return property->value;
}

void
lsm_property_manager_clean_properties (LsmPropertyManager *manager,
				       LsmPropertyBag *property_bag)
{
	LsmProperty *property;
	GSList *iter;

	g_return_if_fail (property_bag != NULL);
	g_return_if_fail (manager != NULL);

	for (iter = property_bag->properties; iter != NULL; iter = iter->next) {
		property = iter->data;

		if (property->id < manager->n_properties) {
			const LsmPropertyInfos *property_infos;

			property_infos = &manager->property_infos[property->id];
			property_free (property, property_infos->trait_class);
		}
	}

	g_slist_free (property_bag->properties);
	property_bag->properties = NULL;
}

char *
lsm_property_manager_serialize (LsmPropertyManager *manager,
				LsmPropertyBag *property_bag)
{
	LsmProperty *property;
	GSList *iter;
	GString *string;
	char *c_string;
	gboolean attribute_found = FALSE;

	g_return_val_if_fail (property_bag != NULL, NULL);
	g_return_val_if_fail (manager != NULL, NULL);

	string = g_string_new ("");

	for (iter = property_bag->properties; iter != NULL; iter = iter->next) {
		property = iter->data;

		if (property->id < manager->n_properties) {
			const LsmPropertyInfos *property_infos;

			property_infos = &manager->property_infos[property->id];
			g_string_append_printf (string, "%s=\"%s\"%s",
						property_infos->name,
						property->value,
						iter->next != NULL ? " ": "");
			if (!attribute_found)
				attribute_found = TRUE;
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

void
lsm_property_manager_apply_property_bag (LsmPropertyManager *manager,
					 LsmPropertyBag *bag,
					 void *style,
					 const void *parent_style)
{
	LsmProperty *property;
	GSList *iter;
	GSList *previous_iter = NULL;

	g_return_if_fail (bag != NULL);
	g_return_if_fail (manager != NULL);

	manager->property_check_count++;
	if (manager->property_check_count == 0) {
		manager->property_check_count++;
		memset (manager->property_check, 0, sizeof (unsigned int) * manager->n_properties);
	}

	for (iter = bag->properties; iter != NULL;) {
		property = iter->data;

		if (property->id < manager->n_properties) {
			if (manager->property_check[property->id] != manager->property_check_count) {
				if (g_strcmp0 (property->value, "inherit") != 0)
					*((LsmProperty **) ((void*) style
							    + LSM_PROPERTY_ID_TO_OFFSET (property->id))) = property;
				else {
					if (parent_style != NULL)
						*((LsmProperty **) ((void*) style
								    + LSM_PROPERTY_ID_TO_OFFSET (property->id))) =
							*((LsmProperty **) ((void*) parent_style
									    + LSM_PROPERTY_ID_TO_OFFSET (property->id)));
				}

				manager->property_check[property->id] = manager->property_check_count;
				previous_iter = iter;
				iter = iter->next;
			} else {
				/* property garbage collector */
				const LsmPropertyInfos *property_infos;

				property_infos = &manager->property_infos[property->id];

				lsm_log_dom ("[LsmPropertyManager::apply_property_bag] Garbage collection of %s=%s",
					     property_infos->name, property->value);

				property_free (property, property_infos->trait_class);

				if (previous_iter == NULL) {
					bag->properties = iter->next;
					g_slist_free_1 (iter);
					iter = bag->properties;
				} else {
					previous_iter->next = iter->next;
					g_slist_free_1 (iter);
					iter = previous_iter->next;
				}
			}
		} else {
			previous_iter = iter;
			iter = iter->next;
		}
	}
}

void lsm_property_manager_init_default_style (LsmPropertyManager *property_manager,
					      void *style)
{
	LsmProperty *property;
	const LsmPropertyInfos *property_infos;
	const LsmTraitClass *trait_class;
	unsigned int i;

	g_return_if_fail (property_manager != NULL);

	for (i = 0; i < property_manager->n_properties; i++) {
		property_infos = &property_manager->property_infos[i];
		trait_class = property_infos->trait_class;

		property = g_slice_alloc0 (PROPERTY_SIZE (trait_class));
		property->id = property_infos->id;
		property->value = g_strdup (property_infos->trait_default);

		if (trait_class->from_string)
			trait_class->from_string (PROPERTY_TRAIT (property),
						  (char *) property_infos->trait_default);

		*((LsmProperty **) ((void*) style
				    + LSM_PROPERTY_ID_TO_OFFSET (property->id))) = property;
	}
}

void
lsm_property_bag_init (LsmPropertyBag *bag)
{
	g_return_if_fail (bag != NULL);

	bag->properties = NULL;
}
