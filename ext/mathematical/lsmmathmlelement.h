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

#ifndef LSM_MATHML_ELEMENT_H
#define LSM_MATHML_ELEMENT_H

#include <lsmdomelement.h>
#include <lsmmathmltypes.h>
#include <lsmmathmlutils.h>
#include <lsmmathmlstyle.h>
#include <lsmmathmlattributes.h>
#include <cairo.h>

G_BEGIN_DECLS

typedef struct {
	char *			math_family;
	LsmMathmlVariant 	math_variant;
	double 			math_size;
	LsmMathmlColor 		math_color;
	LsmMathmlColor 		math_background;
} LsmMathmlElementStyle;

#define LSM_TYPE_MATHML_ELEMENT             (lsm_mathml_element_get_type ())
#define LSM_MATHML_ELEMENT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_MATHML_ELEMENT, LsmMathmlElement))
#define LSM_MATHML_ELEMENT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_MATHML_ELEMENT, LsmMathmlElementClass))
#define LSM_IS_MATHML_ELEMENT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_MATHML_ELEMENT))
#define LSM_IS_MATHML_ELEMENT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_MATHML_ELEMENT))
#define LSM_MATHML_ELEMENT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_MATHML_ELEMENT, LsmMathmlElementClass))

typedef struct _LsmMathmlElementClass LsmMathmlElementClass;

struct _LsmMathmlElement {
	LsmDomElement	element;

	LsmAttribute class_name;
	LsmAttribute id;
	LsmAttribute href;

	LsmMathmlElementStyle style;

	/* View */

	gboolean need_update;
	gboolean need_children_update;
	gboolean need_measure;
	gboolean need_layout;

	double x, y;
	LsmMathmlBbox bbox;
};

struct _LsmMathmlElementClass {
	LsmDomElementClass  parent_class;

	LsmAttributeManager *attribute_manager;

	void				(*update)		(LsmMathmlElement *element, LsmMathmlStyle *style);
	gboolean			(*update_children)	(LsmMathmlElement *element, LsmMathmlStyle *style);
	const LsmMathmlBbox * 		(*measure) 		(LsmMathmlElement *element, LsmMathmlView *view,
								 const LsmMathmlBbox *bbox);
	void 				(*layout) 		(LsmMathmlElement *element, LsmMathmlView *view,
								 double x, double y, const LsmMathmlBbox *bbox);
	void 				(*render)		(LsmMathmlElement *element, LsmMathmlView *view);

	LsmMathmlOperatorElement *	(*get_embellished_core)	(const LsmMathmlElement *self);

	gboolean			(*is_inferred_row)	(const LsmMathmlElement *self);
};

GType lsm_mathml_element_get_type (void);

gboolean		lsm_mathml_element_update 		(LsmMathmlElement *element, const LsmMathmlStyle *style);
const LsmMathmlBbox *	lsm_mathml_element_measure		(LsmMathmlElement *element, LsmMathmlView *view,
								 const LsmMathmlBbox *stretch_bbox);
void 			lsm_mathml_element_layout 		(LsmMathmlElement *element, LsmMathmlView *view,
								 double x, double y, const LsmMathmlBbox *bbox);
void 			lsm_mathml_element_render 		(LsmMathmlElement *element, LsmMathmlView *view);

LsmMathmlOperatorElement *	lsm_mathml_element_get_embellished_core 	(const LsmMathmlElement *self);

const LsmMathmlBbox * 	lsm_mathml_element_get_bbox 		(const LsmMathmlElement *self);
gboolean 		lsm_mathml_element_is_inferred_row 	(const LsmMathmlElement *self);

G_END_DECLS

#endif
