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

#include <lsmsvgswitchelement.h>
#include <lsmdebug.h>
#include <stdio.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_switch_element_get_node_name (LsmDomNode *node)
{
	return "switch";
}

/* GSwitchElement implementation */

/* LsmSvgElement implementation */

static void
_render (LsmSvgElement *element, LsmSvgView *view)
{
	LsmDomNode *node;

	for (node = LSM_DOM_NODE (element)->first_child; node != NULL; node = node->next_sibling)
		if (LSM_IS_SVG_ELEMENT (node)) {
		    lsm_svg_element_render (LSM_SVG_ELEMENT (node), view);
		    return;
		}
}

static void
_get_extents (LsmSvgElement *element, LsmSvgView *view, LsmExtents *extents)
{
	LsmDomNode *node;
	LsmExtents null_extents = {0.0, 0.0, 0.0, 0.0};

	for (node = LSM_DOM_NODE (element)->first_child; node != NULL; node = node->next_sibling)
		if (LSM_IS_SVG_ELEMENT (node)) {
		    lsm_svg_element_get_extents (LSM_SVG_ELEMENT (node), view, extents);
		    return;
		}

	*extents = null_extents;
}

/* LsmSvgSwitchElement implementation */

LsmDomNode *
lsm_svg_switch_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_SWITCH_ELEMENT, NULL);
}

static void
lsm_svg_switch_element_init (LsmSvgSwitchElement *self)
{
}

/* LsmSvgSwitchElement class */


static void
lsm_svg_switch_element_class_init (LsmSvgSwitchElementClass *s_g_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (s_g_class);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (s_g_class);

	parent_class = g_type_class_peek_parent (s_g_class);

	d_node_class->get_node_name = lsm_svg_switch_element_get_node_name;

	s_element_class->render = _render;
	s_element_class->get_extents = _get_extents;

	s_element_class->category =
		LSM_SVG_ELEMENT_CATEGORY_CONTAINER |
		LSM_SVG_ELEMENT_CATEGORY_STRUCTURAL;
}

G_DEFINE_TYPE (LsmSvgSwitchElement, lsm_svg_switch_element, LSM_TYPE_SVG_TRANSFORMABLE)
