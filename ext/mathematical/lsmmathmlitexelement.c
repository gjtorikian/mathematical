/* Lasem
 *
 * Copyright © 2010 Emmanuel Pacaud
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

#include <lsmmathmlitexelement.h>
#include <lsmmathmlview.h>
#include <lsmdomtext.h>
#include <lsmdebug.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_mathml_itex_element_get_node_name (LsmDomNode *node)
{
	return "lasem:itex";
}

static gboolean
lsm_mathml_itex_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	return (LSM_IS_DOM_TEXT (child));
}

/* LsmMathmlElement implementation */

static void
_update (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmMathmlItexElement *itex_element = LSM_MATHML_ITEX_ELEMENT (self);
	LsmDomNode *node;
	GString *string;
	gboolean need_conversion;

	if (style->display == LSM_MATHML_DISPLAY_INLINE)
		string = g_string_new ("$");
	else
		string = g_string_new ("$$");

	for (node = LSM_DOM_NODE (self)->first_child; node != NULL; node = node->next_sibling) {
		if (LSM_IS_DOM_TEXT (node)) {
			g_string_append (string, lsm_dom_node_get_node_value (node));
		}
	}

	if (style->display == LSM_MATHML_DISPLAY_INLINE)
		g_string_append (string, "$");
	else
		g_string_append (string, "$$");

	need_conversion = g_strcmp0 (itex_element->itex, string->str) != 0;

	lsm_debug_update ("[MathmlItex::update] itex = '%s'", itex_element->itex);

	if (need_conversion) {
		LsmMathmlDocument *document;

		g_free (itex_element->itex);
		itex_element->itex = string->str;

		lsm_debug_update ("[MathmlItex::update] need conversion");

		document = lsm_mathml_document_new_from_itex (itex_element->itex,
							      string->len, NULL);
		if (document != NULL) {
			if (itex_element->math != NULL)
				g_object_unref (lsm_dom_node_get_owner_document (LSM_DOM_NODE (itex_element->math)));

			itex_element->math = LSM_MATHML_ELEMENT (lsm_mathml_document_get_root_element (document));
		}
	}

	g_string_free (string, FALSE);

	if (itex_element->math != NULL) {
		lsm_dom_node_changed (LSM_DOM_NODE (itex_element->math));
		self->need_measure = lsm_mathml_element_update (itex_element->math, style);
	}
}

static const LsmMathmlBbox *
_measure (LsmMathmlElement *self, LsmMathmlView *view, const LsmMathmlBbox *bbox)
{
	LsmMathmlItexElement *itex_element = LSM_MATHML_ITEX_ELEMENT (self);

	if (itex_element->math != NULL)
		return lsm_mathml_element_measure (itex_element->math, view, bbox);

	self->bbox.width = 0.0;
	self->bbox.height = 0.0;
	self->bbox.depth = 0.0;

	return &self->bbox;
}

static void
_layout (LsmMathmlElement *self, LsmMathmlView *view,
	 double x, double y, const LsmMathmlBbox *bbox)
{
	LsmMathmlItexElement *itex_element = LSM_MATHML_ITEX_ELEMENT (self);

	if (itex_element->math != NULL)
		lsm_mathml_element_layout (itex_element->math, view, x, y, bbox);
}

static void
_render (LsmMathmlElement *self, LsmMathmlView *view)
{
	LsmMathmlItexElement *itex_element = LSM_MATHML_ITEX_ELEMENT (self);

	if (itex_element->math != NULL)
		lsm_mathml_element_render (itex_element->math, view);
}

/* LsmMathmlItexElement implementation */

LsmDomNode *
lsm_mathml_itex_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_ITEX_ELEMENT, NULL);
}

static void
lsm_mathml_itex_element_init (LsmMathmlItexElement *self)
{
	self->itex = NULL;
	self->math = NULL;
}

static void
lsm_mathml_itex_element_finalize (GObject *object)
{
	LsmMathmlItexElement *itex_element = LSM_MATHML_ITEX_ELEMENT (object);

	g_free (itex_element->itex);
	itex_element->itex = NULL;

	if (itex_element->math != NULL)
		g_object_unref (lsm_dom_node_get_owner_document (LSM_DOM_NODE (itex_element->math)));
	itex_element->math = NULL;

	parent_class->finalize (object);
}

/* LsmMathmlItexElement class */

static void
lsm_mathml_itex_element_class_init (LsmMathmlItexElementClass *itex_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (itex_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (itex_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (itex_class);

	parent_class = g_type_class_peek_parent (itex_class);

	object_class->finalize = lsm_mathml_itex_element_finalize;

	d_node_class->get_node_name = lsm_mathml_itex_element_get_node_name;
	d_node_class->can_append_child = lsm_mathml_itex_can_append_child;

	m_element_class->update = _update;
	m_element_class->measure = _measure;
	m_element_class->layout = _layout;
	m_element_class->render = _render;
}

G_DEFINE_TYPE (LsmMathmlItexElement, lsm_mathml_itex_element, LSM_TYPE_MATHML_ELEMENT)
