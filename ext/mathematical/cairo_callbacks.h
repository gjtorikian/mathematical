#ifndef CAIRO_OVERRIDES_H
#define CAIRO_OVERRIDES_H

#include "ruby.h"

#include <cairo-svg.h>

extern cairo_status_t cairoSvgSurfaceCallback (void *closure, const unsigned char *data, unsigned int length);

extern cairo_status_t cairoPngSurfaceCallback (void *closure, const unsigned char *data, unsigned int length);

#endif
