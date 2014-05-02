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
#include <lsmmathmlunderoverelement.h>
#include <lsmmathmloperatorelement.h>
#include <lsmmathmllayoututils.h>
#include <lsmmathmlview.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_mathml_under_over_get_node_name (LsmDomNode *node)
{
	LsmMathmlUnderOverElement *under_over = LSM_MATHML_UNDER_OVER_ELEMENT (node);

	switch (under_over->type) {
		case LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_UNDER:
			return "munder";
		case LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_OVER:
			return "mover";
		case LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_UNDER_OVER:
		default:
			return "munderover";
	}
}

static gboolean
lsm_mathml_under_over_element_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	LsmMathmlUnderOverElement *under_over = LSM_MATHML_UNDER_OVER_ELEMENT (self);

	if (!LSM_IS_MATHML_ELEMENT (child))
		return FALSE;

	if (self->first_child == NULL ||
	    self->first_child->next_sibling == NULL)
		return TRUE;

	if (under_over->type != LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_UNDER_OVER)
		return FALSE;

	return (self->first_child->next_sibling->next_sibling == NULL);
}

static void
lsm_mathml_under_over_element_update_child_pointers (LsmMathmlUnderOverElement *self)
{
	LsmDomNode *node;

	node = LSM_DOM_NODE (self)->first_child;
	if (node == NULL) {
		self->base = NULL;
		self->underscript = NULL;
		self->overscript = NULL;
		return;
	} else
		self->base = LSM_MATHML_ELEMENT (node);

	node = node->next_sibling;
	if (node != NULL)
		switch (self->type) {
			case LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_OVER:
				self->underscript = NULL;
				self->overscript = LSM_MATHML_ELEMENT (node);
				break;
			case LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_UNDER:
				self->underscript = LSM_MATHML_ELEMENT (node);
				self->overscript = NULL;
				break;
			default:
				self->underscript = LSM_MATHML_ELEMENT (node);
				node = node->next_sibling;
				if (node != NULL)
					self->overscript = LSM_MATHML_ELEMENT (node);
		}
	else {
		self->underscript = NULL;
		self->overscript = NULL;
	}
}

static void
lsm_mathml_under_over_element_post_new_child (LsmDomNode *self, LsmDomNode *child)
{
	LsmMathmlUnderOverElement *under_over = LSM_MATHML_UNDER_OVER_ELEMENT (self);

	lsm_mathml_under_over_element_update_child_pointers (under_over);
}

/* LsmMathmlElement implementation */

static void
lsm_mathml_under_over_element_update (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmMathmlUnderOverElement *under_over = LSM_MATHML_UNDER_OVER_ELEMENT (self);

	under_over->display = style->display;

}

static gboolean
lsm_mathml_under_over_element_update_children (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmMathmlUnderOverElement *under_over = LSM_MATHML_UNDER_OVER_ELEMENT (self);
	LsmMathmlStyle *overscript_style;
	gboolean accent = FALSE;
	gboolean accent_under = FALSE;
	gboolean movable_limits = FALSE;
	double accent_v_space;
	double v_space;
	gboolean need_measure = FALSE;

	accent_v_space = self->style.math_size * LSM_MATHML_SPACE_EM_THIN;
	v_space = under_over->display == LSM_MATHML_DISPLAY_INLINE ?
		self->style.math_size * LSM_MATHML_SPACE_EM_VERY_VERY_THIN :
		self->style.math_size * LSM_MATHML_SPACE_EM_MEDIUM;

	if (under_over->base != NULL)
		if (lsm_mathml_element_update (LSM_MATHML_ELEMENT (under_over->base), style))
			need_measure = TRUE;

	style->display = LSM_MATHML_DISPLAY_INLINE;

	overscript_style = lsm_mathml_style_duplicate (style);

	if (under_over->underscript != NULL) {
		const LsmMathmlOperatorElement *operator;

		operator = lsm_mathml_element_get_embellished_core (under_over->underscript);
		if (operator != NULL) {
			accent_under = operator->accent.value;
			lsm_debug_update ("[UnderOver::update] Underscript is%s an accent (%s)",
				    accent_under ? "" : " not",
				    lsm_dom_node_get_node_name (LSM_DOM_NODE (operator)));
		}

		accent_under = lsm_mathml_boolean_attribute_inherit (&under_over->accent_under, accent_under);

		if (!under_over->accent_under.value)
			lsm_mathml_style_change_script_level (style, +1);

		if (lsm_mathml_element_update (LSM_MATHML_ELEMENT (under_over->underscript), style))
			need_measure = TRUE;
	}

	if (under_over->overscript != NULL) {
		const LsmMathmlOperatorElement *operator;

		operator = lsm_mathml_element_get_embellished_core (under_over->overscript);
		if (operator != NULL) {
			accent = operator->accent.value;
			lsm_debug_update ("[UnderOver::update] Overscript is%s an accent (%s)",
					  accent ? "" : " not",
					  lsm_dom_node_get_node_name (LSM_DOM_NODE (operator)));
		}

		accent = lsm_mathml_boolean_attribute_inherit (&under_over->accent, accent);

		if (!under_over->accent.value)
			lsm_mathml_style_change_script_level (overscript_style, +1);

		if (lsm_mathml_element_update (LSM_MATHML_ELEMENT (under_over->overscript), overscript_style))
			need_measure = TRUE;
	}

	lsm_mathml_style_free (overscript_style);

	if (under_over->base != NULL) {
		const LsmMathmlOperatorElement *operator;

		operator = lsm_mathml_element_get_embellished_core (under_over->base);
		if (operator != NULL) {
			movable_limits = operator->movable_limits.value;
			lsm_debug_update ("[UnderOver::update] movable_limits found");
		}
	}

	under_over->under_space = accent_under ? accent_v_space : v_space;
	under_over->over_space  = accent       ? accent_v_space : v_space;

	under_over->as_script = under_over->display == LSM_MATHML_DISPLAY_INLINE && movable_limits;

	lsm_debug_update ("[UnderOver::update] space under = %g, over = %g",
		    under_over->under_space, under_over->over_space);

	return need_measure;
}

static const LsmMathmlBbox *
lsm_mathml_under_over_element_measure (LsmMathmlElement *self, LsmMathmlView *view, const LsmMathmlBbox *stretch_bbox)
{
	LsmMathmlUnderOverElement *under_over = LSM_MATHML_UNDER_OVER_ELEMENT (self);
	const LsmMathmlOperatorElement *operator;
	LsmDomNode *node;
	const LsmMathmlBbox *child_bbox;
	LsmMathmlBbox regular_stretch_bbox;
	LsmMathmlBbox operator_stretch_bbox;
	LsmMathmlBbox script_bbox;
	double length;
	gboolean stretchy_found = FALSE;
	gboolean all_stretchy = TRUE;
	unsigned int index;

	if (under_over->as_script) {
		lsm_mathml_measure_sub_sup (self, view,
					 under_over->base,
					 under_over->underscript,
					 under_over->overscript,
					 0.0, 0.0,
					 LSM_MATHML_DISPLAY_INLINE,
					 stretch_bbox, &self->bbox,
					 &under_over->underscript_offset,
					 &under_over->overscript_offset);

		return &self->bbox;
	}

	self->bbox = lsm_mathml_bbox_null;

	if (under_over->base == NULL)
		return &self->bbox;

	regular_stretch_bbox = lsm_mathml_bbox_null;
	operator_stretch_bbox = lsm_mathml_bbox_null;

	lsm_debug_measure ("[UnderOver::measure] Begin");

	index = 0;
	for (node = LSM_DOM_NODE (self)->first_child; node != NULL; node = node->next_sibling) {
		if (LSM_IS_MATHML_ELEMENT (node)) {
			operator = lsm_mathml_element_get_embellished_core (LSM_MATHML_ELEMENT (node));
			if (operator != NULL && operator->stretchy.value) {
				stretchy_found = TRUE;

				if (node == LSM_DOM_NODE (under_over->base))
					child_bbox = lsm_mathml_element_measure (LSM_MATHML_ELEMENT (node), view,
									      stretch_bbox);
				else
					child_bbox = lsm_mathml_element_measure (LSM_MATHML_ELEMENT (node), view,
									      &lsm_mathml_bbox_null);
				lsm_mathml_bbox_stretch_horizontally (&operator_stretch_bbox, child_bbox);
			} else {
				all_stretchy = FALSE;

				child_bbox = lsm_mathml_element_measure (LSM_MATHML_ELEMENT (node), view,
								      &lsm_mathml_bbox_null);
				lsm_mathml_bbox_stretch_horizontally (&regular_stretch_bbox, child_bbox);
			}
		}

		index++;
	}

	if (stretchy_found) {
		if (all_stretchy) {
			lsm_debug_measure ("[UnderOver::measure] All stretchy");
			regular_stretch_bbox = operator_stretch_bbox;
		}

		lsm_debug_measure ("[UnderOver::measure] Stretchy found (width = %g, height = %g, depth = %g)",
			    regular_stretch_bbox.width,
			    regular_stretch_bbox.height,
			    regular_stretch_bbox.depth);

		for (node = LSM_DOM_NODE (self)->first_child; node != NULL; node = node->next_sibling) {
			if (LSM_IS_MATHML_ELEMENT (node)) {
				operator = lsm_mathml_element_get_embellished_core (LSM_MATHML_ELEMENT (node));
				if (operator != NULL && operator->stretchy.value) {
					if (node == LSM_DOM_NODE (under_over->base)) {
						LsmMathmlBbox base_stretch_bbox;

						base_stretch_bbox = regular_stretch_bbox;
						lsm_mathml_bbox_stretch (&base_stretch_bbox, stretch_bbox);

						child_bbox = lsm_mathml_element_measure (LSM_MATHML_ELEMENT (node), view,
										      &base_stretch_bbox);
					} else
						child_bbox = lsm_mathml_element_measure (LSM_MATHML_ELEMENT (node), view,
										      &regular_stretch_bbox);
				}
			}
		}
	}

	self->bbox = *lsm_mathml_element_get_bbox (under_over->base);

	if (under_over->overscript != NULL) {
		script_bbox = *lsm_mathml_element_get_bbox (under_over->overscript);
		lsm_mathml_view_get_font_metrics (view, &under_over->overscript->style, NULL, &length);

		if (under_over->display == LSM_MATHML_DISPLAY_INLINE)
			length *= 0.5;

		if (script_bbox.depth < length && !under_over->accent.value)
			under_over->overscript_offset = length - script_bbox.depth;
		else
			under_over->overscript_offset = 0.0;

		script_bbox.depth += under_over->over_space;
		lsm_mathml_bbox_add_over (&self->bbox, &script_bbox);

		self->bbox.height += under_over->overscript_offset;
	}

	if (under_over->underscript != NULL) {
		script_bbox = *lsm_mathml_element_get_bbox (under_over->underscript);
		lsm_mathml_view_get_font_metrics (view, &under_over->underscript->style, &length, NULL);

		if (script_bbox.height < length && !under_over->accent_under.value)
			under_over->underscript_offset = length - script_bbox.height;
		else
			under_over->underscript_offset = 0.0;

		script_bbox.height += under_over->under_space;
		lsm_mathml_bbox_add_under (&self->bbox, &script_bbox);

		self->bbox.depth += under_over->underscript_offset;
	}

	lsm_debug_measure ("[UnderOver::measure] End");

	return &self->bbox;
}

static void
lsm_mathml_under_over_element_layout (LsmMathmlElement *self, LsmMathmlView *view,
				double x, double y, const LsmMathmlBbox *bbox)
{
	LsmMathmlUnderOverElement *under_over = LSM_MATHML_UNDER_OVER_ELEMENT (self);
	const LsmMathmlBbox *child_bbox;

	if (under_over->as_script) {
		lsm_mathml_layout_sub_sup (self, view,
					x, y,
					under_over->base,
					under_over->underscript,
					under_over->overscript,
					under_over->underscript_offset,
					under_over->overscript_offset);

		return;
	}

	if (under_over->base == NULL)
		return;

	child_bbox = lsm_mathml_element_get_bbox (under_over->base);
	lsm_mathml_element_layout (under_over->base, view, x + (bbox->width - child_bbox->width) * 0.5, y,
				child_bbox);

	if (under_over->underscript) {
		child_bbox = lsm_mathml_element_get_bbox (under_over->underscript);
		lsm_mathml_element_layout (under_over->underscript, view,
					x + (bbox->width - child_bbox->width) * 0.5,
					y + self->bbox.depth - child_bbox->depth,
					child_bbox);
	}
	if (under_over->overscript) {
		child_bbox = lsm_mathml_element_get_bbox (under_over->overscript);
		lsm_mathml_element_layout (under_over->overscript, view,
					x + (bbox->width - child_bbox->width) * 0.5,
					y - self->bbox.height + child_bbox->height,
					child_bbox);
	}
}

static LsmMathmlOperatorElement *
lsm_mathml_under_over_element_get_embellished_core (const LsmMathmlElement *self)
{
	if (LSM_DOM_NODE (self)->first_child != NULL)
		return lsm_mathml_element_get_embellished_core (LSM_MATHML_ELEMENT (LSM_DOM_NODE (self)->first_child));

	return NULL;
}

/* LsmMathmlUnderOverElement implementation */

LsmDomNode *
lsm_mathml_under_element_new (void)
{
	LsmDomNode *node;

	node = g_object_new (LSM_TYPE_MATHML_UNDER_OVER_ELEMENT, NULL);
	g_return_val_if_fail (node != NULL, NULL);

	LSM_MATHML_UNDER_OVER_ELEMENT (node)->type = LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_UNDER;

	return node;
}

LsmDomNode *
lsm_mathml_over_element_new (void)
{
	LsmDomNode *node;

	node = g_object_new (LSM_TYPE_MATHML_UNDER_OVER_ELEMENT, NULL);
	g_return_val_if_fail (node != NULL, NULL);

	LSM_MATHML_UNDER_OVER_ELEMENT (node)->type = LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_OVER;

	return node;
}

LsmDomNode *
lsm_mathml_under_over_element_new (void)
{
	LsmDomNode *node;

	node = g_object_new (LSM_TYPE_MATHML_UNDER_OVER_ELEMENT, NULL);
	g_return_val_if_fail (node != NULL, NULL);

	LSM_MATHML_UNDER_OVER_ELEMENT (node)->type = LSM_MATHML_UNDER_OVER_ELEMENT_TYPE_UNDER_OVER;

	return node;
}

static void
lsm_mathml_under_over_element_init (LsmMathmlUnderOverElement *self)
{
}

/* LsmMathmlUnderOverElement class */

static const LsmAttributeInfos _attribute_infos[] = {
	{
		.name = "accent",
		.attribute_offset = offsetof (LsmMathmlUnderOverElement, accent),
		.trait_class = &lsm_mathml_boolean_trait_class
	},
	{
		.name = "accentunder",
		.attribute_offset = offsetof (LsmMathmlUnderOverElement, accent_under),
		.trait_class = &lsm_mathml_boolean_trait_class,
	}
};

static void
lsm_mathml_under_over_element_class_init (LsmMathmlUnderOverElementClass *under_over_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (under_over_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (under_over_class);

	parent_class = g_type_class_peek_parent (under_over_class);

	d_node_class->get_node_name = lsm_mathml_under_over_get_node_name;
	d_node_class->can_append_child = lsm_mathml_under_over_element_can_append_child;
	d_node_class->post_new_child = lsm_mathml_under_over_element_post_new_child;

	m_element_class->update = lsm_mathml_under_over_element_update;
	m_element_class->update_children = lsm_mathml_under_over_element_update_children;
	m_element_class->measure = lsm_mathml_under_over_element_measure;
	m_element_class->layout = lsm_mathml_under_over_element_layout;
	m_element_class->get_embellished_core = lsm_mathml_under_over_element_get_embellished_core;
	m_element_class->is_inferred_row = NULL;
	m_element_class->attribute_manager = lsm_attribute_manager_duplicate (m_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (m_element_class->attribute_manager,
					      G_N_ELEMENTS (_attribute_infos),
					      _attribute_infos);
}

G_DEFINE_TYPE (LsmMathmlUnderOverElement, lsm_mathml_under_over_element, LSM_TYPE_MATHML_ELEMENT)
