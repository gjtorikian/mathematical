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

#include <lsmdebug.h>
#include <lsmmathmlradicalelement.h>
#include <lsmmathmlview.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_mathml_radical_get_node_name (LsmDomNode *self)
{
	LsmMathmlRadicalElement *radical = LSM_MATHML_RADICAL_ELEMENT (self);

	if (radical->type == LSM_MATHML_RADICAL_ELEMENT_TYPE_SQRT)
		return "msqrt";

	return "mroot";
}

static gboolean
lsm_mathml_radical_element_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	LsmMathmlRadicalElement *radical = LSM_MATHML_RADICAL_ELEMENT (self);

	if (radical->type == LSM_MATHML_RADICAL_ELEMENT_TYPE_SQRT)
		return LSM_IS_MATHML_ELEMENT (child);

	return LSM_IS_MATHML_ELEMENT (child) && (self->first_child == NULL ||
					      self->first_child->next_sibling == NULL);
}

/* LsmMathmlElement implementation */

static gboolean
lsm_mathml_radical_element_update_children (LsmMathmlElement *self, LsmMathmlStyle *style)
{
	LsmMathmlRadicalElement *radical = LSM_MATHML_RADICAL_ELEMENT (self);
	LsmDomNode *node;

	if (radical->type == LSM_MATHML_RADICAL_ELEMENT_TYPE_SQRT)
		return LSM_MATHML_ELEMENT_CLASS (parent_class)->update_children (self, style);

	node = LSM_DOM_NODE (self)->first_child;
	if (node != NULL) {
		gboolean need_measure;

		need_measure = lsm_mathml_element_update (LSM_MATHML_ELEMENT (node), style);

		node = node->next_sibling;
		if (node != NULL) {
			lsm_mathml_style_change_script_level (style, +2);
			style->display = LSM_MATHML_DISPLAY_INLINE;

			if (lsm_mathml_element_update (LSM_MATHML_ELEMENT (node), style))
				need_measure = TRUE;
		}

		return need_measure;
	}

	return FALSE;
}

static const LsmMathmlBbox *
lsm_mathml_radical_element_measure (LsmMathmlElement *self, LsmMathmlView *view, const LsmMathmlBbox *bbox)
{
	LsmMathmlRadicalElement *radical = LSM_MATHML_RADICAL_ELEMENT (self);
	LsmMathmlBbox stretch_bbox;
	LsmDomNode *node;
	double x_offset = 0.0;
	double y_offset = 0.0;

	node = LSM_DOM_NODE (self)->first_child;
	if (node == NULL) {
		stretch_bbox.width = 0;
		stretch_bbox.height = self->style.math_size;
		stretch_bbox.depth = 0;
		stretch_bbox.is_defined = TRUE;

		lsm_mathml_view_measure_radical (view, &self->style,
					      &stretch_bbox, &radical->bbox, NULL, NULL);
		self->bbox = radical->bbox;
		return &self->bbox;
	}

	node = LSM_DOM_NODE (self)->first_child;

	if (radical->type == LSM_MATHML_RADICAL_ELEMENT_TYPE_SQRT)
		LSM_MATHML_ELEMENT_CLASS (parent_class)->measure (self, view, &lsm_mathml_bbox_null);
	else
		self->bbox = *lsm_mathml_element_measure (LSM_MATHML_ELEMENT (node), view, NULL);

	stretch_bbox = self->bbox;

	radical->width = self->bbox.width;
	radical->radical_x_offset = 0.0;
	radical->order_y_offset = 0.0;

	lsm_mathml_view_measure_radical (view, &self->style,
				      &stretch_bbox, &radical->bbox,
				      &x_offset, &y_offset);

	lsm_mathml_bbox_add_horizontally (&self->bbox, &radical->bbox);

	lsm_debug_measure ("[LsmMathmlRadicalElement::measure] Radical bbox w = %g, h = %g, d = %g",
		    radical->bbox.width, radical->bbox.height, radical->bbox.depth);

	if (radical->type == LSM_MATHML_RADICAL_ELEMENT_TYPE_ROOT) {

		node = node->next_sibling;

		if (node != NULL) {
			LsmMathmlBbox child_bbox;
			double height;

			child_bbox = *lsm_mathml_element_measure (LSM_MATHML_ELEMENT (node), view, NULL);

			radical->radical_x_offset = child_bbox.width - x_offset;
			self->bbox.width += radical->radical_x_offset;

			lsm_debug_measure ("[LsmMathmlRadicalElement::measure] y_offset = %g", y_offset);

			height = self->bbox.height - y_offset + child_bbox.height + child_bbox.depth;
			if (height > self->bbox.height)
				self->bbox.height = height;

			radical->order_y_offset = - self->bbox.height + child_bbox.height;

			lsm_debug_measure ("[LsmMathmlRadicalElement::measure] order_y_offset = %g",
				    radical->order_y_offset);
		}
	}

	return &self->bbox;
}

static void
lsm_mathml_radical_element_layout (LsmMathmlElement *self, LsmMathmlView *view,
				double x, double y, const LsmMathmlBbox *bbox)
{
	LsmMathmlRadicalElement *radical = LSM_MATHML_RADICAL_ELEMENT (self);
	LsmDomNode *node;

	if (radical->type == LSM_MATHML_RADICAL_ELEMENT_TYPE_SQRT)
		LSM_MATHML_ELEMENT_CLASS (parent_class)->layout (self, view, x + radical->bbox.width, y, bbox);
	else {
		node = LSM_DOM_NODE (self)->first_child;

		if (node != NULL) {
			LsmMathmlBbox child_bbox;

			child_bbox = *lsm_mathml_element_get_bbox (LSM_MATHML_ELEMENT (node));

			lsm_mathml_element_layout (LSM_MATHML_ELEMENT (node), view,
						x + radical->bbox.width + radical->radical_x_offset,
						y, &child_bbox);

			node = node->next_sibling;

			if (node != NULL) {
				child_bbox = *lsm_mathml_element_get_bbox (LSM_MATHML_ELEMENT (node));

				lsm_mathml_element_layout (LSM_MATHML_ELEMENT (node), view, x,
							y + radical->order_y_offset,
							&child_bbox);
			}
		}
	}
}

static void
lsm_mathml_radical_element_render (LsmMathmlElement *self, LsmMathmlView *view)
{
	LsmMathmlRadicalElement *radical = LSM_MATHML_RADICAL_ELEMENT (self);

	lsm_mathml_view_show_radical (view, &self->style,
				   self->x + radical->radical_x_offset, self->y,
				   radical->width, &radical->bbox);

	LSM_MATHML_ELEMENT_CLASS (parent_class)->render (self, view);
}

static gboolean
lsm_mathml_radical_element_is_inferred_row (const LsmMathmlElement *self)
{
	return LSM_MATHML_RADICAL_ELEMENT (self)->type == LSM_MATHML_RADICAL_ELEMENT_TYPE_SQRT;
}

/* LsmMathmlRadicalElement implementation */

LsmDomNode *
lsm_mathml_sqrt_element_new (void)
{
	LsmDomNode *node;

	node = g_object_new (LSM_TYPE_MATHML_RADICAL_ELEMENT, NULL);
	g_return_val_if_fail (node != NULL, NULL);

	LSM_MATHML_RADICAL_ELEMENT (node)->type = LSM_MATHML_RADICAL_ELEMENT_TYPE_SQRT;

	return node;
}

LsmDomNode *
lsm_mathml_root_element_new (void)
{
	LsmDomNode *node;

	node = g_object_new (LSM_TYPE_MATHML_RADICAL_ELEMENT, NULL);
	g_return_val_if_fail (node != NULL, NULL);

	LSM_MATHML_RADICAL_ELEMENT (node)->type = LSM_MATHML_RADICAL_ELEMENT_TYPE_ROOT;

	return node;
}

static void
lsm_mathml_radical_element_init (LsmMathmlRadicalElement *self)
{
}

/* LsmMathmlRadicalElement class */

static void
lsm_mathml_radical_element_class_init (LsmMathmlRadicalElementClass *radical_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (radical_class);
	LsmMathmlElementClass *m_element_class = LSM_MATHML_ELEMENT_CLASS (radical_class);

	parent_class = g_type_class_peek_parent (radical_class);

	d_node_class->get_node_name = lsm_mathml_radical_get_node_name;
	d_node_class->can_append_child = lsm_mathml_radical_element_can_append_child;

	m_element_class->update_children = lsm_mathml_radical_element_update_children;
	m_element_class->measure = lsm_mathml_radical_element_measure;
	m_element_class->layout = lsm_mathml_radical_element_layout;
	m_element_class->render = lsm_mathml_radical_element_render;

	m_element_class->is_inferred_row = lsm_mathml_radical_element_is_inferred_row;
}

G_DEFINE_TYPE (LsmMathmlRadicalElement, lsm_mathml_radical_element, LSM_TYPE_MATHML_ELEMENT)
