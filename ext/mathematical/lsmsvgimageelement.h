/* Lasem
 *
 * Copyright © 2009-2012 Emmanuel Pacaud
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

#ifndef LSM_SVG_IMAGE_ELEMENT_H
#define LSM_SVG_IMAGE_ELEMENT_H

#include <lsmsvgtypes.h>
#include <lsmsvgtransformable.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

G_BEGIN_DECLS

#define LSM_TYPE_SVG_IMAGE_ELEMENT             (lsm_svg_image_element_get_type ())
#define LSM_SVG_IMAGE_ELEMENT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_SVG_IMAGE_ELEMENT, LsmSvgImageElement))
#define LSM_SVG_IMAGE_ELEMENT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_SVG_IMAGE_ELEMENT, LsmSvgImageElementClass))
#define LSM_IS_SVG_IMAGE_ELEMENT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_SVG_IMAGE_ELEMENT))
#define LSM_IS_SVG_IMAGE_ELEMENT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_SVG_IMAGE_ELEMENT))
#define LSM_SVG_IMAGE_ELEMENT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_SVG_IMAGE_ELEMENT, LsmSvgImageElementClass))

typedef struct _LsmSvgImageElementClass LsmSvgImageElementClass;

struct _LsmSvgImageElement {
	LsmSvgTransformable base;

	LsmSvgLengthAttribute	x;
	LsmSvgLengthAttribute	y;
	LsmSvgLengthAttribute	width;
	LsmSvgLengthAttribute	height;

	LsmAttribute		href;

	LsmSvgPreserveAspectRatioAttribute	preserve_aspect_ratio;

	GdkPixbuf *pixbuf;
};

struct _LsmSvgImageElementClass {
	LsmSvgTransformableClass  base_class;
};

GType lsm_svg_image_element_get_type (void);

LsmDomNode *		lsm_svg_image_element_new 		(void);

G_END_DECLS

#endif
