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

#include <lsmmathmllayoututils.h>
#include <lsmmathmloperatorelement.h>
#include <math.h>

void
lsm_mathml_measure_sub_sup (LsmMathmlElement *parent,
			 LsmMathmlView *view,
			 LsmMathmlElement *base,
			 LsmMathmlElement *subscript,
			 LsmMathmlElement *superscript,
			 double subscript_offset_min,
			 double superscript_offset_min,
			 LsmMathmlDisplay display,
			 const LsmMathmlBbox *stretch_bbox,
			 LsmMathmlBbox *bbox,
			 double *subscript_offset,
			 double *superscript_offset)
{
	LsmMathmlBbox const *base_bbox = NULL;
	LsmMathmlBbox const *subscript_bbox = NULL;
	LsmMathmlBbox const *superscript_bbox = NULL;
	LsmMathmlBbox children_bbox = lsm_mathml_bbox_null;
	LsmMathmlOperatorElement *embellished_core;
	double axis_offset, ascent, descent;
	double v_space;
	gboolean is_operator;

	*bbox = lsm_mathml_bbox_null;

	if (base == NULL)
		return;

	embellished_core = lsm_mathml_element_get_embellished_core (base);
	is_operator = embellished_core != NULL;

	/* TODO
	double slant;
	slant = is_operator ? lsm_mathml_operator_element_get_slant (embellished_core, view) : 0.0;
	*/

	axis_offset = lsm_mathml_view_measure_axis_offset (view, parent->style.math_size);
	v_space = parent->style.math_size * LSM_MATHML_SPACE_EM_THIN;
	lsm_mathml_view_get_font_metrics (view, &parent->style, &ascent, &descent);

	if (display == LSM_MATHML_DISPLAY_INLINE)
		descent /= 2.0;

	base_bbox = lsm_mathml_element_measure (LSM_MATHML_ELEMENT (base), view, stretch_bbox);

	*bbox = *base_bbox;

	subscript_bbox = subscript != NULL ? lsm_mathml_element_measure (subscript, view, NULL) : NULL;
	superscript_bbox = superscript != NULL ? lsm_mathml_element_measure (superscript, view, NULL) : NULL;

	if (subscript_bbox != NULL) {
		if (is_operator) {
			*subscript_offset = base_bbox->depth +
				0.5 * lsm_mathml_view_measure_axis_offset (view, subscript->style.math_size);
		} else {
			*subscript_offset = descent;

			if (base_bbox->depth > descent)
				*subscript_offset += base_bbox->depth - descent;
			if (subscript_bbox->height - *subscript_offset > axis_offset)
				*subscript_offset = subscript_bbox->height - axis_offset;
		}
	} else
		*subscript_offset = 0.0;

	if (superscript_bbox != NULL) {
		if (is_operator) {
			*superscript_offset = base_bbox->height -
				1.5 * lsm_mathml_view_measure_axis_offset (view, superscript->style.math_size);
		} else {
			if (display == LSM_MATHML_DISPLAY_INLINE)
				*superscript_offset = axis_offset;
			else {
				double superscript_descent;

				lsm_mathml_view_get_font_metrics (view, &superscript->style,
							       NULL, &superscript_descent);
				*superscript_offset = axis_offset + superscript_descent;
			}

			if (base_bbox->height > ascent)
				*superscript_offset += base_bbox->height - ascent;
			if (*superscript_offset - superscript_bbox->depth < axis_offset)
				*superscript_offset = axis_offset + superscript_bbox->depth;
		}
	} else
		*superscript_offset = 0.0;

	if (superscript_bbox != NULL && subscript_bbox != NULL) {
		double delta = (*superscript_offset + *subscript_offset) -
			(superscript_bbox->depth + subscript_bbox->height);
		if (delta < v_space) {
			*superscript_offset += fabs (delta - v_space) * 0.5;
			*subscript_offset   += fabs (delta - v_space) * 0.5;
		}
	}

	*superscript_offset = MAX (*superscript_offset, superscript_offset_min);
	*subscript_offset = MAX (*subscript_offset, subscript_offset_min);

	if (subscript_bbox != NULL)
		lsm_mathml_bbox_merge_vertically (&children_bbox, subscript_bbox, -*subscript_offset);
	if (superscript_bbox != NULL)
		lsm_mathml_bbox_merge_vertically (&children_bbox, superscript_bbox, *superscript_offset);

	lsm_mathml_bbox_add_horizontally (bbox, &children_bbox);
}

void
lsm_mathml_layout_sub_sup (LsmMathmlElement *parent,
			LsmMathmlView *view,
			double x,
			double y,
			LsmMathmlElement *base,
			LsmMathmlElement *subscript,
			LsmMathmlElement *superscript,
			double subscript_offset,
			double superscript_offset)
{
	const LsmMathmlBbox *base_bbox;
	const LsmMathmlOperatorElement *embellished_core;
	double slant;
	double slant_offset;
	gboolean is_operator;

	if (base == NULL)
		return;

	embellished_core = lsm_mathml_element_get_embellished_core (base);
	is_operator = embellished_core != NULL;

	slant = is_operator ? lsm_mathml_operator_element_get_slant (embellished_core, view) : 0.0;

	base_bbox = lsm_mathml_element_get_bbox (base);

	lsm_mathml_element_layout (base, view, x, y, base_bbox);

	if (subscript) {
		const LsmMathmlBbox *subscript_bbox;

		subscript_bbox = lsm_mathml_element_get_bbox (subscript);

		slant_offset = slant < 0.0 ? (base_bbox->height + subscript_offset -
					      subscript_bbox->height) * sin (slant) : 0.0;

		lsm_mathml_element_layout (subscript, view,
					x + base_bbox->width + slant_offset,
					y + subscript_offset,
					lsm_mathml_element_get_bbox (subscript));
	}
	if (superscript) {
		const LsmMathmlBbox *superscript_bbox;

		superscript_bbox = lsm_mathml_element_get_bbox (superscript);

		slant_offset = slant > 0.0 ? (base_bbox->depth + superscript_offset -
					      superscript_bbox->depth) * sin (-slant) : 0.0;

		lsm_mathml_element_layout (superscript, view,
					x + base_bbox->width,
					y - superscript_offset,
					lsm_mathml_element_get_bbox (superscript));
	}
}
