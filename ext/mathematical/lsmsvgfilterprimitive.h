/* Lasem
 *
 * Copyright © 2010 Emmanuel Pacaud
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

#ifndef LSM_SVG_FILTER_PRIMITIVE_H
#define LSM_SVG_FILTER_PRIMITIVE_H

#include <lsmsvgtypes.h>
#include <lsmsvgelement.h>

G_BEGIN_DECLS

#define LSM_TYPE_SVG_FILTER_PRIMITIVE             (lsm_svg_filter_primitive_get_type ())
#define LSM_SVG_FILTER_PRIMITIVE(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_SVG_FILTER_PRIMITIVE, LsmSvgFilterPrimitive))
#define LSM_SVG_FILTER_PRIMITIVE_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_SVG_FILTER_PRIMITIVE, LsmSvgFilterPrimitiveClass))
#define LSM_IS_SVG_FILTER_PRIMITIVE(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_SVG_FILTER_PRIMITIVE))
#define LSM_IS_SVG_FILTER_PRIMITIVE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_SVG_FILTER_PRIMITIVE))
#define LSM_SVG_FILTER_PRIMITIVE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_SVG_FILTER_PRIMITIVE, LsmSvgFilterPrimitiveClass))

typedef struct _LsmSvgFilterPrimitiveClass LsmSvgFilterPrimitiveClass;

struct _LsmSvgFilterPrimitive {
	LsmSvgElement element;

	LsmSvgLengthAttribute		x;
	LsmSvgLengthAttribute		y;
	LsmSvgLengthAttribute		width;
	LsmSvgLengthAttribute		height;

	LsmAttribute in;
	LsmAttribute result;
};

struct _LsmSvgFilterPrimitiveClass {
	LsmSvgElementClass  element_class;

	void (*apply)		(LsmSvgFilterPrimitive *self, LsmSvgView *view,
				 const char *input, const char *output, const LsmBox *subregion);
};

GType 	lsm_svg_filter_primitive_get_type 	(void);

void 	lsm_svg_filter_primitive_apply 		(LsmSvgFilterPrimitive *self, LsmSvgView *view);

G_END_DECLS

#endif
