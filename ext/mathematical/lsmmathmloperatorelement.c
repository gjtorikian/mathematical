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

#include <lsmdebug.h>
#include <lsmmathmloperatorelement.h>
#include <lsmmathmloperatordictionary.h>
#include <lsmmathmlunderoverelement.h>
#include <lsmmathmlscriptelement.h>
#include <lsmmathmlview.h>

static GObject *parent_class;

/* LsmDomNode implementation */

static const char *
lsm_mathml_operator_element_get_node_name (LsmDomNode *node)
{
	return "mo";
}

static const LsmMathmlOperatorDictionaryEntry *
lsm_mathml_operator_element_dictionary_lookup (LsmMathmlOperatorElement *operator)
{
	const LsmMathmlOperatorDictionaryEntry *entry;
	LsmDomNode *node = LSM_DOM_NODE (operator);
	LsmMathmlForm form;
	char *text;

	for (node = LSM_DOM_NODE (operator);
	     node->parent_node != NULL &&
	     LSM_IS_MATHML_ELEMENT (node->parent_node) &&
	     lsm_mathml_element_get_embellished_core (LSM_MATHML_ELEMENT (node->parent_node)) == operator;
	     node = node->parent_node);

	text = lsm_mathml_presentation_token_get_text (LSM_MATHML_PRESENTATION_TOKEN (operator));

	if (LSM_IS_MATHML_ELEMENT (node->parent_node)) {
	       if (lsm_mathml_element_is_inferred_row (LSM_MATHML_ELEMENT (node->parent_node))) {
		       if ((node->previous_sibling != NULL && node->next_sibling != NULL) ||
			   (node->previous_sibling == NULL && node->next_sibling == NULL))
			       form = LSM_MATHML_FORM_INFIX;
		       else if (node->previous_sibling == NULL)
			       form = LSM_MATHML_FORM_PREFIX;
		       else
			       form = LSM_MATHML_FORM_POSTFIX;
	       } else if (LSM_IS_MATHML_UNDER_OVER_ELEMENT (node->parent_node) &&
			  node->previous_sibling != NULL) {
		       form = LSM_MATHML_FORM_POSTFIX;
	       } else if (LSM_IS_MATHML_SCRIPT_ELEMENT (node->parent_node) &&
			  node->previous_sibling != NULL) {
		       form = LSM_MATHML_FORM_POSTFIX;
	       } else
		       form = LSM_MATHML_FORM_INFIX;
	} else
		form = LSM_MATHML_FORM_INFIX;

	form = lsm_mathml_enum_attribute_inherit (&operator->form, form);

	entry = lsm_mathml_operator_dictionary_lookup (text, form);

	g_free (text);

	return entry;
}

static void
lsm_mathml_operator_element_post_new_child (LsmDomNode *self, LsmDomNode *child)
{
	LsmMathmlOperatorElement *operator_element = LSM_MATHML_OPERATOR_ELEMENT (self);
	const LsmMathmlOperatorDictionaryEntry *entry;

	entry = lsm_mathml_operator_element_dictionary_lookup (operator_element);

	lsm_debug_dom ("[OperatorElement::post_new_child] found %s %s",
		    lsm_mathml_form_to_string (entry->form), entry->name);

	lsm_mathml_boolean_attribute_inherit (&operator_element->stretchy, entry->stretchy);
	lsm_mathml_boolean_attribute_inherit (&operator_element->fence, entry->fence);
	lsm_mathml_boolean_attribute_inherit (&operator_element->accent, entry->accent);
}

/* LsmMathmlElement implementation */

static void
lsm_mathml_operator_element_update (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmMathmlOperatorElement *operator_element = LSM_MATHML_OPERATOR_ELEMENT (self);
	const LsmMathmlOperatorDictionaryEntry *entry;
	LsmMathmlSpace space;

	LSM_MATHML_ELEMENT_CLASS (parent_class)->update (self, style);

	entry = lsm_mathml_operator_element_dictionary_lookup (operator_element);

	lsm_debug_update ("[OperatorElement::update] found %s %s",
		    lsm_mathml_form_to_string (entry->form), entry->name);

	space = entry->left_space;
	lsm_mathml_space_attribute_normalize (&operator_element->left_space, 0.0, &space, style);
	space = entry->right_space;
	lsm_mathml_space_attribute_normalize (&operator_element->right_space, 0.0, &space, style);
	lsm_mathml_boolean_attribute_inherit (&operator_element->stretchy, entry->stretchy);
	lsm_mathml_boolean_attribute_inherit (&operator_element->fence, entry->fence);
	lsm_mathml_boolean_attribute_inherit (&operator_element->accent, entry->accent);

	if (operator_element->accent.value)
		lsm_debug_update ("[OperatorElement::update] Is accent");

	lsm_mathml_boolean_attribute_inherit (&operator_element->large_op, entry->large_op);
	lsm_mathml_boolean_attribute_inherit (&operator_element->movable_limits, entry->movable_limits);
	lsm_mathml_boolean_attribute_inherit (&operator_element->separator, entry->separator);
	space = entry->min_size;
	lsm_mathml_space_attribute_normalize (&operator_element->min_size, 0.0, &space, style);
	space = entry->max_size;
	lsm_mathml_space_attribute_normalize (&operator_element->max_size, 0.0, &space, style);
	lsm_mathml_boolean_attribute_inherit (&operator_element->symmetric, entry->symmetric);

	operator_element->is_large_op = operator_element->large_op.value &&
		(style->display == LSM_MATHML_DISPLAY_BLOCK);
	if (operator_element->is_large_op)
		lsm_debug_update ("[OperatorElement::update] Large op");
}

static const LsmMathmlBbox *
lsm_mathml_operator_element_measure (LsmMathmlElement *self, LsmMathmlView *view, const LsmMathmlBbox *stretch_bbox)
{
	LsmMathmlOperatorElement *operator_element = LSM_MATHML_OPERATOR_ELEMENT (self);
	char *text;

	text = lsm_mathml_presentation_token_get_text (LSM_MATHML_PRESENTATION_TOKEN (self));

	self->bbox = lsm_mathml_bbox_null;

	lsm_mathml_view_measure_operator (view, &self->style,
				       text,
				       operator_element->is_large_op,
				       operator_element->symmetric.value,
				       lsm_mathml_view_measure_axis_offset (view, self->style.math_size),
				       operator_element->stretchy.value ? stretch_bbox : &lsm_mathml_bbox_null,
				       &self->bbox);

	g_free (text);

	self->bbox.width += self->style.math_size * LSM_MATHML_SPACE_EM_VERY_THIN;

	return &self->bbox;
}

static void
lsm_mathml_operator_element_render (LsmMathmlElement *self, LsmMathmlView *view)
{
	LsmMathmlOperatorElement *operator_element = LSM_MATHML_OPERATOR_ELEMENT (self);
	LsmMathmlBbox stretch_bbox;
	char *text;

	text = lsm_mathml_presentation_token_get_text (LSM_MATHML_PRESENTATION_TOKEN (self));

	stretch_bbox = self->bbox;
	stretch_bbox.width -= self->style.math_size * LSM_MATHML_SPACE_EM_VERY_THIN;

	lsm_mathml_view_show_operator (view, &self->style,
				    self->x + 0.5 * self->style.math_size * LSM_MATHML_SPACE_EM_VERY_THIN,
				    self->y, text,
				    operator_element->is_large_op, &stretch_bbox);

	g_free (text);
}

static LsmMathmlOperatorElement *
lsm_mathml_operator_element_get_embellished_core (const LsmMathmlElement *self)
{
	return LSM_MATHML_OPERATOR_ELEMENT (self);
}

/* LsmMathmlOperatorElement implementation */

double
lsm_mathml_operator_element_get_slant (const LsmMathmlOperatorElement *operator_element, LsmMathmlView *view)
{
	char *text;

	g_return_val_if_fail (LSM_IS_MATHML_OPERATOR_ELEMENT (operator_element), 0.0);

	text = lsm_mathml_presentation_token_get_text (LSM_MATHML_PRESENTATION_TOKEN (operator_element));

	return lsm_mathml_view_get_operator_slant (view, &LSM_MATHML_ELEMENT (operator_element)->style, text);
}

LsmDomNode *
lsm_mathml_operator_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_OPERATOR_ELEMENT, NULL);
}

static void
lsm_mathml_operator_element_init (LsmMathmlOperatorElement *self)
{
}

/* LsmMathmlOperatorElement class */

static const LsmAttributeInfos _attribute_infos[] = {
	{
		.name = "form",
		.attribute_offset = offsetof (LsmMathmlOperatorElement, form),
		.trait_class = &lsm_mathml_form_trait_class
	},
	{
		.name = "lspace",
		.attribute_offset = offsetof (LsmMathmlOperatorElement, left_space),
		.trait_class = &lsm_mathml_space_trait_class
	},
	{
		.name = "rspace",
		.attribute_offset = offsetof (LsmMathmlOperatorElement, right_space),
		.trait_class = &lsm_mathml_space_trait_class
	},
	{
		.name = "stretchy",
		.attribute_offset = offsetof (LsmMathmlOperatorElement, stretchy),
		.trait_class = &lsm_mathml_boolean_trait_class,
	},
	{
		.name = "fence",
		.attribute_offset = offsetof (LsmMathmlOperatorElement, fence),
		.trait_class = &lsm_mathml_boolean_trait_class
	},
	{
		.name = "accent",
		.attribute_offset = offsetof (LsmMathmlOperatorElement, accent),
		.trait_class = &lsm_mathml_boolean_trait_class,
	},
	{
		.name = "large_op",
		.attribute_offset = offsetof (LsmMathmlOperatorElement, large_op),
		.trait_class = &lsm_mathml_boolean_trait_class,
	},
	{
		.name = "movable_limits",
		.attribute_offset = offsetof (LsmMathmlOperatorElement, movable_limits),
		.trait_class = &lsm_mathml_boolean_trait_class,
	},
	{
		.name = "separator",
		.attribute_offset = offsetof (LsmMathmlOperatorElement, separator),
		.trait_class = &lsm_mathml_boolean_trait_class,
	},
	{
		.name = "minsize",
		.attribute_offset = offsetof (LsmMathmlOperatorElement, min_size),
		.trait_class = &lsm_mathml_space_trait_class
	},
	{
		.name = "maxsize",
		.attribute_offset = offsetof (LsmMathmlOperatorElement, max_size),
		.trait_class = &lsm_mathml_space_trait_class
	},
	{
		.name = "symmetric",
		.attribute_offset = offsetof (LsmMathmlOperatorElement, symmetric),
		.trait_class = &lsm_mathml_boolean_trait_class,
	}
};

static void
lsm_mathml_operator_element_class_init (LsmMathmlOperatorElementClass *operator_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (operator_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (operator_class);

	parent_class = g_type_class_peek_parent (operator_class);

	d_node_class->get_node_name = lsm_mathml_operator_element_get_node_name;
	d_node_class->post_new_child = lsm_mathml_operator_element_post_new_child;

	m_element_class->update = lsm_mathml_operator_element_update;
	m_element_class->measure = lsm_mathml_operator_element_measure;
	m_element_class->render = lsm_mathml_operator_element_render;
	m_element_class->get_embellished_core = lsm_mathml_operator_element_get_embellished_core;
	m_element_class->attribute_manager = lsm_attribute_manager_duplicate (m_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (m_element_class->attribute_manager,
					      G_N_ELEMENTS (_attribute_infos),
					      _attribute_infos);
}

G_DEFINE_TYPE (LsmMathmlOperatorElement, lsm_mathml_operator_element, LSM_TYPE_MATHML_PRESENTATION_TOKEN)
