/* Lasem
 *
 * Copyright © 2009-2012 Emmanuel Pacaud
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

/**
 * SECTION:lsmdomview
 * @short_description: Base class for DOM views
 */

#include <lsmdebug.h>
#include <lsmdomdocument.h>
#include <lsmdomview.h>

static GObjectClass *parent_class;

/**
 * lsm_dom_view_get_resolution:
 * @self: A #LsmDomView
 *
 * Returns: view resolution, in pixel per inch.
 */

double
lsm_dom_view_get_resolution (LsmDomView *self)
{
	g_return_val_if_fail (LSM_IS_DOM_VIEW (self), 0.0);

	return self->resolution_ppi;
}

/**
 * lsm_dom_view_set_resolution:
 * @self: a #LsmDomView
 * @ppi: resolution, in pixel per inch.
 *
 * Set the view resolution, in pixel per inch.
 */

void
lsm_dom_view_set_resolution (LsmDomView *self, double ppi)
{
	g_return_if_fail (LSM_IS_DOM_VIEW (self));

	if (ppi < 0.0)
		self->resolution_ppi = LSM_DOM_VIEW_DEFAULT_RESOLUTION;
	else
		self->resolution_ppi = ppi;
}

/**
 * lsm_dom_view_set_viewport:
 * @self: a #LsmDomView
 * @viewport_pt: viewport size, in points
 *
 * Set the viewport size.
 */

void
lsm_dom_view_set_viewport (LsmDomView *self, const LsmBox *viewport_pt)
{
	g_return_if_fail (LSM_IS_DOM_VIEW (self));
	g_return_if_fail (viewport_pt != NULL);

	self->viewport_pt = *viewport_pt;
}

/**
 * lsm_dom_view_set_viewport_pixels:
 * @self: a #LsmDomView
 * @viewport: viewport size, in pixels
 *
 * Set the viewport size.
 */

void
lsm_dom_view_set_viewport_pixels (LsmDomView *self, const LsmBox *viewport)
{
	g_return_if_fail (LSM_IS_DOM_VIEW (self));
	g_return_if_fail (viewport != NULL);

	self->viewport_pt.x      = viewport->x      * 72.0 / self->resolution_ppi;
	self->viewport_pt.y      = viewport->y      * 72.0 / self->resolution_ppi;
	self->viewport_pt.width  = viewport->width  * 72.0 / self->resolution_ppi;
	self->viewport_pt.height = viewport->height * 72.0 / self->resolution_ppi;
}

/**
 * lsm_dom_view_get_viewport:
 * @self: a #LsmDomView
 *
 * Returns: viewport size, in points.
 */

LsmBox
lsm_dom_view_get_viewport (LsmDomView *self)
{
	static const LsmBox null_viewport = {0, 0, 0, 0};

	g_return_val_if_fail (LSM_IS_DOM_VIEW (self), null_viewport);

	return self->viewport_pt;
}

/**
 * lsm_dom_view_get_viewport_pixels:
 * @self: a #LsmDomView
 *
 * Returns: viewport size, in pixels.
 */

LsmBox
lsm_dom_view_get_viewport_pixels (LsmDomView *self)
{
	LsmBox viewport = {0, 0, 0, 0};

	g_return_val_if_fail (LSM_IS_DOM_VIEW (self), viewport);

	viewport.x      = self->viewport_pt.x      * self->resolution_ppi / 72.0;
	viewport.y      = self->viewport_pt.y      * self->resolution_ppi / 72.0;
	viewport.width  = self->viewport_pt.width  * self->resolution_ppi / 72.0;
	viewport.height = self->viewport_pt.height * self->resolution_ppi / 72.0;

	return viewport;
}

/**
 * lsm_dom_view_get_size:
 * @view: a #LsmDomView
 * @width: view width placeholder, in points
 * @height: view height placeholder, in points
 * @baseline: view baseline, in points
 *
 * Get the view size and baseline. Baseline is for use of view inside bloc of text.
 */

void
lsm_dom_view_get_size (LsmDomView *view, double *width, double *height, double *baseline)
{
	LsmDomViewClass *view_class;
	double dummy_width = 0.0;
	double dummy_height = 0.0;

	g_return_if_fail (LSM_IS_DOM_VIEW (view));
	g_return_if_fail (view->document != NULL);

	if (width == NULL)
		width = &dummy_width;
	if (height == NULL)
		height = &dummy_height;

	view_class = LSM_DOM_VIEW_GET_CLASS (view);
	if (view_class->measure != NULL)
		view_class->measure (view, width, height, baseline);
}

/**
 * lsm_dom_view_get_size_pixels:
 * @view: a #LsmDomView
 * @width: view width placeholder, in pixels
 * @height: view height placeholder, in pixels
 * @baseline: view baseline, in pixels
 *
 * Get the view size and baseline. Baseline is for use of view inside bloc of text.
 */

void
lsm_dom_view_get_size_pixels (LsmDomView *view, unsigned int *width, unsigned int *height, unsigned int *baseline)
{
	double resolution_ppi;
	double width_pt;
	double height_pt;
	double baseline_pt;

	g_return_if_fail (LSM_IS_DOM_VIEW (view));
	g_return_if_fail (view->document != NULL);

	resolution_ppi = view->resolution_ppi;
	g_return_if_fail (resolution_ppi > 0.0);

	width_pt =  width  != NULL ? *width  * 72.0 / resolution_ppi : 0.0;
	height_pt = height != NULL ? *height * 72.0 / resolution_ppi : 0.0;
	baseline_pt = baseline != NULL? *baseline * 72.0 /resolution_ppi : 0.0;

	lsm_dom_view_get_size (view, &width_pt, &height_pt,&baseline_pt);

	if (width != NULL)
		*width =  (double) (0.5 + width_pt  * resolution_ppi / 72.0);
	if (height != NULL)
		*height = (double) (0.5 + height_pt * resolution_ppi / 72.0);
	if (baseline != NULL)
		*baseline = (double) (0.5 + baseline_pt * resolution_ppi / 72.0);
}

static void
lsm_dom_view_set_cairo_context (LsmDomView *view, cairo_t *cairo)
{
	PangoContext *context;
	cairo_font_options_t *font_options;
	const cairo_font_options_t *current_font_options;
	cairo_surface_t *surface;
	cairo_surface_type_t type;

	g_return_if_fail (LSM_IS_DOM_VIEW (view));

	if (view->cairo == cairo)
		return;

	if (view->cairo != NULL) {
		cairo_destroy (view->cairo);
		g_object_unref (view->pango_layout);
	}

	if (cairo == NULL) {
		view->cairo = NULL;
		view->pango_layout = NULL;

		return;
	}

	cairo_reference (cairo);
	view->cairo = cairo;
	view->pango_layout = pango_cairo_create_layout (cairo);

	surface = cairo_get_target (cairo);

	type = cairo_surface_get_type (surface);

	view->is_vector = (type == CAIRO_SURFACE_TYPE_SVG ||
			   type == CAIRO_SURFACE_TYPE_PDF ||
			   type == CAIRO_SURFACE_TYPE_PS);

	context = pango_layout_get_context (view->pango_layout);
	pango_cairo_context_set_resolution (context, 72);

	current_font_options = pango_cairo_context_get_font_options (context);
	if (current_font_options == NULL)
		font_options = cairo_font_options_create ();
	else
		font_options = cairo_font_options_copy (current_font_options);
	cairo_font_options_set_hint_metrics (font_options, CAIRO_HINT_METRICS_OFF);
	pango_cairo_context_set_font_options (context, font_options);
	cairo_font_options_destroy (font_options);
}

/**
 * lsm_dom_view_render:
 * @view: a #LsmDomView
 * @cairo: cairo context
 * @x: x posiiton for rendering
 * @y: y position for rendering
 *
 * Render @view in the @cairo context.
 */

void
lsm_dom_view_render (LsmDomView *view, cairo_t *cairo, double x, double y)
{
	LsmDomViewClass *view_class;

	g_return_if_fail (LSM_IS_DOM_VIEW (view));
	g_return_if_fail (LSM_IS_DOM_DOCUMENT (view->document));
	g_return_if_fail (cairo != NULL);

	lsm_dom_view_set_cairo_context (view, cairo);

	cairo_save (view->cairo);

	cairo_translate (view->cairo, x, y);

	view_class = LSM_DOM_VIEW_GET_CLASS (view);
	if (view_class->render != NULL)
		view_class->render (view);

	cairo_restore (view->cairo);

	lsm_debug_render ("[LsmDomView::render] cairo status = %s",
			  cairo_status_to_string (cairo_status (view->cairo)));

	lsm_dom_view_set_cairo_context (view, NULL);
}

/**
 * lsm_dom_view_set_document:
 * @view: a #LsmDomView
 * @document: (transfer full): a #LsmDomDocument
 *
 * Change the document attached to @view. The previously attached document is unreferenced.
 */

void
lsm_dom_view_set_document (LsmDomView *view, LsmDomDocument *document)
{
	g_return_if_fail (LSM_IS_DOM_VIEW (view));
	g_return_if_fail (document == NULL || LSM_IS_DOM_DOCUMENT (document));

	if (view->document == document)
		return;

	if (view->document != NULL)
		g_object_unref (view->document);

	if (document != NULL)
	    g_object_ref (document);

	view->document = document;
}

/**
 * lsm_dom_view_set_debug:
 * @view: a #LsmDomView
 * @feature: name of the feature to debug
 * @enable: wether to enable debugging
 *
 * Configure feature debug.
 */

void
lsm_dom_view_set_debug (LsmDomView *view, const char *feature, gboolean enable)
{
	LsmDomViewClass *view_class;

	g_return_if_fail (LSM_IS_DOM_VIEW (view));
	g_return_if_fail (feature != NULL);


	view_class = LSM_DOM_VIEW_GET_CLASS (view);
	if (view_class->set_debug)
		view_class->set_debug (view, feature, enable);
}

static void
lsm_dom_view_init (LsmDomView *view)
{
	PangoFontMap *font_map;
	PangoContext *pango_context;
	cairo_font_options_t *font_options;

	view->resolution_ppi = LSM_DOM_VIEW_DEFAULT_RESOLUTION;
	view->viewport_pt.x = 0;
	view->viewport_pt.y = 0;
	view->viewport_pt.width  = LSM_DOM_VIEW_DEFAULT_VIEWBOX_WIDTH;
	view->viewport_pt.height = LSM_DOM_VIEW_DEFAULT_VIEWBOX_HEIGHT;

	view->font_description = pango_font_description_new ();

	font_map = pango_cairo_font_map_get_default ();

#if PANGO_VERSION_CHECK(1,22,0)
	pango_context = pango_font_map_create_context (font_map);
#else
	pango_context = pango_cairo_font_map_create_context (PANGO_CAIRO_FONT_MAP (font_map));
#endif
	pango_cairo_context_set_resolution (pango_context, 72.0);

	view->measure_pango_layout = pango_layout_new (pango_context);

	font_options = cairo_font_options_create ();

	cairo_font_options_set_hint_metrics (font_options, CAIRO_HINT_METRICS_OFF);
	cairo_font_options_set_hint_style (font_options, CAIRO_HINT_STYLE_NONE);

	pango_cairo_context_set_font_options (pango_context, font_options);

	cairo_font_options_destroy (font_options);

	g_object_unref (pango_context);

	view->pango_layout = NULL;
	view->cairo = NULL;
	view->is_vector = FALSE;
}

static void
lsm_dom_view_finalize (GObject *object)
{
	LsmDomView *view = LSM_DOM_VIEW (object);

	if (view->document)
		g_object_unref (view->document);

	if (view->pango_layout != NULL)
		g_object_unref (view->pango_layout);
	if (view->cairo != NULL)
		cairo_destroy (view->cairo);

	g_object_unref (view->measure_pango_layout);

	pango_font_description_free (view->font_description);

	parent_class->finalize (object);
}

static void
lsm_dom_view_class_init (LsmDomViewClass *view_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (view_class);

	parent_class = g_type_class_peek_parent (view_class);

	object_class->finalize = lsm_dom_view_finalize;
}

G_DEFINE_ABSTRACT_TYPE (LsmDomView, lsm_dom_view, G_TYPE_OBJECT)
