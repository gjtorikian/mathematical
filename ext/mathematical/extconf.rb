require 'mkmf'

system("export PKG_CONFIG_PATH=/opt/X11/lib/pkgconfig:$PKG_CONFIG_PATH")

have_library("xml2")
find_header("libxml/tree.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/parser.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/xpath.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/xpathInternals.h", "/usr/include/libxml2", "/usr/local/include/libxml2")

have_library("pangocairo-1.0")

$LDFLAGS += " #{`pkg-config --static --libs glib-2.0 gdk-pixbuf-2.0 cairo pango`}"
$CFLAGS += " #{`pkg-config --cflags glib-2.0 gdk-pixbuf-2.0 cairo pango`}"

with_cflags("-DGTK_DISABLE_DEPRECATED") do
  create_makefile("mathematical/mathematical")
end
