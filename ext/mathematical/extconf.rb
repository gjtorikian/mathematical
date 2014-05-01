require 'mkmf'

extension_name = 'mathematical'

# dir_config(extension_name)

pkg_config("glib-2.0")
pkg_config("gdk-pixbuf-2.0")

have_library("xml2")
find_header("libxml/tree.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/parser.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/xpath.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/xpathInternals.h", "/usr/include/libxml2", "/usr/local/include/libxml2")

have_library("cairo")
find_header("cairo.h", "/opt/X11/include/cairo")

have_library("pangocairo")
HEADER_DIRS = [
  # First search /opt/local for macports
  '/opt/boxen/homebrew/Cellar/pango/1.36.3/include/pango-1.0/',
]

LIB_DIRS = [
  # First search /opt/local for macports
  '/opt/boxen/homebrew/opt/pango/lib/'
]

dir_config('pango', HEADER_DIRS, LIB_DIRS)
find_header("pango/pangocairo.h")
find_header("pango/pango-font.h")

unless find_library('pango-1.0', 'pango_font_description_new')
  abort "libpango is missing.  please install libpango"
end

dir_config('pangocairo', HEADER_DIRS, LIB_DIRS)
unless find_library('pangocairo-1.0', 'pango_cairo_font_map_get_default')
  abort "libpango is missing.  please install libpango"
end

find_header("pango/pangocairo.h" , "/opt/boxen/homebrew/Cellar/pango/1.36.3/include/pango-1.0/")
find_header("pango/pango-font.h" , "/opt/boxen/homebrew/Cellar/pango/1.36.3/include/pango-1.0/")
find_header("pango/pango-fontmap.h" , "/opt/boxen/homebrew/Cellar/pango/1.36.3/include/pango-1.0/")

# pangocairo-fontmap.c
create_makefile(extension_name)

# /opt/boxen/homebrew/opt/pango/lib/
# otool -L lib/mathematical.bundle