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

#include <lsmmathmlfencedelement.h>
#include <lsmmathmlview.h>

static GObjectClass *parent_class;

/* LsmDomNode implementation */

static const char *
lsm_mathml_fenced_element_get_node_name (LsmDomNode *node)
{
	return "mfenced";
}

/* LsmMathmlElement implementation */

static const LsmMathmlBbox *
lsm_mathml_fenced_element_measure (LsmMathmlElement *self, LsmMathmlView *view, const LsmMathmlBbox *bbox)
{
	LsmMathmlFencedElement *fenced = LSM_MATHML_FENCED_ELEMENT (self);
	LsmMathmlBbox stretch_bbox = lsm_mathml_bbox_null;
	double axis_offset;
	double spacing = 0.0;
	char *open;
	char *close;

	LSM_MATHML_ELEMENT_CLASS (parent_class)->measure (self, view, bbox);

	stretch_bbox = self->bbox;
	open = fenced->open.value;
	close = fenced->close.value;
	axis_offset = lsm_mathml_view_measure_axis_offset (view, self->style.math_size);

	if (open != NULL && open[0] != '\0') {
		lsm_mathml_view_measure_operator (view, &self->style,
					       open, FALSE, TRUE,
					       axis_offset,
					       &stretch_bbox, &fenced->open_bbox);
		spacing += self->style.math_size * LSM_MATHML_SPACE_EM_THIN;
	} else
		fenced->open_bbox = lsm_mathml_bbox_null;

	if (close != NULL && close[0] != '\0') {
		lsm_mathml_view_measure_operator (view, &self->style,
					       close, FALSE, TRUE,
					       axis_offset,
					       &stretch_bbox, &fenced->close_bbox);
		spacing += self->style.math_size * LSM_MATHML_SPACE_EM_THIN;
	} else
		fenced->close_bbox = lsm_mathml_bbox_null;

	lsm_mathml_bbox_add_horizontally (&self->bbox, &fenced->open_bbox);
	lsm_mathml_bbox_add_horizontally (&self->bbox, &fenced->close_bbox);

	self->bbox.width += spacing;

	return &self->bbox;
}

static void
lsm_mathml_fenced_element_layout (LsmMathmlElement *self, LsmMathmlView *view,
			       double x, double y, const LsmMathmlBbox *bbox)
{
	LsmMathmlFencedElement *fenced = LSM_MATHML_FENCED_ELEMENT (self);
	double offset;

	offset = (fenced->open.value != NULL && fenced->open.value[0]) ?
		self->style.math_size * LSM_MATHML_SPACE_EM_THIN : 0.0;

	LSM_MATHML_ELEMENT_CLASS (parent_class)->layout (self, view,
						      offset + x + fenced->open_bbox.width,
						      y, bbox);
}

static void
lsm_mathml_fenced_element_render (LsmMathmlElement *self, LsmMathmlView *view)
{
	LsmMathmlFencedElement *fenced = LSM_MATHML_FENCED_ELEMENT (self);

	lsm_mathml_view_show_operator (view, &self->style,
				    self->x, self->y, fenced->open.value,
				    FALSE, &fenced->open_bbox);

	LSM_MATHML_ELEMENT_CLASS (parent_class)->render (self, view);

	lsm_mathml_view_show_operator (view, &self->style,
				    self->bbox.width + self->x - fenced->close_bbox.width,
				    self->y, fenced->close.value,
				    FALSE, &fenced->close_bbox);
}

/* LsmMathmlFencedElement implementation */

static const char *open_default = "(";
static const char *close_default = ")";
static const char *separators_default = ",";

LsmDomNode *
lsm_mathml_fenced_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_FENCED_ELEMENT, NULL);
}

static void
lsm_mathml_fenced_element_init (LsmMathmlFencedElement *self)
{
	self->open.value = g_strdup (open_default);
	self->close.value = g_strdup (close_default);
	self->separators.value = g_strdup (separators_default);
}

/* LsmMathmlFencedElement class */

static const LsmAttributeInfos _attribute_infos[] = {
	{
		.name = "open",
		.attribute_offset = offsetof (LsmMathmlFencedElement, open),
		.trait_class = &lsm_mathml_string_trait_class,
		.trait_default = &open_default
	},
	{
		.name = "close",
		.attribute_offset = offsetof (LsmMathmlFencedElement, close),
		.trait_class = &lsm_mathml_string_trait_class,
		.trait_default = &close_default
	},
	{
		.name = "separators",
		.attribute_offset = offsetof (LsmMathmlFencedElement, separators),
		.trait_class = &lsm_mathml_string_trait_class,
		.trait_default = &separators_default
	}
};

static void
lsm_mathml_fenced_element_class_init (LsmMathmlFencedElementClass *m_fenced_element_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (m_fenced_element_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (m_fenced_element_class);

	parent_class = g_type_class_peek_parent (m_fenced_element_class);

	d_node_class->get_node_name = lsm_mathml_fenced_element_get_node_name;

	m_element_class->measure = lsm_mathml_fenced_element_measure;
	m_element_class->layout =  lsm_mathml_fenced_element_layout;
	m_element_class->render =  lsm_mathml_fenced_element_render;
	m_element_class->attribute_manager = lsm_attribute_manager_duplicate (m_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (m_element_class->attribute_manager,
					      G_N_ELEMENTS (_attribute_infos),
					      _attribute_infos);
}

G_DEFINE_TYPE (LsmMathmlFencedElement, lsm_mathml_fenced_element, LSM_TYPE_MATHML_PRESENTATION_CONTAINER)

