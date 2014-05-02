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

#include <lsmsvgmarkerelement.h>
#include <lsmsvgview.h>
#include <lsmdebug.h>
#include <lsmdomdocument.h>
#include <stdio.h>
#include <math.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_marker_element_get_node_name (LsmDomNode *node)
{
	return "marker";
}

/* LsmSvgElement implementation */

/* LsmSvgGraphic implementation */

static void
_marker_element_render (LsmSvgElement *self, LsmSvgView *view)
{
	LsmSvgMarkerElement *marker = LSM_SVG_MARKER_ELEMENT (self);
	LsmSvgStyle *style;
	LsmSvgMatrix matrix;
	LsmBox viewport;
	LsmBox viewbox;
	double ref_x, ref_y;

	if (!marker->enable_rendering) {
		/* Remember style for futur rendering.
		 * Spec says properties are inherited from ancestor, not element referencing
		 * the marker element. */
		if (marker->style)
			lsm_svg_style_unref (marker->style);
		marker->style = lsm_svg_style_ref (lsm_svg_view_get_current_style (view));

		lsm_debug_render ("[LsmSvgMarkerElement::render] Direct rendering not allowed");
		return;
	} else {
		marker->enable_rendering = FALSE;
	}

	style = lsm_svg_style_new_inherited (marker->style, &self->property_bag);
	style->ignore_group_opacity = FALSE;
	lsm_svg_view_push_composition (view, style);

	if (marker->stroke_width > 0.0 || marker->units.value != LSM_SVG_MARKER_UNITS_STROKE_WIDTH) {
		ref_x = lsm_svg_view_normalize_length (view, &marker->ref_x.length,
						       LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
		ref_y = lsm_svg_view_normalize_length (view, &marker->ref_y.length,
						       LSM_SVG_LENGTH_DIRECTION_VERTICAL);

		viewport.x = 0.0;
		viewport.y = 0.0;

		viewport.width = lsm_svg_view_normalize_length (view, &marker->width.length,
								LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
		viewport.height = lsm_svg_view_normalize_length (view, &marker->height.length,
								 LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);

		if (lsm_attribute_is_defined (&marker->viewbox.base))
			viewbox = marker->viewbox.value;
		else
			viewbox = viewport;

		if (marker->units.value == LSM_SVG_MARKER_UNITS_STROKE_WIDTH) {
			viewport.width *= marker->stroke_width;
			viewport.height *= marker->stroke_width;

			lsm_debug_render ("[LsmSvgMarkerElement::render] stroke_width scale = %g",
					  marker->stroke_width);
		}

		lsm_svg_view_viewbox_to_viewport (view, &viewport, &viewbox,
						  &marker->preserve_aspect_ratio.value, &ref_x, &ref_y);

		if (marker->orientation.value.type == LSM_SVG_ANGLE_TYPE_FIXED) {
			lsm_svg_matrix_init_rotate (&matrix, marker->orientation.value.angle * M_PI / 180.0);
			lsm_debug_render ("[LsmSvgMarkerElement::render] fixed angle = %g°", marker->orientation.value.angle);
		} else {
			lsm_svg_matrix_init_rotate (&matrix, marker->vertex_angle);
			lsm_debug_render ("[LsmSvgMarkerElement::render] auto angle = %g rad", marker->vertex_angle);
		}
		lsm_svg_matrix_translate (&matrix, -ref_x, -ref_y);

		if (lsm_svg_view_push_matrix (view, &matrix)) {

			lsm_svg_view_push_viewport (view, &viewport, &viewbox,
						    &marker->preserve_aspect_ratio.value, style->overflow->value);

			LSM_SVG_ELEMENT_CLASS (parent_class)->render (self, view);

			lsm_svg_view_pop_viewport (view);
		}

		lsm_svg_view_pop_matrix (view);
	}

	lsm_svg_view_pop_composition (view);
	lsm_svg_style_unref (style);
}

/* LsmSvgMarkerElement implementation */

void
lsm_svg_marker_element_render (LsmSvgMarkerElement *marker, LsmSvgView *view,
			       double stroke_width, double vertex_angle)
{
	g_return_if_fail (LSM_IS_SVG_MARKER_ELEMENT (marker));

	marker->stroke_width = stroke_width;
	marker->vertex_angle = vertex_angle;

	lsm_svg_element_force_render (LSM_SVG_ELEMENT (marker), view);
}

static void
lsm_svg_marker_element_enable_rendering (LsmSvgElement *element)
{
	LSM_SVG_MARKER_ELEMENT (element)->enable_rendering  = TRUE;
}

LsmDomNode *
lsm_svg_marker_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_MARKER_ELEMENT, NULL);
}

static const LsmSvgMarkerUnits units_default =   LSM_SVG_MARKER_UNITS_STROKE_WIDTH;
static const LsmSvgLength length_default = 	 { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_NUMBER};
static const LsmSvgLength width_default = 	 { .value_unit =   3.0, .type = LSM_SVG_LENGTH_TYPE_NUMBER};
static const LsmSvgAngle orientation_default =	 { .angle =        0.0, .type = LSM_SVG_ANGLE_TYPE_FIXED};
static const LsmBox viewbox_default =		{0.0, 0.0, 0.0, 0.0};
static const LsmSvgPreserveAspectRatio preserve_aspect_ratio_default = {
	.defer = FALSE,
	.align = LSM_SVG_ALIGN_X_MID_Y_MID,
	.meet_or_slice = LSM_SVG_MEET_OR_SLICE_MEET
};

static void
lsm_svg_marker_element_init (LsmSvgMarkerElement *self)
{
	self->enable_rendering = FALSE;
	self->ref_x.length = length_default;
	self->ref_y.length = length_default;
	self->width.length = width_default;
	self->height.length = width_default;
	self->preserve_aspect_ratio.value = preserve_aspect_ratio_default;
	self->orientation.value = orientation_default;
}

static void
lsm_svg_marker_element_finalize (GObject *object)
{
	LsmSvgMarkerElement *marker = LSM_SVG_MARKER_ELEMENT (object);

	if (marker->style)
		lsm_svg_style_unref (marker->style);

	parent_class->finalize (object);
}

/* LsmSvgMarkerElement class */

static const LsmAttributeInfos lsm_svg_marker_element_attribute_infos[] = {
	{
		.name = "markerUnits",
		.attribute_offset = offsetof (LsmSvgMarkerElement, units),
		.trait_class = &lsm_svg_marker_units_trait_class,
		.trait_default = &units_default
	},
	{
		.name = "refX",
		.attribute_offset = offsetof (LsmSvgMarkerElement, ref_x),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "refY",
		.attribute_offset = offsetof (LsmSvgMarkerElement, ref_y),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "markerWidth",
		.attribute_offset = offsetof (LsmSvgMarkerElement, width),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &width_default
	},
	{
		.name = "markerHeight",
		.attribute_offset = offsetof (LsmSvgMarkerElement, height),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &width_default
	},
	{
		.name = "orient",
		.attribute_offset = offsetof (LsmSvgMarkerElement, orientation),
		.trait_class = &lsm_svg_angle_trait_class,
		.trait_default = &orientation_default
	},
	{
		.name = "viewBox",
		.attribute_offset = offsetof (LsmSvgMarkerElement, viewbox),
		.trait_class = &lsm_box_trait_class,
		.trait_default = &viewbox_default
	},
	{
		.name = "preserveAspectRatio",
		.attribute_offset = offsetof (LsmSvgMarkerElement, preserve_aspect_ratio),
		.trait_class = &lsm_svg_preserve_aspect_ratio_trait_class,
		.trait_default = &preserve_aspect_ratio_default
	}
};

static void
lsm_svg_marker_element_class_init (LsmSvgMarkerElementClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (klass);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (klass);

	parent_class = g_type_class_peek_parent (klass);

	object_class->finalize = lsm_svg_marker_element_finalize;

	d_node_class->get_node_name = lsm_svg_marker_element_get_node_name;

	s_element_class->category = LSM_SVG_ELEMENT_CATEGORY_CONTAINER;

	s_element_class->render = _marker_element_render;
	s_element_class->enable_rendering = lsm_svg_marker_element_enable_rendering;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_marker_element_attribute_infos),
					      lsm_svg_marker_element_attribute_infos);
}

G_DEFINE_TYPE (LsmSvgMarkerElement, lsm_svg_marker_element, LSM_TYPE_SVG_ELEMENT)
