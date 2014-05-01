/* Lasem
 *
 * Copyright © 2004 Caleb Moore
 * Copyright © 2012 Emmanuel Pacaud
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
 * Authors:
 *	Caleb Moore <c.moore@student.unsw.edu.au>
 * 	Emmanuel Pacaud <emmanuel@gnome.org>
 */

#include <lsmcairo.h>
#include <lsmsvgenums.h>
#include <lsmutils.h>
#include <lsmstr.h>
#include <math.h>
#include <string.h>

typedef struct {
	cairo_t *cr;
	char *ptr;
	char last_command;
	double last_cp_x;
	double last_cp_y;
	double values[7];
} LsmSvgPathContext;

/*
 * Code for:
 *
 * 	_calc_angle 
 * 	_cairo_elliptical_arc 
 * 	_cairo_quadratic_curve_to
 * 	_emit_smooth_curve
 * 	_emit_smooth_quadratic_curve
 *
 * is adapted from the goocanvas library (goocanvasutils.c)
 *
 * GooCanvas. Copyright (C) 2005 Damon Chaplin.
 */

void
lsm_cairo_quadratic_curve_to (cairo_t *cr, double x1, double y1, double x, double y)
{
	double x0, y0, xx1, yy1, xx2, yy2;

	cairo_get_current_point (cr, &x0, &y0);

	/* We need to convert the quadratic into a cubic bezier. */

	xx1 = x0 + (x1 - x0) * 2.0 / 3.0;
	yy1 = y0 + (y1 - y0) * 2.0 / 3.0;

	xx2 = xx1 + (x - x0) / 3.0;
	yy2 = yy1 + (y - y0) / 3.0;

	cairo_curve_to (cr, xx1, yy1, xx2, yy2, x, y);
}

void
lsm_cairo_rel_quadratic_curve_to (cairo_t *cr, double dx1, double dy1, double dx, double dy)
{
	double x0, y0;

	cairo_get_current_point (cr, &x0, &y0);
	lsm_cairo_quadratic_curve_to (cr, x0 + dx1, y0 + dy1, x0 + dx, y0 + dy);
}

static double
_calc_angle (double ux, double uy, double vx, double vy)
{
	double top, u_magnitude, v_magnitude, angle_cos, angle;

	top = ux * vx + uy * vy;
	u_magnitude = sqrt (ux * ux + uy * uy);
	v_magnitude = sqrt (vx * vx + vy * vy);
	angle_cos = top / (u_magnitude * v_magnitude);

	/* We check if the cosine is slightly out-of-bounds. */
	if (angle_cos >= 1.0)
		angle = 0.0;
	if (angle_cos <= -1.0)
		angle = M_PI;
	else
		angle = acos (angle_cos);

	if (ux * vy - uy * vx < 0)
		angle = - angle;

	return angle;
}

void
lsm_cairo_elliptical_arc (cairo_t *cairo, double rx, double ry, double x_axis_rotation,
		       gboolean large_arc_flag, gboolean sweep_flag, double x, double y)
{
	double x1, y1, x2, y2, lambda;
	double v1, v2, angle, angle_sin, angle_cos, x11, y11;
	double rx_squared, ry_squared, x11_squared, y11_squared, top, bottom;
	double c, cx1, cy1, cx, cy, start_angle, angle_delta;

	cairo_get_current_point (cairo, &x1, &y1);

	x2 = x;
	y2 = y;

	/* If the endpoints are exactly the same, just return (see SVG spec). */
	if (x1 == x2 && y1 == y2)
		return;

	/* If either rx or ry is 0, do a simple lineto (see SVG spec). */
	if (rx == 0.0 || ry == 0.0)
	{
		cairo_line_to (cairo, x2, y2);
		return;
	}

	/* Calculate x1' and y1' (as per SVG implementation notes). */
	v1 = (x1 - x2) / 2.0;
	v2 = (y1 - y2) / 2.0;

	angle = x_axis_rotation * (M_PI / 180.0);
	angle_sin = sin (angle);
	angle_cos = cos (angle);

	x11 = (angle_cos * v1) + (angle_sin * v2);
	y11 = - (angle_sin * v1) + (angle_cos * v2);

	/* Ensure rx and ry are positive and large enough. */
	rx = rx > 0.0 ? rx : - rx;
	ry = ry > 0.0 ? ry : - ry;
	lambda = (x11 * x11) / (rx * rx) + (y11 * y11) / (ry * ry);
	if (lambda > 1.0)
	{
		gdouble square_root = sqrt (lambda);
		rx *= square_root;
		ry *= square_root;
	}

	/* Calculate cx' and cy'. */
	rx_squared = rx * rx;
	ry_squared = ry * ry;
	x11_squared = x11 * x11;
	y11_squared = y11 * y11;

	top = (rx_squared * ry_squared) - (rx_squared * y11_squared)
		- (ry_squared * x11_squared);
	if (top < 0.0)
	{
		c = 0.0;
	}
	else
	{
		bottom = (rx_squared * y11_squared) + (ry_squared * x11_squared);
		c = sqrt (top / bottom);
	}

	if (large_arc_flag == sweep_flag)
		c = - c;

	cx1 = c * ((rx * y11) / ry);
	cy1 = c * (- (ry * x11) / rx);

	/* Calculate cx and cy. */
	cx = (angle_cos * cx1) - (angle_sin * cy1) + (x1 + x2) / 2;
	cy = (angle_sin * cx1) + (angle_cos * cy1) + (y1 + y2) / 2;

	/* Calculate the start and end angles. */
	v1 = (x11 - cx1) / rx;
	v2 = (y11 - cy1) / ry;

	start_angle = _calc_angle (1, 0, v1, v2);
	angle_delta = _calc_angle (v1, v2, (-x11 - cx1) / rx, (-y11 - cy1) / ry);

	if (sweep_flag == 0 && angle_delta > 0.0)
		angle_delta -= 2 * M_PI;
	else if (sweep_flag == 1 && angle_delta < 0.0)
		angle_delta += 2 * M_PI;

	/* Now draw the arc. */
	cairo_save (cairo);
	cairo_translate (cairo, cx, cy);
	cairo_rotate (cairo, angle);
	cairo_scale (cairo, rx, ry);

	if (angle_delta > 0.0)
		cairo_arc (cairo, 0.0, 0.0, 1.0,
			   start_angle, start_angle + angle_delta);
	else
		cairo_arc_negative (cairo, 0.0, 0.0, 1.0,
				    start_angle, start_angle + angle_delta);

	cairo_restore (cairo);
}

void
lsm_cairo_rel_elliptical_arc (cairo_t *cairo, double rx, double ry, double x_axis_rotation,
			   gboolean large_arc_flag, gboolean sweep_flag, double dx, double dy)
{
	double x, y;

	cairo_get_current_point (cairo, &x, &y);

	lsm_cairo_elliptical_arc (cairo, rx, ry, x_axis_rotation, large_arc_flag, sweep_flag, x +dx ,y + dy);
}

void
lsm_cairo_vertical (cairo_t *cairo, double y)
{
	double x0, y0;

	cairo_get_current_point (cairo, &x0, &y0);
	cairo_line_to (cairo, x0, y);
}

void
lsm_cairo_rel_vertical (cairo_t *cairo, double dy)
{
	double x0, y0;

	cairo_get_current_point (cairo, &x0, &y0);
	cairo_line_to (cairo, x0, y0 + dy);
}

void
lsm_cairo_horizontal (cairo_t *cairo, double x)
{
	double x0, y0;

	cairo_get_current_point (cairo, &x0, &y0);
	cairo_line_to (cairo, x, y0);
}

void
lsm_cairo_rel_horizontal (cairo_t *cairo, double dx)
{
	double x0, y0;

	cairo_get_current_point (cairo, &x0, &y0);
	cairo_line_to (cairo, x0 + dx, y0);
}

static void
_emit_function_1 (LsmSvgPathContext *ctxt,
		  void (*cairo_func) (cairo_t *, double))
{
	while (lsm_str_parse_double_list (&ctxt->ptr, 1, ctxt->values) == 1)
		cairo_func (ctxt->cr, ctxt->values[0]);
}

static void
_emit_function_2 (LsmSvgPathContext *ctxt,
		  void (*cairo_func_a) (cairo_t *, double, double),
		  void (*cairo_func_b) (cairo_t *, double, double))
{

	if (lsm_str_parse_double_list (&ctxt->ptr, 2, ctxt->values) == 2) {
		cairo_func_a (ctxt->cr, ctxt->values[0], ctxt->values[1]);

		/* Why oh why does the specification say Line is implied here ? */

		while (lsm_str_parse_double_list (&ctxt->ptr, 2, ctxt->values) == 2)
			cairo_func_b (ctxt->cr, ctxt->values[0], ctxt->values[1]);
	}
}

static void
_emit_function_4 (LsmSvgPathContext *ctxt,
		  void (*cairo_func) (cairo_t *, double, double, double, double))
{
	while (lsm_str_parse_double_list (&ctxt->ptr, 4, ctxt->values) == 4)
		cairo_func (ctxt->cr, ctxt->values[0], ctxt->values[1], ctxt->values[2], ctxt->values[3]);
}

static void
_emit_smooth_curve (LsmSvgPathContext *ctxt, gboolean relative)
{
	double x, y;
	double x0, y0;

	cairo_get_current_point (ctxt->cr, &x0, &y0);

	switch (ctxt->last_command) {
		case 'C':
			x = 2 * x0 - ctxt->values[2];
			y = 2 * y0 - ctxt->values[3];
			break;
		case 'c':
			x = 2 * x0 - (ctxt->values[2] + x0 - ctxt->values[4]);
			y = 2 * y0 - (ctxt->values[3] + y0 - ctxt->values[5]);
			break;
		case 'S':
			x = 2 * x0 - ctxt->values[0];
			y = 2 * y0 - ctxt->values[1];
			break;
		case 's':
			x = 2 * x0 - (ctxt->values[0] + x0 - ctxt->values[2]);
			y = 2 * y0 - (ctxt->values[1] + y0 - ctxt->values[3]);
			break;
		default: x = x0; y = y0; break;
	}

	while (lsm_str_parse_double_list (&ctxt->ptr, 4, ctxt->values) == 4) {
		if (relative) {
			cairo_get_current_point (ctxt->cr, &x0, &y0);
			cairo_curve_to (ctxt->cr,
					x, y,
					x0 + ctxt->values[0], y0 + ctxt->values[1],
					x0 + ctxt->values[2], y0 + ctxt->values[3]);
			x = 2 * (x0 + ctxt->values[2]) - (x0 + ctxt->values[0]);
			y = 2 * (y0 + ctxt->values[3]) - (y0 + ctxt->values[1]);
		} else {
			cairo_curve_to (ctxt->cr, x, y,
					ctxt->values[0], ctxt->values[1], ctxt->values[2], ctxt->values[3]);
			x = 2 * ctxt->values[2] - ctxt->values[0];
			y = 2 * ctxt->values[3] - ctxt->values[1];
		}
	}
}

static void
_emit_smooth_quadratic_curve (LsmSvgPathContext *ctxt, gboolean relative)
{
	double x, y;
	double x0, y0;

	cairo_get_current_point (ctxt->cr, &x0, &y0);

	switch (ctxt->last_command) {
		case 'Q':
			ctxt->last_cp_x = ctxt->values[0];
			ctxt->last_cp_y = ctxt->values[1];
			break;
		case 'q':
			ctxt->last_cp_x = ctxt->values[0] + x0 - ctxt->values[2];
			ctxt->last_cp_y = ctxt->values[1] + y0 - ctxt->values[3];
			break;
		case 'T':
		case 't':
			break;
		default: ctxt->last_cp_x = x0; ctxt->last_cp_y = y0; break;
	}

	while (lsm_str_parse_double_list (&ctxt->ptr, 2, ctxt->values) == 2) {
		x = 2 * x0 - ctxt->last_cp_x;
		y = 2 * y0 - ctxt->last_cp_y;
		if (relative) {
			cairo_get_current_point (ctxt->cr, &x0, &y0);
			lsm_cairo_quadratic_curve_to (ctxt->cr, x, y, x0 + ctxt->values[0], y0 + ctxt->values[1]);
		} else {
			lsm_cairo_quadratic_curve_to (ctxt->cr, x, y, ctxt->values[0], ctxt->values[1]);
		}
		ctxt->last_cp_x = x;
		ctxt->last_cp_y = y;
		cairo_get_current_point (ctxt->cr, &x0, &y0);
	}
}

static void
_emit_function_6 (LsmSvgPathContext *ctxt,
		  void (*cairo_func) (cairo_t *, double, double, double ,double, double, double))
{
	while (lsm_str_parse_double_list (&ctxt->ptr, 6, ctxt->values) == 6)
		cairo_func (ctxt->cr, ctxt->values[0], ctxt->values[1], ctxt->values[2],
			              ctxt->values[3], ctxt->values[4], ctxt->values[5]);
}

static void
_emit_function_7 (LsmSvgPathContext *ctxt,
		  void (*cairo_func) (cairo_t *, double, double, double ,gboolean, gboolean, double, double))
{
	while (lsm_str_parse_double_list (&ctxt->ptr, 7, ctxt->values) == 7)
		cairo_func (ctxt->cr, ctxt->values[0], ctxt->values[1], ctxt->values[2],
			              ctxt->values[3], ctxt->values[4], ctxt->values[5],
				      ctxt->values[6]);
}

void
lsm_cairo_emit_svg_path (cairo_t *cr, char const *path)
{
	LsmSvgPathContext ctxt;

	g_return_if_fail (cr != NULL);

	if (path == NULL)
		return;

	ctxt.cr = cr;
	ctxt.ptr = (char *) path;
	ctxt.last_command = '\0';
	cairo_get_current_point (cr,
				 &ctxt.values[0],
				 &ctxt.values[1]);
	ctxt.values[2] = ctxt.values[4] = ctxt.values[0];
	ctxt.values[3] = ctxt.values[5] = ctxt.values[1];

	lsm_str_skip_spaces (&ctxt.ptr);

	while (*ctxt.ptr != '\0') {
		char command;

		command = *ctxt.ptr;
		ctxt.ptr++;
		lsm_str_skip_spaces (&ctxt.ptr);

		if (!cairo_has_current_point (cr)) {
			cairo_move_to (cr, 0, 0);
			ctxt.values[2] = ctxt.values[4] = ctxt.values[0] = 0;
			ctxt.values[3] = ctxt.values[5] = ctxt.values[1] = 0;
		}

		switch (command) {
			case 'M': _emit_function_2 (&ctxt, cairo_move_to, cairo_line_to); break;
			case 'm': _emit_function_2 (&ctxt, cairo_rel_move_to, cairo_rel_line_to); break;
			case 'L': _emit_function_2 (&ctxt, cairo_line_to, cairo_line_to); break;
			case 'l': _emit_function_2 (&ctxt, cairo_rel_line_to, cairo_rel_line_to); break;
			case 'C': _emit_function_6 (&ctxt, cairo_curve_to); break;
			case 'c': _emit_function_6 (&ctxt, cairo_rel_curve_to); break;
			case 'S': _emit_smooth_curve (&ctxt, FALSE); break;
			case 's': _emit_smooth_curve (&ctxt, TRUE); break;
			case 'V': _emit_function_1 (&ctxt, lsm_cairo_vertical); break;
			case 'v': _emit_function_1 (&ctxt, lsm_cairo_rel_vertical); break;
			case 'H': _emit_function_1 (&ctxt, lsm_cairo_horizontal); break;
			case 'h': _emit_function_1 (&ctxt, lsm_cairo_rel_horizontal); break;
			case 'Q': _emit_function_4 (&ctxt, lsm_cairo_quadratic_curve_to); break;
			case 'q': _emit_function_4 (&ctxt, lsm_cairo_rel_quadratic_curve_to); break;
			case 'T': _emit_smooth_quadratic_curve (&ctxt, FALSE); break;
			case 't': _emit_smooth_quadratic_curve (&ctxt, TRUE); break;
			case 'A': _emit_function_7 (&ctxt, lsm_cairo_elliptical_arc); break;
			case 'a': _emit_function_7 (&ctxt, lsm_cairo_rel_elliptical_arc); break;
			case 'Z':
			case 'z': cairo_close_path (cr); break;
			default: break;
		}

		ctxt.last_command = command;
	}
}

void
lsm_cairo_box_user_to_device (cairo_t *cairo, LsmBox *to, const LsmBox *from)
{
	if (to == NULL)
		return;

	if (from == NULL || cairo == NULL) {
		to->x = 0;
		to->y = 0;
		to->width = 0;
		to->height = 0;
	}

	*to = *from;

	cairo_user_to_device (cairo, &to->x, &to->y);
	cairo_user_to_device_distance (cairo, &to->width, &to->height);
}

void
lsm_cairo_box_device_to_user (cairo_t *cairo, LsmBox *to, const LsmBox *from)
{
	if (to == NULL)
		return;

	if (from == NULL || cairo == NULL) {
		to->x = 0;
		to->y = 0;
		to->width = 0;
		to->height = 0;
	}

	*to = *from;

	cairo_device_to_user (cairo, &to->x, &to->y);
	cairo_device_to_user_distance (cairo, &to->width, &to->height);
}

/**
 * lsm_cairo_set_source_pixbuf:
 * @cairo: a cairo context
 * @pixbuf: a #GdkPixbuf
 * @pixbuf_x: X coordinate of location to place upper left corner of @pixbuf
 * @pixbuf_y: Y coordinate of location to place upper left corner of @pixbuf
 *
 * Sets the given pixbuf as the source pattern for @cairo.
 *
 * The pattern has an extend mode of %CAIRO_EXTEND_NONE and is aligned
 * so that the origin of @pixbuf is @pixbuf_x, @pixbuf_y.
 *
 * Since: 0.4
 */

void
lsm_cairo_set_source_pixbuf (cairo_t *cairo,
                             const GdkPixbuf *pixbuf,
                             double pixbuf_x,
                             double pixbuf_y)
{
	gint width = gdk_pixbuf_get_width (pixbuf);
	gint height = gdk_pixbuf_get_height (pixbuf);
	guchar *gdk_pixels = gdk_pixbuf_get_pixels (pixbuf);
	int gdk_rowstride = gdk_pixbuf_get_rowstride (pixbuf);
	int n_channels = gdk_pixbuf_get_n_channels (pixbuf);
	int cairo_stride;
	guchar *cairo_pixels;
	cairo_format_t format;
	cairo_surface_t *surface;
	static const cairo_user_data_key_t key;
	int j;

	if (n_channels == 3)
		format = CAIRO_FORMAT_RGB24;
	else
		format = CAIRO_FORMAT_ARGB32;

	cairo_stride = cairo_format_stride_for_width (format, width);
	cairo_pixels = g_malloc (height * cairo_stride);
	surface = cairo_image_surface_create_for_data ((unsigned char *)cairo_pixels,
						       format,
						       width, height, cairo_stride);

	cairo_surface_set_user_data (surface, &key,
				     cairo_pixels, (cairo_destroy_func_t)g_free);

	for (j = height; j; j--)
	{
		guchar *p = gdk_pixels;
		guchar *q = cairo_pixels;

		if (n_channels == 3)
		{
			guchar *end = p + 3 * width;

			while (p < end)
			{
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
				q[0] = p[2];
				q[1] = p[1];
				q[2] = p[0];
#else
				q[1] = p[0];
				q[2] = p[1];
				q[3] = p[2];
#endif
				p += 3;
				q += 4;
			}
		}
		else
		{
			guchar *end = p + 4 * width;
			guint t1,t2,t3;

#define MULT(d,c,a,t) G_STMT_START { t = c * a + 0x7f; d = ((t >> 8) + t) >> 8; } G_STMT_END

			while (p < end)
			{
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
				MULT(q[0], p[2], p[3], t1);
				MULT(q[1], p[1], p[3], t2);
				MULT(q[2], p[0], p[3], t3);
				q[3] = p[3];
#else
				q[0] = p[3];
				MULT(q[1], p[0], p[3], t1);
				MULT(q[2], p[1], p[3], t2);
				MULT(q[3], p[2], p[3], t3);
#endif

				p += 4;
				q += 4;
			}

#undef MULT
		}

		gdk_pixels += gdk_rowstride;
		cairo_pixels += cairo_stride;
	}

	cairo_set_source_surface (cairo, surface, pixbuf_x, pixbuf_y);
	cairo_surface_destroy (surface);
}

