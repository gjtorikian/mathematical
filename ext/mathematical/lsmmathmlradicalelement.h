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

#ifndef LSM_MATHML_RADICAL_ELEMENT_H
#define LSM_MATHML_RADICAL_ELEMENT_H

#include <lsmmathmltypes.h>
#include <lsmmathmlelement.h>

G_BEGIN_DECLS

typedef enum {
	LSM_MATHML_RADICAL_ELEMENT_TYPE_SQRT,
	LSM_MATHML_RADICAL_ELEMENT_TYPE_ROOT
} LsmMathmlRadicalElementType;

#define LSM_TYPE_MATHML_RADICAL_ELEMENT             (lsm_mathml_radical_element_get_type ())
#define LSM_MATHML_RADICAL_ELEMENT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_MATHML_RADICAL_ELEMENT, LsmMathmlRadicalElement))
#define LSM_MATHML_RADICAL_ELEMENT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_MATHML_RADICAL_ELEMENT, LsmMathmlRadicalElementClass))
#define LSM_IS_MATHML_RADICAL_ELEMENT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_MATHML_RADICAL_ELEMENT))
#define LSM_IS_MATHML_RADICAL_ELEMENT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_MATHML_RADICAL_ELEMENT))
#define LSM_MATHML_RADICAL_ELEMENT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_MATHML_RADICAL_ELEMENT, LsmMathmlRadicalElementClass))

typedef struct _LsmMathmlRadicalElementClass LsmMathmlRadicalElementClass;

struct _LsmMathmlRadicalElement {
	LsmMathmlElement	element;

	LsmMathmlRadicalElementType type;

	/* View properties */

	LsmMathmlBbox bbox;
	double width;
	double radical_x_offset;
	double order_y_offset;
};

struct _LsmMathmlRadicalElementClass {
	LsmMathmlElementClass  parent_class;
};

GType lsm_mathml_radical_element_get_type (void);

LsmDomNode * 	lsm_mathml_root_element_new 	(void);
LsmDomNode * 	lsm_mathml_sqrt_element_new 	(void);

G_END_DECLS

#endif

