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

#include <lsmmathmlactionelement.h>

/* LsmDomNode implementation */

static const char *
lsm_mathml_action_element_get_node_name (LsmDomNode *node)
{
	return "maction";
}

/* LsmMathmlElement implementation */

static const LsmMathmlBbox *
lsm_mathml_action_element_measure (LsmMathmlElement *self, LsmMathmlView *view, const LsmMathmlBbox *bbox)
{
	if (LSM_DOM_NODE (self)->first_child != NULL)
		self->bbox = *lsm_mathml_element_measure (LSM_MATHML_ELEMENT (LSM_DOM_NODE (self)->first_child),
						       view, bbox);
	else
		self->bbox = lsm_mathml_bbox_null;

	return &self->bbox;
}

static void
lsm_mathml_action_element_layout (LsmMathmlElement *self, LsmMathmlView *view,
			       double x, double y, const LsmMathmlBbox *bbox)
{
	if (LSM_DOM_NODE (self)->first_child != NULL)
		lsm_mathml_element_layout (LSM_MATHML_ELEMENT (LSM_DOM_NODE (self)->first_child),
					view, x, y, bbox);
}

static void
lsm_mathml_action_element_render (LsmMathmlElement *self, LsmMathmlView *view)
{
	if (LSM_DOM_NODE (self)->first_child != NULL)
		lsm_mathml_element_render (LSM_MATHML_ELEMENT (LSM_DOM_NODE (self)->first_child), view);
}

/* LsmMathmlActionElement implementation */

LsmDomNode *
lsm_mathml_action_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_ACTION_ELEMENT, NULL);
}

static void
lsm_mathml_action_element_init (LsmMathmlActionElement *element)
{
}

/* LsmMathmlActionElement class */

static void
lsm_mathml_action_element_class_init (LsmMathmlActionElementClass *m_action_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (m_action_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (m_action_class);

	d_node_class->get_node_name = lsm_mathml_action_element_get_node_name;

	m_element_class->measure = lsm_mathml_action_element_measure;
	m_element_class->layout = lsm_mathml_action_element_layout;
	m_element_class->render = lsm_mathml_action_element_render;
}

G_DEFINE_TYPE (LsmMathmlActionElement, lsm_mathml_action_element, LSM_TYPE_MATHML_PRESENTATION_CONTAINER)

