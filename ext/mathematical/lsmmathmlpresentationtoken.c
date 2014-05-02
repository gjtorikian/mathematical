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

#include <lsmmathmlpresentationtoken.h>
#include <lsmmathmlview.h>
#include <lsmdomtext.h>

#include <math.h>
#include <string.h>

static GObjectClass *parent_class;

/* LsmDomNode implementation */

static const char *
lsm_mathml_presentation_token_get_node_name (LsmDomNode *node)
{
	LsmMathmlPresentationToken *token = LSM_MATHML_PRESENTATION_TOKEN (node);

	switch (token->type) {
		case LSM_MATHML_PRESENTATION_TOKEN_TYPE_NUMBER:
			return "mn";
		case LSM_MATHML_PRESENTATION_TOKEN_TYPE_IDENTIFIER:
			return "mi";
		case LSM_MATHML_PRESENTATION_TOKEN_TYPE_TEXT:
		default:
			return "mtext";
	}
}

static gboolean
lsm_mathml_presentation_token_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	return (LSM_IS_DOM_TEXT (child) /*||
		LSM_IS_MATHML_GLYPH_ELEMENT (child) ||
		LSM_IS_MATHML_ALIGN_MARK_ELEMENT (child)*/);
}

/* LsmMathmlElement implementation */

static char *
_get_text (LsmMathmlPresentationToken *self)
{
	LsmDomNode *node;
	GString *string = g_string_new ("");
	char *text;

	for (node = LSM_DOM_NODE (self)->first_child; node != NULL; node = node->next_sibling) {
		if (LSM_IS_DOM_TEXT (node)) {
			g_string_append (string, lsm_dom_node_get_node_value (node));
		}
	}

	text = g_strdup (/* FIXME is it safe ? */g_strstrip (string->str));

	g_string_free (string, TRUE);

	return text;
}

char *
lsm_mathml_presentation_token_get_text (LsmMathmlPresentationToken *self)
{
	LsmMathmlPresentationTokenClass *token_class;

	g_return_val_if_fail (LSM_IS_MATHML_PRESENTATION_TOKEN (self), NULL);

	token_class = LSM_MATHML_PRESENTATION_TOKEN_GET_CLASS (self);

	return token_class->get_text (self);
}

static void
lsm_mathml_presentation_token_update (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmMathmlPresentationToken *token = LSM_MATHML_PRESENTATION_TOKEN (self);
	LsmMathmlLength length;

	if (token->type == LSM_MATHML_PRESENTATION_TOKEN_TYPE_IDENTIFIER) {
		char *text;
		text = lsm_mathml_presentation_token_get_text (token);
		style->math_variant = g_utf8_strlen (text, -1) > 1 ?
			LSM_MATHML_VARIANT_NORMAL : LSM_MATHML_VARIANT_ITALIC;
		g_free (text);
	}

	lsm_mathml_variant_set_font_style (&style->math_variant, token->font_style.value);
	lsm_mathml_variant_set_font_weight (&style->math_variant, token->font_weight.value);

	lsm_mathml_style_set_math_family (style,
					  lsm_mathml_string_attribute_inherit (&token->math_family,
									       style->math_family));
	style->math_variant = lsm_mathml_enum_attribute_inherit (&token->math_variant, style->math_variant);
	style->math_color = lsm_mathml_color_attribute_inherit (&token->math_color, style->math_color);
	style->math_background = lsm_mathml_color_attribute_inherit (&token->math_background, style->math_background);

	length.unit = LSM_MATHML_UNIT_PT;
	length.value = style->math_size;
	style->math_size = lsm_mathml_length_attribute_normalize (&token->math_size,
								  style->math_size,
								  &length, style);
}

static const LsmMathmlBbox *
lsm_mathml_presentation_token_measure (LsmMathmlElement *self, LsmMathmlView *view, const LsmMathmlBbox *bbox)
{
	char *text;

	text = lsm_mathml_presentation_token_get_text (LSM_MATHML_PRESENTATION_TOKEN (self));

	lsm_mathml_view_measure_text (view, &self->style, text, &self->bbox);

	g_free (text);

	self->bbox.width += self->style.math_size * LSM_MATHML_SPACE_EM_VERY_THIN;

	return &self->bbox;
}

static void
lsm_mathml_presentation_token_layout (LsmMathmlElement *self, LsmMathmlView *view,
				   double x, double y, const LsmMathmlBbox *bbox)
{
}

static void
lsm_mathml_presentation_token_render (LsmMathmlElement *self, LsmMathmlView *view)
{
	char *text;

	text = lsm_mathml_presentation_token_get_text (LSM_MATHML_PRESENTATION_TOKEN (self));

	lsm_mathml_view_show_text (view, &self->style,
				self->x + 0.5 * self->style.math_size * LSM_MATHML_SPACE_EM_VERY_THIN,
				self->y, text);

	g_free (text);
}

LsmDomNode *
lsm_mathml_number_element_new (void)
{
	LsmDomNode *node;

	node = g_object_new (LSM_TYPE_MATHML_PRESENTATION_TOKEN, NULL);
	g_return_val_if_fail (node != NULL, NULL);

	LSM_MATHML_PRESENTATION_TOKEN (node)->type = LSM_MATHML_PRESENTATION_TOKEN_TYPE_NUMBER;

	return node;
}

LsmDomNode *
lsm_mathml_identifier_element_new (void)
{
	LsmDomNode *node;

	node = g_object_new (LSM_TYPE_MATHML_PRESENTATION_TOKEN, NULL);
	g_return_val_if_fail (node != NULL, NULL);

	LSM_MATHML_PRESENTATION_TOKEN (node)->type = LSM_MATHML_PRESENTATION_TOKEN_TYPE_IDENTIFIER;

	return node;
}

LsmDomNode *
lsm_mathml_text_element_new (void)
{
	LsmDomNode *node;

	node = g_object_new (LSM_TYPE_MATHML_PRESENTATION_TOKEN, NULL);
	g_return_val_if_fail (node != NULL, NULL);

	LSM_MATHML_PRESENTATION_TOKEN (node)->type = LSM_MATHML_PRESENTATION_TOKEN_TYPE_TEXT;

	return node;
}

static const LsmMathmlLength length_default = {1.0, LSM_MATHML_UNIT_NONE};
static const LsmMathmlFontStyle font_style_default = LSM_MATHML_FONT_STYLE_ERROR;
static const LsmMathmlFontWeight font_weight_default = LSM_MATHML_FONT_WEIGHT_ERROR;

static void
lsm_mathml_presentation_token_init (LsmMathmlPresentationToken *self)
{
	self->math_size.length = length_default;

	self->font_weight.value = font_weight_default;
	self->font_style.value = font_style_default;
}

/* LsmMathmlPresentationToken class */

static const LsmAttributeInfos _attribute_infos[] = {
	{
		.name = "mathfamily",
		.attribute_offset = offsetof (LsmMathmlPresentationToken, math_family),
		.trait_class = &lsm_mathml_string_trait_class
	},
	{
		.name = "mathsize",
		.attribute_offset = offsetof (LsmMathmlPresentationToken, math_size),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "mathvariant",
		.attribute_offset = offsetof (LsmMathmlPresentationToken, math_variant),
		.trait_class = &lsm_mathml_variant_trait_class,
	},
	{
		.name = "mathcolor",
		.attribute_offset = offsetof (LsmMathmlPresentationToken, math_color),
		.trait_class = &lsm_mathml_color_trait_class,
	},
	{
		.name = "mathbackground",
		.attribute_offset = offsetof (LsmMathmlPresentationToken, math_background),
		.trait_class = &lsm_mathml_color_trait_class,
	},
	/* Deprecated attributes */
	{
		.name = "fontfamily",
		.attribute_offset = offsetof (LsmMathmlPresentationToken, math_family),
		.trait_class = &lsm_mathml_string_trait_class
	},
	{
		.name = "fontsize",
		.attribute_offset = offsetof (LsmMathmlPresentationToken, math_size),
		.trait_class = &lsm_mathml_length_trait_class,
		.trait_default = &length_default
	},
	{
		.name = "fontstyle",
		.attribute_offset = offsetof (LsmMathmlPresentationToken, font_style),
		.trait_class = &lsm_mathml_font_style_trait_class,
		.trait_default = &font_style_default
	},
	{
		.name = "fontweight",
		.attribute_offset = offsetof (LsmMathmlPresentationToken, font_weight),
		.trait_class = &lsm_mathml_font_weight_trait_class,
		.trait_default = &font_weight_default
	},
	{
		.name = "color",
		.attribute_offset = offsetof (LsmMathmlPresentationToken, math_color),
		.trait_class = &lsm_mathml_color_trait_class,
	},
	{
		.name = "background",
		.attribute_offset = offsetof (LsmMathmlPresentationToken, math_background),
		.trait_class = &lsm_mathml_color_trait_class,
	}
};

static void
lsm_mathml_presentation_token_class_init (LsmMathmlPresentationTokenClass *m_token_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (m_token_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (m_token_class);

	parent_class = g_type_class_peek_parent (m_token_class);

	d_node_class->get_node_name = lsm_mathml_presentation_token_get_node_name;
	d_node_class->can_append_child = lsm_mathml_presentation_token_can_append_child;

	m_element_class->layout = lsm_mathml_presentation_token_layout;
	m_element_class->measure = lsm_mathml_presentation_token_measure;
	m_element_class->render = lsm_mathml_presentation_token_render;
	m_element_class->is_inferred_row = NULL;
	m_element_class->attribute_manager = lsm_attribute_manager_duplicate (m_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (m_element_class->attribute_manager,
					      G_N_ELEMENTS (_attribute_infos),
					      _attribute_infos);

	m_element_class->update = lsm_mathml_presentation_token_update;

	m_token_class->get_text = _get_text;
}

G_DEFINE_TYPE (LsmMathmlPresentationToken, lsm_mathml_presentation_token, LSM_TYPE_MATHML_ELEMENT)
