/* Lasem
 *
 * Copyright © 2007-2008 Emmanuel Pacaud
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

#include <lsmmathmldocument.h>
#include <lsmmathmlsemanticselement.h>
#include <lsmmathmlphantomelement.h>
#include <lsmmathmlmathelement.h>
#include <lsmmathmltableelement.h>
#include <lsmmathmltablerowelement.h>
#include <lsmmathmltablecellelement.h>
#include <lsmmathmlspaceelement.h>
#include <lsmmathmlradicalelement.h>
#include <lsmmathmlscriptelement.h>
#include <lsmmathmlfractionelement.h>
#include <lsmmathmlunderoverelement.h>
#include <lsmmathmloperatorelement.h>
#include <lsmmathmlstringelement.h>
#include <lsmmathmlrowelement.h>
#include <lsmmathmlpaddedelement.h>
#include <lsmmathmlfencedelement.h>
#include <lsmmathmlerrorelement.h>
#include <lsmmathmlactionelement.h>
#include <lsmmathmlstyleelement.h>
#include <lsmmathmlalignmarkelement.h>
#include <lsmmathmlaligngroupelement.h>
#include <lsmmathmlitexelement.h>
#include <lsmmathmlview.h>
#include <lsmdebug.h>
#include <gio/gio.h>
#include <string.h>

#include <lsmdomparser.h>

#include <../itex2mml/itex2MML.h>

/* LsmDomNode implementation */

static gboolean
lsm_mathml_document_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	return (LSM_IS_MATHML_MATH_ELEMENT (child));
}

/* LsmDomDocument implementation */

static LsmDomElement *
_create_element (LsmDomDocument *document, const char *tag_name)
{
	LsmDomNode *node = NULL;

	if (strcmp (tag_name, "math") == 0)
		node = lsm_mathml_math_element_new ();
	else if (strcmp (tag_name, "mtable") == 0)
		node = lsm_mathml_table_element_new ();
	else if (strcmp (tag_name, "mtr") == 0)
		node = lsm_mathml_table_row_element_new ();
	else if (strcmp (tag_name, "mlabeledtr") == 0)
		node = lsm_mathml_labeled_table_row_element_new ();
	else if (strcmp (tag_name, "mtd") == 0)
		node = lsm_mathml_table_cell_element_new ();
	else if (strcmp (tag_name, "mspace") == 0)
		node = lsm_mathml_space_element_new ();
	else if (strcmp (tag_name, "msqrt") == 0)
		node = lsm_mathml_sqrt_element_new ();
	else if (strcmp (tag_name, "mroot") == 0)
		node = lsm_mathml_root_element_new ();
	else if (strcmp (tag_name, "msub") == 0)
		node = lsm_mathml_sub_element_new ();
	else if (strcmp (tag_name, "msup") == 0)
		node = lsm_mathml_sup_element_new ();
	else if (strcmp (tag_name, "msubsup") == 0)
		node = lsm_mathml_sub_sup_element_new ();
	else if (strcmp (tag_name, "mfrac") == 0)
		node = lsm_mathml_fraction_element_new ();
	else if (strcmp (tag_name, "munder") == 0)
		node = lsm_mathml_under_element_new ();
	else if (strcmp (tag_name, "mover") == 0)
		node = lsm_mathml_over_element_new ();
	else if (strcmp (tag_name, "munderover") == 0)
		node = lsm_mathml_under_over_element_new ();
	else if (strcmp (tag_name, "mo") == 0)
		node = lsm_mathml_operator_element_new ();
	else if (strcmp (tag_name, "mrow") == 0)
		node = lsm_mathml_row_element_new ();
	else if (strcmp (tag_name, "mn") == 0)
		node = lsm_mathml_number_element_new ();
	else if (strcmp (tag_name, "mi") == 0)
		node = lsm_mathml_identifier_element_new ();
	else if (strcmp (tag_name, "mtext") == 0)
		node = lsm_mathml_text_element_new ();
	else if (strcmp (tag_name, "ms") == 0)
		node = lsm_mathml_string_element_new ();
	else if (strcmp (tag_name, "mstyle") == 0)
		node = lsm_mathml_style_element_new ();
	else if (strcmp (tag_name, "mphantom") == 0)
		node = lsm_mathml_phantom_element_new ();
	else if (strcmp (tag_name, "mpadded") == 0)
		node = lsm_mathml_padded_element_new ();
	else if (strcmp (tag_name, "mfenced") == 0)
		node = lsm_mathml_fenced_element_new ();
	else if (strcmp (tag_name, "merror") == 0)
		node = lsm_mathml_error_element_new ();
	else if (strcmp (tag_name, "maction") == 0)
		node = lsm_mathml_action_element_new ();
	else if (strcmp (tag_name, "malignmark") == 0)
		node = lsm_mathml_align_mark_element_new ();
	else if (strcmp (tag_name, "maligngroup") == 0)
		node = lsm_mathml_align_group_element_new ();
	else if (strcmp (tag_name, "semantics") == 0)
		node = lsm_mathml_semantics_element_new ();
	else if (strcmp (tag_name, "lasem:itex") == 0)
		node = lsm_mathml_itex_element_new ();
	else
		lsm_debug_dom ("[MathmlDocument::create_element] Unknown tag (%s)", tag_name);

	return LSM_DOM_ELEMENT (node);
}

static LsmDomElement *
lsm_mathml_document_create_element (LsmDomDocument *document, const char *tag_name)
{
	LsmDomElement *element;

	element = _create_element (document, tag_name);
	if (element != NULL)
		return element;

	if (g_str_has_prefix (tag_name, "math:"))
		return _create_element (document, &tag_name[4]);

	return NULL;
}

static LsmDomView *
lsm_mathml_document_create_view (LsmDomDocument *document)
{
	return LSM_DOM_VIEW (lsm_mathml_view_new (LSM_MATHML_DOCUMENT (document)));
}

/* LsmMathmlDocument implementation */

LsmDomDocument *
lsm_mathml_document_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_DOCUMENT, NULL);
}

static void
lsm_mathml_document_init (LsmMathmlDocument *document)
{
}

/* Additional methods */

LsmMathmlMathElement *
lsm_mathml_document_get_root_element (const LsmMathmlDocument *document)
{
	return LSM_MATHML_MATH_ELEMENT (lsm_dom_document_get_document_element (LSM_DOM_DOCUMENT (document)));
}

/* LsmMathmlDocument class */

static void
lsm_mathml_document_class_init (LsmMathmlDocumentClass *m_document_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (m_document_class);
	LsmDomDocumentClass *d_document_class = LSM_DOM_DOCUMENT_CLASS (m_document_class);

	d_node_class->can_append_child = lsm_mathml_document_can_append_child;

	d_document_class->create_element = lsm_mathml_document_create_element;
	d_document_class->create_view = lsm_mathml_document_create_view;
}

G_DEFINE_TYPE (LsmMathmlDocument, lsm_mathml_document, LSM_TYPE_DOM_DOCUMENT)

static GQuark
lsm_mathml_document_error_quark (void)
{
	static GQuark q = 0;

        if (q == 0) {
                q = g_quark_from_static_string ("lsm-mathml-error-quark");
        }

        return q;
}

#define LSM_MATHML_DOCUMENT_ERROR lsm_mathml_document_error_quark ()

typedef enum {
	LSM_MATHML_DOCUMENT_ERROR_INVALID_ITEX
} LsmMathmlDocumentError;

LsmMathmlDocument *
lsm_mathml_document_new_from_itex (const char *itex, int size, GError **error)
{
	LsmDomDocument *document;
	char *xml;

	g_return_val_if_fail (itex != NULL, NULL);

	xml = itex2MML_parse (itex, size);

	if (xml == NULL) {
		lsm_debug_dom ("[LsmMathmlDocument::new_from_itex] Invalid document");

		g_set_error (error,
			     LSM_MATHML_DOCUMENT_ERROR,
			     LSM_MATHML_DOCUMENT_ERROR_INVALID_ITEX,
			     "Invalid itex document.");

		return NULL;
	}

	document = lsm_dom_document_new_from_memory (xml, -1, error);

	itex2MML_free_string (xml);

	if (document == NULL)
		return NULL;

	if (!LSM_IS_MATHML_DOCUMENT (document)) {
		g_object_unref (document);
		return NULL;
	}

	return LSM_MATHML_DOCUMENT (document);
}

static LsmMathmlDocument *
lsm_mathml_document_new_from_itex_file (GFile *file, GError **error)
{
	LsmMathmlDocument *document;
	gsize size = 0;
	char *contents = NULL;

	if (!g_file_load_contents (file, NULL, &contents, &size, NULL, error))
		return NULL;

	document = lsm_mathml_document_new_from_itex (contents, size, error);

	g_free (contents);

	return document;
}

LsmMathmlDocument *
lsm_mathml_document_new_from_itex_path (const char *path, GError **error)
{
	LsmMathmlDocument *document;
	GFile *file;

	g_return_val_if_fail (path != NULL, NULL);

	file = g_file_new_for_path (path);

	document = lsm_mathml_document_new_from_itex_file (file, error);

	g_object_unref (file);

	if (document != NULL)
		lsm_dom_document_set_path (LSM_DOM_DOCUMENT (document), path);

	return document;
}

LsmMathmlDocument *
lsm_mathml_document_new_from_itex_url (const char *url, GError **error)
{
	LsmMathmlDocument *document;
	GFile *file;

	g_return_val_if_fail (url != NULL, NULL);

	file = g_file_new_for_uri (url);

	document = lsm_mathml_document_new_from_itex_file (file, error);

	g_object_unref (file);

	if (document != NULL)
		lsm_dom_document_set_url (LSM_DOM_DOCUMENT (document), url);

	return document;
}
