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

#include <lsmmathmlspaceelement.h>
#include <lsmmathmlview.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_mathml_space_get_node_name (LsmDomNode *node)
{
	return "mspace";
}

static gboolean
lsm_mathml_space_element_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	return FALSE;
}

/* LsmMathmlElement implementation */

static void
lsm_mathml_space_element_update (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmMathmlSpaceElement *space_element = LSM_MATHML_SPACE_ELEMENT (self);
	static LsmMathmlSpace space = {.name = LSM_MATHML_SPACE_NAME_ERROR,
		{ .unit = LSM_MATHML_UNIT_PX, .value = 0.0}};
	static LsmMathmlLength length = {.unit = LSM_MATHML_UNIT_PX, .value = 0.0};

	lsm_mathml_space_attribute_normalize (&space_element->width, 0.0, &space, style);
	lsm_mathml_length_attribute_normalize (&space_element->height, 0.0, &length, style);
	lsm_mathml_length_attribute_normalize (&space_element->depth, 0.0, &length, style);
}

static const LsmMathmlBbox *
lsm_mathml_space_element_measure (LsmMathmlElement *self, LsmMathmlView *view, const LsmMathmlBbox *bbox)
{
	LsmMathmlSpaceElement *space_element = LSM_MATHML_SPACE_ELEMENT (self);

	self->bbox.width = space_element->width.value;
	self->bbox.height = space_element->height.value;
	self->bbox.depth = space_element->depth.value;
	self->bbox.is_defined = TRUE;

	return &self->bbox;
}

static void
lsm_mathml_space_element_layout (LsmMathmlElement *self, LsmMathmlView *view,
				double x, double y, const LsmMathmlBbox *bbox)
{
	LSM_MATHML_ELEMENT_CLASS (parent_class)->layout (self, view, x, y, bbox);
}

/* LsmMathmlSpaceElement implementation */

LsmDomNode *
lsm_mathml_space_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_SPACE_ELEMENT, NULL);
}

static const LsmMathmlSpace space_default = {LSM_MATHML_SPACE_NAME_ERROR, {0.0, LSM_MATHML_UNIT_EM}};
static const LsmMathmlLength length_default = {1.0, LSM_MATHML_UNIT_NONE};

static void
lsm_mathml_space_element_init (LsmMathmlSpaceElement *self)
{
	self->width.space = space_default;
	self->height.length = length_default;
	self->depth.length = length_default;
}

/* LsmMathmlSpaceElement class */

static const LsmAttributeInfos _attribute_infos[] = {
	{
		.name = "width",
		.attribute_offset = offsetof (LsmMathmlSpaceElement, width),
		.trait_class = &lsm_mathml_space_trait_class,
		.trait_default = &space_default
	},
	{
		.name = "depth",
		.attribute_offset = offsetof (LsmMathmlSpaceElement, depth),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "height",
		.attribute_offset = offsetof (LsmMathmlSpaceElement, height),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	}
};

static void
lsm_mathml_space_element_class_init (LsmMathmlSpaceElementClass *space_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (space_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (space_class);

	parent_class = g_type_class_peek_parent (space_class);

	d_node_class->get_node_name = lsm_mathml_space_get_node_name;
	d_node_class->can_append_child = lsm_mathml_space_element_can_append_child;

	m_element_class->update = lsm_mathml_space_element_update;
	m_element_class->measure = lsm_mathml_space_element_measure;
	m_element_class->layout = lsm_mathml_space_element_layout;
	m_element_class->is_inferred_row = NULL;
	m_element_class->attribute_manager = lsm_attribute_manager_duplicate (m_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (m_element_class->attribute_manager,
					      G_N_ELEMENTS (_attribute_infos),
					      _attribute_infos);
}

G_DEFINE_TYPE (LsmMathmlSpaceElement, lsm_mathml_space_element, LSM_TYPE_MATHML_ELEMENT)
