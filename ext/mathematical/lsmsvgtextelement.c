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

#include <lsmsvgtextelement.h>
#include <lsmsvgtspanelement.h>
#include <lsmsvgview.h>
#include <lsmdomtext.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_text_element_get_node_name (LsmDomNode *node)
{
	return "text";
}

static gboolean
lsm_svg_text_element_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	return (LSM_IS_SVG_TSPAN_ELEMENT (child) || LSM_IS_DOM_TEXT (child));
}

/* LsmSvgElement implementation */

/* LsmSvgGraphic implementation */

static void
lsm_svg_text_element_render (LsmSvgElement *self, LsmSvgView *view)
{
	LsmSvgTextElement *text = LSM_SVG_TEXT_ELEMENT (self);
	LsmDomNode *node = LSM_DOM_NODE (self);
	LsmDomNode *iter;
	GString *string = g_string_new ("");
	double x, y;

	if (node->first_child == NULL)
		return;

	for (iter = LSM_DOM_NODE (self)->first_child; iter != NULL; iter = iter->next_sibling) {
		if (LSM_IS_DOM_TEXT (iter)) {
			g_string_append (string, lsm_dom_node_get_node_value (iter));
		}
	}

	x = lsm_svg_view_normalize_length (view, &text->x.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	y = lsm_svg_view_normalize_length (view, &text->y.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);

	lsm_svg_view_show_text (view, g_strstrip (string->str), x, y);

	g_string_free (string, TRUE);

	for (iter = LSM_DOM_NODE (self)->first_child; iter != NULL; iter = iter->next_sibling)
		if (LSM_IS_SVG_ELEMENT (iter))
		    lsm_svg_element_render (LSM_SVG_ELEMENT (iter), view);
}

static void
lsm_svg_text_element_get_extents (LsmSvgElement *self, LsmSvgView *view, LsmExtents *extents)
{
	LsmSvgTextElement *text = LSM_SVG_TEXT_ELEMENT (self);
	LsmDomNode *iter;
	GString *string = g_string_new ("");
	double x, y;

	for (iter = LSM_DOM_NODE (self)->first_child; iter != NULL; iter = iter->next_sibling) {
		if (LSM_IS_DOM_TEXT (iter)) {
			g_string_append (string, lsm_dom_node_get_node_value (iter));
		}
	}

	x = lsm_svg_view_normalize_length (view, &text->x.length, LSM_SVG_LENGTH_DIRECTION_HORIZONTAL);
	y = lsm_svg_view_normalize_length (view, &text->y.length, LSM_SVG_LENGTH_DIRECTION_VERTICAL);

	lsm_svg_view_text_extents (view, g_strstrip (string->str), x, y, extents);

	g_string_free (string, TRUE);
}

/* LsmSvgTextElement implementation */

LsmDomNode *
lsm_svg_text_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_TEXT_ELEMENT, NULL);
}

static const LsmSvgLength length_default = 	 { .value_unit =   0.0, .type = LSM_SVG_LENGTH_TYPE_PX};

static void
lsm_svg_text_element_init (LsmSvgTextElement *self)
{
	self->x.length = length_default;
	self->y.length = length_default;
}

static void
lsm_svg_text_element_finalize (GObject *object)
{
	parent_class->finalize (object);
}

/* LsmSvgTextElement class */

static const LsmAttributeInfos lsm_svg_text_element_attribute_infos[] = {
	{
		.name = "x",
		.attribute_offset = offsetof (LsmSvgTextElement, x),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "y",
		.attribute_offset = offsetof (LsmSvgTextElement, y),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = &length_default
	}
};

static void
lsm_svg_text_element_class_init (LsmSvgTextElementClass *s_text_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (s_text_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (s_text_class);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (s_text_class);

	parent_class = g_type_class_peek_parent (s_text_class);

	object_class->finalize = lsm_svg_text_element_finalize;

	d_node_class->get_node_name = lsm_svg_text_element_get_node_name;
	d_node_class->can_append_child = lsm_svg_text_element_can_append_child;

	s_element_class->category =
		LSM_SVG_ELEMENT_CATEGORY_GRAPHICS |
		LSM_SVG_ELEMENT_CATEGORY_TEXT_CONTENT;

	s_element_class->render = lsm_svg_text_element_render;
	s_element_class->get_extents = lsm_svg_text_element_get_extents;
	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	s_element_class->is_shape_element = TRUE;

	lsm_attribute_manager_add_attributes (s_element_class->attribute_manager,
					      G_N_ELEMENTS (lsm_svg_text_element_attribute_infos),
					      lsm_svg_text_element_attribute_infos);
}

G_DEFINE_TYPE (LsmSvgTextElement, lsm_svg_text_element, LSM_TYPE_SVG_TRANSFORMABLE)
