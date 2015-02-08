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
#include <lasem_overrides.h>
