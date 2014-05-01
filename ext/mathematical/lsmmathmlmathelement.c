/* Lasem
 * 
 * Copyright © 2007-2008 Emmanuel Pacaud
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

#include <lsmmathmlmathelement.h>
#include <lsmmathmlstyleelement.h>
#include <lsmmathmlview.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_mathml_math_element_get_node_name (LsmDomNode *node)
{
	return "math";
}

/* LsmMathmlElement implementation */

static void
_update (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmMathmlMathElement *math_element = LSM_MATHML_MATH_ELEMENT (self);
	LsmMathmlMode default_mode;

	default_mode = lsm_mathml_enum_attribute_inherit (&math_element->mode,
							  (style->display == LSM_MATHML_DISPLAY_INLINE) ?
							  LSM_MATHML_MODE_INLINE : LSM_MATHML_MODE_DISPLAY);

	style->display = lsm_mathml_enum_attribute_inherit (&math_element->display,
							    (default_mode == LSM_MATHML_MODE_INLINE) ?
							    LSM_MATHML_DISPLAY_INLINE : LSM_MATHML_DISPLAY_BLOCK);
}

/* LsmMathmlMathElement implementation */

LsmMathmlStyle *
lsm_mathml_math_element_get_default_style (LsmMathmlMathElement *math_element)
{
	g_return_val_if_fail (LSM_IS_MATHML_MATH_ELEMENT (math_element), NULL);

	return math_element->default_style;
}

void
lsm_mathml_math_element_set_default_style (LsmMathmlMathElement *math_element, LsmMathmlStyle *style)
{
	g_return_if_fail (LSM_IS_MATHML_MATH_ELEMENT (math_element));
	g_return_if_fail (style != NULL);

	if (style == math_element->default_style) {
		lsm_dom_node_changed (LSM_DOM_NODE (math_element));
		return;
	}

	lsm_mathml_style_free (math_element->default_style);
	math_element->default_style = lsm_mathml_style_duplicate (style);

	lsm_dom_node_changed (LSM_DOM_NODE (math_element));
}

void
lsm_mathml_math_element_update (LsmMathmlMathElement *math_element)
{
	lsm_mathml_element_update (LSM_MATHML_ELEMENT (math_element),
				   lsm_mathml_math_element_get_default_style (math_element));
}

const LsmMathmlBbox *
lsm_mathml_math_element_measure (LsmMathmlMathElement *math_element,
			      LsmMathmlView *view)
{
	return lsm_mathml_element_measure (LSM_MATHML_ELEMENT (math_element), view, NULL);
}

void
lsm_mathml_math_element_layout (LsmMathmlMathElement *math_element,
			     LsmMathmlView *view,
			     const LsmMathmlBbox *bbox)
{
	lsm_mathml_element_layout (LSM_MATHML_ELEMENT (math_element), view, 0, 0, bbox);
}

void
lsm_mathml_math_element_render (LsmMathmlMathElement *math_element, LsmMathmlView *view)
{
	lsm_mathml_element_render (LSM_MATHML_ELEMENT (math_element), view);
}

LsmDomNode *
lsm_mathml_math_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_MATH_ELEMENT, NULL);
}

static void
lsm_mathml_math_element_init (LsmMathmlMathElement *self)
{
	LsmMathmlStyle *style;

	style = lsm_mathml_style_new ();
	self->default_style = style;
	g_return_if_fail (style != NULL);

	style->math_size = 12.0;

	style->display = LSM_MATHML_DISPLAY_INLINE;

	style->script_level = 0;
	style->script_size_multiplier = 0.71;
	style->script_min_size = 8.0;

	style->very_very_thin_math_space = 	LSM_MATHML_SPACE_EM_VERY_VERY_THIN * style->math_size;
	style->very_thin_math_space = 		LSM_MATHML_SPACE_EM_VERY_THIN * style->math_size;
	style->thin_math_space = 		LSM_MATHML_SPACE_EM_THIN * style->math_size;
	style->medium_math_space = 		LSM_MATHML_SPACE_EM_MEDIUM * style->math_size;
	style->thick_math_space = 		LSM_MATHML_SPACE_EM_THICK * style->math_size;
	style->very_thick_math_space = 		LSM_MATHML_SPACE_EM_VERY_THICK * style->math_size;
	style->very_very_thick_math_space = 	LSM_MATHML_SPACE_EM_VERY_VERY_THICK * style->math_size;

	style->math_family = g_strdup ("Serif");
	style->math_variant = LSM_MATHML_VARIANT_NORMAL;
	style->math_color.red = 0;
	style->math_color.green = 0;
	style->math_color.blue = 0;
	style->math_color.alpha = 1;
	style->math_background.red = 0;
	style->math_background.green = 0;
	style->math_background.blue = 0;
	style->math_background.alpha = 0;

	style->subscript_shift = 0;
	style->superscript_shift = 0;

	style->line_thickness = 0.1 * style->math_size;
}

static void
lsm_mathml_math_element_finalize (GObject *object)
{
	LsmMathmlMathElement *math_element = LSM_MATHML_MATH_ELEMENT (object);

	lsm_mathml_style_free (math_element->default_style);

	parent_class->finalize (object);
}

/* LsmMathmlMathElement class */

static const LsmAttributeInfos _attribute_infos[] = {
	{
		.name = "display",
		.attribute_offset = offsetof (LsmMathmlMathElement, display),
		.trait_class = &lsm_mathml_display_trait_class,
	},
	{
		.name = "mode",
		.attribute_offset = offsetof (LsmMathmlMathElement, mode),
		.trait_class = &lsm_mathml_mode_trait_class,
	}
};

static void
lsm_mathml_math_element_class_init (LsmMathmlMathElementClass *math_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (math_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (math_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (math_class);

	parent_class = g_type_class_peek_parent (math_class);

	object_class->finalize = lsm_mathml_math_element_finalize;

	d_node_class->get_node_name = lsm_mathml_math_element_get_node_name;

	m_element_class->update = _update;
	m_element_class->attribute_manager = lsm_attribute_manager_duplicate (m_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (m_element_class->attribute_manager,
					      G_N_ELEMENTS (_attribute_infos),
					      _attribute_infos);
}

G_DEFINE_TYPE (LsmMathmlMathElement, lsm_mathml_math_element, LSM_TYPE_MATHML_ELEMENT)
