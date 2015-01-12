 /****************************************************************************
 * Mathematical_rb Copyright(c) 2014, Garen J. Torikian, All rights reserved.
 * --------------------------------------------------------------------------
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ****************************************************************************/

#include "ruby.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <lsm.h>
#include <lsmmathml.h>
#include <glib.h>
#include <glib/gi18n.h>
#include <glib/gprintf.h>
#include <gio/gio.h>
#include <cairo-pdf.h>
#include <cairo-svg.h>
#include <cairo-ps.h>
#include "mtex2MML.h"

#define CSTR2SYM(str) ID2SYM(rb_intern(str))

static VALUE rb_mMathematical;
static VALUE rb_cMathematicalProcess;

// Raised when the size of the latex string is too large
static VALUE rb_eMaxsizeError;
// Raised when the contents could not be parsed
static VALUE rb_eParseError;
// Raised when the SVG document could not be created
static VALUE rb_eDocumentCreationError;
// Raised when the SVG document could not be read
static VALUE rb_eDocumentReadError;

typedef enum {
  FORMAT_SVG,
  FORMAT_PNG,
  FORMAT_MATHML
} FileFormat;

/**
 * lsm_mtex_to_mathml:
 * @mtex: (allow-none): an mtex string
 * @size: mtex string length, -1 if NULL terminated
 *
 * Converts an mtex string to a Mathml representation.
 *
 * Return value: a newly allocated string, NULL on parse error. The returned data must be freed using @lsm_mtex_free_mathml_buffer.
 */

char *
lsm_mtex_to_mathml (const char *mtex, gssize size)
{
  gsize usize;
  char *mathml;

  if (mtex == NULL)
    return NULL;

  if (size < 0)
    usize = strlen (mtex);
  else
    usize = size;

  mathml = mtex2MML_parse (mtex, usize);
  if (mathml == NULL)
    return NULL;

  if (mathml[0] == '\0') {
    mtex2MML_free_string (mathml);
    return NULL;
  }

  return mathml;
}

/**
 * lsm_mtex_free_mathml_buffer:
 * @mathml: (allow-none): a mathml buffer
 *
 * Free the buffer returned by @lsm_mtex_to_mathml.
 */

void
lsm_mtex_free_mathml_buffer (char *mathml)
{
  if (mathml == NULL)
    return;

  mtex2MML_free_string (mathml);
}

cairo_status_t cairoSvgSurfaceCallback (void *closure, const unsigned char *data, unsigned int length) {
  VALUE self = (VALUE) closure;
  if (rb_iv_get(self, "@svg") == Qnil) {
    rb_iv_set(self, "@svg", rb_str_new2(""));
  }

  rb_str_cat(rb_iv_get(self, "@svg"), data, length);

  return CAIRO_STATUS_SUCCESS;
}

cairo_status_t cairoPngSurfaceCallback (void *closure, const unsigned char *data, unsigned int length) {
  VALUE self = (VALUE) closure;
  if (rb_iv_get(self, "@png") == Qnil) {
    rb_iv_set(self, "@png", rb_str_new2(""));
  }

  rb_str_cat(rb_iv_get(self, "@png"), data, length);

  return CAIRO_STATUS_SUCCESS;
}

static VALUE MATHEMATICAL_init(VALUE self, VALUE rb_Options) {
  Check_Type (rb_Options, T_HASH);
  VALUE rb_ppi, rb_zoom, rb_maxsize, rb_format;

  rb_ppi = rb_hash_aref(rb_Options, CSTR2SYM("ppi"));
  rb_zoom = rb_hash_aref(rb_Options, CSTR2SYM("zoom"));
  rb_maxsize = rb_hash_aref(rb_Options, CSTR2SYM("maxsize"));
  rb_format = rb_hash_aref(rb_Options, CSTR2SYM("format"));

  Check_Type(rb_ppi, T_FLOAT);
  Check_Type(rb_zoom, T_FLOAT);
  Check_Type(rb_maxsize, T_FIXNUM);
  Check_Type(rb_format, T_STRING);

  rb_iv_set(self, "@ppi", rb_ppi);
  rb_iv_set(self, "@zoom", rb_zoom);
  rb_iv_set(self, "@maxsize", rb_maxsize);
  rb_iv_set(self, "@format", rb_format);

  rb_iv_set(self, "@png", Qnil);
  rb_iv_set(self, "@svg", Qnil);

  return self;
}

static VALUE MATHEMATICAL_process(VALUE self, VALUE rb_LatexCode) {
  Check_Type (rb_LatexCode, T_STRING);

  unsigned long maxsize = (unsigned long) FIX2INT(rb_iv_get(self, "@maxsize"));

  const char *latex_code = StringValueCStr(rb_LatexCode);
  unsigned long latex_size = (unsigned long) strlen(latex_code);

  // make sure that the passed latex string is not larger than the maximum value of a signed long (or the maxsize option)
  if (maxsize == 0)
    maxsize = LONG_MAX;

  if (latex_size > maxsize)
    rb_raise(rb_eMaxsizeError, "Size of latex string (%lu) is greater than the maxsize (%lu)!", latex_size, maxsize);

#if !GLIB_CHECK_VERSION(2,36,0)
  g_type_init ();
#endif

  VALUE result_hash = rb_hash_new();
  const char* rb_format = RSTRING_PTR(rb_iv_get(self, "@format"));

  // convert the TeX math to MathML
  char * mathml = lsm_mtex_to_mathml(latex_code, latex_size);
  if (mathml == NULL) rb_raise(rb_eParseError, "Failed to parse mtex");

  if (strncmp(rb_format, "mathml", 6) == 0) {
    rb_hash_aset (result_hash, rb_tainted_str_new2 ("mathml"),    rb_str_new2(mathml));
    mtex2MML_free_string(mathml);
    return result_hash;
  }

  int mathml_size = strlen(mathml);

  LsmDomDocument *document;
  document = lsm_dom_document_new_from_memory(mathml, mathml_size, NULL);

  lsm_mtex_free_mathml_buffer(mathml);

  if (document == NULL) rb_raise(rb_eDocumentCreationError, "Failed to create document");

  LsmDomView *view;
  FileFormat format;

  double ppi = NUM2DBL(rb_iv_get(self, "@ppi"));
  double zoom = NUM2DBL(rb_iv_get(self, "@zoom"));

  view = lsm_dom_document_create_view (document);
  lsm_dom_view_set_resolution (view, ppi);

  double width_pt = 2.0, height_pt = 2.0;
  unsigned int height, width;

  lsm_dom_view_get_size (view, &width_pt, &height_pt, NULL);
  lsm_dom_view_get_size_pixels (view, &width, &height, NULL);

  width_pt *= zoom;
  height_pt *= zoom;

  cairo_t *cairo;
  cairo_surface_t *surface;

  if (strncmp(rb_format, "svg", 3) == 0) {
    format = FORMAT_SVG;
    surface = cairo_svg_surface_create_for_stream (cairoSvgSurfaceCallback, self, width_pt, height_pt);
  }
  else if (strncmp(rb_format, "png", 3) == 0) {
    format = FORMAT_PNG;
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
  }

  cairo = cairo_create (surface);
  cairo_surface_destroy (surface);
  cairo_scale (cairo, zoom, zoom);
  lsm_dom_view_render (view, cairo, 0, 0);

  switch (format) {
    case FORMAT_PNG:
      cairo_surface_write_to_png_stream (cairo_get_target (cairo), cairoPngSurfaceCallback, self);
      break;
    default:
      break;
  }

  cairo_destroy (cairo);
  g_object_unref (view);
  g_object_unref (document);

  switch (format) {
    case FORMAT_SVG:
      if (rb_iv_get(self, "@svg") == Qnil) rb_raise(rb_eDocumentReadError, "Failed to read SVG contents");
      rb_hash_aset (result_hash, rb_tainted_str_new2 ("svg"),    rb_iv_get(self, "@svg"));
      break;
    case FORMAT_PNG:
      if (rb_iv_get(self, "@png") == Qnil) rb_raise(rb_eDocumentReadError, "Failed to read PNG contents");
      rb_hash_aset (result_hash, rb_tainted_str_new2 ("png"),    rb_iv_get(self, "@png"));
      break;
    default:
      break;
  }

  rb_hash_aset (result_hash, rb_tainted_str_new2 ("width"),  INT2FIX(width_pt));
  rb_hash_aset (result_hash, rb_tainted_str_new2 ("height"), INT2FIX(height_pt));

  // we need to clear out this key when attempting multiple calls. See http://git.io/i1hblQ
  rb_iv_set(self, "@svg", Qnil);
  rb_iv_set(self, "@png", Qnil);

  return result_hash;
}

void Init_mathematical() {
  rb_mMathematical = rb_define_module("Mathematical");

  rb_cMathematicalProcess = rb_define_class_under(rb_mMathematical, "Process", rb_cObject);
  rb_eMaxsizeError = rb_define_class_under(rb_mMathematical, "MaxsizeError", rb_eStandardError);
  rb_eParseError = rb_define_class_under(rb_mMathematical, "ParseError", rb_eStandardError);
  rb_eDocumentCreationError = rb_define_class_under(rb_mMathematical, "DocumentCreationError", rb_eStandardError);
  rb_eDocumentReadError = rb_define_class_under(rb_mMathematical, "DocumentReadError", rb_eStandardError);

  rb_define_method(rb_cMathematicalProcess, "initialize", MATHEMATICAL_init, 1);
  rb_define_method(rb_cMathematicalProcess, "process", MATHEMATICAL_process, 1);
}
