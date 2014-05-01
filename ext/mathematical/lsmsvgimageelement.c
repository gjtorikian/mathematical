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

#include <lsmsvgimageelement.h>
#include <lsmsvgview.h>
#include <lsmdebug.h>
#include <lsmdomdocument.h>
#include <stdio.h>
#include <string.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_image_element_get_node_name (LsmDomNode *node)
{
	return "image";
}

static void
lsm_svg_image_element_set_attribute (LsmDomElement *self, const char *name, const char *value)
{
	LsmSvgImageElement *image_element = LSM_SVG_IMAGE_ELEMENT (self);

	LSM_DOM_ELEMENT_CLASS (parent_class)->set_attribute (self, name, value);

	if (g_strcmp0 (name, "xlink:href") == 0 && image_element->pixbuf != NULL) {
		g_object_unref (image_element->pixbuf);
		image_element->pixbuf = NULL;
	}
}

static gboolean
lsm_svg_use_can_append_child (LsmDomNode *node, LsmDomNode *child)
{
	return FALSE;
}

/* LsmSvgElement implementation */

/* LsmSvgGraphic implementation */

static void
lsm_svg_image_element_render (LsmSvgElement *self, LsmSvgView *view)
{
	LsmSvgImageElement *image;
	LsmBox viewport;
	LsmBox viewbox;

	image = LSM_SVG_IMAGE_ELEMENT (self);

	if (image->pixbuf == NULL) {
		LsmDomDocument *document;
		char *data;
		gsize size;

		document = lsm_dom_node_get_owner_document (LSM_DOM_NODE (self));

		if (image->href.value != NULL) {
			data = lsm_dom_document_get_href_data (document, image->href.value, &size);
			if (data != NULL) {
				GdkPixbufLoader *loader;

				loader = gdk_pixbuf_loader_new ();

				gdk_pixbuf_loader_write (loader, (guchar *) data, size, NULL);

				g_free (data);

				gdk_pixbuf_loader_close (loader, NULL);

				image->pixbuf = gdk_pixbuf_loader_get_pixbuf (loader);
				g_object_ref (image->pixbuf);

				g_object_unref (loader);
			} else
				lsm_debug_render ("[SvgImageElement::render] Failed to load image '%s'",
						  image->href.value);
		} else
			lsm_debug_render ("[SvgImageElement::render] Missing xlink:href attribute");

	}

	if (image->pixbuf == NULL)
		return;

	viewport.x      = lsm_svg_view_normalize_length (view, &image->x.length,
							 LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	viewport.y      = lsm_svg_view_normalize_length (view, &image->y.length,
							 LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	viewport.width  = lsm_svg_view_normalize_length (view, &image->width.length,
							 LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	viewport.height = lsm_svg_view_normalize_length (view, &image->height.length,
							 LSM_SVG_LENGTH_DIRECTION_VERTICAL);

	lsm_debug_render ("[LsmSvgImageElement::graphic_render] viewport %g, %g, %g, %g",
		   viewport.x, viewport.y, viewport.width, viewport.height);

	viewbox.x = 0;
	viewbox.y = 0;
	viewbox.width = gdk_pixbuf_get_width (image->pixbuf);
	viewbox.height = gdk_pixbuf_get_height (image->pixbuf);

	lsm_svg_view_push_viewport (view, &viewport, &viewbox, &image->preserve_aspect_ratio.value, LSM_SVG_OVERFLOW_HIDDEN);

	lsm_svg_view_show_viewport (view, &viewbox);

	lsm_svg_view_show_pixbuf (view, image->pixbuf);

	lsm_svg_view_pop_viewport (view);
}

static void
lsm_svg_image_element_get_extents (LsmSvgElement *self, LsmSvgView *view, LsmExtents *extents)
{
	LsmSvgImageElement *image;

	image = LSM_SVG_IMAGE_ELEMENT (self);
	double x, y;
	double w, h;

	x = lsm_svg_view_normalize_length (view, &image->x.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	y = lsm_svg_view_normalize_length (view, &image->y.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);
	w = lsm_svg_view_normalize_length (view, &image->width.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	h = lsm_svg_view_normalize_length (view, &image->height.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);

	extents->x1 = x;
	extents->y1 = y;
	extents->x2 = x + w;
	extents->y2 = y + h;
}

/* LsmSvgImageElement implementation */

LsmDomNode *
lsm_svg_image_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_IMAGE_ELEMENT, NULL);
}

static const LsmSvgLength length_default = 	 { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PX};
static const LsmSvgPreserveAspectRatio preserve_aspect_ratio_default = {
	.defer = FALSE,
	.align = LSM_SVG_ALIGN_X_MID_Y_MID,
	.meet_or_slice = LSM_SVG_MEET_OR_SLICE_MEET
};

static void
lsm_svg_image_element_init (LsmSvgImageElement *self)
{
	self->pixbuf = NULL;
	self->x.length = length_default;
	self->y.length = length_default;
	self->width.length = length_default;
	self->height.length = length_default;
	self->preserve_aspect_ratio.value = preserve_aspect_ratio_default;
}

static void
lsm_svg_image_element_finalize (GObject *gobject)
{
	LsmSvgImageElement *image = LSM_SVG_IMAGE_ELEMENT (gobject);

	if (image->pixbuf != NULL)
		g_object_unref (image->pixbuf);

	parent_class->finalize (gobject);
}

/* LsmSvgImageElement class */

static const LsmAttributeInfos lsm_svg_image_element_attribute_infos[] = {
	{
		.name = "x",
		.attribute_offset = offsetof (LsmSvgImageElement, x),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "y",
		.attribute_offset = offsetof (LsmSvgImageElement, y),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "width",
		.attribute_offset = offsetof (LsmSvgImageElement, width),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "height",
		.attribute_offset = offsetof (LsmSvgImageElement, height),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "xlink:href",
		.attribute_offset = offsetof (LsmSvgImageElement, href),
		.trait_class = &lsm_null_trait_class
	},
	{
		.name = "preserveAspectRatio",
		.attribute_offset = offsetof (LsmSvgImageElement, preserve_aspect_ratio),
		.trait_class = &lsm_svg_preserve_aspect_ratio_trait_class,
		.trait_default = &preserve_aspect_ratio_default
	}
};

static void
lsm_svg_image_element_class_init (LsmSvgImageElementClass *klass)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (klass);
	LsmDomElementClass *d_element_class = LSM_DOM_ELEMENT_CLASS (klass);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (klass);

	parent_class = g_type_class_peek_parent (klass);

	gobject_class->finalize = lsm_svg_image_element_finalize;

	d_node_class->get_node_name = lsm_svg_image_element_get_node_name;
	d_node_class->can_append_child = lsm_svg_use_can_append_child;

	d_element_class->set_attribute = lsm_svg_image_element_set_attribute;

	s_element_class->category =
		LSM_SVG_ELEMENT_CATEGORY_GRAPHICS |
		LSM_SVG_ELEMENT_CATEGORY_GRAPHICS_REFERENCING;

	s_element_class->render = lsm_svg_image_element_render;
	s_element_class->get_extents = lsm_svg_image_element_get_extents;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_image_element_attribute_infos),
					      lsm_svg_image_element_attribute_infos);
}

G_DEFINE_TYPE (LsmSvgImageElement, lsm_svg_image_element, LSM_TYPE_SVG_TRANSFORMABLE)
