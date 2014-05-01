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

#include <lsmsvgpatternelement.h>
#include <lsmsvgview.h>
#include <lsmdebug.h>
#include <lsmdomdocument.h>
#include <stdio.h>

typedef struct {
	LsmSvgLength x;
	LsmSvgLength y;
	LsmSvgLength width;
	LsmSvgLength height;
	LsmSvgMatrix transform;
	LsmSvgPatternUnits units;
	LsmSvgPatternUnits content_units;
	LsmBox viewbox;
	LsmSvgPreserveAspectRatio preserve_aspect_ratio;
} LsmSvgPatternElementAttributes;

static LsmSvgPatternElementAttributes default_attributes = {
	.x = { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PX},
	.y = { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PX},
	.width = { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PX},
	.height = { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PX},
	.transform = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0, LSM_SVG_MATRIX_FLAGS_IDENTITY},
	.units = LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX,
	.content_units = LSM_SVG_PATTERN_UNITS_USER_SPACE_ON_USE,
	.viewbox = {0.0, 0.0, 0.0, 0.0},
	.preserve_aspect_ratio = {
		.defer = FALSE,
		.align = LSM_SVG_ALIGN_X_MID_Y_MID,
		.meet_or_slice = LSM_SVG_MEET_OR_SLICE_MEET
	}
};

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
_pattern_element_get_node_name (LsmDomNode *node)
{
	return "pattern";
}

/* LsmSvgElement implementation */

static LsmSvgPatternElement *
lsm_svg_pattern_element_inherit_referenced (LsmDomDocument *owner,
					    LsmSvgPatternElement *pattern,
					    LsmSvgPatternElementAttributes *attributes,
					    GSList **elements)
{
	LsmSvgPatternElement *referenced_pattern = pattern;
	LsmDomElement *element;

	*elements = g_slist_prepend (*elements, pattern);

	if (lsm_attribute_is_defined (&pattern->href)) {
		char *id;
		GSList *iter;
		gboolean circular_reference_found = FALSE;

		id = pattern->href.value;
		if (id == NULL)
			return NULL;
		if (*id == '#')
			id++;

		element = lsm_dom_document_get_element_by_id (owner, id);

		for (iter = *elements; iter != NULL; iter = iter->next)
			if (iter->data == element) {
				lsm_debug_render ("[LsmSvgPatternElement::inherit_attributes] "
					   "Circular reference (id = %s)", id);
				circular_reference_found = TRUE;
			}

		if (!circular_reference_found) {
			if (LSM_IS_SVG_PATTERN_ELEMENT (element), elements) {
				lsm_debug_render ("[LsmSvgPatternElement::inherit_attributes] "
						  "Found referenced element '%s'", id);

				referenced_pattern = lsm_svg_pattern_element_inherit_referenced
					(owner,
					 LSM_SVG_PATTERN_ELEMENT (element),
					 attributes, elements);
			} else {
				lsm_debug_render ("[LsmSvgPatternElement::inherit_attributes] "
						  "Referenced element '%s' not found", id);
				referenced_pattern = NULL;
			}
		} else
			referenced_pattern = NULL;
	}

	if (lsm_attribute_is_defined (&pattern->x.base))
		attributes->x = pattern->x.length;
	if (lsm_attribute_is_defined (&pattern->y.base))
		attributes->y = pattern->y.length;
	if (lsm_attribute_is_defined (&pattern->width.base))
		attributes->width = pattern->width.length;
	if (lsm_attribute_is_defined (&pattern->height.base))
		attributes->height = pattern->height.length;
	if (lsm_attribute_is_defined (&pattern->transform.base))
		attributes->transform = pattern->transform.matrix;
	if (lsm_attribute_is_defined (&pattern->units.base))
		attributes->units = pattern->units.value;
	if (lsm_attribute_is_defined (&pattern->content_units.base))
		attributes->content_units = pattern->content_units.value;
	if (lsm_attribute_is_defined (&pattern->viewbox.base))
		attributes->viewbox = pattern->viewbox.value;
	if (lsm_attribute_is_defined (&pattern->preserve_aspect_ratio.base))
		attributes->preserve_aspect_ratio = pattern->preserve_aspect_ratio.value;

	return referenced_pattern;
}

static void
lsm_svg_pattern_element_render (LsmSvgElement *self, LsmSvgView *view)
{
	LsmSvgPatternElement *pattern = LSM_SVG_PATTERN_ELEMENT (self);
	LsmSvgPatternElement *referenced_pattern;
	gboolean is_object_bounding_box;
	gboolean is_viewbox_defined;
	LsmBox viewport;
	LsmBox image_box;
	const LsmBox *pattern_extents;
	LsmSvgStyle *style;
	gboolean is_matrix_invertible = TRUE;

	if (!pattern->enable_rendering) {
		lsm_debug_render ("[LsmSvgPatternElement::render] Direct rendering not allowed");
		return;
	} else {
		pattern->enable_rendering = FALSE;
	}

	if (lsm_attribute_is_defined (&pattern->href)) {
		LsmSvgPatternElementAttributes attributes;
		LsmDomDocument *owner;
		attributes = default_attributes;
		GSList *elements = NULL;

		owner = lsm_dom_node_get_owner_document (LSM_DOM_NODE (self));

		referenced_pattern = lsm_svg_pattern_element_inherit_referenced (owner, pattern,
										 &attributes, &elements);

		g_slist_free (elements);

		pattern->x.length = attributes.x;
		pattern->y.length = attributes.y;
		pattern->width.length = attributes.width;
		pattern->height.length = attributes.height;
		pattern->transform.matrix = attributes.transform;
		pattern->units.value = attributes.units;
		pattern->content_units.value = attributes.content_units;
		pattern->viewbox.value = attributes.viewbox;
		pattern->preserve_aspect_ratio.value = attributes.preserve_aspect_ratio;
	} else
		referenced_pattern = pattern;

	if (referenced_pattern == NULL)
		return;

	style = lsm_svg_style_new_inherited (NULL, &self->property_bag);
	style->ignore_group_opacity = FALSE;
	lsm_svg_view_push_composition (view, style);

	pattern_extents = lsm_svg_view_get_pattern_extents (view);

	is_object_bounding_box = (pattern->units.value == LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX);

	if (is_object_bounding_box) {
		LsmBox viewbox = {.x = 0.0, .y = .0, .width = 1.0, .height = 1.0};

		lsm_svg_view_push_viewbox (view, &viewbox);
	}

	viewport.x      = lsm_svg_view_normalize_length (view, &pattern->x.length,
							 LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	viewport.y      = lsm_svg_view_normalize_length (view, &pattern->y.length,
							 LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	viewport.width  = lsm_svg_view_normalize_length (view, &pattern->width.length,
							 LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	viewport.height = lsm_svg_view_normalize_length (view, &pattern->height.length,
							 LSM_SVG_LENGTH_DIRECTION_VERTICAL);

	image_box = viewport;

	if (is_object_bounding_box) {
		lsm_svg_view_pop_viewbox (view);

		image_box.x *= pattern_extents->width;
		image_box.y *= pattern_extents->height;
		image_box.width *= pattern_extents->width;
		image_box.height *= pattern_extents->height;
	}

	if (viewport.width <= 0.0 || viewport.height <= 0.0) {
		lsm_debug_render ("[LsmSvgPatternElement::render] Invalid viewport w = %g, h = %g",
			   viewport.width, viewport.height);
		lsm_svg_view_pop_composition (view);
		lsm_svg_style_unref (style);
		return;
	}

	lsm_debug_render ("[LsmSvgPatternElement::render] Create pattern x = %g, y = %g, w = %g, h = %g",
		   viewport.x, viewport.y, viewport.width, viewport.height);

	if (!lsm_svg_view_create_surface_pattern (view, &image_box,
						  &pattern->transform.matrix,
						  LSM_SVG_VIEW_SURFACE_TYPE_AUTO)) {
		lsm_debug_render ("[LsmSvgPatternElement::render] Intermediate surface creation failed");
		lsm_svg_view_pop_composition (view);
		lsm_svg_style_unref (style);
		return;
	}

	is_object_bounding_box = (pattern->content_units.value == LSM_SVG_PATTERN_UNITS_OBJECT_BOUNDING_BOX);

	if (is_object_bounding_box) {
		LsmSvgMatrix matrix;
		LsmBox viewbox = {.x = 0.0, .y = .0, .width = 1.0, .height = 1.0};

		lsm_svg_matrix_init_scale (&matrix, pattern_extents->width, pattern_extents->height);
		lsm_svg_matrix_translate (&matrix, -pattern_extents->x, -pattern_extents->y);
		lsm_svg_view_push_viewbox (view, &viewbox);
		is_matrix_invertible = lsm_svg_view_push_matrix (view, &matrix);

		lsm_debug_render ("[LsmSvgPatternElement::render] object_bounding_box"
			   " x_scale = %g, y_scale = %g, x_offset = %g, y_offset = %g",
			   pattern_extents->width, pattern_extents->height,
			   pattern_extents->x,     pattern_extents->y);
	}

	if (is_matrix_invertible) {

		is_viewbox_defined = lsm_attribute_is_defined (&pattern->viewbox.base);

		if (!(is_viewbox_defined) ||
		    (is_viewbox_defined && pattern->viewbox.value.width > 0.0 && pattern->viewbox.value.height > 0.0)) {

			lsm_svg_view_push_viewport (view, &viewport, is_viewbox_defined ? &pattern->viewbox.value : NULL,
						    &pattern->preserve_aspect_ratio.value, LSM_SVG_OVERFLOW_HIDDEN);

			LSM_SVG_ELEMENT_CLASS (parent_class)->render (LSM_SVG_ELEMENT (referenced_pattern), view);

			lsm_svg_view_pop_viewport (view);
		}
	}

	if (is_object_bounding_box) {
		lsm_svg_view_pop_matrix (view);
		lsm_svg_view_pop_viewbox (view);
	}

	lsm_svg_view_pop_composition (view);
	lsm_svg_style_unref (style);
}

static void
lsm_svg_pattern_element_enable_rendering (LsmSvgElement *element)
{
	LSM_SVG_PATTERN_ELEMENT (element)->enable_rendering  = TRUE;
}

/* LsmSvgPatternElement implementation */

LsmDomNode *
lsm_svg_pattern_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_PATTERN_ELEMENT, NULL);
}

static void
lsm_svg_pattern_element_init (LsmSvgPatternElement *self)
{
	self->enable_rendering = FALSE;
	self->x.length = default_attributes.x;
	self->y.length = default_attributes.y;
	self->width.length = default_attributes.width;
	self->height.length = default_attributes.height;
	self->transform.matrix = default_attributes.transform;
	self->units.value = default_attributes.units;
	self->content_units.value = default_attributes.content_units;
	self->preserve_aspect_ratio.value = default_attributes.preserve_aspect_ratio;
}

/* LsmSvgPatternElement class */

static const LsmAttributeInfos lsm_svg_pattern_element_attribute_infos[] = {
	{
		.name = "x",
		.attribute_offset = offsetof (LsmSvgPatternElement, x),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &default_attributes.x
	},
	{
		.name = "y",
		.attribute_offset = offsetof (LsmSvgPatternElement, y),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &default_attributes.y
	},
	{
		.name = "width",
		.attribute_offset = offsetof (LsmSvgPatternElement, width),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &default_attributes.width
	},
	{
		.name = "height",
		.attribute_offset = offsetof (LsmSvgPatternElement, height),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &default_attributes.height
	},
	{
		.name = "patternUnits",
		.attribute_offset = offsetof (LsmSvgPatternElement, units),
		.trait_class = &lsm_svg_pattern_units_trait_class,
		.trait_default = &default_attributes.units
	},
	{
		.name = "patternContentUnits",
		.attribute_offset = offsetof (LsmSvgPatternElement, content_units),
		.trait_class = &lsm_svg_pattern_units_trait_class,
		.trait_default = &default_attributes.content_units
	},
	{
		.name = "patternTransform",
		.attribute_offset = offsetof (LsmSvgPatternElement, transform),
		.trait_class = &lsm_svg_matrix_trait_class,
		.trait_default = &default_attributes.transform
	},
	{
		.name = "xlink:href",
		.attribute_offset = offsetof (LsmSvgPatternElement, href),
		.trait_class = &lsm_null_trait_class
	},
	{
		.name = "viewBox",
		.attribute_offset = offsetof (LsmSvgPatternElement, viewbox),
		.trait_class = &lsm_box_trait_class,
		.trait_default = &default_attributes.viewbox
	},
	{
		.name = "preserveAspectRatio",
		.attribute_offset = offsetof (LsmSvgPatternElement, preserve_aspect_ratio),
		.trait_class = &lsm_svg_preserve_aspect_ratio_trait_class,
		.trait_default = &default_attributes.preserve_aspect_ratio
	}
};

static void
lsm_svg_pattern_element_class_init (LsmSvgPatternElementClass *klass)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (klass);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (klass);

	parent_class = g_type_class_peek_parent (klass);

	d_node_class->get_node_name = _pattern_element_get_node_name;

	s_element_class->category = LSM_SVG_ELEMENT_CATEGORY_CONTAINER;

	s_element_class->render = lsm_svg_pattern_element_render;
	s_element_class->enable_rendering = lsm_svg_pattern_element_enable_rendering;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_pattern_element_attribute_infos),
					      lsm_svg_pattern_element_attribute_infos);
}

G_DEFINE_TYPE (LsmSvgPatternElement, lsm_svg_pattern_element, LSM_TYPE_SVG_ELEMENT)
