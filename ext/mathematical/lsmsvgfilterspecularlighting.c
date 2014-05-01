/* Lasem
 * 
 * Copyright © 2012 Emmanuel Pacaud
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

#include <lsmsvgfilterspecularlighting.h>
#include <lsmsvgview.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_filter_specular_lighting_get_node_name (LsmDomNode *node)
{
	return "feSpecularLighting";
}

/* LsmSvgElement implementation */

static void
lsm_svg_filter_specular_lighting_apply  (LsmSvgFilterPrimitive *self, LsmSvgView *view,
				     const char *input, const char *output, const LsmBox *subregion)
{
/*        lsm_svg_view_apply_specular_lighting (view, output, subregion);*/
}

/* LsmSvgFilterSpecularLighting implementation */

static const double surface_scale_default = 1.0;
static const double specular_constant_default = 1.0;
static const double specular_exponent_default = 1.0;
static const LsmSvgOneOrTwoDouble kernel_unit_length_default = {1.0, 1.0};

LsmDomNode *
lsm_svg_filter_specular_lighting_new (void)
{
	return g_object_new (LSM_TYPE_SVG_FILTER_SPECULAR_LIGHTING, NULL);
}

static void
lsm_svg_filter_specular_lighting_init (LsmSvgFilterSpecularLighting *self)
{
	self->surface_scale.value = surface_scale_default;
	self->specular_constant.value = specular_constant_default;
	self->specular_exponent.value = specular_exponent_default;
	self->kernel_unit_length.value = kernel_unit_length_default;

}

static void
lsm_svg_filter_specular_lighting_finalize (GObject *object)
{
	parent_class->finalize (object);
}

/* LsmSvgFilterSpecularLighting class */

static const LsmAttributeInfos lsm_svg_filter_specular_lighting_attribute_infos[] = {
	{
		.name = "sufaceScale",
		.attribute_offset = offsetof (LsmSvgFilterSpecularLighting, surface_scale),
		.trait_class = &lsm_double_trait_class,
		.trait_default = &surface_scale_default
	},
	{
		.name = "specularConstant",
		.attribute_offset = offsetof (LsmSvgFilterSpecularLighting, specular_constant),
		.trait_class = &lsm_double_trait_class,
		.trait_default = &specular_constant_default
	},
	{
		.name = "specularExponent",
		.attribute_offset = offsetof (LsmSvgFilterSpecularLighting, specular_exponent),
		.trait_class = &lsm_double_trait_class,
		.trait_default = &specular_exponent_default
	},
	{
		.name = "kernelUnitLength",
		.attribute_offset = offsetof (LsmSvgFilterSpecularLighting, kernel_unit_length),
		.trait_class = &lsm_svg_one_or_two_double_trait_class,
		.trait_default = &kernel_unit_length_default
	}
};

static void
lsm_svg_filter_specular_lighting_class_init (LsmSvgFilterSpecularLightingClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (klass);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (klass);
	LsmSvgFilterPrimitiveClass *f_primitive_class = LSM_SVG_FILTER_PRIMITIVE_CLASS (klass);

	parent_class = g_type_class_peek_parent (klass);

	object_class->finalize = lsm_svg_filter_specular_lighting_finalize;

	d_node_class->get_node_name = lsm_svg_filter_specular_lighting_get_node_name;

	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_filter_specular_lighting_attribute_infos),
					      lsm_svg_filter_specular_lighting_attribute_infos);

	f_primitive_class->apply = lsm_svg_filter_specular_lighting_apply;
}

G_DEFINE_TYPE (LsmSvgFilterSpecularLighting, lsm_svg_filter_specular_lighting, LSM_TYPE_SVG_FILTER_PRIMITIVE)
