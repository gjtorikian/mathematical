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

#include <lsmsvgsvgelement.h>
#include <lsmsvgstyle.h>
#include <lsmsvgview.h>
#include <lsmdebug.h>
#include <lsmsvgdocument.h>
#include <math.h>
#include <stdio.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_svg_element_get_node_name (LsmDomNode *node)
{
	return "svg";
}

/* LsmSvgElement implementation */

void
lsm_svg_svg_element_measure (LsmSvgSvgElement *self, LsmSvgView *view, double *width, double *height)
{
	LsmSvgViewbox *svg_viewbox;
	LsmBox viewport;
	gboolean is_outermost_svg;
	double resolution_ppi;
	double svg_x;
	double svg_y;
	double svg_width;
	double svg_height;
	double font_size;

	g_return_if_fail (LSM_IS_SVG_SVG_ELEMENT (self));

	resolution_ppi = lsm_dom_view_get_resolution (LSM_DOM_VIEW (view));
	viewport = lsm_dom_view_get_viewport_pixels (LSM_DOM_VIEW (view));

	svg_viewbox = lsm_svg_viewbox_new (resolution_ppi, &viewport);
	font_size = 10 * resolution_ppi / 72.0;

	is_outermost_svg = LSM_IS_SVG_DOCUMENT (lsm_dom_node_get_parent_node (LSM_DOM_NODE (self)));

	if (lsm_attribute_is_defined (&self->x.base) && !is_outermost_svg)
		svg_x = lsm_svg_length_normalize (&self->x.length, svg_viewbox,
						  font_size, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	else
		svg_x = viewport.x;

	if (lsm_attribute_is_defined (&self->y.base) && !is_outermost_svg)
		svg_y = lsm_svg_length_normalize (&self->y.length, svg_viewbox,
						  font_size, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	else
		svg_y = viewport.y;

	if (lsm_attribute_is_defined (&self->width.base))
		svg_width = lsm_svg_length_normalize (&self->width.length, svg_viewbox,
						       font_size, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	else
		svg_width = viewport.width;

	if (lsm_attribute_is_defined (&self->height.base))
		svg_height = lsm_svg_length_normalize (&self->height.length, svg_viewbox,
						       font_size, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	else
		svg_height = viewport.height;

	if (width != NULL)
		*width = svg_width * 72.0 / resolution_ppi;
	if (height != NULL)
		*height = svg_height * 72.0 / resolution_ppi;

	self->svg_box.x = svg_x;
	self->svg_box.y = svg_y;
	self->svg_box.width = svg_width;
	self->svg_box.height = svg_height;

	lsm_debug_measure ("[LsmSvgSvgElement::measure] Size = %g, %g, %g, %g",
		   svg_x, svg_y, svg_width, svg_height);

	lsm_svg_viewbox_free (svg_viewbox);
}

/* LsmSvgGraphic implementation */

static void
_svg_element_render (LsmSvgElement *self, LsmSvgView *view)
{
	LsmSvgSvgElement *svg = LSM_SVG_SVG_ELEMENT (self);
	gboolean is_viewbox_defined;
	gboolean is_outermost_svg;
	LsmBox viewport;

	is_outermost_svg = LSM_IS_SVG_DOCUMENT (lsm_dom_node_get_parent_node (LSM_DOM_NODE (self)));

	if (is_outermost_svg) {
		/* outermost svg - ignore x and y */
		viewport.x = 0;
		viewport.y = 0;
	} else {
		viewport.x = lsm_svg_view_normalize_length (view, &svg->x.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
		viewport.y = lsm_svg_view_normalize_length (view, &svg->y.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	}
	viewport.width  = lsm_svg_view_normalize_length (view, &svg->width.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	viewport.height = lsm_svg_view_normalize_length (view, &svg->height.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);

	is_viewbox_defined = lsm_attribute_is_defined ((LsmAttribute *) &svg->viewbox);

	if (is_viewbox_defined && (svg->viewbox.value.width == 0.0 ||
				   svg->viewbox.value.height == 0.0))
		return;

	if (viewport.width <= 0.0 || viewport.height <= 0.0)
		return;

	lsm_debug_render ("[LsmSvgSvgElement::render] viewport %g, %g, %g, %g",
		   viewport.x, viewport.y, viewport.width, viewport.height);

	lsm_svg_view_show_viewport (view, &viewport);

	lsm_svg_view_push_viewport (view, &viewport, is_viewbox_defined ? &svg->viewbox.value : NULL,
				    &svg->preserve_aspect_ratio.value, LSM_SVG_OVERFLOW_HIDDEN);

	LSM_SVG_ELEMENT_CLASS (parent_class)->render (self, view);

	lsm_svg_view_pop_viewport (view);
}

/* LsmSvgSvgElement implementation */

void
lsm_svg_svg_element_render (LsmSvgSvgElement *svg, LsmSvgView *view)
{
	lsm_svg_view_push_viewport (view, &svg->svg_box, NULL, NULL, LSM_SVG_OVERFLOW_HIDDEN);
	lsm_svg_element_render (LSM_SVG_ELEMENT (svg), view);
	lsm_svg_view_pop_viewport (view);
}

LsmDomNode *
lsm_svg_svg_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_SVG_ELEMENT, NULL);
}

static const LsmSvgLength x_y_default = 	 { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PERCENTAGE};
static const LsmSvgLength width_height_default = { .value_unit = 100.0, .type = LSM_SVG_LENGTH_TYPE_PERCENTAGE};
static const LsmBox viewbox_default =		 {0.0, 0.0, 0.0, 0.0};
static const LsmSvgPreserveAspectRatio preserve_aspect_ratio_default = {
	.defer = FALSE,
	.align = LSM_SVG_ALIGN_X_MID_Y_MID,
	.meet_or_slice = LSM_SVG_MEET_OR_SLICE_MEET
};

static void
lsm_svg_svg_element_init (LsmSvgSvgElement *self)
{
	self->x.length = x_y_default;
	self->y.length = x_y_default;
	self->width.length = width_height_default;
	self->height.length = width_height_default;
	self->viewbox.value = viewbox_default;
	self->preserve_aspect_ratio.value = preserve_aspect_ratio_default;
}

static void
lsm_svg_svg_element_finalize (GObject *object)
{
	parent_class->finalize (object);
}

/* LsmSvgSvgElement class */

static const LsmAttributeInfos lsm_svg_svg_element_attribute_infos[] = {
	{
		.name = "x",
		.attribute_offset = offsetof (LsmSvgSvgElement, x),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &x_y_default
	},
	{
		.name = "y",
		.attribute_offset = offsetof (LsmSvgSvgElement, y),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &x_y_default
	},
	{
		.name = "width",
		.attribute_offset = offsetof (LsmSvgSvgElement, width),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &width_height_default
	},
	{
		.name = "height",
		.attribute_offset = offsetof (LsmSvgSvgElement, height),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &width_height_default
	},
	{
		.name = "viewBox",
		.attribute_offset = offsetof (LsmSvgSvgElement, viewbox),
		.trait_class = &lsm_box_trait_class,
		.trait_default = &viewbox_default
	},
	{
		.name = "preserveAspectRatio",
		.attribute_offset = offsetof (LsmSvgSvgElement, preserve_aspect_ratio),
		.trait_class = &lsm_svg_preserve_aspect_ratio_trait_class,
		.trait_default = &preserve_aspect_ratio_default
	}
};

static void
lsm_svg_svg_element_class_init (LsmSvgSvgElementClass *s_svg_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (s_svg_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (s_svg_class);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (s_svg_class);

	parent_class = g_type_class_peek_parent (s_svg_class);

	object_class->finalize = lsm_svg_svg_element_finalize;

	d_node_class->get_node_name = lsm_svg_svg_element_get_node_name;

	s_element_class->category =
		LSM_SVG_ELEMENT_CATEGORY_CONTAINER |
		LSM_SVG_ELEMENT_CATEGORY_STRUCTURAL;

	s_element_class->render = _svg_element_render;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_svg_element_attribute_infos),
					      lsm_svg_svg_element_attribute_infos);
}

G_DEFINE_TYPE (LsmSvgSvgElement, lsm_svg_svg_element, LSM_TYPE_SVG_ELEMENT)
