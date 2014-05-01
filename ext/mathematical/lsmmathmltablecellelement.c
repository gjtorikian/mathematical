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

#include <lsmmathmltablecellelement.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_mathml_table_cell_get_node_name (LsmDomNode *node)
{
	return "mtd";
}

/* LsmMathmlElement implementation */

static const LsmMathmlBbox *
lsm_mathml_table_cell_element_measure (LsmMathmlElement *self, LsmMathmlView *view, const LsmMathmlBbox *bbox)
{
	LSM_MATHML_ELEMENT_CLASS (parent_class)->measure (self, view, bbox);

	return &self->bbox;
}

static void
lsm_mathml_table_cell_element_layout (LsmMathmlElement *self, LsmMathmlView *view,
				double x, double y, const LsmMathmlBbox *bbox)
{
	LSM_MATHML_ELEMENT_CLASS (parent_class)->layout (self, view, x, y, bbox);
}

/* LsmMathmlTableCellElement implementation */

void
lsm_mathml_table_cell_element_get_spans (const LsmMathmlTableCellElement *self,
				      unsigned int *row_span,
				      unsigned int *column_span)
{
	if (row_span != NULL)
		*row_span = 0;
	if (column_span != NULL)
		*column_span = 0;

	g_return_if_fail (LSM_IS_MATHML_TABLE_CELL_ELEMENT (self));

	if (row_span != NULL)
		*row_span = self->row_span.value;
	if (column_span != NULL)
		*column_span = self->column_span.value;
}

static const unsigned int span_default = 1;

LsmDomNode *
lsm_mathml_table_cell_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_TABLE_CELL_ELEMENT, NULL);
}

static void
lsm_mathml_table_cell_element_init (LsmMathmlTableCellElement *self)
{
}

/* LsmMathmlTableCellElement class */

static const LsmAttributeInfos _attribute_infos[] = {
	{
		.name = "rowspan",
		.attribute_offset = offsetof (LsmMathmlTableCellElement, row_span),
		.trait_class = &lsm_mathml_unsigned_trait_class,
		.trait_default = &span_default
	},
	{
		.name = "columnspan",
		.attribute_offset = offsetof (LsmMathmlTableCellElement, column_span),
		.trait_class = &lsm_mathml_unsigned_trait_class,
		.trait_default = &span_default
	}
};

static void
lsm_mathml_table_cell_element_class_init (LsmMathmlTableCellElementClass *table_cell_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (table_cell_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (table_cell_class);

	parent_class = g_type_class_peek_parent (table_cell_class);

	d_node_class->get_node_name = lsm_mathml_table_cell_get_node_name;

	m_element_class->measure = lsm_mathml_table_cell_element_measure;
	m_element_class->layout = lsm_mathml_table_cell_element_layout;
	m_element_class->attribute_manager = lsm_attribute_manager_duplicate (m_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (m_element_class->attribute_manager,
					      G_N_ELEMENTS (_attribute_infos),
					      _attribute_infos);
}

G_DEFINE_TYPE (LsmMathmlTableCellElement, lsm_mathml_table_cell_element, LSM_TYPE_MATHML_ELEMENT)
