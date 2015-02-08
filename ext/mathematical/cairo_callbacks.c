#include <cairo_callbacks.h>

cairo_status_t cairoSvgSurfaceCallback (void *closure, const unsigned char *data, unsigned int length)
{
  VALUE self = (VALUE) closure;
  if (rb_iv_get(self, "@svg") == Qnil) {
    rb_iv_set(self, "@svg", rb_str_new2(""));
  }

  rb_str_cat(rb_iv_get(self, "@svg"), data, length);

  return CAIRO_STATUS_SUCCESS;
}

cairo_status_t cairoPngSurfaceCallback (void *closure, const unsigned char *data, unsigned int length)
{
  VALUE self = (VALUE) closure;
  if (rb_iv_get(self, "@png") == Qnil) {
    rb_iv_set(self, "@png", rb_str_new2(""));
  }

  rb_str_cat(rb_iv_get(self, "@png"), data, length);

  return CAIRO_STATUS_SUCCESS;
}
