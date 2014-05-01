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

#include <lsmmathmlstyleelement.h>

#include <math.h>

GObject *parent_class;

/* LsmDomNode implementation */

static const char *
lsm_mathml_style_element_get_node_name (LsmDomNode *node)
{
	return "mstyle";
}

/* LsmMathmlElement implementation */

static void
lsm_mathml_style_element_update (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmMathmlStyleElement *style_element = LSM_MATHML_STYLE_ELEMENT (self);
	LsmMathmlLength length;
	gboolean display_style;
	int new_script_level;

	length.unit = LSM_MATHML_UNIT_PT;

	display_style = style->display == LSM_MATHML_DISPLAY_BLOCK;
	lsm_mathml_boolean_attribute_inherit (&style_element->display_style, display_style);
	style->display = style_element->display_style.value ? LSM_MATHML_DISPLAY_BLOCK : LSM_MATHML_DISPLAY_INLINE;

	style->script_size_multiplier = lsm_mathml_double_attribute_inherit (&style_element->script_size_multiplier,
									     style->script_size_multiplier);
	length.value = style->script_min_size;
	style->script_min_size = lsm_mathml_length_attribute_normalize (&style_element->script_min_size,
									style->script_min_size,
								        &length, style);

	new_script_level = lsm_mathml_script_level_attribute_apply (&style_element->script_level,
								    style->script_level);

	lsm_mathml_style_change_script_level (style, new_script_level - style->script_level);

	/* token */

	lsm_mathml_variant_set_font_style (&style->math_variant, style_element->font_style.value);
	lsm_mathml_variant_set_font_weight (&style->math_variant, style_element->font_weight.value);


	lsm_mathml_style_set_math_family (style,
					  lsm_mathml_string_attribute_inherit (&style_element->math_family,
									       style->math_family));
	style->math_color = lsm_mathml_color_attribute_inherit (&style_element->math_color,
								style->math_color);
	style->math_background = lsm_mathml_color_attribute_inherit (&style_element->math_background,
								     style->math_background);
	style->math_variant = lsm_mathml_enum_attribute_inherit (&style_element->math_variant, style->math_variant);
	length.value = style->math_size;
	style->math_size = lsm_mathml_length_attribute_normalize (&style_element->math_size,
								  style->math_size,
								  &length, style);

	/* mstyle */

	length.value = style->very_very_thin_math_space;
	style->very_very_thin_math_space =
		lsm_mathml_length_attribute_normalize (&style_element->very_very_thin_math_space,
						       style->very_very_thin_math_space,
						       &length, style);
	length.value = style->very_thin_math_space;
	style->very_thin_math_space =
		lsm_mathml_length_attribute_normalize (&style_element->very_thin_math_space,
						       style->very_thin_math_space,
						       &length, style);
	length.value = style->thin_math_space;
	style->thin_math_space =
		lsm_mathml_length_attribute_normalize (&style_element->thin_math_space,
						       style->thin_math_space,
						       &length, style);
	length.value = style->medium_math_space;
	style->medium_math_space =
		lsm_mathml_length_attribute_normalize (&style_element->medium_math_space,
						       style->medium_math_space,
						       &length, style);
	length.value = style->thick_math_space;
	style->thick_math_space =
		lsm_mathml_length_attribute_normalize (&style_element->thick_math_space,
						       style->thick_math_space,
						       &length, style);
	length.value = style->very_thick_math_space;
	style->very_thick_math_space =
		lsm_mathml_length_attribute_normalize (&style_element->very_thick_math_space,
						       style->very_thick_math_space,
						       &length, style);
	length.value = style->very_very_thick_math_space;
	style->very_very_thick_math_space =
		lsm_mathml_length_attribute_normalize (&style_element->very_very_thick_math_space,
						       style->very_very_thick_math_space,
						       &length, style);

	/* mfrac */

	length.value = style->line_thickness;
	style->line_thickness = lsm_mathml_length_attribute_normalize (&style_element->line_thickness,
								       style->line_thickness,
								       &length, style);
}

/* LsmMathmlStyleElement implementation */

LsmDomNode *
lsm_mathml_style_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_STYLE_ELEMENT, NULL);
}

static const LsmMathmlLength length_default = {1.0, LSM_MATHML_UNIT_NONE};
static const LsmMathmlFontStyle font_style_default = LSM_MATHML_FONT_STYLE_ERROR;
static const LsmMathmlFontWeight font_weight_default = LSM_MATHML_FONT_WEIGHT_ERROR;

static void
lsm_mathml_style_element_init (LsmMathmlStyleElement *self)
{
	self->script_min_size.length = length_default;
	self->very_very_thin_math_space.length = length_default;
	self->very_thin_math_space.length = length_default;
	self->thin_math_space.length = length_default;
	self->medium_math_space.length = length_default;
	self->thick_math_space.length = length_default;
	self->very_thick_math_space.length = length_default;
	self->very_very_thick_math_space.length = length_default;
	self->math_size.length = length_default;
	self->line_thickness.length = length_default;

	self->font_weight.value = font_weight_default;
	self->font_style.value = font_style_default;
}

/* LsmMathmlStyleElement class */

static const LsmAttributeInfos _attribute_infos[] = {
	{
		.name = "displaystyle",
		.attribute_offset = offsetof (LsmMathmlStyleElement, display_style),
		.trait_class = &lsm_mathml_boolean_trait_class
	},
	{
		.name = "scriptlevel",
		.attribute_offset = offsetof (LsmMathmlStyleElement, script_level),
		.trait_class = &lsm_mathml_script_level_trait_class
	},
	{
		.name = "scriptminsize",
		.attribute_offset = offsetof (LsmMathmlStyleElement, script_min_size),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "scriptsizemultiplier",
		.attribute_offset = offsetof (LsmMathmlStyleElement, script_size_multiplier),
		.trait_class = &lsm_mathml_double_trait_class
	},
	{
		.name = "veryverythinmathspace",
		.attribute_offset = offsetof (LsmMathmlStyleElement, very_very_thin_math_space),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "verythinmathspace",
		.attribute_offset = offsetof (LsmMathmlStyleElement, very_thin_math_space),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "thinmathspace",
		.attribute_offset = offsetof (LsmMathmlStyleElement, thin_math_space),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "mediummathspace",
		.attribute_offset = offsetof (LsmMathmlStyleElement, medium_math_space),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "thickmathspace",
		.attribute_offset = offsetof (LsmMathmlStyleElement, thick_math_space),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "verythickmathspace",
		.attribute_offset = offsetof (LsmMathmlStyleElement, very_thick_math_space),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "veryverythickmathspace",
		.attribute_offset = offsetof (LsmMathmlStyleElement, very_very_thick_math_space),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "mathfamily",
		.attribute_offset = offsetof (LsmMathmlStyleElement, math_family),
		.trait_class = &lsm_mathml_string_trait_class
	},
	{
		.name = "mathsize",
		.attribute_offset = offsetof (LsmMathmlStyleElement, math_size),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "mathvariant",
		.attribute_offset = offsetof (LsmMathmlStyleElement, math_variant),
		.trait_class = &lsm_mathml_variant_trait_class,
	},
	{
		.name = "mathcolor",
		.attribute_offset = offsetof (LsmMathmlStyleElement, math_color),
		.trait_class = &lsm_mathml_color_trait_class,
	},
	{
		.name = "mathbackground",
		.attribute_offset = offsetof (LsmMathmlStyleElement, math_background),
		.trait_class = &lsm_mathml_color_trait_class,
	},
	{
		.name = "linethickness",
		.attribute_offset = offsetof (LsmMathmlStyleElement, line_thickness),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	/* Deprecated attributes */
	{
		.name = "fontfamily",
		.attribute_offset = offsetof (LsmMathmlStyleElement, math_family),
		.trait_class = &lsm_mathml_string_trait_class
	},
	{
		.name = "fontstyle",
		.attribute_offset = offsetof (LsmMathmlStyleElement, font_style),
		.trait_class = &lsm_mathml_font_style_trait_class,
		.trait_default = &font_style_default
	},
	{
		.name = "fontweight",
		.attribute_offset = offsetof (LsmMathmlStyleElement, font_weight),
		.trait_class = &lsm_mathml_font_weight_trait_class,
		.trait_default = &font_weight_default
	},
	{
		.name = "color",
		.attribute_offset = offsetof (LsmMathmlStyleElement, math_color),
		.trait_class = &lsm_mathml_color_trait_class,
	},
	{
		.name = "background",
		.attribute_offset = offsetof (LsmMathmlStyleElement, math_background),
		.trait_class = &lsm_mathml_color_trait_class,
	}
};

static void
lsm_mathml_style_element_class_init (LsmMathmlStyleElementClass *style_class)
{
	LsmDomNodeClass *node_class = LSM_DOM_NODE_CLASS (style_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (style_class);

	parent_class = g_type_class_peek_parent (style_class);

	node_class->get_node_name = lsm_mathml_style_element_get_node_name;

	m_element_class->update = lsm_mathml_style_element_update;
	m_element_class->attribute_manager = lsm_attribute_manager_duplicate (m_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (m_element_class->attribute_manager,
					      G_N_ELEMENTS (_attribute_infos),
					      _attribute_infos);
}

G_DEFINE_TYPE (LsmMathmlStyleElement, lsm_mathml_style_element, LSM_TYPE_MATHML_PRESENTATION_CONTAINER)
