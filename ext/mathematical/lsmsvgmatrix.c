/* Lasem
 *
 * Copyright © 2009 Emmanuel Pacaud
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

#include <lsmsvgmatrix.h>
#include <math.h>

gboolean
lsm_svg_matrix_is_identity (const LsmSvgMatrix *matrix)
{
	return ((matrix->flags & LSM_SVG_MATRIX_FLAGS_IDENTITY) != 0);
}

void
lsm_svg_matrix_init (LsmSvgMatrix *matrix, double a, double b, double c, double d, double e, double f)
{
	matrix->a = a;
	matrix->b = b;
	matrix->c = c;
	matrix->d = d;
	matrix->e = e;
	matrix->f = f;
	matrix->flags = 0;
}

void
lsm_svg_matrix_init_identity (LsmSvgMatrix *matrix)
{
	lsm_svg_matrix_init (matrix, 1, 0, 0, 1, 0, 0);
	matrix->flags |= LSM_SVG_MATRIX_FLAGS_IDENTITY;
}

void
lsm_svg_matrix_init_scale (LsmSvgMatrix *matrix, double sx, double sy)
{
	lsm_svg_matrix_init (matrix, sx, 0, 0, sy, 0, 0);
}

void
lsm_svg_matrix_scale (LsmSvgMatrix *matrix, double sx, double sy)
{
	LsmSvgMatrix tmp;

	lsm_svg_matrix_init_scale (&tmp, sx, sy);
	lsm_svg_matrix_multiply (matrix, &tmp, matrix);
}

void
lsm_svg_matrix_init_translate (LsmSvgMatrix *matrix, double tx, double ty)
{
	lsm_svg_matrix_init (matrix, 1, 0, 0, 1, tx, ty);
}

void
lsm_svg_matrix_translate (LsmSvgMatrix *matrix, double tx, double ty)
{
	LsmSvgMatrix tmp;

	lsm_svg_matrix_init_translate (&tmp, tx, ty);
	lsm_svg_matrix_multiply (matrix, &tmp, matrix);
}

void
lsm_svg_matrix_init_rotate (LsmSvgMatrix *matrix, double radians)
{
	double  s;
	double  c;

	s = sin (radians);
	c = cos (radians);

	lsm_svg_matrix_init (matrix, c, s, -s, c, 0, 0);
}

void
lsm_svg_matrix_rotate (LsmSvgMatrix *matrix, double radians)
{
	LsmSvgMatrix tmp;

	lsm_svg_matrix_init_rotate (&tmp,radians);
	lsm_svg_matrix_multiply (matrix, &tmp, matrix);
}

void
lsm_svg_matrix_init_skew_x (LsmSvgMatrix *matrix, double radians)
{
	lsm_svg_matrix_init (matrix, 1, 0, tan(radians), 1, 0, 0);
}

void
lsm_svg_matrix_skew_x (LsmSvgMatrix *matrix, double radians)
{
	LsmSvgMatrix tmp;

	lsm_svg_matrix_init_skew_x (&tmp,radians);
	lsm_svg_matrix_multiply (matrix, &tmp, matrix);
}

void
lsm_svg_matrix_init_skew_y (LsmSvgMatrix *matrix, double radians)
{
	lsm_svg_matrix_init (matrix, 1, tan(radians), 0, 1, 0, 0);
}

void
lsm_svg_matrix_skew_y (LsmSvgMatrix *matrix, double radians)
{
	LsmSvgMatrix tmp;

	lsm_svg_matrix_init_skew_y (&tmp,radians);
	lsm_svg_matrix_multiply (matrix, &tmp, matrix);
}

void
lsm_svg_matrix_multiply (LsmSvgMatrix *result, const LsmSvgMatrix *a, const LsmSvgMatrix *b)
{
	LsmSvgMatrix r;

	if ((a->flags & LSM_SVG_MATRIX_FLAGS_IDENTITY) != 0) {
		*result = *b;
		return;
	}
	if ((b->flags & LSM_SVG_MATRIX_FLAGS_IDENTITY) != 0) {
		*result = *a;
		return;
	}

	r.a = a->a * b->a + a->b * b->c;
	r.b = a->a * b->b + a->b * b->d;

	r.c = a->c * b->a + a->d * b->c;
	r.d = a->c * b->b + a->d * b->d;

	r.e = a->e * b->a + a->f * b->c + b->e;
	r.f = a->e * b->b + a->f * b->d + b->f;

	r.flags = 0;

	*result = r;
}

void
lsm_svg_matrix_transform_point (const LsmSvgMatrix *matrix, double *x, double *y)
{
	double new_x;
	double new_y;

	if ((matrix->flags & LSM_SVG_MATRIX_FLAGS_IDENTITY) != 0)
		return;

	new_x = (matrix->a * *x + matrix->c * *y) + matrix->e;
	new_y = (matrix->b * *x + matrix->d * *y) + matrix->f;

	*x = new_x;
	*y = new_y;
}

void
lsm_svg_matrix_transform_bounding_box (const LsmSvgMatrix *matrix, double *x1, double *y1, double *x2, double *y2)
{
	double x12, y12, x21, y21;
	double x_min, y_min, x_max, y_max;

	if ((matrix->flags & LSM_SVG_MATRIX_FLAGS_IDENTITY) != 0)
		return;

	x12 = *x1;
	y12 = *y2;
	x21 = *x2;
	y21 = *y1;

	lsm_svg_matrix_transform_point (matrix, x1, y1);
	lsm_svg_matrix_transform_point (matrix, x2, y2);
	lsm_svg_matrix_transform_point (matrix, &x12, &y12);
	lsm_svg_matrix_transform_point (matrix, &x21, &y21);

	x_min = MIN (MIN (*x1, *x2), MIN (x12, x21));
	x_max = MAX (MAX (*x1, *x2), MAX (x12, x21));
	y_min = MIN (MIN (*y1, *y2), MIN (y12, y21));
	y_max = MAX (MAX (*y1, *y2), MAX (y12, y21));

	*x1 = x_min;
	*y1 = y_min;
	*x2 = x_max;
	*y2 = y_max;
}
