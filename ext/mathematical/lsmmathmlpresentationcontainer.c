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

#include <lsmmathmlpresentationcontainer.h>
#include <lsmmathmlview.h>

/* LsmMathmlElement implementation */

/* LsmMathmlPresentationContainer implementation */

static void
lsm_mathml_presentation_container_init (LsmMathmlPresentationContainer *container)
{
}

/* LsmMathmlPresentationContainer class */

static void
lsm_mathml_presentation_container_class_init (LsmMathmlPresentationContainerClass *klass)
{
}

G_DEFINE_ABSTRACT_TYPE (LsmMathmlPresentationContainer, lsm_mathml_presentation_container, LSM_TYPE_MATHML_ELEMENT)
