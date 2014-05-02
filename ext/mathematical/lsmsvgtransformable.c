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

#include <lsmdebug.h>
#include <lsmsvgtransformable.h>
#include <lsmsvgview.h>

static GObjectClass *parent_class;

/* LsmDomNode implementation */

/* LsmDomElement implementation */

/* LsmSvgTransformable implementation */

static void
lsm_svg_transformable_transformed_render (LsmSvgElement *element, LsmSvgView *view)
{
	LsmSvgTransformable *transformable = LSM_SVG_TRANSFORMABLE (element);
	gboolean is_identity_transform;
	gboolean is_matrix_invertible = TRUE;

	is_identity_transform = lsm_svg_matrix_is_identity (&transformable->transform.matrix);

	if (!is_identity_transform)
		is_matrix_invertible = lsm_svg_view_push_matrix (view, &transformable->transform.matrix);
	else
		is_matrix_invertible = TRUE;

	if (is_matrix_invertible)
		LSM_SVG_ELEMENT_CLASS (parent_class)->transformed_render (element, view);

	if (!is_identity_transform)
		lsm_svg_view_pop_matrix (view);
}

static void
lsm_svg_transformable_transformed_get_extents (LsmSvgElement *element, LsmSvgView *view, LsmExtents *extents)
{
	LsmSvgTransformable *transformable = LSM_SVG_TRANSFORMABLE (element);
	LsmSvgElementClass *element_class = LSM_SVG_ELEMENT_GET_CLASS (element);

	element_class->get_extents (element, view, extents);

	if (!lsm_svg_matrix_is_identity (&transformable->transform.matrix))
		lsm_svg_matrix_transform_bounding_box (&transformable->transform.matrix,
						       &extents->x1, &extents->y1,
						       &extents->x2, &extents->y2);
}

static void
lsm_svg_transformable_init (LsmSvgTransformable *transformable)
{
	lsm_svg_matrix_init_identity (&transformable->transform.matrix);
}

/* LsmSvgTransformable class */

static const LsmSvgMatrix matrix_default =	 { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, LSM_SVG_MATRIX_FLAGS_IDENTITY};

static const LsmAttributeInfos lsm_svg_transformable_attribute_infos[] = {
	{
		.name = "transform",
		.attribute_offset = offsetof (LsmSvgTransformable, transform),
		.trait_class = &lsm_svg_matrix_trait_class,
		.trait_default = &matrix_default
	}
};

static void
lsm_svg_transformable_class_init (LsmSvgTransformableClass *klass)
{
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (klass);

	parent_class = g_type_class_peek_parent (klass);

	s_element_class->transformed_render = lsm_svg_transformable_transformed_render;
	s_element_class->transformed_get_extents = lsm_svg_transformable_transformed_get_extents;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_transformable_attribute_infos),
					      lsm_svg_transformable_attribute_infos);
}

G_DEFINE_ABSTRACT_TYPE (LsmSvgTransformable, lsm_svg_transformable, LSM_TYPE_SVG_ELEMENT)
