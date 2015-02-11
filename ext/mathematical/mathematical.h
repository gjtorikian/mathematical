#include "ruby.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <lsm.h>
#include <lsmmathml.h>
#include <glib.h>
#include <glib/gi18n.h>
#include <glib/gprintf.h>
#include <gio/gio.h>
#include <cairo-svg.h>

#include "mtex2MML.h"
#include <cairo_callbacks.h>
#include <lasem_overrides.h>

typedef enum {
  FORMAT_SVG,
  FORMAT_PNG,
  FORMAT_MATHML
} FileFormat;
