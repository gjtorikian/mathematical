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

#include <lsmmathmlscriptelement.h>
#include <lsmmathmllayoututils.h>
#include <lsmmathmlview.h>
#include <math.h>

/* GdomNode implementation */

static const char *
lsm_mathml_script_element_get_node_name (LsmDomNode *node)
{
	LsmMathmlScriptElement *script = LSM_MATHML_SCRIPT_ELEMENT (node);

	switch (script->type) {
		case LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUB:
			return "msub";
		case LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUP:
			return "msup";
		case LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUB_SUP:
		default:
			return "msubsup";
	}
}

static gboolean
lsm_mathml_script_element_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	LsmMathmlScriptElement *script = LSM_MATHML_SCRIPT_ELEMENT (self);

	if (!LSM_IS_MATHML_ELEMENT (child))
		return FALSE;

	if (self->first_child == NULL ||
	    self->first_child->next_sibling == NULL)
		return TRUE;

	if (script->type != LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUB_SUP)
		return FALSE;

	return (self->first_child->next_sibling->next_sibling == NULL);
}

static void
lsm_mathml_script_element_update_child_pointers (LsmMathmlScriptElement *self)
{
	LsmDomNode *node;

	node = LSM_DOM_NODE (self)->first_child;
	if (node == NULL) {
		self->base = NULL;
		self->subscript = NULL;
		self->superscript = NULL;
		return;
	} else
		self->base = LSM_MATHML_ELEMENT (node);

	node = node->next_sibling;
	if (node != NULL)
		switch (self->type) {
			case LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUP:
				self->subscript = NULL;
				self->superscript = LSM_MATHML_ELEMENT (node);
				break;
			case LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUB:
				self->subscript = LSM_MATHML_ELEMENT (node);
				self->superscript = NULL;
				break;
			default:
				self->subscript = LSM_MATHML_ELEMENT (node);
				node = node->next_sibling;
				if (node != NULL)
					self->superscript = LSM_MATHML_ELEMENT (node);
		}
	else {
		self->subscript = NULL;
		self->superscript = NULL;
	}
}

static void
lsm_mathml_script_element_post_new_child (LsmDomNode *self, LsmDomNode *child)
{
	LsmMathmlScriptElement *script = LSM_MATHML_SCRIPT_ELEMENT (self);

	lsm_mathml_script_element_update_child_pointers (script);
}

/* LsmMathmlElement implementation */

static void
lsm_mathml_script_element_update (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmMathmlScriptElement *script = LSM_MATHML_SCRIPT_ELEMENT (self);
	LsmMathmlLength length;

	length.unit = LSM_MATHML_UNIT_PT;

	length.value = style->superscript_shift;
	style->superscript_shift = lsm_mathml_length_attribute_normalize (&script->superscript_shift,
									  style->superscript_shift,
									  &length, style);
	length.value = style->subscript_shift;
	style->subscript_shift = lsm_mathml_length_attribute_normalize (&script->subscript_shift,
									style->subscript_shift,
									&length, style);

	script->display = style->display;
}

static gboolean
lsm_mathml_script_element_update_children (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmMathmlScriptElement *script = LSM_MATHML_SCRIPT_ELEMENT (self);
	gboolean need_measure = FALSE;

	if (script->base != NULL)
		if (lsm_mathml_element_update (LSM_MATHML_ELEMENT (script->base), style))
			need_measure = TRUE;

	lsm_mathml_style_change_script_level (style, +1);
	style->display = LSM_MATHML_DISPLAY_INLINE;

	if (script->subscript != NULL)
		if (lsm_mathml_element_update (LSM_MATHML_ELEMENT (script->subscript), style))
			need_measure = TRUE;
	if (script->superscript != NULL)
		if  (lsm_mathml_element_update (LSM_MATHML_ELEMENT (script->superscript), style))
			need_measure = TRUE;

	return need_measure;
}

static const LsmMathmlBbox *
lsm_mathml_script_element_measure (LsmMathmlElement *element, LsmMathmlView *view,
				const LsmMathmlBbox *stretch_bbox)
{
	LsmMathmlScriptElement *script = LSM_MATHML_SCRIPT_ELEMENT (element);

	lsm_mathml_measure_sub_sup (element,view,
				    script->base,
				    script->subscript,
				    script->superscript,
				    script->subscript_shift.value,
				    script->superscript_shift.value,
				    script->display, stretch_bbox, &element->bbox,
				    &script->subscript_offset, &script->superscript_offset);

	return &element->bbox;
}

static void
lsm_mathml_script_element_layout (LsmMathmlElement *self, LsmMathmlView *view,
			       double x, double y, const LsmMathmlBbox *bbox)
{
	LsmMathmlScriptElement *script = LSM_MATHML_SCRIPT_ELEMENT (self);

	lsm_mathml_layout_sub_sup (self, view, x, y, script->base, script->subscript, script->superscript,
				script->subscript_offset, script->superscript_offset);
}

static LsmMathmlOperatorElement *
lsm_mathml_script_element_get_embellished_core (const LsmMathmlElement *self)
{
	if (LSM_DOM_NODE (self)->first_child != NULL)
		return lsm_mathml_element_get_embellished_core (LSM_MATHML_ELEMENT (LSM_DOM_NODE (self)->first_child));

	return NULL;
}

/* LsmMathmlScriptElement implementation */

LsmDomNode *
lsm_mathml_sub_element_new (void)
{
	LsmDomNode *node;

	node = g_object_new (LSM_TYPE_MATHML_SCRIPT_ELEMENT, NULL);
	g_return_val_if_fail (node != NULL, NULL);

	LSM_MATHML_SCRIPT_ELEMENT (node)->type = LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUB;

	return node;
}

LsmDomNode *
lsm_mathml_sup_element_new (void)
{
	LsmDomNode *node;

	node = g_object_new (LSM_TYPE_MATHML_SCRIPT_ELEMENT, NULL);
	g_return_val_if_fail (node != NULL, NULL);

	LSM_MATHML_SCRIPT_ELEMENT (node)->type = LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUP;

	return node;
}

LsmDomNode *
lsm_mathml_sub_sup_element_new (void)
{
	LsmDomNode *node;

	node = g_object_new (LSM_TYPE_MATHML_SCRIPT_ELEMENT, NULL);
	g_return_val_if_fail (node != NULL, NULL);

	LSM_MATHML_SCRIPT_ELEMENT (node)->type = LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUB_SUP;

	return node;
}

static const LsmMathmlLength length_default = {1.0, LSM_MATHML_UNIT_NONE};

static void
lsm_mathml_script_element_init (LsmMathmlScriptElement *self)
{
	self->subscript_shift.length = length_default;
	self->superscript_shift.length = length_default;
}

/* LsmMathmlScriptElement class */

static const LsmAttributeInfos _attribute_infos[] = {
	{
		.name = "subscriptshift",
		.attribute_offset = offsetof (LsmMathmlScriptElement, subscript_shift),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "superscriptshift",
		.attribute_offset = offsetof (LsmMathmlScriptElement, superscript_shift),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	}
};

static void
lsm_mathml_script_element_class_init (LsmMathmlScriptElementClass *script_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (script_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (script_class);

	d_node_class->get_node_name = lsm_mathml_script_element_get_node_name;
	d_node_class->can_append_child = lsm_mathml_script_element_can_append_child;
	d_node_class->post_new_child = lsm_mathml_script_element_post_new_child;

	m_element_class->update = lsm_mathml_script_element_update;
	m_element_class->update_children = lsm_mathml_script_element_update_children;
	m_element_class->measure = lsm_mathml_script_element_measure;
	m_element_class->layout = lsm_mathml_script_element_layout;
	m_element_class->get_embellished_core = lsm_mathml_script_element_get_embellished_core;
	m_element_class->is_inferred_row = NULL;
	m_element_class->attribute_manager = lsm_attribute_manager_duplicate (m_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (m_element_class->attribute_manager,
					      G_N_ELEMENTS (_attribute_infos),
					      _attribute_infos);
}

G_DEFINE_TYPE (LsmMathmlScriptElement, lsm_mathml_script_element, LSM_TYPE_MATHML_ELEMENT)
