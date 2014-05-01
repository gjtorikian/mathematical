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

#include <lsmsvgmaskelement.h>
#include <lsmsvgview.h>
#include <lsmdebug.h>
#include <stdio.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
_mask_element_get_node_name (LsmDomNode *node)
{
	return "mask";
}

/* LsmSvgElement implementation */

static void
lsm_svg_mask_element_render (LsmSvgElement *self, LsmSvgView *view)
{
	LsmSvgMaskElement *mask = LSM_SVG_MASK_ELEMENT (self);
	gboolean is_object_bounding_box;
	LsmBox viewport;
	const LsmBox *mask_extents;
	LsmSvgStyle *style;
	gboolean is_matrix_invertible = TRUE;

	if (!mask->enable_rendering) {
		lsm_debug_render ("[LsmSvgMaskElement::render] Direct rendering not allowed");
		return;
	} else {
		mask->enable_rendering = FALSE;
	}

	style = lsm_svg_style_new_inherited (NULL, &self->property_bag);
	style->ignore_group_opacity = FALSE;
	lsm_svg_view_push_composition (view, style);

	mask_extents = lsm_svg_view_get_pattern_extents (view);

	is_object_bounding_box = (mask->units.value == LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX);

	if (is_object_bounding_box) {
		LsmBox viewbox = {.x = 0.0, .y = .0, .width = 1.0, .height = 1.0};

		lsm_svg_view_push_viewbox (view, &viewbox);
	}

	viewport.x      = lsm_svg_view_normalize_length (view, &mask->x.length,
							 LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	viewport.y      = lsm_svg_view_normalize_length (view, &mask->y.length,
							 LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	viewport.width  = lsm_svg_view_normalize_length (view, &mask->width.length,
							 LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	viewport.height = lsm_svg_view_normalize_length (view, &mask->height.length,
							 LSM_SVG_LENGTH_DIRECTION_VERTICAL);

	if (is_object_bounding_box) {
		lsm_svg_view_pop_viewbox (view);

		viewport.x = viewport.x * mask_extents->width + mask_extents->x;
		viewport.y = viewport.y * mask_extents->height + mask_extents->y;
		viewport.width *= mask_extents->width;
		viewport.height *= mask_extents->height;
	}

	if (viewport.width <= 0.0 || viewport.height <= 0.0) {
		lsm_debug_render ("[LsmSvgMaskElement::render] Invalid viewport w = %g, h = %g",
			   viewport.width, viewport.height);
		lsm_svg_view_pop_composition (view);
		lsm_svg_style_unref (style);
		return;
	}

	if (!lsm_svg_view_create_surface_pattern (view, &viewport,
						  NULL,
						  LSM_SVG_VIEW_SURFACE_TYPE_IMAGE)) {
		lsm_debug_render ("[LsmSvgMaskElement::render] Intermediate surface creation failed");
		lsm_svg_view_pop_composition (view);
		lsm_svg_style_unref (style);
		return;
	}

	lsm_debug_render ("[LsmSvgMaskElement::render] Create mask x = %g, y = %g, w = %g, h = %g",
		   viewport.x, viewport.y, viewport.width, viewport.height);

	is_object_bounding_box = (mask->content_units.value == LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX);

	if (is_object_bounding_box) {
		LsmSvgMatrix matrix;
		LsmBox viewbox = {.x = 0.0, .y = .0, .width = 1.0, .height = 1.0};

		lsm_svg_matrix_init_translate (&matrix, +mask_extents->x, +mask_extents->y);
		lsm_svg_matrix_scale (&matrix, mask_extents->width, mask_extents->height);
		lsm_svg_view_push_viewbox (view, &viewbox);
		is_matrix_invertible = lsm_svg_view_push_matrix (view, &matrix);

		lsm_debug_render ("[LsmSvgMaskElement::render] object_bounding_box"
			   " x_scale = %g, y_scale = %g, x_offset = %g, y_offset = %g",
			   mask_extents->width, mask_extents->height,
			   mask_extents->x, mask_extents->y);
	}

	if (is_matrix_invertible)
		LSM_SVG_ELEMENT_CLASS (parent_class)->render (self, view);

	if (is_object_bounding_box) {
		lsm_svg_view_pop_matrix (view);
		lsm_svg_view_pop_viewbox (view);
	}

	lsm_svg_view_pop_composition (view);
	lsm_svg_style_unref (style);
}

static void
lsm_svg_mask_element_enable_rendering (LsmSvgElement *element)
{
	LSM_SVG_MASK_ELEMENT (element)->enable_rendering  = TRUE;
}

/* LsmSvgMaskElement implementation */

LsmDomNode *
lsm_svg_mask_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_MASK_ELEMENT, NULL);
}

static const LsmSvgLength x_y_default = 	{ .value_unit = -10.0, .type = LSM_SVG_LENGTH_TYPE_PERCENTAGE};
static const LsmSvgLength width_height_default ={ .value_unit = 120.0, .type = LSM_SVG_LENGTH_TYPE_PERCENTAGE};
static const LsmSvgPatternUnits units_default =  	LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX;
static const LsmSvgPatternUnits content_units_default = LSM_SVG_PATTERN_UNITS_USER_SPACE_ON_USE;

static void
lsm_svg_mask_element_init (LsmSvgMaskElement *self)
{
	self->enable_rendering = FALSE;
	self->x.length = x_y_default;
	self->y.length = x_y_default;
	self->width.length = width_height_default;
	self->height.length = width_height_default;
	self->units.value = units_default;
	self->content_units.value = content_units_default;
}

/* LsmSvgMaskElement class */

static const LsmAttributeInfos lsm_svg_mask_element_attribute_infos[] = {
	{
		.name = "x",
		.attribute_offset = offsetof (LsmSvgMaskElement, x),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &x_y_default
	},
	{
		.name = "y",
		.attribute_offset = offsetof (LsmSvgMaskElement, y),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &x_y_default
	},
	{
		.name = "width",
		.attribute_offset = offsetof (LsmSvgMaskElement, width),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &width_height_default
	},
	{
		.name = "height",
		.attribute_offset = offsetof (LsmSvgMaskElement, height),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &width_height_default
	},
	{
		.name = "maskUnits",
		.attribute_offset = offsetof (LsmSvgMaskElement, units),
		.trait_class = &lsm_svg_pattern_units_trait_class,
		.trait_default = &units_default
	},
	{
		.name = "maskContentUnits",
		.attribute_offset = offsetof (LsmSvgMaskElement, content_units),
		.trait_class = &lsm_svg_pattern_units_trait_class,
		.trait_default = &content_units_default
	}
};

static void
lsm_svg_mask_element_class_init (LsmSvgMaskElementClass *klass)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (klass);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (klass);

	parent_class = g_type_class_peek_parent (klass);

	d_node_class->get_node_name = _mask_element_get_node_name;

	s_element_class->category = LSM_SVG_ELEMENT_CATEGORY_CONTAINER;

	s_element_class->render = lsm_svg_mask_element_render;
	s_element_class->enable_rendering = lsm_svg_mask_element_enable_rendering;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_mask_element_attribute_infos),
					      lsm_svg_mask_element_attribute_infos);
}

G_DEFINE_TYPE (LsmSvgMaskElement, lsm_svg_mask_element, LSM_TYPE_SVG_ELEMENT)
