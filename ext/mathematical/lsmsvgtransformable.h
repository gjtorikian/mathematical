/* Lasem
 *
 * Copyright © 2007-2012 Emmanuel Pacaud
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

#ifndef LSM_SVG_TRANSFORMABLE_H
#define LSM_SVG_TRANSFORMABLE_H

#include <lsmsvgelement.h>

G_BEGIN_DECLS

#define LSM_TYPE_SVG_TRANSFORMABLE             (lsm_svg_transformable_get_type ())
#define LSM_SVG_TRANSFORMABLE(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_SVG_TRANSFORMABLE, LsmSvgTransformable))
#define LSM_SVG_TRANSFORMABLE_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_SVG_TRANSFORMABLE, LsmSvgTransformableClass))
#define LSM_IS_SVG_TRANSFORMABLE(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_SVG_TRANSFORMABLE))
#define LSM_IS_SVG_TRANSFORMABLE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_SVG_TRANSFORMABLE))
#define LSM_SVG_TRANSFORMABLE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_SVG_TRANSFORMABLE, LsmSvgTransformableClass))

typedef struct _LsmSvgTransformableClass LsmSvgTransformableClass;

struct _LsmSvgTransformable {
	LsmSvgElement	element;

	LsmSvgTransformAttribute 	transform;
};

struct _LsmSvgTransformableClass {
	LsmSvgElementClass  parent_class;
};

GType 	lsm_svg_transformable_get_type 			(void);

G_END_DECLS

#endif
