/* Lasem
 * 
 * Copyright © 2011 Emmanuel Pacaud
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

#include <lsmmathmlsemanticselement.h>
#include <lsmmathmlview.h>

/* LsmDomNode implementation */

static const char *
lsm_mathml_semantics_element_get_node_name (LsmDomNode *node)
{
	return "semantics";
}

static gboolean
lsm_mathml_semantics_element_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	if (!LSM_IS_MATHML_ELEMENT (child))
		return FALSE;

	return TRUE;
}

/* LsmMathmlElement implementation */

/* LsmMathmlSemanticsElement implementation */

LsmMathmlElement *
lsm_mathml_semantics_element_get_body (LsmMathmlSemanticsElement *semantics)
{
	LsmDomNode *node;

	g_return_val_if_fail (LSM_IS_MATHML_SEMANTICS_ELEMENT (semantics), NULL);

       	node = LSM_DOM_NODE (semantics);

	return LSM_MATHML_ELEMENT (node->first_child);
}

LsmDomNode *
lsm_mathml_semantics_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_SEMANTICS_ELEMENT, NULL);
}

static void
lsm_mathml_semantics_element_init (LsmMathmlSemanticsElement *semantics)
{
}

/* LsmMathmlSemanticsElement class */

static void
lsm_mathml_semantics_element_class_init (LsmMathmlSemanticsElementClass *klass)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (klass);

	d_node_class->get_node_name = lsm_mathml_semantics_element_get_node_name;
	d_node_class->can_append_child = lsm_mathml_semantics_element_can_append_child;
}

G_DEFINE_TYPE (LsmMathmlSemanticsElement, lsm_mathml_semantics_element, LSM_TYPE_MATHML_ELEMENT)
