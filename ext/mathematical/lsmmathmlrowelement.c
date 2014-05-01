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

#include <lsmmathmlrowelement.h>

/* LsmDomNode implementation */

static const char *
lsm_mathml_row_element_get_node_name (LsmDomNode *node)
{
	return "mrow";
}

/* LsmMathmlRowElement implementation */

LsmDomNode *
lsm_mathml_row_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_ROW_ELEMENT, NULL);
}

static void
lsm_mathml_row_element_init (LsmMathmlRowElement *element)
{
}

/* LsmMathmlRowElement class */

static void
lsm_mathml_row_element_class_init (LsmMathmlRowElementClass *klass)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (klass);

	d_node_class->get_node_name = lsm_mathml_row_element_get_node_name;
}

G_DEFINE_TYPE (LsmMathmlRowElement, lsm_mathml_row_element, LSM_TYPE_MATHML_PRESENTATION_CONTAINER)

