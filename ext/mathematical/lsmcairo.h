/* Lasem
 *
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
 * Author:
 * 	Emmanuel Pacaud <emmanuel@gnome.org>
 */

#ifndef LSM_CAIRO_H
#define LSM_CAIRO_H

#include <lsmtypes.h>
#include <cairo.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

G_BEGIN_DECLS

void 			lsm_cairo_quadratic_curve_to 		(cairo_t *cr, double x1, double y1, double x, double y);
void			lsm_cairo_rel_quadratic_curve_to 	(cairo_t *cr, double dx1, double dy1, double dx, double dy);
void 			lsm_cairo_elliptical_arc 		(cairo_t *cairo, double rx, double ry, double x_axis_rotation,
								 gboolean large_arc_flag, gboolean sweep_flag, double x, double y);
void 			lsm_cairo_rel_elliptical_arc 		(cairo_t *cairo, double rx, double ry, double x_axis_rotation,
								 gboolean large_arc_flag, gboolean sweep_flag, double dx, double dy);
void 			lsm_cairo_vertical 			(cairo_t *cairo, double y);
void 			lsm_cairo_rel_vertical 			(cairo_t *cairo, double dy);
void 			lsm_cairo_horizontal 			(cairo_t *cairo, double x);
void 			lsm_cairo_rel_horizontal 		(cairo_t *cairo, double dx);
void 			lsm_cairo_emit_svg_path 		(cairo_t *cr, char const *path);
void 			lsm_cairo_box_user_to_device 		(cairo_t *cairo, LsmBox *to, const LsmBox *from);
void 			lsm_cairo_box_device_to_user 		(cairo_t *cairo, LsmBox *to, const LsmBox *from);
void 			lsm_cairo_set_source_pixbuf 		(cairo_t *cairo, const GdkPixbuf *pixbuf,
								 double pixbuf_x, double pixbuf_y);

G_END_DECLS

#endif
