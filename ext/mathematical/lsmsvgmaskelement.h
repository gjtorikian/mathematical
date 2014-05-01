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

#ifndef LSM_SVG_MASK_ELEMENT_H
#define LSM_SVG_MASK_ELEMENT_H

#include <lsmsvgtypes.h>
#include <lsmsvgelement.h>

G_BEGIN_DECLS

#define LSM_TYPE_SVG_MASK_ELEMENT             (lsm_svg_mask_element_get_type ())
#define LSM_SVG_MASK_ELEMENT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_SVG_MASK_ELEMENT, LsmSvgMaskElement))
#define LSM_SVG_MASK_ELEMENT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_SVG_MASK_ELEMENT, LsmSvgMaskElementClass))
#define LSM_IS_SVG_MASK_ELEMENT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_SVG_MASK_ELEMENT))
#define LSM_IS_SVG_MASK_ELEMENT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_SVG_MASK_ELEMENT))
#define LSM_SVG_MASK_ELEMENT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_SVG_MASK_ELEMENT, LsmSvgMaskElementClass))

typedef struct _LsmSvgMaskElementClass LsmSvgMaskElementClass;

struct _LsmSvgMaskElement {
	LsmSvgElement element;

	LsmSvgLengthAttribute		x;
	LsmSvgLengthAttribute		y;
	LsmSvgLengthAttribute		width;
	LsmSvgLengthAttribute		height;
	LsmSvgPatternUnitsAttribute	units;
	LsmSvgPatternUnitsAttribute	content_units;

	gboolean enable_rendering;
};

struct _LsmSvgMaskElementClass {
	LsmSvgElementClass  element_class;
};

GType lsm_svg_mask_element_get_type (void);

LsmDomNode * 	lsm_svg_mask_element_new 	(void);

G_END_DECLS

#endif
