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

#ifndef LSM_MATHML_ACTION_ELEMENT_H
#define LSM_MATHML_ACTION_ELEMENT_H

#include <lsmmathmltypes.h>
#include <lsmmathmlpresentationcontainer.h>

G_BEGIN_DECLS

#define LSM_TYPE_MATHML_ACTION_ELEMENT             (lsm_mathml_action_element_get_type ())
#define LSM_MATHML_ACTION_ELEMENT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_MATHML_ACTION_ELEMENT, LsmMathmlActionElement))
#define LSM_MATHML_ACTION_ELEMENT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_MATHML_ACTION_ELEMENT, LsmMathmlActionElementClass))
#define LSM_IS_MATHML_ACTION_ELEMENT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_MATHML_ACTION_ELEMENT))
#define LSM_IS_MATHML_ACTION_ELEMENT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_MATHML_ACTION_ELEMENT))
#define LSM_MATHML_ACTION_ELEMENT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_MATHML_ACTION_ELEMENT, LsmMathmlActionElementClass))

typedef struct _LsmMathmlActionElementClass LsmMathmlActionElementClass;

struct _LsmMathmlActionElement {
	LsmMathmlPresentationContainer presentation_container;
};

struct _LsmMathmlActionElementClass {
	LsmMathmlPresentationContainerClass parent_class;
};

GType lsm_mathml_action_element_get_type (void);

LsmDomNode *lsm_mathml_action_element_new (void);

G_END_DECLS

#endif


