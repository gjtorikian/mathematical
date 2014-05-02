/* Lasem
 *
 * Copyright © 2010 Emmanuel Pacaud
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

#include <lsmsvgfilterprimitive.h>
#include <lsmsvgview.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static gboolean
lsm_svg_filter_primitive_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	return FALSE;
}

/* LsmSvgElement implementation */

/* LsmSvgFilterPrimitive implementation */

void
lsm_svg_filter_primitive_apply  (LsmSvgFilterPrimitive *self, LsmSvgView *view)
{
	LsmSvgFilterPrimitiveClass *primitive_class;
	const LsmSvgStyle *parent_style;
	LsmSvgStyle *style;
	LsmBox subregion;
	gboolean is_x_defined;
	gboolean is_y_defined;
	gboolean is_width_defined;
	gboolean is_height_defined;
	
	g_return_if_fail (LSM_IS_SVG_FILTER_PRIMITIVE (self));

	primitive_class = LSM_SVG_FILTER_PRIMITIVE_GET_CLASS (self);

	is_x_defined = lsm_attribute_is_defined (&self->x.base);
	is_y_defined = lsm_attribute_is_defined (&self->y.base);
	is_width_defined = lsm_attribute_is_defined (&self->width.base);
	is_height_defined = lsm_attribute_is_defined (&self->height.base);

	subregion = lsm_svg_view_get_filter_surface_extents (view, "SourceGraphic");

	if (is_x_defined)
		subregion.x = lsm_svg_view_normalize_length (view, &self->x.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	if (is_y_defined)
		subregion.y = lsm_svg_view_normalize_length (view, &self->y.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	if (is_width_defined)
		subregion.width = lsm_svg_view_normalize_length (view, &self->width.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	if (is_height_defined)
		subregion.height = lsm_svg_view_normalize_length (view, &self->height.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);

	lsm_log_render ("[Svg::FilterPrimitive::apply] Apply %s at %g,%g over a %gx%g region",
		       	lsm_dom_node_get_node_name (LSM_DOM_NODE (self)),
			subregion.x, subregion.y, subregion.width, subregion.height);

	parent_style = lsm_svg_view_get_current_style (view);
	style = lsm_svg_style_new_inherited (parent_style, &(LSM_SVG_ELEMENT (self))->property_bag);

	lsm_svg_view_push_style (view, style);

	if (primitive_class->apply != NULL)
		primitive_class->apply (self, view, self->in.value, self->result.value, &subregion);

	lsm_svg_view_pop_style (view);

	lsm_svg_style_unref (style);
}

static const LsmSvgLength x_y_default = 	 { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PERCENTAGE};
static const LsmSvgLength width_height_default = { .value_unit = 100.0, .type = LSM_SVG_LENGTH_TYPE_PERCENTAGE};

static void
lsm_svg_filter_primitive_init (LsmSvgFilterPrimitive *self)
{
	self->x.length = x_y_default;
	self->y.length = x_y_default;
	self->width.length = width_height_default;
	self->height.length = width_height_default;
}

static void
lsm_svg_filter_primitive_finalize (GObject *object)
{
	parent_class->finalize (object);
}

/* LsmSvgFilterPrimitive class */

static const LsmAttributeInfos lsm_svg_filter_primitive_attribute_infos[] = {
	{
		.name = "x",
		.attribute_offset = offsetof (LsmSvgFilterPrimitive, x),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &x_y_default
	},
	{
		.name = "y",
		.attribute_offset = offsetof (LsmSvgFilterPrimitive, y),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &x_y_default
	},
	{
		.name = "width",
		.attribute_offset = offsetof (LsmSvgFilterPrimitive, width),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &width_height_default
	},
	{
		.name = "height",
		.attribute_offset = offsetof (LsmSvgFilterPrimitive, height),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &width_height_default
	},
	{
		.name = "in",
		.attribute_offset = offsetof (LsmSvgFilterPrimitive, in),
		.trait_class = &lsm_null_trait_class
	},
	{
		.name = "result",
		.attribute_offset = offsetof (LsmSvgFilterPrimitive, result),
		.trait_class = &lsm_null_trait_class
	}
};

static void
lsm_svg_filter_primitive_class_init (LsmSvgFilterPrimitiveClass *s_rect_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (s_rect_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (s_rect_class);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (s_rect_class);

	parent_class = g_type_class_peek_parent (s_rect_class);

	object_class->finalize = lsm_svg_filter_primitive_finalize;

	d_node_class->can_append_child = lsm_svg_filter_primitive_can_append_child;

	s_element_class->category = LSM_SVG_ELEMENT_CATEGORY_FILTER_PRIMITIVE;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_filter_primitive_attribute_infos),
					      lsm_svg_filter_primitive_attribute_infos);
}

G_DEFINE_ABSTRACT_TYPE (LsmSvgFilterPrimitive, lsm_svg_filter_primitive, LSM_TYPE_SVG_ELEMENT)
