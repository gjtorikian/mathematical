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

#ifndef LSM_SVG_ELEMENT_H
#define LSM_SVG_ELEMENT_H

#include <lsmsvgtypes.h>
#include <lsmsvgattributes.h>
#include <lsmsvgstyle.h>
#include <lsmdom.h>
#include <cairo.h>

G_BEGIN_DECLS

#define LSM_TYPE_SVG_ELEMENT             (lsm_svg_element_get_type ())
#define LSM_SVG_ELEMENT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_SVG_ELEMENT, LsmSvgElement))
#define LSM_SVG_ELEMENT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_SVG_ELEMENT, LsmSvgElementClass))
#define LSM_IS_SVG_ELEMENT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_SVG_ELEMENT))
#define LSM_IS_SVG_ELEMENT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_SVG_ELEMENT))
#define LSM_SVG_ELEMENT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_SVG_ELEMENT, LsmSvgElementClass))

typedef struct _LsmSvgElementClass LsmSvgElementClass;

struct _LsmSvgElement {
	LsmDomElement	element;

	LsmPropertyBag property_bag;

	LsmAttribute			id;
	LsmAttribute			class_name;
};

struct _LsmSvgElementClass {
	LsmDomElementClass  parent_class;

	LsmAttributeManager *attribute_manager;

	LsmSvgElementCategory category;

	void		(*enable_rendering)		(LsmSvgElement *element);
	void 		(*render)			(LsmSvgElement *element, LsmSvgView *view);
	void 		(*get_extents)			(LsmSvgElement *element, LsmSvgView *view, LsmExtents *extents);
	void 		(*transformed_render)		(LsmSvgElement *element, LsmSvgView *view);
	void 		(*transformed_get_extents)	(LsmSvgElement *element, LsmSvgView *view, LsmExtents *extents);

	gboolean is_shape_element;
};

GType lsm_svg_element_get_type (void);

LsmSvgElementCategory	lsm_svg_element_get_category	(LsmSvgElement *element);

void 		lsm_svg_element_render 				(LsmSvgElement *element, LsmSvgView *view);
void 		lsm_svg_element_render 				(LsmSvgElement *element, LsmSvgView *view);
void 		lsm_svg_element_force_render 			(LsmSvgElement *element, LsmSvgView *view);
void		lsm_svg_element_get_extents			(LsmSvgElement *element, LsmSvgView *view, LsmExtents *extents);
void 		lsm_svg_element_transformed_get_extents 	(LsmSvgElement *element, LsmSvgView *view, LsmExtents *extents);

G_END_DECLS

#endif
