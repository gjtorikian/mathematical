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

#include <lsmmathmltableelement.h>
#include <lsmmathmltablerowelement.h>
#include <lsmmathmloperatorelement.h>
#include <lsmmathmlview.h>

#define LSM_MATHML_TABLE_ELEMENT_LINE_WIDTH 1 /* 1 pt */

static const gboolean equal_default = FALSE;
static const LsmMathmlLine frame_default = LSM_MATHML_LINE_NONE;
static int row_align_values[1] = {LSM_MATHML_ROW_ALIGN_BASELINE};
static const LsmMathmlEnumList row_align_default = {.n_values = 1, .values = row_align_values};
static int column_align_values[1] = {LSM_MATHML_COLUMN_ALIGN_CENTER};
static const LsmMathmlEnumList column_align_default = {.n_values = 1, .values = column_align_values};
static LsmMathmlSpace row_spacing_values[1] = {
	{.name = LSM_MATHML_SPACE_NAME_ERROR, .length = {.unit = LSM_MATHML_UNIT_EX, .value = 1.0}}
};
static const LsmMathmlSpaceList row_spacing_default = {.n_spaces = 1, .spaces = row_spacing_values};
static LsmMathmlSpace column_spacing_values[1] = {
	{.name = LSM_MATHML_SPACE_NAME_ERROR, .length = {.unit = LSM_MATHML_UNIT_EM, .value = 0.8}}
};
static const LsmMathmlSpaceList column_spacing_default = {.n_spaces = 1, .spaces = column_spacing_values};
static int lines_values[1] = {LSM_MATHML_LINE_NONE};
static const LsmMathmlEnumList lines_default = {.n_values = 1, .values = lines_values};
static LsmMathmlSpace frame_spacing_values[2] = {
	{.name = LSM_MATHML_SPACE_NAME_ERROR, .length = {.unit = LSM_MATHML_UNIT_EM, .value = 0.4}},
	{.name = LSM_MATHML_SPACE_NAME_ERROR, .length = {.unit = LSM_MATHML_UNIT_EX, .value = 0.5}}
};
static const LsmMathmlSpaceList frame_spacing_default = {.n_spaces = 2, .spaces = frame_spacing_values};

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_mathml_table_get_node_name (LsmDomNode *node)
{
	return "mtable";
}

static gboolean
lsm_mathml_table_element_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	return LSM_IS_MATHML_TABLE_ROW_ELEMENT (child);
}

/* LsmMathmlElement implementation */

static void
lsm_mathml_table_element_update (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmMathmlTableElement *table = LSM_MATHML_TABLE_ELEMENT (self);

	lsm_mathml_space_list_attribute_normalize (&table->row_spacing, 0.0, &row_spacing_default, style);
	lsm_mathml_space_list_attribute_normalize (&table->column_spacing, 0.0, &column_spacing_default, style);
	lsm_mathml_space_list_attribute_normalize (&table->frame_spacing, 0.0, &frame_spacing_default, style);
}

static const LsmMathmlBbox *
lsm_mathml_table_element_measure (LsmMathmlElement *self, LsmMathmlView *view, const LsmMathmlBbox *bbox)
{
	LsmMathmlTableElement *table = LSM_MATHML_TABLE_ELEMENT (self);
	LsmDomNode *row_node;
	LsmDomNode *cell_node;
	const LsmMathmlBbox *cell_bbox;
	unsigned int row, column;
	unsigned int max_index;
	double max_height = 0.0;
	double max_width = 0.0;
	double max_depth = 0.0;
	double height;
	gboolean stretchy_found = FALSE;

	table->line_width = LSM_MATHML_TABLE_ELEMENT_LINE_WIDTH;

	g_free (table->widths);
	g_free (table->heights);
	g_free (table->depths);

	table->n_columns = 0;
	table->n_rows = 0;

	self->bbox = lsm_mathml_bbox_null;

	/* Count the number of columns and rows */

	for (row_node = LSM_DOM_NODE (self)->first_child;
	     row_node != NULL;
	     row_node = row_node->next_sibling) {
		unsigned int counter = 0;

		for (cell_node = row_node->first_child;
		     cell_node != NULL;
		     cell_node = cell_node->next_sibling)
			counter++;
		table->n_rows++;
		if (table->n_columns < counter)
			table->n_columns = counter;
	}

	if (table->n_rows < 1 || table->n_columns < 1) {
		table->n_columns = 0;
		table->n_rows = 0;
		return &self->bbox;
	}

	self->bbox.is_defined = TRUE;

	table->widths = g_new (double, table->n_columns);
	table->heights = g_new (double, table->n_rows);
	table->depths = g_new (double, table->n_rows);

	/* Calculate maximum height for each row and maximum width for each column */

	row = 0;
	for (row_node = LSM_DOM_NODE (self)->first_child;
	     row_node != NULL;
	     row_node = row_node->next_sibling) {
		column = 0;
		table->heights[row] = 0.0;
		table->depths[row] = 0.0;
		for (cell_node = row_node->first_child;
		     cell_node != NULL;
		     cell_node = cell_node->next_sibling) {
			cell_bbox = lsm_mathml_element_measure (LSM_MATHML_ELEMENT (cell_node), view, NULL);
			max_width = MAX (max_width, cell_bbox->width);
			max_height = MAX (max_height, cell_bbox->height);
			max_depth = MAX (max_depth, cell_bbox->depth);
			if (row == 0)
				table->widths[column] = cell_bbox->width;
			else
				table->widths[column] = MAX (table->widths[column], cell_bbox->width);
			if (column == 0) {
				table->heights[row] = cell_bbox->height;
				table->depths[row] = cell_bbox->depth;
			} else {
				table->heights[row] = MAX (table->heights[row], cell_bbox->height);
				table->depths[row]  = MAX (table->depths[row],  cell_bbox->depth);
			}

			if (!stretchy_found) {
				const LsmMathmlOperatorElement *operator;

				operator = lsm_mathml_element_get_embellished_core (LSM_MATHML_ELEMENT (cell_node));
				if (operator != NULL && operator->stretchy.value)
					stretchy_found = TRUE;
			}

			column++;
		}
		row++;
	}

	/* All rows have the same height ? */

	if (table->equal_rows.value)
		for (row = 0; row < table->n_rows; row++) {
			table->heights[row] = max_height;
			table->depths[row] = max_depth;
		}

	/* All columns have the same width ? */

	if (table->equal_columns.value)
		for (column = 0; column < table->n_columns; column++)
			table->widths[column] = max_width;

	max_index = table->column_spacing.n_values -  1;
	for (column = 0; column < table->n_columns; column++) {
		self->bbox.width += table->widths[column];
		if (column < table->n_columns - 1)
			self->bbox.width += table->column_spacing.values[MIN (column, max_index)];
	}

	height = 0.0;

	max_index = table->row_spacing.n_values -  1;
	for (row = 0; row < table->n_rows; row++) {
		height += table->heights[row] + table->depths[row];
		if (row < table->n_rows - 1)
			height += table->row_spacing.values[MIN (row, max_index)];
	}

	height += 2 * table->frame_spacing.values[1];

	/* Add the line widths to the table bbox */

	self->bbox.width += table->line_width * (1 + table->n_columns);
	height += table->line_width * (1 + table->n_rows);

	/* Center vertically */

	self->bbox.height = 0.5 * height;
	self->bbox.depth = height - self->bbox.height;

	self->bbox.width += 2 * table->frame_spacing.values[0];

	{
		double axis_offset;
		double length;

		axis_offset = lsm_mathml_view_measure_axis_offset (view, self->style.math_size);
		length = (self->bbox.height + self->bbox.depth) * 0.5;
		self->bbox.height = axis_offset + length;
		self->bbox.depth = length - axis_offset;
	}

	if (stretchy_found) {
		const LsmMathmlOperatorElement *operator;
		LsmMathmlBbox stretch_bbox;

		row = 0;
		for (row_node = LSM_DOM_NODE (self)->first_child;
		     row_node != NULL;
		     row_node = row_node->next_sibling) {
			column = 0;
			for (cell_node = row_node->first_child;
			     cell_node != NULL;
			     cell_node = cell_node->next_sibling) {
				operator = lsm_mathml_element_get_embellished_core (LSM_MATHML_ELEMENT (cell_node));
				if (operator != NULL && operator->stretchy.value) {
					stretch_bbox.width = table->widths[column];
					stretch_bbox.height = table->heights[row];
					stretch_bbox.depth = table->depths[row];
					lsm_mathml_element_measure (LSM_MATHML_ELEMENT (cell_node), view,
								 &stretch_bbox);
				}
				column++;
			}
			row++;
		}
	}

	return &self->bbox;
}

static void
lsm_mathml_table_element_layout (LsmMathmlElement *self, LsmMathmlView *view,
				double x, double y, const LsmMathmlBbox *bbox)
{
	LsmMathmlTableElement *table = LSM_MATHML_TABLE_ELEMENT (self);
	LsmDomNode *row_node, *cell_node;
	double y_offset, x_offset;
	unsigned int max_column;
	unsigned int max_row;
	unsigned int row, column;
	double x_cell, y_cell;

	if (table->n_rows < 1 || table->n_columns < 1)
		return;

	max_column = table->column_spacing.n_values -  1;
	max_row = table->row_spacing.n_values -  1;

	y_offset = -self->bbox.height;
        y_offset += table->frame_spacing.values[1];
	y_offset += table->line_width;

	row = 0;
	for (row_node = LSM_DOM_NODE (self)->first_child;
	     row_node != NULL;
	     row_node = row_node->next_sibling) {
		column = 0;
		x_offset = table->frame_spacing.values[0];
		x_offset += table->line_width;
		for (cell_node = row_node->first_child;
		     cell_node != NULL;
		     cell_node = cell_node->next_sibling) {
			bbox = lsm_mathml_element_get_bbox (LSM_MATHML_ELEMENT (cell_node));

			switch (table->row_align.enum_list.values[MIN (row,
								       table->row_align.enum_list.n_values - 1)]) {
				case LSM_MATHML_ROW_ALIGN_TOP:
					y_cell = y + y_offset + bbox->height;
					break;
				case LSM_MATHML_ROW_ALIGN_BOTTOM:
					y_cell = y + y_offset + table->heights[row] + table->depths[row] -
						bbox->depth;
					break;
				case LSM_MATHML_ROW_ALIGN_CENTER:
					y_cell = y + y_offset + (table->heights[row] +
								 table->depths[row] -
								 bbox->height - bbox->depth) * 0.5 +
						bbox->height;
					break;
				default:
					y_cell = y + y_offset + table->heights[row];
			}

			switch (table->column_align.enum_list.values[MIN (column,
									  table->column_align.enum_list.n_values
									  - 1)]) {
				case LSM_MATHML_COLUMN_ALIGN_LEFT:
					x_cell = x + x_offset;
					break;
				case LSM_MATHML_COLUMN_ALIGN_RIGHT:
					x_cell = x + x_offset + table->widths[column] - bbox->width;
					break;
				default:
					x_cell = x + x_offset + (table->widths[column] - bbox->width) * 0.5;
			}

			lsm_mathml_element_layout (LSM_MATHML_ELEMENT (cell_node), view,
						x_cell, y_cell, bbox);

			if (column < table->n_columns - 1) {
				x_offset += table->widths[column];
				x_offset += table->column_spacing.values[MIN (column, max_column)];
				x_offset += table->line_width;
				column++;
			}
		}

		if (row < table->n_rows - 1) {
			y_offset += table->heights[row] + table->depths[row];
			y_offset += table->row_spacing.values[MIN (row, max_row)];
			y_offset += table->line_width;
			row++;
		}
	}
}

static void
lsm_mathml_table_element_render (LsmMathmlElement *self, LsmMathmlView *view)
{
	LsmMathmlTableElement *table = LSM_MATHML_TABLE_ELEMENT (self);
	double x, y;
	double x0, y0, x1, y1;
	double position;
	double spacing;
	unsigned int i;

	if (table->n_rows < 1 || table->n_columns < 1)
		return;

	x0 = self->x + 0.5 * table->line_width;
	y0 = self->y - self->bbox.height + 0.5 * table->line_width;
	x1 = x0 + self->bbox.width - table->line_width;
	y1 = y0 + self->bbox.height + self->bbox.depth - table->line_width;

	lsm_mathml_view_show_rectangle (view, &self->style,
				     x0, y0, x1 - x0, y1 - y0,
				     table->frame.value, table->line_width);

	position  = self->y - self->bbox.height;
        position += table->frame_spacing.values[1];
	position += table->line_width;

	for (i = 0; i < table->n_rows - 1; i++) {
		position += table->heights[i] + table->depths[i];
		spacing = table->row_spacing.values[MIN (i, table->row_spacing.n_values - 1)];
		y = position + (0.5 * spacing) + table->line_width * 0.5;
		lsm_mathml_view_show_line (view, &self->style,
					x0, y, x1, y,
					table->row_lines.enum_list.values[MIN (i,
									       table->row_lines.enum_list.n_values
									       - 1)],
					table->line_width);
		position += spacing + table->line_width;
	}

	position  = self->x;
        position += table->frame_spacing.values[0];
	position += table->line_width;

	for (i = 0; i < table->n_columns - 1; i++) {
		position += table->widths[i];
		spacing = table->column_spacing.values[MIN (i, table->column_spacing.n_values - 1)];
		x = position + 0.5 * (spacing + table->line_width);
		lsm_mathml_view_show_line (view, &self->style,
					x, y0, x, y1,
					table->column_lines.enum_list.values[MIN (i,
										  table->column_lines.enum_list.n_values
										  - 1)],
					table->line_width);
		position += spacing + table->line_width;
	}

	LSM_MATHML_ELEMENT_CLASS (parent_class)->render (self, view);
}

/* LsmMathmlTableElement implementation */

LsmDomNode *
lsm_mathml_table_element_new (void)
{
	return g_object_new (LSM_TYPE_MATHML_TABLE_ELEMENT, NULL);
}

static void
lsm_mathml_table_element_init (LsmMathmlTableElement *table)
{
	table->widths = NULL;
	table->heights = NULL;
	table->depths = NULL;
	table->n_columns = 0;
	table->n_rows = 0;
	table->line_width = 0;

	table->equal_columns.value = equal_default;
	table->equal_rows.value = equal_default;
	table->frame.value = frame_default;

	lsm_mathml_enum_list_init (&table->row_align.enum_list, &row_align_default);
	lsm_mathml_enum_list_init (&table->column_align.enum_list, &column_align_default);
	lsm_mathml_enum_list_init (&table->row_lines.enum_list, &lines_default);
	lsm_mathml_enum_list_init (&table->column_lines.enum_list, &lines_default);
}

static void
lsm_mathml_table_element_finalize (GObject *object)
{
	LsmMathmlTableElement *table = LSM_MATHML_TABLE_ELEMENT (object);

	g_free (table->widths);
	g_free (table->heights);
	g_free (table->depths);
	table->widths = NULL;
	table->heights = NULL;
	table->depths = NULL;

	g_free (table->row_spacing.values);
	g_free (table->column_spacing.values);
	g_free (table->frame_spacing.values);
	table->row_spacing.values = NULL;
	table->column_spacing.values = NULL;
	table->frame_spacing.values = NULL;

	parent_class->finalize (object);
}

/* LsmMathmlTableElement class */

static const LsmAttributeInfos _attribute_infos[] = {
	{
		.name = "equalrows",
		.attribute_offset = offsetof (LsmMathmlTableElement, equal_rows),
		.trait_class = &lsm_mathml_boolean_trait_class,
		.trait_default = &equal_default
	},
	{
		.name = "equalcolumns",
		.attribute_offset = offsetof (LsmMathmlTableElement, equal_columns),
		.trait_class = &lsm_mathml_boolean_trait_class,
		.trait_default = &equal_default
	},
	{
		.name = "frame",
		.attribute_offset = offsetof (LsmMathmlTableElement, frame),
		.trait_class = &lsm_mathml_line_trait_class,
		.trait_default = &frame_default
	},
	{
		.name = "rowalign",
		.attribute_offset = offsetof (LsmMathmlTableElement, row_align),
		.trait_class = &lsm_mathml_row_align_list_trait_class,
		.trait_default = &row_align_default
	},
	{
		.name = "columnalign",
		.attribute_offset = offsetof (LsmMathmlTableElement, column_align),
		.trait_class = &lsm_mathml_column_align_list_trait_class,
		.trait_default = &column_align_default
	},
	{
		.name = "rowspacing",
		.attribute_offset = offsetof (LsmMathmlTableElement, row_spacing),
		.trait_class = &lsm_mathml_space_list_trait_class,
		.trait_default = &row_spacing_default
	},
	{
		.name = "columnspacing",
		.attribute_offset = offsetof (LsmMathmlTableElement, column_spacing),
		.trait_class = &lsm_mathml_space_list_trait_class,
		.trait_default = &column_spacing_default
	},
	{
		.name = "rowlines",
		.attribute_offset = offsetof (LsmMathmlTableElement, row_lines),
		.trait_class = &lsm_mathml_line_list_trait_class,
		.trait_default = &lines_default
	},
	{
		.name = "columnlines",
		.attribute_offset = offsetof (LsmMathmlTableElement, column_lines),
		.trait_class = &lsm_mathml_line_list_trait_class,
		.trait_default = &lines_default
	},
	{
		.name = "framespacing",
		.attribute_offset = offsetof (LsmMathmlTableElement, frame_spacing),
		.trait_class = &lsm_mathml_space_list_trait_class,
		.trait_default = &frame_spacing_default
	}
};

static void
lsm_mathml_table_element_class_init (LsmMathmlTableElementClass *table_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (table_class);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (table_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (table_class);

	parent_class = g_type_class_peek_parent (table_class);

	object_class->finalize = lsm_mathml_table_element_finalize;

	d_node_class->get_node_name = lsm_mathml_table_get_node_name;
	d_node_class->can_append_child = lsm_mathml_table_element_can_append_child;

	m_element_class->update = lsm_mathml_table_element_update;
	m_element_class->measure = lsm_mathml_table_element_measure;
	m_element_class->layout = lsm_mathml_table_element_layout;
	m_element_class->render = lsm_mathml_table_element_render;
	m_element_class->is_inferred_row = NULL;
	m_element_class->attribute_manager = lsm_attribute_manager_duplicate (m_element_class->attribute_manager);

	lsm_attribute_manager_add_attributes (m_element_class->attribute_manager,
					      G_N_ELEMENTS (_attribute_infos),
					      _attribute_infos);
}

G_DEFINE_TYPE (LsmMathmlTableElement, lsm_mathml_table_element, LSM_TYPE_MATHML_ELEMENT)
