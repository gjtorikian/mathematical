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

#include <lsmdebug.h>
#include <lsmmathmlstringelement.h>
#include <lsmmathmlview.h>

static GObject *parent_class;

/* LsmDomNode implementation */

static const char *
lsm_mathml_string_element_get_node_name (LsmDomNode *node)
{
	return "ms";
}

/* LsmMathmlElement implementation */

static void
lsm_mathml_string_element_update (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LSM_MATHML_ELEMENT_CLASS (parent_class)->update (self, style);
}

/* LsmMathmlPresentationToken implementation */

static char *
lsm_mathml_string_element_get_text (LsmMathmlPresentationToken *token)
{
	LsmMathmlStringElement *string = LSM_MATHML_STRING_ELEMENT (token);
	char *token_text;
	char *text;

	token_text = LSM_MATHML_PRESENTATION_TOKEN_CLASS (parent_class)->get_text (token);

	text = g_strdup_printf ("%s%s%s",
				string->left_quote.value != NULL ? string->left_quote.value : "",
				token_text != NULL ? token_text : "",
				string->right_quote.value != NULL ? string->right_quote.value : "");

	g_free (token_text);

	return text;
}

/* LsmMathmlStringElement implementation */

static const char *quote_default = "\"";

LsmDomNode *
lsm_mathml_string_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_STRING_ELEMENT, NULL);
}

static void
lsm_mathml_string_element_init (LsmMathmlStringElement *self)
{
	self->left_quote.value = g_strdup (quote_default);
	self->right_quote.value = g_strdup (quote_default);
}

/* LsmMathmlStringElement class */

static const LsmAttributeInfos _attribute_infos[] = {
	{
		.name = "lquote",
		.attribute_offset = offsetof (LsmMathmlStringElement, left_quote),
		.trait_class = &lsm_mathml_string_trait_class,
		.trait_default = &quote_default
	},
	{
		.name = "rquote",
		.attribute_offset = offsetof (LsmMathmlStringElement, right_quote),
		.trait_class = &lsm_mathml_string_trait_class,
		.trait_default = &quote_default
	}
};

static void
lsm_mathml_string_element_class_init (LsmMathmlStringElementClass *string_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (string_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (string_class);
	LsmMathmlPresentationTokenClass *m_token_class = LSM_MATHML_PRESENTATION_TOKEN_CLASS (string_class);

	parent_class = g_type_class_peek_parent (string_class);

	d_node_class->get_node_name = lsm_mathml_string_element_get_node_name;

	m_element_class->update = lsm_mathml_string_element_update;
	m_element_class->attribute_manager = lsm_attribute_manager_duplicate (m_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (m_element_class->attribute_manager,
					      G_N_ELEMENTS (_attribute_infos),
					      _attribute_infos);

	m_token_class->get_text = lsm_mathml_string_element_get_text;
}

G_DEFINE_TYPE (LsmMathmlStringElement, lsm_mathml_string_element, LSM_TYPE_MATHML_PRESENTATION_TOKEN)

