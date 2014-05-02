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

#include <lsmsvgellipseelement.h>
#include <lsmsvgview.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_ellipse_element_get_node_name (LsmDomNode *node)
{
	return "ellipse";
}

/* LsmSvgElement implementation */

/* LsmSvgGraphic implementation */

static void
_normalize_length (LsmSvgEllipseElement *ellipse, LsmSvgView *view, double *cx, double *cy, double *rx, double *ry)
{
	*cx = lsm_svg_view_normalize_length (view, &ellipse->cx.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	*cy = lsm_svg_view_normalize_length (view, &ellipse->cy.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	*rx = lsm_svg_view_normalize_length (view, &ellipse->rx.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	*ry = lsm_svg_view_normalize_length (view, &ellipse->ry.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
}

static void
lsm_svg_ellipse_element_render (LsmSvgElement *self, LsmSvgView *view)
{
	LsmSvgEllipseElement *ellipse = LSM_SVG_ELLIPSE_ELEMENT (self);
	double cx, cy, rx, ry;

	_normalize_length (ellipse, view, &cx, &cy, &rx, &ry);

	lsm_svg_view_show_ellipse (view, cx, cy, rx, ry);
}

static void
lsm_svg_ellipse_element_get_extents (LsmSvgElement *self, LsmSvgView *view, LsmExtents *extents)
{
	LsmSvgEllipseElement *ellipse = LSM_SVG_ELLIPSE_ELEMENT (self);
	double cx, cy, rx, ry;

	_normalize_length (ellipse, view, &cx, &cy, &rx, &ry);

	extents->x1 = cx - rx;
	extents->y1 = cy - ry;
	extents->x2 = cx + rx;
	extents->y2 = cy + ry;
}

/* LsmSvgEllipseElement implementation */

LsmDomNode *
lsm_svg_ellipse_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_ELLIPSE_ELEMENT, NULL);
}

static const LsmSvgLength length_default = 	 { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PX};

static void
lsm_svg_ellipse_element_init (LsmSvgEllipseElement *self)
{
	self->cx.length = length_default;
	self->cy.length = length_default;
	self->rx.length = length_default;
	self->ry.length = length_default;
}

static void
lsm_svg_ellipse_element_finalize (GObject *object)
{
	parent_class->finalize (object);
}

/* LsmSvgEllipseElement class */

static const LsmAttributeInfos lsm_svg_ellipse_element_attribute_infos[] = {
	{
		.name = "cx",
		.attribute_offset = offsetof (LsmSvgEllipseElement, cx),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "cy",
		.attribute_offset = offsetof (LsmSvgEllipseElement, cy),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "rx",
		.attribute_offset = offsetof (LsmSvgEllipseElement, rx),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "ry",
		.attribute_offset = offsetof (LsmSvgEllipseElement, ry),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	}
};

static void
lsm_svg_ellipse_element_class_init (LsmSvgEllipseElementClass *s_rect_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (s_rect_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (s_rect_class);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (s_rect_class);

	parent_class = g_type_class_peek_parent (s_rect_class);

	object_class->finalize = lsm_svg_ellipse_element_finalize;

	d_node_class->get_node_name = lsm_svg_ellipse_element_get_node_name;

	s_element_class->category =
		LSM_SVG_ELEMENT_CATEGORY_GRAPHICS |
		LSM_SVG_ELEMENT_CATEGORY_SHAPE |
		LSM_SVG_ELEMENT_CATEGORY_BASIC_SHAPE;

	s_element_class->render = lsm_svg_ellipse_element_render;
	s_element_class->get_extents = lsm_svg_ellipse_element_get_extents;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	s_element_class->is_shape_element = TRUE;

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_ellipse_element_attribute_infos),
					      lsm_svg_ellipse_element_attribute_infos);
}

G_DEFINE_TYPE (LsmSvgEllipseElement, lsm_svg_ellipse_element, LSM_TYPE_SVG_TRANSFORMABLE)
