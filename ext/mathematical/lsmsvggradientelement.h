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

#ifndef LSM_SVG_GRADIENT_ELEMENT_H
#define LSM_SVG_GRADIENT_ELEMENT_H

#include <lsmsvgtypes.h>
#include <lsmsvgelement.h>

G_BEGIN_DECLS

typedef struct {
	LsmSvgMatrix transform;
	LsmSvgPatternUnits units;
	LsmSvgSpreadMethod spread_method;
} LsmSvgGradientElementAttributes;

#define LSM_TYPE_SVG_GRADIENT_ELEMENT             (lsm_svg_gradient_element_get_type ())
#define LSM_SVG_GRADIENT_ELEMENT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_SVG_GRADIENT_ELEMENT, LsmSvgGradientElement))
#define LSM_SVG_GRADIENT_ELEMENT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_SVG_GRADIENT_ELEMENT, LsmSvgGradientElementClass))
#define LSM_IS_SVG_GRADIENT_ELEMENT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_SVG_GRADIENT_ELEMENT))
#define LSM_IS_SVG_GRADIENT_ELEMENT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_SVG_GRADIENT_ELEMENT))
#define LSM_SVG_GRADIENT_ELEMENT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_SVG_GRADIENT_ELEMENT, LsmSvgGradientElementClass))

typedef struct _LsmSvgGradientElementClass LsmSvgGradientElementClass;

struct _LsmSvgGradientElement {
	LsmSvgElement element;

	LsmSvgTransformAttribute transform;
	LsmSvgPatternUnitsAttribute units;
	LsmSvgSpreadMethodAtttribute spread_method;
	LsmAttribute href;

	gboolean enable_rendering;
};

struct _LsmSvgGradientElementClass {
	LsmSvgElementClass  element_class;

	LsmSvgGradientElement * (*create_gradient)	(LsmSvgElement *self, LsmSvgView *view);
};

GType lsm_svg_gradient_element_get_type (void);

G_END_DECLS

#endif
