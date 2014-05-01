/* Lasem
 *
 * Copyright © 2009 Emmanuel Pacaud
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

#include <lsmsvglineargradientelement.h>
#include <lsmsvgview.h>
#include <lsmdomdocument.h>
#include <lsmdebug.h>
#include <stdio.h>

typedef struct {
	LsmSvgGradientElementAttributes base;
	LsmSvgLength x1;
	LsmSvgLength y1;
	LsmSvgLength x2;
	LsmSvgLength y2;
} LsmSvgLinearGradientElementAttributes;

static const LsmSvgLinearGradientElementAttributes default_attributes = {
	.base = {
		.transform = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0, LSM_SVG_MATRIX_FLAGS_IDENTITY},
		.units = LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX,
		.spread_method = LSM_SVG_SPREAD_METHOD_PAD
	},
	.x1 = { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PERCENTAGE},
	.y1 = { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PERCENTAGE},
	.x2 = { .value_unit = 100.0, .type = LSM_SVG_LENGTH_TYPE_PERCENTAGE},
	.y1 = { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PERCENTAGE}
};

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_linear_gradient_element_get_node_name (LsmDomNode *node)
{
	return "linearGradient";
}

/* LsmSvgElement implementation */

static LsmSvgGradientElement *
lsm_svg_linear_gradient_element_inherit_referenced (LsmDomDocument *owner,
						    LsmSvgGradientElement *gradient,
						    LsmSvgLinearGradientElementAttributes *attributes,
						    GSList **elements)
{
	LsmSvgGradientElement *referenced_gradient = gradient;
	LsmDomElement *element;

	*elements = g_slist_prepend (*elements, gradient);

	if (lsm_attribute_is_defined (&gradient->href)) {
		char *id;
		GSList *iter;
		gboolean circular_reference_found = FALSE;

		id = gradient->href.value;
		if (id == NULL)
			return NULL;
		if (*id == '#')
			id++;

		element = lsm_dom_document_get_element_by_id (owner, id);

		for (iter = *elements; iter != NULL; iter = iter->next)
			if (iter->data == element) {
				lsm_debug_render ("[LsmSvgLinearGradientElement::inherit_attributes] "
					   "Circular reference (id = %s)", id);
				circular_reference_found = TRUE;
			}

		if (!circular_reference_found) {
			if (LSM_IS_SVG_GRADIENT_ELEMENT (element)) {
				lsm_debug_render ("[LsmSvgLinearGradientElement::inherit_attributes]"
						  " Found referenced element '%s'", id);

				referenced_gradient = lsm_svg_linear_gradient_element_inherit_referenced
					(owner,
					 LSM_SVG_GRADIENT_ELEMENT (element),
					 attributes, elements);

			} else {
				lsm_debug_render ("[LsmSvgLinearGradientElement::inherit_attributes]"
						  " Referenced element '%s' not found", id);
				referenced_gradient = NULL;
			}
		} else
			referenced_gradient = NULL;
	}

	if (LSM_IS_SVG_LINEAR_GRADIENT_ELEMENT (gradient)) {
		LsmSvgLinearGradientElement *linear = LSM_SVG_LINEAR_GRADIENT_ELEMENT (gradient);
		if (lsm_attribute_is_defined (&linear->x1.base))
			attributes->x1 = linear->x1.length;
		if (lsm_attribute_is_defined (&linear->y1.base))
			attributes->y1 = linear->y1.length;
		if (lsm_attribute_is_defined (&linear->x1.base))
			attributes->x2 = linear->x2.length;
		if (lsm_attribute_is_defined (&linear->y2.base))
			attributes->y2 = linear->y2.length;
	}

	if (lsm_attribute_is_defined (&gradient->transform.base))
		attributes->base.transform = gradient->transform.matrix;
	if (lsm_attribute_is_defined (&gradient->units.base))
		attributes->base.units = gradient->units.value;
	if (lsm_attribute_is_defined (&gradient->spread_method.base))
		attributes->base.spread_method = gradient->spread_method.value;

	return referenced_gradient;
}

static LsmSvgGradientElement *
lsm_svg_linear_gradient_element_create_gradient (LsmSvgElement *self,
						 LsmSvgView *view)
{
	LsmSvgLinearGradientElement *gradient = LSM_SVG_LINEAR_GRADIENT_ELEMENT (self);
	LsmSvgGradientElement *referenced_gradient;
	gboolean is_object_bounding_box;
	double x1, x2, y1, y2;

	if (lsm_attribute_is_defined (&gradient->base.href)) {
		LsmSvgLinearGradientElementAttributes attributes;
		LsmDomDocument *owner;
		attributes = default_attributes;
		GSList *elements = NULL;

		owner = lsm_dom_node_get_owner_document (LSM_DOM_NODE (self));

		referenced_gradient = lsm_svg_linear_gradient_element_inherit_referenced
			(owner, LSM_SVG_GRADIENT_ELEMENT (gradient), &attributes, &elements);

		g_slist_free (elements);

		gradient->x1.length = attributes.x1;
		gradient->y1.length = attributes.y1;
		gradient->x2.length = attributes.x2;
		gradient->y2.length = attributes.y2;

		gradient->base.transform.matrix = attributes.base.transform;
		gradient->base.units.value = attributes.base.units;
		gradient->base.spread_method.value = attributes.base.spread_method;
	} else
		referenced_gradient = LSM_SVG_GRADIENT_ELEMENT (gradient);

	if (referenced_gradient == NULL)
		return NULL;

	is_object_bounding_box = (gradient->base.units.value == LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX);

	if (is_object_bounding_box) {
		LsmBox viewbox = {.x = 0.0, .y = .0, .width = 1.0, .height = 1.0};

		lsm_svg_view_push_viewbox (view, &viewbox);
	}

	x1 = lsm_svg_view_normalize_length (view, &gradient->x1.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	y1 = lsm_svg_view_normalize_length (view, &gradient->y1.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	x2 = lsm_svg_view_normalize_length (view, &gradient->x2.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	y2 = lsm_svg_view_normalize_length (view, &gradient->y2.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);

	if (is_object_bounding_box)
		lsm_svg_view_pop_viewbox (view);

	lsm_debug_render ("[LsmSvgLinearGradientElement::render] Create linear %g, %g, %g, %g",
		    x1, y1, x2, y2);

	lsm_svg_view_create_linear_gradient (view, x1, y1, x2, y2);

	return referenced_gradient;
}

/* LsmSvgLinearGradientElement implementation */

LsmDomNode *
lsm_svg_linear_gradient_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_LINEAR_GRADIENT_ELEMENT, NULL);
}

static void
lsm_svg_linear_gradient_element_init (LsmSvgLinearGradientElement *self)
{
	self->x1.length = default_attributes.x1;
	self->y1.length = default_attributes.y1;
	self->x2.length = default_attributes.x2;
	self->y2.length = default_attributes.y2;
}

static void
lsm_svg_linear_gradient_element_finalize (GObject *object)
{
	parent_class->finalize (object);
}

/* LsmSvgLinearGradientElement class */

static const LsmAttributeInfos lsm_svg_linear_gradient_element_attribute_infos[] = {
	{
		.name = "x1",
		.attribute_offset = offsetof (LsmSvgLinearGradientElement, x1),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &default_attributes.x1
	},
	{
		.name = "y1",
		.attribute_offset = offsetof (LsmSvgLinearGradientElement, y1),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &default_attributes.y1
	},
	{
		.name = "x2",
		.attribute_offset = offsetof (LsmSvgLinearGradientElement, x2),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &default_attributes.x2
	},
	{
		.name = "y2",
		.attribute_offset = offsetof (LsmSvgLinearGradientElement, y2),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &default_attributes.y2
	}
};

static void
lsm_svg_linear_gradient_element_class_init (LsmSvgLinearGradientElementClass *s_svg_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (s_svg_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (s_svg_class);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (s_svg_class);
	LsmSvgGradientElementClass *s_gradient_class = LSM_SVG_GRADIENT_ELEMENT_CLASS (s_svg_class);

	parent_class = g_type_class_peek_parent (s_svg_class);

	object_class->finalize = lsm_svg_linear_gradient_element_finalize;

	d_node_class->get_node_name = lsm_svg_linear_gradient_element_get_node_name;

	s_element_class->category = LSM_SVG_ELEMENT_CATEGORY_GRADIENT;

	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_linear_gradient_element_attribute_infos),
					      lsm_svg_linear_gradient_element_attribute_infos);

	s_gradient_class->create_gradient = lsm_svg_linear_gradient_element_create_gradient;
}

G_DEFINE_TYPE (LsmSvgLinearGradientElement, lsm_svg_linear_gradient_element, LSM_TYPE_SVG_GRADIENT_ELEMENT)
