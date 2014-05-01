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

#include <lsmmathmlalignmarkelement.h>
#include <lsmmathmlview.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_mathml_align_mark_get_node_name (LsmDomNode *node)
{
	return "malignmark";
}

static gboolean
lsm_mathml_align_mark_element_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	return FALSE;
}

/* LsmMathmlElement implementation */

static void
lsm_mathml_align_mark_element_update (LsmMathmlElement *self, LsmMathmlStyle *style)
{
}

static const LsmMathmlBbox *
lsm_mathml_align_mark_element_measure (LsmMathmlElement *self, LsmMathmlView *view, const LsmMathmlBbox *bbox)
{
	self->bbox = lsm_mathml_bbox_null;

	return &self->bbox;
}

static void
lsm_mathml_align_mark_element_layout (LsmMathmlElement *self, LsmMathmlView *view,
				   double x, double y, const LsmMathmlBbox *bbox)
{
}

static void
lsm_mathml_align_mark_element_render (LsmMathmlElement *element, LsmMathmlView *view)
{
}

/* LsmMathmlAlignMarkElement implementation */

LsmDomNode *
lsm_mathml_align_mark_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_ALIGN_MARK_ELEMENT, NULL);
}

static void
lsm_mathml_align_mark_element_init (LsmMathmlAlignMarkElement *self)
{
}

/* LsmMathmlAlignMarkElement class */

static void
lsm_mathml_align_mark_element_class_init (LsmMathmlAlignMarkElementClass *align_mark_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (align_mark_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (align_mark_class);

	parent_class = g_type_class_peek_parent (align_mark_class);

	d_node_class->get_node_name = lsm_mathml_align_mark_get_node_name;
	d_node_class->can_append_child = lsm_mathml_align_mark_element_can_append_child;

	m_element_class->update = lsm_mathml_align_mark_element_update;
	m_element_class->measure = lsm_mathml_align_mark_element_measure;
	m_element_class->layout = lsm_mathml_align_mark_element_layout;
	m_element_class->render = lsm_mathml_align_mark_element_render;
	m_element_class->is_inferred_row = NULL;
}

G_DEFINE_TYPE (LsmMathmlAlignMarkElement, lsm_mathml_align_mark_element, LSM_TYPE_MATHML_ELEMENT)
