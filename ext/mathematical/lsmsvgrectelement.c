/* Lasem
 *
 * Copyright © 2009-2012 Emmanuel Pacaud
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

#include <lsmsvgrectelement.h>
#include <lsmsvgview.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_rect_element_get_node_name (LsmDomNode *node)
{
	return "rect";
}

/* LsmSvgElement implementation */

/* LsmSvgGraphic implementation */

static void
lsm_svg_rect_element_render (LsmSvgElement *self, LsmSvgView *view)
{
	LsmSvgRectElement *rect = LSM_SVG_RECT_ELEMENT (self);
	double x, y;
	double rx, ry;
	double w, h;

	x = lsm_svg_view_normalize_length (view, &rect->x.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	y = lsm_svg_view_normalize_length (view, &rect->y.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	rx = lsm_svg_view_normalize_length (view, &rect->rx.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	ry = lsm_svg_view_normalize_length (view, &rect->ry.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	w = lsm_svg_view_normalize_length (view, &rect->width.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	h = lsm_svg_view_normalize_length (view, &rect->height.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);

	/* SVG specification is so weird sometimes ... */
	if (w == 0.0 || h == 0.0)
		return;

	if (!lsm_attribute_is_defined (&rect->rx.base))
		rx = ry;
	else if (!lsm_attribute_is_defined (&rect->ry.base))
		ry = rx;

	lsm_svg_view_show_rectangle (view, x, y, w, h, rx, ry);
}

static void
lsm_svg_rect_element_get_extents (LsmSvgElement *self, LsmSvgView *view, LsmExtents *extents)
{
	LsmSvgRectElement *rect = LSM_SVG_RECT_ELEMENT (self);
	double x, y;
	double w, h;

	x = lsm_svg_view_normalize_length (view, &rect->x.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	y = lsm_svg_view_normalize_length (view, &rect->y.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	w = lsm_svg_view_normalize_length (view, &rect->width.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	h = lsm_svg_view_normalize_length (view, &rect->height.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);

	extents->x1 = x;
	extents->y1 = y;
	extents->x2 = x + w;
	extents->y2 = y + h;
}

/* LsmSvgRectElement implementation */

LsmDomNode *
lsm_svg_rect_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_RECT_ELEMENT, NULL);
}

static const LsmSvgLength length_default = 	 { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PX};
static const LsmSvgLength unset_length_default = { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_ERROR};

static void
lsm_svg_rect_element_init (LsmSvgRectElement *self)
{
	self->x.length = length_default;
	self->y.length = length_default;
	self->width.length = length_default;
	self->height.length = length_default;
	self->rx.length = unset_length_default;
	self->ry.length = unset_length_default;
}

static void
lsm_svg_rect_element_finalize (GObject *object)
{
	parent_class->finalize (object);
}

/* LsmSvgRectElement class */

static const LsmAttributeInfos lsm_svg_rect_element_attribute_infos[] = {
	{
		.name = "x",
		.attribute_offset = offsetof (LsmSvgRectElement, x),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "y",
		.attribute_offset = offsetof (LsmSvgRectElement, y),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "width",
		.attribute_offset = offsetof (LsmSvgRectElement, width),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "height",
		.attribute_offset = offsetof (LsmSvgRectElement, height),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "rx",
		.attribute_offset = offsetof (LsmSvgRectElement, rx),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &unset_length_default
	},
	{
		.name = "ry",
		.attribute_offset = offsetof (LsmSvgRectElement, ry),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &unset_length_default
	}
};

static void
lsm_svg_rect_element_class_init (LsmSvgRectElementClass *s_rect_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (s_rect_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (s_rect_class);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (s_rect_class);

	parent_class = g_type_class_peek_parent (s_rect_class);

	object_class->finalize = lsm_svg_rect_element_finalize;

	d_node_class->get_node_name = lsm_svg_rect_element_get_node_name;

	s_element_class->category =
		LSM_SVG_ELEMENT_CATEGORY_GRAPHICS |
		LSM_SVG_ELEMENT_CATEGORY_SHAPE |
		LSM_SVG_ELEMENT_CATEGORY_BASIC_SHAPE;

	s_element_class->render = lsm_svg_rect_element_render;
	s_element_class->get_extents = lsm_svg_rect_element_get_extents;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	s_element_class->is_shape_element = TRUE;

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_rect_element_attribute_infos),
					      lsm_svg_rect_element_attribute_infos);
}

G_DEFINE_TYPE (LsmSvgRectElement, lsm_svg_rect_element, LSM_TYPE_SVG_TRANSFORMABLE)
