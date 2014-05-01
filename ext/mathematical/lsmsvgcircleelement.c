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

#include <lsmsvgcircleelement.h>
#include <lsmsvgview.h>
#include <lsmdebug.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_circle_element_get_node_name (LsmDomNode *node)
{
	return "circle";
}

/* LsmSvgElement implementation */

/* LsmSvgGraphic implementation */

static void
_normalize_length (LsmSvgCircleElement *circle, LsmSvgView *view, double *cx, double *cy, double *r)
{
	*cx = lsm_svg_view_normalize_length (view, &circle->cx.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	*cy = lsm_svg_view_normalize_length (view, &circle->cy.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	*r  = lsm_svg_view_normalize_length (view, &circle->r.length,  LSM_SVG_LENGTH_DIRECTION_DIAGONAL);
}

static void
lsm_svg_circle_element_render (LsmSvgElement *self, LsmSvgView *view)
{
	LsmSvgCircleElement *circle = LSM_SVG_CIRCLE_ELEMENT (self);
	double cx, cy, r;

	_normalize_length (circle, view, &cx,&cy,&r);

	lsm_debug_render ("[LsmSvgCircleElement::render] cx = %g, cy = %g, r = %g", cx, cy, r);

	lsm_svg_view_show_circle (view, cx, cy, r);
}

static void
lsm_svg_circle_element_get_extents (LsmSvgElement *self, LsmSvgView *view, LsmExtents *extents)
{
	LsmSvgCircleElement *circle = LSM_SVG_CIRCLE_ELEMENT (self);
	double cx, cy, r;

	_normalize_length (circle, view, &cx,&cy,&r);

	extents->x1 = cx - r;
	extents->y1 = cy - r;
	extents->x2 = cx + r;
	extents->y2 = cy + r;
}

/* LsmSvgCircleElement implementation */

LsmDomNode *
lsm_svg_circle_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_CIRCLE_ELEMENT, NULL);
}

static const LsmSvgLength length_default = 	 { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PX};

static void
lsm_svg_circle_element_init (LsmSvgCircleElement *self)
{
	self->cx.length = length_default;
	self->cy.length = length_default;
	self->r.length = length_default;
}

static void
lsm_svg_circle_element_finalize (GObject *object)
{
	parent_class->finalize (object);
}

/* LsmSvgCircleElement class */

static const LsmAttributeInfos lsm_svg_circle_element_attribute_infos[] = {
	{
		.name = "cx",
		.attribute_offset = offsetof (LsmSvgCircleElement, cx),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "cy",
		.attribute_offset = offsetof (LsmSvgCircleElement, cy),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "r",
		.attribute_offset = offsetof (LsmSvgCircleElement, r),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	}
};

static void
lsm_svg_circle_element_class_init (LsmSvgCircleElementClass *s_rect_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (s_rect_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (s_rect_class);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (s_rect_class);

	parent_class = g_type_class_peek_parent (s_rect_class);

	object_class->finalize = lsm_svg_circle_element_finalize;

	d_node_class->get_node_name = lsm_svg_circle_element_get_node_name;

	s_element_class->category =
		LSM_SVG_ELEMENT_CATEGORY_GRAPHICS |
		LSM_SVG_ELEMENT_CATEGORY_SHAPE |
		LSM_SVG_ELEMENT_CATEGORY_BASIC_SHAPE;

	s_element_class->render = lsm_svg_circle_element_render;
	s_element_class->get_extents = lsm_svg_circle_element_get_extents;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	s_element_class->is_shape_element = TRUE;

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_circle_element_attribute_infos),
					      lsm_svg_circle_element_attribute_infos);
}

G_DEFINE_TYPE (LsmSvgCircleElement, lsm_svg_circle_element, LSM_TYPE_SVG_TRANSFORMABLE)
