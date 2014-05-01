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

#ifndef LSM_DOM_VIEW_H
#define LSM_DOM_VIEW_H

#include <lsmdomtypes.h>
#include <lsmutils.h>
#include <cairo.h>
#include <pango/pangocairo.h>

G_BEGIN_DECLS

#define LSM_DOM_VIEW_DEFAULT_RESOLUTION 	 72.0
#define LSM_DOM_VIEW_DEFAULT_VIEWBOX_WIDTH	320.0
#define LSM_DOM_VIEW_DEFAULT_VIEWBOX_HEIGHT 	200.0

#define LSM_TYPE_DOM_VIEW             (lsm_dom_view_get_type ())
#define LSM_DOM_VIEW(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_DOM_VIEW, LsmDomView))
#define LSM_DOM_VIEW_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_DOM_VIEW, LsmDomViewClass))
#define LSM_IS_DOM_VIEW(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_DOM_VIEW))
#define LSM_IS_DOM_VIEW_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_DOM_VIEW))
#define LSM_DOM_VIEW_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_DOM_VIEW, LsmDomViewClass))

typedef struct _LsmDomViewClass LsmDomViewClass;

struct _LsmDomView {
	GObject	object;

	LsmDomDocument *	document;

	PangoFontDescription *	font_description;
	PangoLayout *		pango_layout;
	PangoLayout *		measure_pango_layout;
	cairo_t *		cairo;
	gboolean		is_vector;

	double resolution_ppi;
	LsmBox viewport_pt;
};

struct _LsmDomViewClass {
	GObjectClass parent_class;

	GType document_type;

	void (*measure)		(LsmDomView *view, double *width, double *height, double *baseline);
	void (*render)		(LsmDomView *view);
	void (*set_debug)	(LsmDomView *view, const char *feature, gboolean enable);
};

GType lsm_dom_view_get_type (void);

double		lsm_dom_view_get_resolution	(LsmDomView *self);
void		lsm_dom_view_set_resolution	(LsmDomView *self, double ppi);

void 		lsm_dom_view_set_viewport 	(LsmDomView *self, const LsmBox *viewport_pt);
void 		lsm_dom_view_set_viewport_pixels(LsmDomView *self, const LsmBox *viewport);
LsmBox 		lsm_dom_view_get_viewport 	(LsmDomView *self);
LsmBox 		lsm_dom_view_get_viewport_pixels(LsmDomView *self);

void 		lsm_dom_view_render 		(LsmDomView *view, cairo_t *cairo, double x, double y);

void		lsm_dom_view_get_size		(LsmDomView *view, double *width, double *height, double *baseline);
void 		lsm_dom_view_get_size_pixels 	(LsmDomView *view, unsigned int *width, unsigned int *height,
						 unsigned int *baseline);

void		lsm_dom_view_set_debug		(LsmDomView *view, const char *feature, gboolean enable);

void 		lsm_dom_view_set_document 	(LsmDomView *view, LsmDomDocument *document);

G_END_DECLS

#endif
