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

#include <lsmsvglineelement.h>
#include <lsmsvgview.h>
#include <lsmdebug.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_line_element_get_node_name (LsmDomNode *node)
{
	return "line";
}

/* LsmSvgElement implementation */

/* LsmSvgGraphic implementation */

static void
_normalize_length (LsmSvgLineElement *line, LsmSvgView *view, double *x1, double *y1, double *x2, double *y2)
{
	*x1 = lsm_svg_view_normalize_length (view, &line->x1.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	*y1 = lsm_svg_view_normalize_length (view, &line->y1.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	*x2 = lsm_svg_view_normalize_length (view, &line->x2.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	*y2 = lsm_svg_view_normalize_length (view, &line->y2.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);

}

static void
lsm_svg_line_element_render (LsmSvgElement *self, LsmSvgView *view)
{
	LsmSvgLineElement *line = LSM_SVG_LINE_ELEMENT (self);
	double x1, y1, x2, y2;

	_normalize_length (line, view, &x1, &y1, &x2, &y2);

	lsm_debug_render ("[LsmSvgLineElement::render] %g, %g, %g, %g", x1, y1, x2, y2);

	lsm_svg_view_show_line (view, x1, y1, x2, y2);
}

static void
lsm_svg_line_element_get_extents (LsmSvgElement *self, LsmSvgView *view, LsmExtents *extents)
{
	LsmSvgLineElement *line = LSM_SVG_LINE_ELEMENT (self);
	double x1, y1, x2, y2;

	_normalize_length (line, view, &x1, &y1, &x2, &y2);

	extents->x1 = MIN (x1, x2);
	extents->y1 = MIN (y1, y2);
	extents->x2 = MAX (x1, x2);
	extents->y2 = MAX (y1, y2);
}

/* LsmSvgLineElement implementation */

LsmDomNode *
lsm_svg_line_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_LINE_ELEMENT, NULL);
}

static const LsmSvgLength length_default = 	 { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PX};

static void
lsm_svg_line_element_init (LsmSvgLineElement *self)
{
	self->x1.length = length_default;
	self->x2.length = length_default;
	self->y1.length = length_default;
	self->y2.length = length_default;
}

/* LsmSvgLineElement class */

static const LsmAttributeInfos lsm_svg_line_element_attribute_infos[] = {
	{
		.name = "x1",
		.attribute_offset = offsetof (LsmSvgLineElement, x1),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "y1",
		.attribute_offset = offsetof (LsmSvgLineElement, y1),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "x2",
		.attribute_offset = offsetof (LsmSvgLineElement, x2),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "y2",
		.attribute_offset = offsetof (LsmSvgLineElement, y2),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	}
};

static void
lsm_svg_line_element_class_init (LsmSvgLineElementClass *s_rect_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (s_rect_class);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (s_rect_class);

	parent_class = g_type_class_peek_parent (s_rect_class);

	d_node_class->get_node_name = lsm_svg_line_element_get_node_name;

	s_element_class->category =
		LSM_SVG_ELEMENT_CATEGORY_GRAPHICS |
		LSM_SVG_ELEMENT_CATEGORY_SHAPE |
		LSM_SVG_ELEMENT_CATEGORY_BASIC_SHAPE;

	s_element_class->render = lsm_svg_line_element_render;
	s_element_class->get_extents = lsm_svg_line_element_get_extents;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	s_element_class->is_shape_element = TRUE;

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_line_element_attribute_infos),
					      lsm_svg_line_element_attribute_infos);
}

G_DEFINE_TYPE (LsmSvgLineElement, lsm_svg_line_element, LSM_TYPE_SVG_TRANSFORMABLE)
