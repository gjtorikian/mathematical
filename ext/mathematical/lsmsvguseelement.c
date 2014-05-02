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

#include <lsmsvguseelement.h>
#include <lsmsvgview.h>
#include <lsmdebug.h>
#include <lsmdomdocument.h>
#include <stdio.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_use_element_get_node_name (LsmDomNode *node)
{
	return "use";
}

static gboolean
lsm_svg_use_can_append_child (LsmDomNode *node, LsmDomNode *child)
{
	return FALSE;
}

/* LsmSvgElement implementation */

/* LsmSvgGraphic implementation */

static LsmDomElement *
_get_used_element (LsmSvgUseElement *use_element)
{
	LsmDomDocument *document;
	LsmDomElement *element;
	const char *id;

	document = lsm_dom_node_get_owner_document (LSM_DOM_NODE (use_element));
	if (document == NULL) {
		lsm_debug_dom ("[LsmSvgUseElement::_get_used_element] Owner document not found");
		return NULL;
	}

	id = use_element->href.value;
	if (id == NULL)
		return NULL;

	if (*id == '#')
		id++;

	element = lsm_dom_document_get_element_by_id (document, id);
	if (!LSM_IS_SVG_ELEMENT (element)) {
		lsm_debug_dom ("[LsmSvgUseElement::_get_used_element] Target '%s' not found", id);
		return NULL;
	}

	return element;
}

static void
lsm_svg_use_element_render (LsmSvgElement *self, LsmSvgView *view)
{
	LsmSvgUseElement *use_element = LSM_SVG_USE_ELEMENT (self);
	LsmDomElement *element;
	LsmSvgMatrix matrix;
	double x, y;

	if (use_element->flags & LSM_SVG_USE_ELEMENT_FLAGS_IN_USE_FOR_RENDER) {
		lsm_debug_render ("[LsmSvgUseElement::render] Circular reference");
		return;
	}

	element = _get_used_element (use_element);
	if (element == NULL)
		return;

	use_element->flags |= LSM_SVG_USE_ELEMENT_FLAGS_IN_USE_FOR_RENDER;

	x = lsm_svg_view_normalize_length (view, &use_element->x.length,
					   LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	y = lsm_svg_view_normalize_length (view, &use_element->y.length,
					   LSM_SVG_LENGTH_DIRECTION_VERTICAL);

	lsm_svg_matrix_init_translate (&matrix, x, y);

	if (lsm_svg_view_push_matrix (view, &matrix))
		lsm_svg_element_render (LSM_SVG_ELEMENT (element), view);

	lsm_svg_view_pop_matrix (view);

	use_element->flags &= ~LSM_SVG_USE_ELEMENT_FLAGS_IN_USE_FOR_RENDER;
}

static void
lsm_svg_use_element_get_extents (LsmSvgElement *self, LsmSvgView *view, LsmExtents *extents)
{
	LsmSvgUseElement *use_element = LSM_SVG_USE_ELEMENT (self);
	LsmDomElement *element;
	LsmSvgMatrix matrix;
	double x, y;

	if (use_element->flags & LSM_SVG_USE_ELEMENT_FLAGS_IN_USE_FOR_GET_EXTENTS) {
		lsm_debug_render ("[LsmSvgUseElement::get_extents] Circular reference");
		extents->x1 = 0;
		extents->y1 = 0;
		extents->x2 = 0;
		extents->y2 = 0;
		return;
	}

	element = _get_used_element (use_element);
	if (element == NULL) {
		extents->x1 = 0;
		extents->y1 = 0;
		extents->x2 = 0;
		extents->y2 = 0;
		return;
	}

	use_element->flags |= LSM_SVG_USE_ELEMENT_FLAGS_IN_USE_FOR_GET_EXTENTS;

	x = lsm_svg_view_normalize_length (view, &use_element->x.length,
					   LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	y = lsm_svg_view_normalize_length (view, &use_element->y.length,
					   LSM_SVG_LENGTH_DIRECTION_VERTICAL);

	lsm_svg_element_transformed_get_extents (LSM_SVG_ELEMENT (element), view, extents);

	lsm_svg_matrix_init_translate (&matrix, x, y);

	if (lsm_svg_view_push_matrix (view, &matrix))
		lsm_svg_matrix_transform_bounding_box (&matrix,
						       &extents->x1, &extents->y1,
						       &extents->x2, &extents->y2);
	lsm_svg_view_pop_matrix (view);

	use_element->flags &= ~LSM_SVG_USE_ELEMENT_FLAGS_IN_USE_FOR_GET_EXTENTS;
}

/* LsmSvgUseElement implementation */

LsmDomNode *
lsm_svg_use_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_USE_ELEMENT, NULL);
}

static const LsmSvgLength length_default = 	 { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PX};

static void
lsm_svg_use_element_init (LsmSvgUseElement *self)
{
	self->x.length = length_default;
	self->y.length = length_default;
	self->width.length = length_default;
	self->height.length = length_default;
}

/* LsmSvgUseElement class */

static const LsmAttributeInfos lsm_svg_use_element_attribute_infos[] = {
	{
		.name = "x",
		.attribute_offset = offsetof (LsmSvgUseElement, x),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "y",
		.attribute_offset = offsetof (LsmSvgUseElement, y),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "width",
		.attribute_offset = offsetof (LsmSvgUseElement, width),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "height",
		.attribute_offset = offsetof (LsmSvgUseElement, height),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "xlink:href",
		.attribute_offset = offsetof (LsmSvgUseElement, href),
		.trait_class = &lsm_null_trait_class
	}
};

static void
lsm_svg_use_element_class_init (LsmSvgUseElementClass *klass)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (klass);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (klass);

	parent_class = g_type_class_peek_parent (klass);

	d_node_class->get_node_name = lsm_svg_use_element_get_node_name;
	d_node_class->can_append_child = lsm_svg_use_can_append_child;

	s_element_class->category =
		LSM_SVG_ELEMENT_CATEGORY_GRAPHICS |
		LSM_SVG_ELEMENT_CATEGORY_GRAPHICS_REFERENCING |
		LSM_SVG_ELEMENT_CATEGORY_STRUCTURAL;

	s_element_class->render = lsm_svg_use_element_render;
	s_element_class->get_extents = lsm_svg_use_element_get_extents;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_use_element_attribute_infos),
					      lsm_svg_use_element_attribute_infos);
}

G_DEFINE_TYPE (LsmSvgUseElement, lsm_svg_use_element, LSM_TYPE_SVG_TRANSFORMABLE)
