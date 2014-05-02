/*
 * Copyright © 2007-2008  Emmanuel Pacaud
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <lsm.h>
#include <lsmmathml.h>
#include <glib.h>
#include <glib/gi18n.h>
#include <glib/gprintf.h>
#include <gio/gio.h>
#include <cairo-pdf.h>
#include <cairo-svg.h>
#include <cairo-ps.h>

#include "itex2MML.h"

static char *option_debug_domains = NULL;
static char *option_output_file_format = NULL;
static char **option_input_filenames = NULL;
static char *option_output_filename = NULL;
double option_ppi = 72.0;
double option_zoom = 1.0;

typedef enum {
	FORMAT_SVG,
	FORMAT_PDF,
	FORMAT_PS,
	FORMAT_PNG,
	FORMAT_UNKNOWN
} FileFormat;

static char const *file_formats[] = {
	"svg",
	"pdf",
	"ps",
	"png",
	"svg"
};

static const GOptionEntry entries[] =
{
	{ G_OPTION_REMAINING,	' ', 0,	G_OPTION_ARG_FILENAME_ARRAY,
		&option_input_filenames, 	NULL, NULL},
	{ "output",		'o', 0, G_OPTION_ARG_FILENAME,
		&option_output_filename,	N_("Output filename"), NULL},
	{ "format", 		'f', 0, G_OPTION_ARG_STRING,
		&option_output_file_format, 	N_("Output format"), NULL },
	{ "ppi", 		'p', 0, G_OPTION_ARG_DOUBLE,
		&option_ppi, 			N_("Pixel per inch"), NULL },
	{ "zoom", 		'z', 0, G_OPTION_ARG_DOUBLE,
		&option_zoom, 			N_("Zoom"), NULL },
	{ "debug", 		'd', 0, G_OPTION_ARG_STRING,
		&option_debug_domains,		N_("Debug domains"), NULL },
	{ NULL }
};

int mainbar(int argc, char **argv)
{
	LsmDomDocument *document;
	LsmDomView *view;
	cairo_t *cairo;
	cairo_surface_t *surface;
	GError *error = NULL;
	GOptionContext *context;
	FileFormat format;
	char *output_filename;
	char *input_filename;
	double height_pt, width_pt;
	unsigned int height, width;

	g_type_init ();

	context = g_option_context_new (NULL);
	g_option_context_add_main_entries (context, entries, NULL);

	// if (!g_option_context_parse (context, &argc, &argv, &error))
	// {
	// 	g_option_context_free (context);
	// 	g_print (_("Option parsing failed: %s\n"), error->message);
	// 	return EXIT_FAILURE;
	// }

	g_option_context_free (context);

	// if (option_zoom < 0.0) {
	// 	g_print (_("Invalid zoom value"));
	// 	return EXIT_FAILURE;
	// }

	lsm_debug_enable (option_debug_domains);

	// if (option_input_filenames == NULL || g_strv_length (option_input_filenames) > 1) {
	// 	g_print (_("One input file name is required\n"));
	// 	return EXIT_FAILURE;
	// }
	// option_input_filenames = ;

	input_filename = "/Users/garentorikian/Downloads/lasem-ruby/foo.mml";

	if (option_output_file_format != NULL) {
		for (format = 0; format < G_N_ELEMENTS(file_formats) - 1; format++)
			if (g_ascii_strcasecmp (option_output_file_format, file_formats[format]) == 0)
				break;
		if (FORMAT_UNKNOWN == format) {
			g_print (_("Unknown format : %s\n"), option_output_file_format);
			return EXIT_FAILURE;
		}
	} else
		format = FORMAT_UNKNOWN;

	if (option_output_filename != NULL) {
		char *extension;

		output_filename = option_output_filename;

		extension = g_strrstr (output_filename, ".");
		if (extension != NULL) {
			extension++;
			for (format = 0; format < G_N_ELEMENTS(file_formats) - 1; format++)
				if (g_ascii_strcasecmp (extension, file_formats[format]) == 0)
					break;
		}
	} else {
		char *filename;
		char *directory;
		char *extension;
		char *new_filename;

		filename = g_path_get_basename (input_filename);
		directory = g_path_get_dirname (input_filename);

		extension = g_strrstr (filename, ".");
		if (extension != NULL)
			*extension = '\0';

		new_filename = g_strconcat (filename, ".", file_formats[format], NULL);
		output_filename = g_build_filename (directory, new_filename, NULL);

		g_free (filename);
		g_free (new_filename);
		g_free (directory);
	}

	document = lsm_dom_document_new_from_path (input_filename,
						   NULL);
	if (document == NULL) {
		document = lsm_dom_document_new_from_url (input_filename,
							  NULL);
		if (document == NULL) {
			document = LSM_DOM_DOCUMENT (lsm_mathml_document_new_from_itex_path (input_filename,
											     NULL));
			if (document == NULL) {
				document = LSM_DOM_DOCUMENT (lsm_mathml_document_new_from_itex_url (input_filename,
												    NULL));
			}
		}
	}

	if (document != NULL) {
		if (lsm_debug_check (&lsm_debug_category_dom, LSM_DEBUG_LEVEL_LOG)) {
			void *buffer;
			int size;

			lsm_dom_document_save_to_memory (document, &buffer, &size, NULL);

			if (buffer != NULL) {
				g_printf ("%*s\n", size, (char *) buffer);
				g_free (buffer);
			}
		}

		view = lsm_dom_document_create_view (document);
		lsm_dom_view_set_resolution (view, option_ppi);

		width_pt = 2.0;
		height_pt = 2.0;

		lsm_dom_view_get_size (view, &width_pt, &height_pt, NULL);
		lsm_dom_view_get_size_pixels (view, &width, &height, NULL);

		width_pt *= option_zoom;
		height_pt *= option_zoom;
		width *= option_zoom;
		height *= option_zoom;

		switch (format) {
			case FORMAT_PDF:
				surface = cairo_pdf_surface_create (output_filename,
								    width_pt, height_pt);
				break;
			case FORMAT_PS:
				surface = cairo_ps_surface_create (output_filename,
								   width_pt, height_pt);
				break;
			case FORMAT_PNG:
				surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
								      width,
								      height);
				break;
			case FORMAT_SVG:
			default:
				surface = cairo_svg_surface_create (output_filename,
								    width_pt, height_pt);
				break;
		}

		cairo = cairo_create (surface);
		cairo_surface_destroy (surface);
		cairo_scale (cairo, option_zoom, option_zoom);

		lsm_dom_view_render (view, cairo, 0, 0);

		switch (format) {
			case FORMAT_PNG:
				cairo_surface_write_to_png (cairo_get_target (cairo),
							    output_filename);
				break;
			default:
				break;
		}

		cairo_destroy (cairo);

		g_object_unref (view);

		g_object_unref (document);

		lsm_debug_render ("width = %g pt, height = %g pt",  width_pt, height_pt);
	} else {
		g_print (_("Can't load '%s'\n"), input_filename);

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
