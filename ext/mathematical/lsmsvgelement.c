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
#include <lsmattributes.h>
#include <lsmproperties.h>
#include <lsmdomdocument.h>
#include <lsmsvgelement.h>
#include <lsmsvgtransformable.h>
#include <lsmsvgpatternelement.h>
#include <lsmsvgradialgradientelement.h>
#include <lsmsvglineargradientelement.h>
#include <lsmsvgclippathelement.h>
#include <lsmsvgmarkerelement.h>
#include <lsmsvgmaskelement.h>
#include <lsmsvgfilterelement.h>
#include <lsmsvgview.h>
#include <string.h>

static GObjectClass *parent_class;

/* LsmDomNode implementation */

static gboolean
lsm_svg_element_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	return (LSM_IS_SVG_ELEMENT (child));
}

static gboolean
lsm_svg_element_child_changed (LsmDomNode *parent, LsmDomNode *child)
{
#if 0
	if (LSM_IS_SVG_ELEMENT (child) &&
	    lsm_svg_element_get_category (LSM_SVG_ELEMENT (child)) == 0)
		g_warning ("Category not defined for '%s'", lsm_dom_node_get_node_name (child));
#endif

	return TRUE;
}

/* LsmDomElement implementation */

static void
lsm_svg_element_set_attribute (LsmDomElement *self, const char* name, const char *value)
{
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_GET_CLASS (self);
	LsmSvgElement *s_element = LSM_SVG_ELEMENT (self);

	lsm_debug_dom ("[LsmSvgElement::set_attribute] node = %s, name = %s, value = %s",
		    lsm_dom_node_get_node_name (LSM_DOM_NODE (self)), name, value);

	/* TODO Avoid double hash table lookup */
	if (!lsm_attribute_manager_set_attribute (s_element_class->attribute_manager,
						  self, name, value))
		lsm_svg_property_bag_set_property (&s_element->property_bag, name, value);

	if (g_strcmp0 (name, "id") == 0 ||
	    g_strcmp0 (name, "xml:id") == 0) {
		LsmDomDocument *document;

		document = lsm_dom_node_get_owner_document (LSM_DOM_NODE (self));
		if (document != NULL)
			lsm_dom_document_register_element (document, LSM_DOM_ELEMENT (self), value);
	}
}

const char *
lsm_svg_element_get_attribute (LsmDomElement *self, const char *name)
{
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_GET_CLASS(self);
	LsmSvgElement *s_element = LSM_SVG_ELEMENT (self);
	const char *value;

	/* TODO Avoid double hash table lookup */
	value = lsm_attribute_manager_get_attribute (s_element_class->attribute_manager,
						     self, name);
	if (value != NULL)
		return value;

	return lsm_svg_property_bag_get_property (&s_element->property_bag, name);
}

static char *
lsm_svg_element_get_serialized_attributes (LsmDomElement *self)
{
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_GET_CLASS(self);
	LsmSvgElement *s_element = LSM_SVG_ELEMENT (self);
	char *properties;
	char *attributes;
	char *result;

	properties = lsm_svg_property_bag_serialize (&s_element->property_bag);
	attributes = lsm_attribute_manager_serialize (s_element_class->attribute_manager, self);

	if (attributes == NULL)
		return properties;

	if (properties == NULL)
		return attributes;

	result = g_strconcat (attributes, " ", properties, NULL);

	g_free (properties);
	g_free (attributes);

	return result;
}

/* LsmSvgElement implementation */

LsmSvgElementCategory
lsm_svg_element_get_category (LsmSvgElement *element)
{
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_GET_CLASS (element);

	return s_element_class != NULL ? s_element_class->category : 0;
}

static void
_render (LsmSvgElement *element, LsmSvgView *view)
{
	LsmDomNode *node;

	lsm_debug_render ("[LsmSvgElement::_render");

	for (node = LSM_DOM_NODE (element)->first_child; node != NULL; node = node->next_sibling)
		if (LSM_IS_SVG_ELEMENT (node))
		    lsm_svg_element_render (LSM_SVG_ELEMENT (node), view);
}

static void
_transformed_render (LsmSvgElement *element, LsmSvgView *view)
{
	LsmSvgElementClass *element_class;
	const LsmSvgStyle *parent_style;
	LsmSvgStyle *style;

	element_class = LSM_SVG_ELEMENT_GET_CLASS (element);

	parent_style = lsm_svg_view_get_current_style (view);
	style = lsm_svg_style_new_inherited (parent_style, &element->property_bag);
	style->ignore_group_opacity = element_class->is_shape_element;

	if (style->visibility->value == LSM_SVG_VISIBILITY_VISIBLE &&
	    style->display->value != LSM_SVG_DISPLAY_NONE) {

		lsm_debug_render ("[LsmSvgElement::render] Render %s (%s)",
				  lsm_dom_node_get_node_name (LSM_DOM_NODE (element)),
				  element->id.value != NULL ? element->id.value : "no id");
		lsm_svg_view_push_element (view, element);
		lsm_svg_view_push_composition (view, style);

		element_class->render (element, view);

		lsm_svg_view_pop_composition (view);
		lsm_svg_view_pop_element (view);
	}

	lsm_svg_style_unref (style);
}

void
lsm_svg_element_render (LsmSvgElement *element, LsmSvgView *view)
{
	LsmSvgElementClass *element_class;

	g_return_if_fail (LSM_IS_SVG_ELEMENT (element));

	element_class = LSM_SVG_ELEMENT_GET_CLASS (element);

	if (element_class->render != NULL)
		element_class->transformed_render (element, view);
}

static void
lsm_svg_element_enable_rendering (LsmSvgElement *element)
{
	LsmSvgElementClass *element_class;

	g_return_if_fail (LSM_IS_SVG_ELEMENT (element));

	element_class = LSM_SVG_ELEMENT_GET_CLASS (element);
	g_return_if_fail (element_class->enable_rendering != NULL);

	element_class->enable_rendering (element);
}

void
lsm_svg_element_force_render (LsmSvgElement *element, LsmSvgView *view)
{
	g_return_if_fail (LSM_IS_SVG_PATTERN_ELEMENT (element) ||
			  LSM_IS_SVG_RADIAL_GRADIENT_ELEMENT (element) ||
			  LSM_IS_SVG_LINEAR_GRADIENT_ELEMENT (element) ||
			  LSM_IS_SVG_MASK_ELEMENT (element) ||
			  LSM_IS_SVG_CLIP_PATH_ELEMENT (element) ||
			  LSM_IS_SVG_MARKER_ELEMENT (element) ||
			  LSM_IS_SVG_FILTER_ELEMENT (element));

	lsm_svg_element_enable_rendering (element);
	lsm_svg_element_render (element, view);
}

void
lsm_svg_element_transformed_get_extents (LsmSvgElement *element, LsmSvgView *view, LsmExtents *extents)
{
	LsmSvgElementClass *element_class;
	g_return_if_fail (LSM_IS_SVG_ELEMENT (element));
	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (extents != NULL);

	element_class = LSM_SVG_ELEMENT_GET_CLASS (element);

	if (element_class->transformed_get_extents != NULL)
		element_class->transformed_get_extents (element, view, extents);
	else
		element_class->get_extents (element, view, extents);
}

static void
_get_extents (LsmSvgElement *element, LsmSvgView *view, LsmExtents *extents)
{
	LsmDomNode *node;
	gboolean first_child = TRUE;
	LsmExtents element_extents = {0.0, 0.0, 0.0, 0.0};

	lsm_debug_render ("[LsmSvgElement::_get_extents]");

	for (node = LSM_DOM_NODE (element)->first_child; node != NULL; node = node->next_sibling) {
		if (LSM_IS_SVG_ELEMENT (node)) {
			LsmExtents child_extents;
			LsmSvgElement *child_element;
			LsmSvgElementClass *child_element_class;

			child_element = LSM_SVG_ELEMENT (node);
			child_element_class = LSM_SVG_ELEMENT_GET_CLASS (node);
			
			if (child_element_class->transformed_get_extents != NULL)
				child_element_class->transformed_get_extents (child_element, view, &child_extents);
			else
				child_element_class->get_extents (child_element, view, &child_extents);

			if (first_child) {
				element_extents = child_extents;
				first_child = FALSE;
			} else {
				element_extents.x1 = MIN (element_extents.x1, child_extents.x1);
				element_extents.y1 = MIN (element_extents.y1, child_extents.y1);
				element_extents.x2 = MAX (element_extents.x2, child_extents.x2);
				element_extents.y2 = MAX (element_extents.y2, child_extents.y2);
			}
		}
	}

	*extents = element_extents;
}

void
lsm_svg_element_get_extents (LsmSvgElement *element, LsmSvgView *view, LsmExtents *extents)
{
	LsmSvgElementClass *element_class;

	g_return_if_fail (LSM_IS_SVG_ELEMENT (element));
	g_return_if_fail (LSM_IS_SVG_VIEW (view));
	g_return_if_fail (extents != NULL);

	element_class = LSM_SVG_ELEMENT_GET_CLASS (element);
	element_class->get_extents (element, view, extents);

	if (element->id.value != NULL)
		lsm_debug_measure ("LsmSvgElement::get_extents] Extents for '%s' = %g,%g %g,%g",
				   element->id.value,
				   extents->x1, extents->y1, extents->x2, extents->y2);
	else
		lsm_debug_measure ("LsmSvgElement::get_extents] Extents for <%s> = %g,%g %g,%g",
				   lsm_dom_node_get_node_name (LSM_DOM_NODE (element)),
				   extents->x1, extents->y1, extents->x2, extents->y2);
}

static void
lsm_svg_element_init (LsmSvgElement *element)
{
}

static void
lsm_svg_element_finalize (GObject *object)
{
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_GET_CLASS (object);
	LsmSvgElement *svg_element = LSM_SVG_ELEMENT (object);

	lsm_svg_property_bag_clean (&svg_element->property_bag);
	lsm_attribute_manager_clean_attributes (s_element_class->attribute_manager, svg_element);

	parent_class->finalize (object);
}

/* LsmSvgElement class */

static const LsmSvgMatrix matrix_default =	 { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, LSM_SVG_MATRIX_FLAGS_IDENTITY};

static const LsmAttributeInfos lsm_svg_attribute_infos[] = {
	{
		.name = "id",
		.trait_class = &lsm_null_trait_class,
		.attribute_offset = offsetof (LsmSvgElement, id)
	},
	{
		.name = "xml:id",
		.trait_class = &lsm_null_trait_class,
		.attribute_offset = offsetof (LsmSvgElement, id)
	},
	{
		.name = "class",
		.trait_class = &lsm_null_trait_class,
		.attribute_offset = offsetof (LsmSvgElement, class_name)
	}
};

static void
lsm_svg_element_class_init (LsmSvgElementClass *s_element_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (s_element_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (s_element_class);
	LsmDomElementClass *d_element_class = LSM_DOM_ELEMENT_CLASS (s_element_class);

	parent_class = g_type_class_peek_parent (s_element_class);

	object_class->finalize = lsm_svg_element_finalize;

	d_node_class->can_append_child = lsm_svg_element_can_append_child;
	d_node_class->child_changed = lsm_svg_element_child_changed;

	d_element_class->get_attribute = lsm_svg_element_get_attribute;
	d_element_class->set_attribute = lsm_svg_element_set_attribute;
	d_element_class->get_serialized_attributes = lsm_svg_element_get_serialized_attributes;

	s_element_class->category = 0;

	s_element_class->render = _render;
	s_element_class->get_extents = _get_extents;
	s_element_class->transformed_render = _transformed_render;
	s_element_class->transformed_get_extents = NULL;
	s_element_class->attribute_manager = lsm_attribute_manager_new (G_N_ELEMENTS (lsm_svg_attribute_infos),
									lsm_svg_attribute_infos);
}

G_DEFINE_ABSTRACT_TYPE (LsmSvgElement, lsm_svg_element, LSM_TYPE_DOM_ELEMENT)
