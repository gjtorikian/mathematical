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

#include <lsmsvgfiltergaussianblur.h>
#include <lsmsvgview.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_filter_gaussian_blur_get_node_name (LsmDomNode *node)
{
	return "feGaussianBlur";
}

/* LsmSvgElement implementation */

static void
lsm_svg_filter_gaussian_blur_apply  (LsmSvgFilterPrimitive *self, LsmSvgView *view,
				     const char *input, const char *output, const LsmBox *subregion)
{
	LsmSvgFilterGaussianBlur *blur = LSM_SVG_FILTER_GAUSSIAN_BLUR (self);
	LsmSvgLength length;
	double std_a, std_b;

	length.type = LSM_SVG_LENGTH_TYPE_ERROR;

	length.value_unit = blur->std_deviation.value.a;
	std_a = lsm_svg_view_normalize_length (view, &length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);

	length.value_unit = blur->std_deviation.value.b;
	std_b = lsm_svg_view_normalize_length (view, &length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);

	lsm_svg_view_apply_gaussian_blur (view, input, output, subregion, std_a, std_b);
}

/* LsmSvgFilterGaussianBlur implementation */

static const LsmSvgOneOrTwoDouble std_deviation_default =  {.a = 0.0, .b = 0.0};

LsmDomNode *
lsm_svg_filter_gaussian_blur_new (void)
{
	return g_object_new (LSM_TYPE_SVG_FILTER_GAUSSIAN_BLUR, NULL);
}

static void
lsm_svg_filter_gaussian_blur_init (LsmSvgFilterGaussianBlur *self)
{
	self->std_deviation.value = std_deviation_default;
}

static void
lsm_svg_filter_gaussian_blur_finalize (GObject *object)
{
	parent_class->finalize (object);
}

/* LsmSvgFilterGaussianBlur class */

static const LsmAttributeInfos lsm_svg_filter_gaussian_blur_attribute_infos[] = {
	{
		.name = "stdDeviation",
		.attribute_offset = offsetof (LsmSvgFilterGaussianBlur, std_deviation),
		.trait_class = &lsm_svg_one_or_two_double_trait_class,
		.trait_default = &std_deviation_default
	}
};

static void
lsm_svg_filter_gaussian_blur_class_init (LsmSvgFilterGaussianBlurClass *f_blur_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (f_blur_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (f_blur_class);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (f_blur_class);
	LsmSvgFilterPrimitiveClass *f_primitive_class = LSM_SVG_FILTER_PRIMITIVE_CLASS (f_blur_class);

	parent_class = g_type_class_peek_parent (f_blur_class);

	object_class->finalize = lsm_svg_filter_gaussian_blur_finalize;

	d_node_class->get_node_name = lsm_svg_filter_gaussian_blur_get_node_name;

	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_filter_gaussian_blur_attribute_infos),
					      lsm_svg_filter_gaussian_blur_attribute_infos);

	f_primitive_class->apply = lsm_svg_filter_gaussian_blur_apply;
}

G_DEFINE_TYPE (LsmSvgFilterGaussianBlur, lsm_svg_filter_gaussian_blur, LSM_TYPE_SVG_FILTER_PRIMITIVE)
