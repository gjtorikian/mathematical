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

#include <lsmsvgstopelement.h>
#include <lsmsvgview.h>
#include <lsmdebug.h>
#include <stdio.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_stop_element_get_node_name (LsmDomNode *node)
{
	return "stop";
}


/* LsmSvgElement implementation */

static void
lsm_svg_stop_element_render (LsmSvgElement *element, LsmSvgView *view)
{
	LsmSvgStopElement *stop = LSM_SVG_STOP_ELEMENT (element);
	double offset;

	if (stop->offset.length.type == LSM_SVG_LENGTH_TYPE_PERCENTAGE)
		offset = stop->offset.length.value_unit / 100.0;
	else
		offset = stop->offset.length.value_unit;

	lsm_debug_render ("[LsmSvgStopElement::render] Add stop at %g", offset);

	lsm_svg_view_add_gradient_color_stop (view, offset);
}

/* LsmSvgStopElement implementation */

LsmDomNode *
lsm_svg_stop_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_STOP_ELEMENT, NULL);
}

static const LsmSvgLength length_default = 	{ .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_NUMBER};

static void
lsm_svg_stop_element_init (LsmSvgStopElement *self)
{
	self->offset.length = length_default;
}

/* LsmSvgStopElement class */

static const LsmAttributeInfos lsm_svg_stop_element_attribute_infos[] = {
	{
		.name = "offset",
		.attribute_offset = offsetof (LsmSvgStopElement, offset),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	}
};

static void
lsm_svg_stop_element_class_init (LsmSvgStopElementClass *klass)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (klass);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (klass);

	parent_class = g_type_class_peek_parent (klass);

	d_node_class->get_node_name = lsm_svg_stop_element_get_node_name;

	s_element_class->category = LSM_SVG_ELEMENT_CATEGORY_NONE;

	s_element_class->render = lsm_svg_stop_element_render;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_stop_element_attribute_infos),
					      lsm_svg_stop_element_attribute_infos);

}

G_DEFINE_TYPE (LsmSvgStopElement, lsm_svg_stop_element, LSM_TYPE_SVG_ELEMENT)
