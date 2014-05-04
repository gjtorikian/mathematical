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

#include <lsmmathmlelement.h>
#include <lsmmathmlspaceelement.h>
#include <lsmmathmloperatorelement.h>
#include <lsmmathmlview.h>
#include <lsmdebug.h>

static GObjectClass *parent_class;

static const LsmMathmlBbox null_bbox = {0.0,0.0,0.0, FALSE};

/* LsmDomNode implementation */

static gboolean
lsm_mathml_element_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	return (LSM_IS_MATHML_ELEMENT (child));
}

static void
lsm_mathml_element_changed (LsmDomNode *self)
{
	LsmMathmlElement *element = LSM_MATHML_ELEMENT (self);

	element->need_update = TRUE;
	element->need_measure = TRUE;
}

static gboolean
lsm_mathml_element_child_changed (LsmDomNode *parent, LsmDomNode *child)
{
	LsmMathmlElement *element = LSM_MATHML_ELEMENT (parent);

	if (element->need_children_update)
		return FALSE;

	element->need_children_update = TRUE;
	element->need_measure = TRUE;

	return TRUE;
}

/* LsmDomElement implementation */

static void
lsm_mathml_element_set_attribute (LsmDomElement *self, const char* name, const char *value)
{
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_GET_CLASS(self);

	lsm_attribute_manager_set_attribute (m_element_class->attribute_manager,
					     self, name, value);
}

static const char *
lsm_mathml_element_get_attribute (LsmDomElement *self, const char *name)
{
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_GET_CLASS(self);

	return lsm_attribute_manager_get_attribute (m_element_class->attribute_manager,
						    self, name);
}

static char *
lsm_mathml_element_get_serialized_attributes (LsmDomElement *self)
{
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_GET_CLASS(self);

	return lsm_attribute_manager_serialize (m_element_class->attribute_manager, self);
}

/* LsmMathmlElement implementation */

static gboolean
_update_children (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmDomNode *node;
	gboolean need_measure = FALSE;

	for (node = LSM_DOM_NODE (self)->first_child; node != NULL; node = node->next_sibling)
		if (LSM_IS_MATHML_ELEMENT (node))
			if (lsm_mathml_element_update (LSM_MATHML_ELEMENT (node), style))
				need_measure = TRUE;

	return need_measure;
}

/**
 * lsm_mathml_element_update:
 * @self: a #LsmMathmlElement
 * @parent_style: self parent style
 *
 * Update the actual property of an element and it's children. This function parses the element attributes and also make elements inherit style from their parents.
 *
 * Returns: TRUE if the size of the element has changed and needs to be recalculated.
 */

gboolean
lsm_mathml_element_update (LsmMathmlElement *self, const LsmMathmlStyle *parent_style)
{
	LsmMathmlElementClass *element_class;
	LsmMathmlStyle *style;
	gboolean need_measure;

	g_return_val_if_fail (LSM_IS_MATHML_ELEMENT (self), FALSE);
	g_return_val_if_fail (parent_style != NULL, FALSE);

	if (!self->need_update && !self->need_children_update) {
		lsm_debug_update ("[Element::update] %s already up to date",
				  lsm_dom_node_get_node_name (LSM_DOM_NODE (self)));
		return FALSE;
	}

	element_class = LSM_MATHML_ELEMENT_GET_CLASS (self);

	style = lsm_mathml_style_duplicate (parent_style);
	g_return_val_if_fail (style != NULL, FALSE);

	if (element_class->update != NULL)
		element_class->update (self, style);

	lsm_debug_update ("[Element::update] update %s (%s-%g)",
			  lsm_dom_node_get_node_name (LSM_DOM_NODE (self)),
			  style->math_family != NULL ? style->math_family : "undefined" ,
			  style->math_size);

	g_free (self->style.math_family);
	self->style.math_family = g_strdup (style->math_family);
	self->style.math_variant = style->math_variant;
	self->style.math_size = style->math_size;
	self->style.math_color = style->math_color;
	self->style.math_background = style->math_background;

	if (self->need_update) {
		LsmDomNode *node;

		for (node = LSM_DOM_NODE (self)->first_child; node != NULL; node = node->next_sibling)
			if (LSM_IS_MATHML_ELEMENT (node))
				LSM_MATHML_ELEMENT (node)->need_update = TRUE;
	}

	if (element_class->update_children != NULL)
		need_measure = element_class->update_children (self, style);
	else
		need_measure = FALSE;

	lsm_mathml_style_free (style);

	self->need_measure = need_measure || self->need_update;

	self->need_update = FALSE;
	self->need_children_update = FALSE;

	return self->need_measure;
}

/* Inferred mrow implementation */

static const LsmMathmlBbox *
_measure (LsmMathmlElement *self, LsmMathmlView *view, const LsmMathmlBbox *bbox)
{
	const LsmMathmlOperatorElement *operator;
	LsmDomNode *node;
	LsmMathmlBbox child_bbox;
	LsmMathmlBbox stretch_bbox;
	gboolean stretchy_found = FALSE;
	unsigned int n_elements = 0;

	self->bbox = lsm_mathml_bbox_null;

	stretch_bbox = *bbox;

	for (node = LSM_DOM_NODE (self)->first_child; node != NULL; node = node->next_sibling) {
		if (LSM_IS_MATHML_ELEMENT (node)) {
			operator = lsm_mathml_element_get_embellished_core (LSM_MATHML_ELEMENT (node));
			if (operator != NULL && operator->stretchy.value) {
				stretchy_found = TRUE;
				child_bbox = *lsm_mathml_element_measure (LSM_MATHML_ELEMENT (operator), view,
								       &lsm_mathml_bbox_null);
				lsm_mathml_bbox_stretch_vertically (&stretch_bbox, &child_bbox);
			} else {
				child_bbox = *lsm_mathml_element_measure (LSM_MATHML_ELEMENT (node), view,
								       &lsm_mathml_bbox_null);
				if (operator != NULL)
					child_bbox.width += operator->left_space.value + operator->right_space.value;
				lsm_mathml_bbox_add_horizontally (&self->bbox, &child_bbox);
				lsm_mathml_bbox_stretch_vertically (&stretch_bbox, &child_bbox);
			}
			n_elements++;
		}
	}

	if (stretchy_found) {
		lsm_debug_measure ("[Element::_measure] Stretchy found (width = %g, height = %g, depth = %g)",
			    stretch_bbox.width, stretch_bbox.height, stretch_bbox.depth);

		for (node = LSM_DOM_NODE (self)->first_child; node != NULL; node = node->next_sibling) {
			if (LSM_IS_MATHML_ELEMENT (node)) {
				operator = lsm_mathml_element_get_embellished_core (LSM_MATHML_ELEMENT (node));
				if (operator != NULL && operator->stretchy.value) {
					child_bbox = *lsm_mathml_element_measure (LSM_MATHML_ELEMENT (node), view,
									       &stretch_bbox);
					child_bbox.width += operator->left_space.value + operator->right_space.value;
					lsm_mathml_bbox_add_horizontally (&self->bbox, &child_bbox);
				}
			}
		}
	}

	return &self->bbox;
}

const LsmMathmlBbox *
lsm_mathml_element_measure (LsmMathmlElement *element, LsmMathmlView *view, const LsmMathmlBbox *stretch_bbox)
{
	LsmMathmlElementClass *element_class;

	g_return_val_if_fail (LSM_IS_MATHML_ELEMENT (element), &null_bbox);

	element_class = LSM_MATHML_ELEMENT_GET_CLASS (element);

	g_return_val_if_fail (element_class != NULL, &null_bbox);

	if (stretch_bbox == NULL)
		stretch_bbox = &lsm_mathml_bbox_null;

	if (element->need_measure || stretch_bbox->is_defined) {
		if (element_class->measure) {
			element->bbox = *(element_class->measure (element, view, stretch_bbox));

			lsm_debug_measure ("[Element::measure] Bbox (%s) %g, %g, %g",
				    lsm_dom_node_get_node_name (LSM_DOM_NODE (element)),
				    element->bbox.width, element->bbox.height, element->bbox.depth);
		} else {

			lsm_debug_measure ("[Element::measure] method not defined");
			element->bbox.width = 0.0;
			element->bbox.height = 0.0;
			element->bbox.depth = 0.0;
		}

		element->need_measure = FALSE;
		element->need_layout = TRUE;
	} else
		lsm_debug_measure ("[Element::measure] %s already up to date",
			    lsm_dom_node_get_node_name (LSM_DOM_NODE (element)));

	return &element->bbox;
}

/* Inferred mrow implementation */

static void
_layout (LsmMathmlElement *self, LsmMathmlView *view,
	 double x, double y, const LsmMathmlBbox *bbox)
{
	const LsmMathmlOperatorElement *operator;
	LsmDomNode *node;
	LsmMathmlBbox child_bbox;
	double offset;

	for (node = LSM_DOM_NODE (self)->first_child; node != NULL; node = node->next_sibling)
		if (LSM_IS_MATHML_ELEMENT (node)) {
			child_bbox = *lsm_mathml_element_get_bbox (LSM_MATHML_ELEMENT (node));
			operator = lsm_mathml_element_get_embellished_core (LSM_MATHML_ELEMENT (node));
			if (operator != NULL)
				offset = operator->left_space.value;
			else
				offset = 0.0;
			lsm_mathml_element_layout (LSM_MATHML_ELEMENT (node), view, x + offset, y, &child_bbox);
			if (operator != NULL)
				child_bbox.width += offset + operator->right_space.value;
			x += child_bbox.width;
		}
}

void
lsm_mathml_element_layout (LsmMathmlElement *self, LsmMathmlView *view,
			double x, double y, const LsmMathmlBbox *bbox)
{
	LsmMathmlElementClass *element_class;

	g_return_if_fail (LSM_IS_MATHML_ELEMENT (self));

	element_class = LSM_MATHML_ELEMENT_GET_CLASS (self);

	g_return_if_fail (element_class != NULL);

	lsm_debug_measure ("[Element::layout] assigned bbox for %s = %g, %g, %g at %g, %g",
		    lsm_dom_node_get_node_name (LSM_DOM_NODE (self)), bbox->width, bbox->height, bbox->depth, x , y);

	self->x = x;
	self->y = y;

	if (element_class->layout)
		element_class->layout (self, view, x, y, bbox);

	self->need_layout = FALSE;
}

/* Inferred mrow implementation */

static void
_render (LsmMathmlElement *element, LsmMathmlView *view)
{
	LsmDomNode *node;

	for (node = LSM_DOM_NODE (element)->first_child; node != NULL; node = node->next_sibling)
		if (LSM_IS_MATHML_ELEMENT (node))
		    lsm_mathml_element_render (LSM_MATHML_ELEMENT (node), view);
}

void
lsm_mathml_element_render (LsmMathmlElement *element, LsmMathmlView *view)
{
	LsmMathmlElementClass *element_class;

	g_return_if_fail (LSM_IS_MATHML_ELEMENT (element));
	element_class = LSM_MATHML_ELEMENT_GET_CLASS (element);
	g_return_if_fail (element_class != NULL);

	if (element_class->render) {
		lsm_mathml_view_show_bbox (view, element->x, element->y, &element->bbox);
		lsm_mathml_view_show_background (view, &element->style,
					      element->x, element->y,
					      &element->bbox);
		element_class->render (element, view);
	}
}

/* Inferred mrow implementation */

static LsmMathmlOperatorElement *
_get_embellished_core (const LsmMathmlElement *self)
{
	LsmDomNode *node;
	LsmMathmlOperatorElement *core = NULL;

	g_assert (LSM_IS_MATHML_ELEMENT (self));

	for (node = LSM_DOM_NODE (self)->first_child; node != NULL; node = node->next_sibling) {
		if (LSM_IS_MATHML_ELEMENT (node)) {
			if (!LSM_IS_MATHML_SPACE_ELEMENT (node)) {
				if (core != NULL)
					return NULL;
				core = lsm_mathml_element_get_embellished_core (LSM_MATHML_ELEMENT (node));
			}
		} else
			if (core != NULL)
				return NULL;
	}

	return core;
}

LsmMathmlOperatorElement *
lsm_mathml_element_get_embellished_core (const LsmMathmlElement *self)
{
	LsmMathmlElementClass *element_class;

	g_return_val_if_fail (LSM_IS_MATHML_ELEMENT (self), NULL);

	element_class = LSM_MATHML_ELEMENT_GET_CLASS (self);

	if (element_class->get_embellished_core != NULL)
		return element_class->get_embellished_core (self);

	return NULL;
}

const LsmMathmlBbox *
lsm_mathml_element_get_bbox (const LsmMathmlElement *self)
{
	g_return_val_if_fail (LSM_IS_MATHML_ELEMENT (self), &lsm_mathml_bbox_null);

	return &self->bbox;
}

static gboolean
_is_inferred_row (const LsmMathmlElement *self)
{
	return TRUE;
}

gboolean
lsm_mathml_element_is_inferred_row (const LsmMathmlElement *self)
{
	LsmMathmlElementClass *element_class;

	g_return_val_if_fail (LSM_IS_MATHML_ELEMENT (self), FALSE);

	element_class = LSM_MATHML_ELEMENT_GET_CLASS (self);

	if (element_class->is_inferred_row != NULL)
		return element_class->is_inferred_row (self);

	return FALSE;
}

static void
lsm_mathml_element_init (LsmMathmlElement *element)
{
	element->need_update = TRUE;
	element->need_measure = TRUE;
}

static void
lsm_mathml_element_finalize (GObject *object)
{
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_GET_CLASS (object);
	LsmMathmlElement *m_element = LSM_MATHML_ELEMENT (object);

	g_free (m_element->style.math_family);

	lsm_attribute_manager_clean_attributes (m_element_class->attribute_manager, m_element);

	parent_class->finalize (object);
}

/* LsmMathmlElement class */

static const LsmAttributeInfos lsm_svg_attribute_infos[] = {
	{
		.name = "id",
		.trait_class = &lsm_null_trait_class,
		.attribute_offset = offsetof (LsmMathmlElement, id)
	},
	{
		.name = "class",
		.trait_class = &lsm_null_trait_class,
		.attribute_offset = offsetof (LsmMathmlElement, class_name)
	},
	{
		.name = "href",
		.trait_class = &lsm_null_trait_class,
		.attribute_offset = offsetof (LsmMathmlElement, href)
	}
};

static void
lsm_mathml_element_class_init (LsmMathmlElementClass *m_element_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (m_element_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (m_element_class);
	LsmDomElementClass *d_element_class = LSM_DOM_ELEMENT_CLASS (m_element_class);

	parent_class = g_type_class_peek_parent (m_element_class);

	object_class->finalize = lsm_mathml_element_finalize;

	d_node_class->can_append_child = lsm_mathml_element_can_append_child;
	d_node_class->changed = lsm_mathml_element_changed;
	d_node_class->child_changed = lsm_mathml_element_child_changed;

	d_element_class->get_attribute = lsm_mathml_element_get_attribute;
	d_element_class->set_attribute = lsm_mathml_element_set_attribute;
	d_element_class->get_serialized_attributes = lsm_mathml_element_get_serialized_attributes;

	m_element_class->update = NULL;
	m_element_class->update_children = _update_children;
	m_element_class->measure = _measure;
	m_element_class->layout = _layout;
	m_element_class->render = _render;
	m_element_class->get_embellished_core = _get_embellished_core;
	m_element_class->is_inferred_row = _is_inferred_row;
	m_element_class->attribute_manager = lsm_attribute_manager_new (G_N_ELEMENTS (lsm_svg_attribute_infos),
									lsm_svg_attribute_infos);
}

G_DEFINE_ABSTRACT_TYPE (LsmMathmlElement, lsm_mathml_element, LSM_TYPE_DOM_ELEMENT)
