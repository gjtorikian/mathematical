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

#include <lsmsvgradialgradientelement.h>
#include <lsmsvgview.h>
#include <lsmsvgdocument.h>
#include <lsmdebug.h>
#include <stdio.h>
#include <math.h>

typedef struct {
	LsmSvgGradientElementAttributes base;
	LsmSvgLength cx;
	LsmSvgLength cy;
	LsmSvgLength r;
	LsmSvgLength fx;
	LsmSvgLength fy;
	gboolean is_fx_defined;
	gboolean is_fy_defined;
} LsmSvgRadialGradientElementAttributes;

static const LsmSvgRadialGradientElementAttributes default_attributes = {
	.base = {
		.transform = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0, LSM_SVG_MATRIX_FLAGS_IDENTITY},
		.units = LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX,
		.spread_method = LSM_SVG_SPREAD_METHOD_PAD,
	},
	.cx = {.value_unit = 50.0, .type = LSM_SVG_LENGTH_TYPE_PERCENTAGE},
	.cy = {.value_unit = 50.0, .type = LSM_SVG_LENGTH_TYPE_PERCENTAGE},
	.r  = {.value_unit = 50.0, .type = LSM_SVG_LENGTH_TYPE_PERCENTAGE},
	.fx = {.value_unit =  0.0, .type = LSM_SVG_LENGTH_TYPE_ERROR},
	.fy = {.value_unit =  0.0, .type = LSM_SVG_LENGTH_TYPE_ERROR},
	.is_fx_defined = FALSE,
	.is_fy_defined = FALSE
};

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_radial_gradient_element_get_node_name (LsmDomNode *node)
{
	return "radialGradient";
}

/* LsmSvgGradientElement implementation */

static LsmSvgGradientElement *
lsm_svg_radial_gradient_element_inherit_referenced (LsmSvgDocument *owner,
						    LsmSvgGradientElement *gradient,
						    LsmSvgRadialGradientElementAttributes *attributes,
						    GSList **elements)
{
	LsmSvgGradientElement *referenced_gradient = gradient;
	LsmSvgElement *element;

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

		element = lsm_svg_document_get_element_by_id (owner, id);

		for (iter = *elements; iter != NULL; iter = iter->next)
			if (iter->data == element) {
				lsm_debug_render ("[LsmSvgRadialGradientElement::inherit_attributes] "
					   "Circular reference (id = %s)", id);
				circular_reference_found = TRUE;
			}

		if (!circular_reference_found) {
			if (LSM_IS_SVG_GRADIENT_ELEMENT (element)) {
				lsm_debug_render ("[LsmSvgRadialGradientElement::inherit_attributes]"
						  " Found referenced element '%s'", id);

				referenced_gradient = lsm_svg_radial_gradient_element_inherit_referenced
					(owner,
					 LSM_SVG_GRADIENT_ELEMENT (element),
					 attributes, elements);
			} else {
				lsm_debug_render ("[LsmSvgRadialGradientElement::inherit_attributes]"
						  " Referenced element '%s' not found", id);
				referenced_gradient = NULL;
			}
		} else
			referenced_gradient = NULL;

	}

	if (LSM_IS_SVG_RADIAL_GRADIENT_ELEMENT (gradient)) {
		LsmSvgRadialGradientElement *radial = LSM_SVG_RADIAL_GRADIENT_ELEMENT (gradient);

		if (lsm_attribute_is_defined (&radial->cx.base))
			attributes->cx = radial->cx.length;
		if (lsm_attribute_is_defined (&radial->cy.base))
			attributes->cy = radial->cy.length;
		if (lsm_attribute_is_defined (&radial->r.base))
			attributes->r = radial->r.length;
		if (lsm_attribute_is_defined (&radial->fx.base)) {
			attributes->fx = radial->fx.length;
			attributes->is_fx_defined = TRUE;
		}
		if (lsm_attribute_is_defined (&radial->fy.base)) {
			attributes->fy = radial->fy.length;
			attributes->is_fy_defined = TRUE;
		}
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
lsm_svg_radial_gradient_element_create_gradient (LsmSvgElement *self,
						 LsmSvgView *view)
{
	LsmSvgRadialGradientElement *gradient = LSM_SVG_RADIAL_GRADIENT_ELEMENT (self);
	LsmSvgGradientElement *referenced_gradient;
	gboolean is_object_bounding_box;
	double cx, cy, fx, fy, r;
	double gradient_radius;
	gboolean is_fx_defined;
	gboolean is_fy_defined;

	if (lsm_attribute_is_defined (&gradient->base.href)) {
		LsmSvgRadialGradientElementAttributes attributes;
		LsmSvgDocument *owner;
		attributes = default_attributes;
		GSList *elements = NULL;

		owner = LSM_SVG_DOCUMENT (lsm_dom_node_get_owner_document (LSM_DOM_NODE (self)));

		referenced_gradient = lsm_svg_radial_gradient_element_inherit_referenced
			(owner, LSM_SVG_GRADIENT_ELEMENT (gradient), &attributes, &elements);

		g_slist_free (elements);

		gradient->cx.length = attributes.cx;
		gradient->cy.length = attributes.cy;
		gradient->r.length = attributes.r;
		gradient->fx.length = attributes.fx;
		gradient->fy.length = attributes.fy;

		is_fx_defined = attributes.is_fx_defined;
		is_fy_defined = attributes.is_fy_defined;

		gradient->base.transform.matrix = attributes.base.transform;
		gradient->base.units.value = attributes.base.units;
		gradient->base.spread_method.value = attributes.base.spread_method;
	} else {
		referenced_gradient = LSM_SVG_GRADIENT_ELEMENT (gradient);

		is_fx_defined = lsm_attribute_is_defined (&gradient->fx.base);
		is_fy_defined = lsm_attribute_is_defined (&gradient->fy.base);
	}

	if (referenced_gradient == NULL)
		return NULL;

	is_object_bounding_box = (gradient->base.units.value == LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX);

	if (is_object_bounding_box) {
		LsmBox viewbox = {.x = 0.0, .y = .0, .width = 1.0, .height = 1.0};

		lsm_svg_view_push_viewbox (view, &viewbox);
	}

	cx = lsm_svg_view_normalize_length (view, &gradient->cx.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	cy = lsm_svg_view_normalize_length (view, &gradient->cy.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	r  = lsm_svg_view_normalize_length (view, &gradient->r.length,  LSM_SVG_LENGTH_DIRECTION_DIAGONAL);

	if (is_fx_defined)
		fx = lsm_svg_view_normalize_length (view, &gradient->fx.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	else
		fx = cx;

	if (is_fy_defined)
		fy = lsm_svg_view_normalize_length (view, &gradient->fy.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	else
		fy = cy;

	gradient_radius = sqrt ((fx - cx) * (fx - cx) + (fy - cy) * (fy - cy));
	if (gradient_radius > r) {
		if (gradient_radius > 0.0) {
			fx = cx + ((fx - cx) * r / gradient_radius);
			fy = cy + ((fy - cy) * r / gradient_radius);
		} else {
			fx = cx;
			fy = cy;
		}
	}

	if (is_object_bounding_box)
		lsm_svg_view_pop_viewbox (view);

	lsm_debug_render ("[LsmSvgRadialElement::render] cx = %g, cy = %g, r = %g, fx = %g, fy = %g",
		    cx, cy, r, fx, fy);

	lsm_svg_view_create_radial_gradient (view, cx, cy, r, fx, fy);

	return referenced_gradient;
}

/* LsmSvgRadialGradientElement implementation */

LsmDomNode *
lsm_svg_radial_gradient_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_RADIAL_GRADIENT_ELEMENT, NULL);
}

static void
lsm_svg_radial_gradient_element_init (LsmSvgRadialGradientElement *self)
{
	self->cx.length = default_attributes.cx;
	self->cy.length = default_attributes.cy;
	self->r.length = default_attributes.r;
	self->fx.length = default_attributes.fx;
	self->fy.length = default_attributes.fy;
}

static void
lsm_svg_radial_gradient_element_finalize (GObject *object)
{
	parent_class->finalize (object);
}

/* LsmSvgRadialGradientElement class */

static const LsmAttributeInfos lsm_svg_radial_gradient_element_attribute_infos[] = {
	{
		.name = "cx",
		.attribute_offset = offsetof (LsmSvgRadialGradientElement, cx),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &default_attributes.cx
	},
	{
		.name = "cy",
		.attribute_offset = offsetof (LsmSvgRadialGradientElement, cy),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &default_attributes.cy
	},
	{
		.name = "r",
		.attribute_offset = offsetof (LsmSvgRadialGradientElement, r),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &default_attributes.r
	},
	{
		.name = "fx",
		.attribute_offset = offsetof (LsmSvgRadialGradientElement, fx),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &default_attributes.fx
	},
	{
		.name = "fy",
		.attribute_offset = offsetof (LsmSvgRadialGradientElement, fy),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &default_attributes.fy
	}
};

static void
lsm_svg_radial_gradient_element_class_init (LsmSvgRadialGradientElementClass *s_svg_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (s_svg_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (s_svg_class);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (s_svg_class);
	LsmSvgGradientElementClass *s_gradient_class = LSM_SVG_GRADIENT_ELEMENT_CLASS (s_svg_class);

	parent_class = g_type_class_peek_parent (s_svg_class);

	object_class->finalize = lsm_svg_radial_gradient_element_finalize;

	d_node_class->get_node_name = lsm_svg_radial_gradient_element_get_node_name;

	s_element_class->category = LSM_SVG_ELEMENT_CATEGORY_GRADIENT;

	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_radial_gradient_element_attribute_infos),
					      lsm_svg_radial_gradient_element_attribute_infos);

	s_gradient_class->create_gradient = lsm_svg_radial_gradient_element_create_gradient;
}

G_DEFINE_TYPE (LsmSvgRadialGradientElement, lsm_svg_radial_gradient_element, LSM_TYPE_SVG_GRADIENT_ELEMENT)
