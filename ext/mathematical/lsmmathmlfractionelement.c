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

#include <lsmmathmlfractionelement.h>
#include <lsmmathmlview.h>

static GObjectClass *parent_class;

/* LsmDomNode implementation */

static const char *
lsm_mathml_fraction_element_get_node_name (LsmDomNode *node)
{
	return "mfrac";
}

static gboolean
lsm_mathml_fraction_element_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	return (LSM_IS_MATHML_ELEMENT (child) &&
		(self->first_child == NULL ||
		 self->first_child->next_sibling == NULL));
}

/* LsmMathmlElement implementation */

static void
lsm_mathml_fraction_element_update (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmMathmlFractionElement *fraction = LSM_MATHML_FRACTION_ELEMENT (self);
	LsmMathmlLength length;

	length.unit = LSM_MATHML_UNIT_PT;

	length.value = style->line_thickness;
	style->line_thickness = lsm_mathml_length_attribute_normalize (&fraction->line_thickness,
								       style->line_thickness,
								       &length, style);

	fraction->display = style->display;
}

static gboolean
lsm_mathml_fraction_element_update_children (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	if (style->display == LSM_MATHML_DISPLAY_INLINE)
		lsm_mathml_style_change_script_level (style, +1);
	else
		style->display = LSM_MATHML_DISPLAY_INLINE;

	return LSM_MATHML_ELEMENT_CLASS (parent_class)->update_children (self, style);
}

static const LsmMathmlBbox *
lsm_mathml_fraction_element_measure (LsmMathmlElement *self, LsmMathmlView *view, const LsmMathmlBbox *bbox)
{
	LsmMathmlFractionElement *fraction = LSM_MATHML_FRACTION_ELEMENT (self);
	LsmDomNode *node;
	const LsmMathmlBbox *child_bbox;
	double h_space;
	double v_space;
	double length, dividend_offset, divisor_offset;

	fraction->axis_offset = lsm_mathml_view_measure_axis_offset (view, self->style.math_size);

	if (fraction->display == LSM_MATHML_DISPLAY_INLINE)
		v_space = self->style.math_size * LSM_MATHML_SPACE_EM_VERY_THIN;
	else
		v_space = self->style.math_size * LSM_MATHML_SPACE_EM_MEDIUM;
	h_space = self->style.math_size * LSM_MATHML_SPACE_EM_VERY_THIN;

	self->bbox.is_defined = TRUE;
	self->bbox.depth = - (fraction->axis_offset - v_space - 0.5 * fraction->line_thickness.value);

	self->bbox.width = 0.0;
	self->bbox.height = fraction->axis_offset + v_space + 0.5 * fraction->line_thickness.value;

	node = LSM_DOM_NODE (self)->first_child;

	if (node == NULL)
		return &self->bbox;

	child_bbox = lsm_mathml_element_measure (LSM_MATHML_ELEMENT (node), view, NULL);
	lsm_mathml_view_get_font_metrics (view, &LSM_MATHML_ELEMENT (node)->style, NULL, &length);

	if (fraction->display == LSM_MATHML_DISPLAY_INLINE)
		length *= 0.5;

	if (child_bbox->depth < length)
		dividend_offset = length - child_bbox->depth;
	else
		dividend_offset = 0.0;

	lsm_mathml_bbox_add_over (&self->bbox, child_bbox);

	node = node->next_sibling;

	if (node == NULL)
		return &self->bbox;

	child_bbox = lsm_mathml_element_measure (LSM_MATHML_ELEMENT (node), view, NULL);
	lsm_mathml_view_get_font_metrics (view, &LSM_MATHML_ELEMENT (node)->style, &length, NULL);
	if (child_bbox->height < length)
		divisor_offset = length - child_bbox->height;
	else
		divisor_offset = 0.0;

	lsm_mathml_bbox_add_under (&self->bbox, child_bbox);

	self->bbox.height += dividend_offset;
	self->bbox.depth += divisor_offset;
	self->bbox.width += 2.0 * h_space;

	return &self->bbox;
}

static void
lsm_mathml_fraction_element_layout (LsmMathmlElement *self, LsmMathmlView *view,
				 double x, double y, const LsmMathmlBbox *bbox)
{
	LsmDomNode *node;
	const LsmMathmlBbox *child_bbox;

	node = LSM_DOM_NODE (self)->first_child;

	if (node != NULL) {
		child_bbox = lsm_mathml_element_get_bbox (LSM_MATHML_ELEMENT (node));
		lsm_mathml_element_layout (LSM_MATHML_ELEMENT (node), view,
					x + (bbox->width - child_bbox->width) / 2.0,
					y - self->bbox.height + child_bbox->height,
					child_bbox);

		node = node->next_sibling;
		if (node != NULL) {
			child_bbox = lsm_mathml_element_get_bbox (LSM_MATHML_ELEMENT (node));
			lsm_mathml_element_layout (LSM_MATHML_ELEMENT (node), view,
						x + (bbox->width - child_bbox->width) / 2.0,
						y + self->bbox.depth - child_bbox->depth,
						child_bbox);
		}
	}
}

static void
lsm_mathml_fraction_element_render (LsmMathmlElement *self, LsmMathmlView *view)
{
	LsmMathmlFractionElement *fraction = LSM_MATHML_FRACTION_ELEMENT (self);
	double h_space;

	h_space = self->style.math_size * LSM_MATHML_SPACE_EM_VERY_THIN;

	lsm_mathml_view_show_fraction_line (view, &self->style,
					 self->x + h_space,
					 self->y - fraction->axis_offset,
					 self->bbox.width - 2.0 * h_space,
					 fraction->line_thickness.value);

	LSM_MATHML_ELEMENT_CLASS (parent_class)->render (self, view);
}

static LsmMathmlOperatorElement *
lsm_mathml_fraction_element_get_embellished_core (const LsmMathmlElement *self)
{
	if (LSM_DOM_NODE (self)->first_child != NULL)
		return lsm_mathml_element_get_embellished_core (LSM_MATHML_ELEMENT (LSM_DOM_NODE (self)->first_child));

	return NULL;
}

/* LsmMathmlFraction implementation */

static const gboolean bevelled_default = FALSE;

LsmDomNode *
lsm_mathml_fraction_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_FRACTION_ELEMENT, NULL);
}

static const LsmMathmlLength length_default = {1.0, LSM_MATHML_UNIT_NONE};

static void
lsm_mathml_fraction_element_init (LsmMathmlFractionElement *self)
{
	self->axis_offset = 0.0;

	self->bevelled.value = bevelled_default;
	self->line_thickness.length = length_default;
}

/* LsmMathmlFractionElement class */

static const LsmAttributeInfos _attribute_infos[] = {
	{
		.name = "bevelled",
		.attribute_offset = offsetof (LsmMathmlFractionElement, bevelled),
		.trait_class = &lsm_mathml_boolean_trait_class,
		.trait_default = &bevelled_default
	},
	{
		.name = "linethickness",
		.attribute_offset = offsetof (LsmMathmlFractionElement, line_thickness),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
};

static void
lsm_mathml_fraction_element_class_init (LsmMathmlFractionElementClass *fraction_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (fraction_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (fraction_class);

	parent_class = g_type_class_peek_parent (fraction_class);

	d_node_class->get_node_name = lsm_mathml_fraction_element_get_node_name;
	d_node_class->can_append_child = lsm_mathml_fraction_element_can_append_child;

	m_element_class->update = lsm_mathml_fraction_element_update;
	m_element_class->update_children = lsm_mathml_fraction_element_update_children;
	m_element_class->measure = lsm_mathml_fraction_element_measure;
	m_element_class->layout = lsm_mathml_fraction_element_layout;
	m_element_class->render = lsm_mathml_fraction_element_render;
	m_element_class->get_embellished_core = lsm_mathml_fraction_element_get_embellished_core;
	m_element_class->is_inferred_row = NULL;
	m_element_class->attribute_manager = lsm_attribute_manager_duplicate (m_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (m_element_class->attribute_manager,
					      G_N_ELEMENTS (_attribute_infos),
					      _attribute_infos);
}

G_DEFINE_TYPE (LsmMathmlFractionElement, lsm_mathml_fraction_element, LSM_TYPE_MATHML_ELEMENT)
