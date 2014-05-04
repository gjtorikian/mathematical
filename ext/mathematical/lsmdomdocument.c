/* Lasem
 *
 * Copyright © 2007-2010 Emmanuel Pacaud
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

/**
 * SECTION:lsmdomdocument
 * @short_description: Base class for DOM document nodes
 */

#include <lsmdomdocument.h>
#include <lsmdomelement.h>
#include <lsmstr.h>
#include <lsmdebug.h>
#include <lsmdomtext.h>
#include <gio/gio.h>
#include <string.h>

static GObjectClass *parent_class;

/* LsmDomNode implementation */

static const char *
lsm_dom_document_get_node_name (LsmDomNode *node)
{
	return "#document";
}

static LsmDomNodeType
lsm_dom_document_get_node_type (LsmDomNode *node)
{
	return LSM_DOM_NODE_TYPE_DOCUMENT_NODE;
}

/* LsmDomDocument implementation */


/**
 * lsm_dom_document_get_document_element:
 * @self: a #LsmDomElement
 *
 * Returns: (transfer none): document element
 */

LsmDomElement *
lsm_dom_document_get_document_element (LsmDomDocument *self)
{
	g_return_val_if_fail (LSM_IS_DOM_DOCUMENT (self), NULL);

	return LSM_DOM_ELEMENT (lsm_dom_node_get_first_child (LSM_DOM_NODE (self)));
}

/**
 * lsm_dom_document_create_element:
 * @self: a #LsmDomDocument
 * @tag_name: name of the element to create
 *
 * Returns: (transfer full): a newly created #LsmDomElement
 */

LsmDomElement *
lsm_dom_document_create_element (LsmDomDocument *document, const char *tag_name)
{
	LsmDomDocumentClass *document_class;
	LsmDomElement *element;

	g_return_val_if_fail (LSM_IS_DOM_DOCUMENT (document), NULL);

	document_class = LSM_DOM_DOCUMENT_GET_CLASS (document);
	if (document_class->create_element == NULL)
		return NULL;

	element = document_class->create_element (document, tag_name);
	if (element != NULL)
		LSM_DOM_NODE (element)->owner_document = document;

	return element;
}

static LsmDomText *
lsm_dom_document_create_text_node_base (LsmDomDocument *document, const char *data)
{
	LsmDomText *text_node;

	text_node = LSM_DOM_TEXT (lsm_dom_text_new (data));

	if (text_node != NULL)
		LSM_DOM_NODE (text_node)->owner_document = document;

	return text_node;
}

/**
 * lsm_dom_document_create_text_node:
 * @self: a #LsmDomDocument
 * @data: content of the text node
 *
 * Returns: (transfer full): a newly created #LsmDomText
 */

LsmDomText *
lsm_dom_document_create_text_node (LsmDomDocument *document, const char *data)
{
	g_return_val_if_fail (LSM_IS_DOM_DOCUMENT (document), NULL);

	return LSM_DOM_DOCUMENT_GET_CLASS (document)->create_text_node (document, data);
}

/**
 * lsm_dom_document_create_view:
 * @self: a #LsmDomDocument
 *
 * Returns: (transfer full): a new #LsmDomView
 */

LsmDomView *
lsm_dom_document_create_view (LsmDomDocument *self)
{
	g_return_val_if_fail (LSM_IS_DOM_DOCUMENT (self), NULL);

	return LSM_DOM_DOCUMENT_GET_CLASS (self)->create_view (self);
}

const char *
lsm_dom_document_get_url (LsmDomDocument *self)
{
	g_return_val_if_fail (LSM_IS_DOM_DOCUMENT (self), NULL);

	return self->url;
}

void
lsm_dom_document_set_path (LsmDomDocument *self, const char *path)
{
	g_return_if_fail (LSM_IS_DOM_DOCUMENT (self));

	g_free (self->url);

	if (path == NULL) {
		self->url = NULL;
		return;
	}

	self->url = lsm_str_to_uri (path);
}

void
lsm_dom_document_set_url (LsmDomDocument *self, const char *url)
{
	g_return_if_fail (LSM_IS_DOM_DOCUMENT (self));
	g_return_if_fail (url == NULL || lsm_str_is_uri (url));

	g_free (self->url);
	self->url = g_strdup (url);
}

/**
 * lsm_dom_document_get_href_data:
 * @self: a #LsmDomDocument
 * @href: href
 * @size: placeholder for the size of the returned data
 *
 * Returns: (transfer full): a newly allocated buffer containing the requested data.
 */

void *
lsm_dom_document_get_href_data (LsmDomDocument *self, const char *href, gsize *size)
{
	GFile *file;
	char *data = NULL;

	g_return_val_if_fail (LSM_IS_DOM_DOCUMENT (self), NULL);
	g_return_val_if_fail (href != NULL, NULL);

	if (strncmp (href, "data:", 5) == 0) {
		while (*href != '\0' && *href != ',')
			href++;
		return g_base64_decode (href, size);
	}

	file = g_file_new_for_uri (href);

	if (!g_file_load_contents (file, NULL, &data, size, NULL, NULL) && self->url != NULL) {
		GFile *document_file;
		GFile *parent_file;

		g_object_unref (file);

		document_file = g_file_new_for_uri (self->url);
		parent_file = g_file_get_parent (document_file);
		file = g_file_resolve_relative_path (parent_file, href);
		g_object_unref (document_file);
		g_object_unref (parent_file);

		g_file_load_contents (file, NULL, &data, size, NULL, NULL);
	}

	g_object_unref (file);

	return data;
}

static void
lsm_dom_document_init (LsmDomDocument *document)
{
}

static void
lsm_dom_document_finalize (GObject *object)
{
	LsmDomDocument *document = LSM_DOM_DOCUMENT (object);

	g_free (document->url);

	parent_class->finalize (object);
}

/* LsmDomDocument class */

static void
lsm_dom_document_class_init (LsmDomDocumentClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	LsmDomNodeClass *node_class = LSM_DOM_NODE_CLASS (klass);

	parent_class = g_type_class_peek_parent (klass);

	object_class->finalize = lsm_dom_document_finalize;

	node_class->get_node_name = lsm_dom_document_get_node_name;
	node_class->get_node_type = lsm_dom_document_get_node_type;

	klass->create_text_node = lsm_dom_document_create_text_node_base;
}

G_DEFINE_ABSTRACT_TYPE (LsmDomDocument, lsm_dom_document, LSM_TYPE_DOM_NODE)

