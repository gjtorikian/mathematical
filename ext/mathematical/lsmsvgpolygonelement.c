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

#include <lsmsvgpolygonelement.h>
#include <lsmsvgview.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_polygon_element_get_node_name (LsmDomNode *node)
{
	return "polygon";
}

/* LsmSvgElement implementation */

/* LsmSvgGraphic implementation */

static void
lsm_svg_polygon_element_render (LsmSvgElement *self, LsmSvgView *view)
{
	LsmSvgPolygonElement *polygon = LSM_SVG_POLYGON_ELEMENT (self);

	lsm_svg_view_show_polygon (view, polygon->points.value);
}

static void
lsm_svg_polygon_element_get_extents (LsmSvgElement *self, LsmSvgView *view, LsmExtents *extents)
{
	LsmSvgPolygonElement *polygon = LSM_SVG_POLYGON_ELEMENT (self);

	lsm_str_point_list_exents (polygon->points.value, extents);
}

/* LsmSvgPolygonElement implementation */

LsmDomNode *
lsm_svg_polygon_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_POLYGON_ELEMENT, NULL);
}

static void
lsm_svg_polygon_element_init (LsmSvgPolygonElement *self)
{
}

/* LsmSvgPolygonElement class */

static const LsmAttributeInfos lsm_svg_polygon_element_attribute_infos[] = {
	{
		.name = "points",
		.attribute_offset = offsetof (LsmSvgPolygonElement, points),
		.trait_class = &lsm_null_trait_class
	}
};

static void
lsm_svg_polygon_element_class_init (LsmSvgPolygonElementClass *s_rect_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (s_rect_class);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (s_rect_class);

	parent_class = g_type_class_peek_parent (s_rect_class);

	d_node_class->get_node_name = lsm_svg_polygon_element_get_node_name;

	s_element_class->category =
		LSM_SVG_ELEMENT_CATEGORY_GRAPHICS |
		LSM_SVG_ELEMENT_CATEGORY_SHAPE |
		LSM_SVG_ELEMENT_CATEGORY_BASIC_SHAPE;

	s_element_class->render = lsm_svg_polygon_element_render;
	s_element_class->get_extents = lsm_svg_polygon_element_get_extents;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	s_element_class->is_shape_element = TRUE;

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_polygon_element_attribute_infos),
					      lsm_svg_polygon_element_attribute_infos);
}

G_DEFINE_TYPE (LsmSvgPolygonElement, lsm_svg_polygon_element, LSM_TYPE_SVG_TRANSFORMABLE)
