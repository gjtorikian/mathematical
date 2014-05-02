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

#ifndef LSM_MATHML_PRESENTATION_TOKEN_H
#define LSM_MATHML_PRESENTATION_TOKEN_H

#include <lsmmathmltypes.h>
#include <lsmmathmlelement.h>

G_BEGIN_DECLS

typedef enum {
	LSM_MATHML_PRESENTATION_TOKEN_TYPE_NUMBER,
	LSM_MATHML_PRESENTATION_TOKEN_TYPE_IDENTIFIER,
	LSM_MATHML_PRESENTATION_TOKEN_TYPE_TEXT
} LsmMathmlPresentationTokenType;

#define LSM_TYPE_MATHML_PRESENTATION_TOKEN             (lsm_mathml_presentation_token_get_type ())
#define LSM_MATHML_PRESENTATION_TOKEN(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_MATHML_PRESENTATION_TOKEN, LsmMathmlPresentationToken))
#define LSM_MATHML_PRESENTATION_TOKEN_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_MATHML_PRESENTATION_TOKEN, LsmMathmlPresentationTokenClass))
#define LSM_IS_MATHML_PRESENTATION_TOKEN(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_MATHML_PRESENTATION_TOKEN))
#define LSM_IS_MATHML_PRESENTATION_TOKEN_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_MATHML_PRESENTATION_TOKEN))
#define LSM_MATHML_PRESENTATION_TOKEN_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_MATHML_PRESENTATION_TOKEN, LsmMathmlPresentationTokenClass))

typedef struct _LsmMathmlPresentationTokenClass LsmMathmlPresentationTokenClass;

struct _LsmMathmlPresentationToken {
	LsmMathmlElement	element;

	LsmMathmlPresentationTokenType type;

	LsmMathmlStringAttribute	math_family;
	LsmMathmlEnumAttribute		math_variant;
	LsmMathmlLengthAttribute	math_size;
	LsmMathmlColorAttribute		math_color;
	LsmMathmlColorAttribute		math_background;

	/* Deprecated style attributes */

	LsmMathmlEnumAttribute font_weight;
	LsmMathmlEnumAttribute font_style;
};

struct _LsmMathmlPresentationTokenClass {
	LsmMathmlElementClass  parent_class;

	char * (*get_text)	(LsmMathmlPresentationToken *self);
};

GType lsm_mathml_presentation_token_get_type (void);

LsmDomNode *	lsm_mathml_number_element_new (void);
LsmDomNode *	lsm_mathml_identifier_element_new (void);
LsmDomNode *	lsm_mathml_text_element_new (void);

/* Extra functions */

char *		lsm_mathml_presentation_token_get_text 	(LsmMathmlPresentationToken *self);

G_END_DECLS

#endif

