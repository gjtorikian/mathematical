/****************************************************************************
* Mathematical Copyright(c) 2014, Garen J. Torikian, All rights reserved.
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

#include <mathematical.h>

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

static VALUE MATHEMATICAL_init(VALUE self, VALUE rb_Options)
{
  Check_Type (rb_Options, T_HASH);
  VALUE rb_ppi, rb_zoom, rb_maxsize, rb_format, rb_delimiter;

  rb_ppi = rb_hash_aref(rb_Options, CSTR2SYM("ppi"));
  rb_zoom = rb_hash_aref(rb_Options, CSTR2SYM("zoom"));
  rb_maxsize = rb_hash_aref(rb_Options, CSTR2SYM("maxsize"));
  rb_format = rb_hash_aref(rb_Options, CSTR2SYM("formatInt"));
  rb_delimiter = rb_hash_aref(rb_Options, CSTR2SYM("delimiter"));

  Check_Type(rb_ppi, T_FLOAT);
  Check_Type(rb_zoom, T_FLOAT);
  Check_Type(rb_maxsize, T_FIXNUM);
  Check_Type(rb_format, T_FIXNUM);
  Check_Type(rb_delimiter, T_FIXNUM);

  rb_iv_set(self, "@ppi", rb_ppi);
  rb_iv_set(self, "@zoom", rb_zoom);
  rb_iv_set(self, "@maxsize", rb_maxsize);
  rb_iv_set(self, "@format", rb_format);
  rb_iv_set(self, "@delimiter", rb_delimiter);

  rb_iv_set(self, "@png", Qnil);
  rb_iv_set(self, "@svg", Qnil);

  return self;
}

void print_and_raise(VALUE error_type, const char* format, ...)
{
  va_list args;
  va_start(args, format);

  vfprintf(stderr, format, args);
  rb_raise(error_type, format, args);

  va_end(args);
}

static VALUE process_rescue(VALUE args, VALUE exception_object)
{
  VALUE rescue_hash = rb_hash_new();

  rb_hash_aset (rescue_hash, CSTR2SYM ("data"), args);
  rb_hash_aset (rescue_hash, CSTR2SYM ("exception"), exception_object);

  return rescue_hash;
}

VALUE process(VALUE self, unsigned long maxsize, const char *latex_code, unsigned long latex_size, int delimiter, int parse_type)
{
  if (latex_size > maxsize) {
    print_and_raise(rb_eMaxsizeError, "Size of latex string is greater than the maxsize");
  }

  VALUE result_hash = rb_hash_new();
  FileFormat format = (FileFormat) FIX2INT(rb_iv_get(self, "@format"));

  /* convert the TeX math to MathML */
  char * mathml = lsm_mtex_to_mathml(latex_code, latex_size, delimiter, parse_type);
  if (mathml == NULL) { print_and_raise(rb_eParseError, "Failed to parse mtex"); }

  if (format == FORMAT_MATHML || parse_type == TEXT_FILTER) {
    rb_hash_aset (result_hash, CSTR2SYM ("data"), rb_str_new2(mathml));
    mtex2MML_free_string(mathml);
    return result_hash;
  }

  int mathml_size = strlen(mathml);

  LsmDomDocument *document;
  document = lsm_dom_document_new_from_memory(mathml, mathml_size, NULL);

  lsm_mtex_free_mathml_buffer(mathml);

  if (document == NULL) { print_and_raise(rb_eDocumentCreationError, "Failed to create document"); }

  LsmDomView *view;

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

  if (format == FORMAT_SVG) {
    surface = cairo_svg_surface_create_for_stream (cairoSvgSurfaceCallback, (VALUE*)self, width_pt, height_pt);
  } else if (format == FORMAT_PNG) {
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
  }

  cairo = cairo_create (surface);
  cairo_scale (cairo, zoom, zoom);
  lsm_dom_view_render (view, cairo, 0, 0);

  switch (format) {
  case FORMAT_PNG:
    cairo_surface_write_to_png_stream (cairo_get_target (cairo), cairoPngSurfaceCallback, (VALUE*)self);
    break;
  default:
    break;
  }

  cairo_destroy (cairo);
  cairo_surface_destroy (surface);
  g_object_unref (view);
  g_object_unref (document);

  switch (format) {
  case FORMAT_SVG: {
    if (rb_iv_get(self, "@svg") == Qnil) { print_and_raise(rb_eDocumentReadError, "Failed to read SVG contents"); }
    rb_hash_aset (result_hash, CSTR2SYM ("data"), rb_iv_get(self, "@svg"));
    break;
  }
  case FORMAT_PNG: {
    if (rb_iv_get(self, "@png") == Qnil) { print_and_raise(rb_eDocumentReadError, "Failed to read PNG contents"); }
    rb_hash_aset (result_hash, CSTR2SYM ("data"), rb_iv_get(self, "@png"));
    break;
  }
  default: {
    /* should be impossible, Ruby code prevents this */
    print_and_raise(rb_eTypeError, "not valid format");
    break;
  }
  }

  rb_hash_aset (result_hash, CSTR2SYM ("width"),  INT2FIX(width_pt));
  rb_hash_aset (result_hash, CSTR2SYM ("height"), INT2FIX(height_pt));

  /* we need to clear out this key when attempting multiple calls. See http://git.io/i1hblQ */
  rb_iv_set(self, "@svg", Qnil);
  rb_iv_set(self, "@png", Qnil);

  return result_hash;
}

/* `process` can potentially raise a bunch of exceptions, so we need to wrap
   the call in a rescue. And `rb_rescue` only takes one argument, so we need
   to pack everything in an array, and then unpack it in `process_helper`. */
static VALUE process_helper(VALUE data)
{
  VALUE *args = (VALUE *) data;

  return process(args[0], NUM2ULONG(args[1]), StringValueCStr(args[2]), NUM2ULONG(args[3]), NUM2INT(args[4]), NUM2INT(args[5]));
}

static VALUE MATHEMATICAL_process(VALUE self, VALUE rb_Input, VALUE rb_ParseType)
{
  Check_Type(rb_ParseType, T_FIXNUM);

  unsigned long maxsize = (unsigned long) FIX2INT(rb_iv_get(self, "@maxsize"));

  /* make sure that the passed latex string is not larger than the maximum value of
    a signed long (or the maxsize option) */
  if (maxsize == 0) {
    maxsize = LONG_MAX;
  }

#if !GLIB_CHECK_VERSION(2,36,0)
  g_type_init ();
#endif

  const char *latex_code;
  unsigned long latex_size;

  VALUE output;

  switch (TYPE(rb_Input)) {
  case T_STRING: {
    latex_code = StringValueCStr(rb_Input);
    latex_size = (unsigned long) strlen(latex_code);

    VALUE args[6];
    args[0] = self;
    args[1] = ULONG2NUM(maxsize);
    args[2] = rb_Input;
    args[3] = ULONG2NUM(latex_size);
    args[4] = rb_iv_get(self, "@delimiter");
    args[5] = rb_ParseType;

    output = rb_rescue(process_helper, (VALUE)args, process_rescue, rb_Input);
    break;
  }
  case T_ARRAY: {
    int length = RARRAY_LEN(rb_Input), i;
    VALUE hash;
    output = rb_ary_new2(length);

    for (i = 0; i < length; i++) {
      /* grab the ith element */
      VALUE math = rb_ary_entry(rb_Input, i);

      /* get the string and length */
      latex_code = StringValueCStr(math);
      latex_size = (unsigned long) strlen(latex_code);

      VALUE args[6];
      args[0] = self;
      args[1] = ULONG2NUM(maxsize);
      args[2] = math;
      args[3] = ULONG2NUM(latex_size);
      args[4] = rb_iv_get(self, "@delimiter");
      args[5] = rb_ParseType;

      hash = rb_rescue(process_helper, (VALUE)args, process_rescue, math);

      rb_ary_store(output, i, hash);
    }
    break;
  }
  default: {
    /* should be impossible, Ruby code prevents this */
    print_and_raise(rb_eTypeError, "not valid value");
    output = (VALUE)NULL;
    break;
  }
  }

  return output;
}

void Init_mathematical()
{
  rb_mMathematical = rb_define_class("Mathematical", rb_cObject);

  rb_cMathematicalProcess = rb_define_class_under(rb_mMathematical, "Process", rb_cObject);
  rb_eMaxsizeError = rb_define_class_under(rb_mMathematical, "MaxsizeError", rb_eStandardError);
  rb_eParseError = rb_define_class_under(rb_mMathematical, "ParseError", rb_eStandardError);
  rb_eDocumentCreationError = rb_define_class_under(rb_mMathematical, "DocumentCreationError", rb_eStandardError);
  rb_eDocumentReadError = rb_define_class_under(rb_mMathematical, "DocumentReadError", rb_eStandardError);

  rb_define_method(rb_cMathematicalProcess, "initialize", MATHEMATICAL_init, 1);
  rb_define_method(rb_cMathematicalProcess, "process", MATHEMATICAL_process, 2);
}
