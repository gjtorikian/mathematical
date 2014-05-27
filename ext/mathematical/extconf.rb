require 'mkmf'
require 'rbconfig'
host_os = RbConfig::CONFIG['host_os']

LASEM_DIR = File.join(File.dirname(__FILE__), "lasem", "src")
ITEX_DIR = File.join(File.dirname(__FILE__), "itexToMML")

if host_os =~ /darwin|mac os/
  ENV['PKG_CONFIG_PATH'] = "/opt/X11/lib/pkgconfig:#{ENV['PKG_CONFIG_PATH']}"
end

have_library("xml2")
find_header("libxml/tree.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/parser.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/xpath.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/xpathInternals.h", "/usr/include/libxml2", "/usr/local/include/libxml2")

have_library("pangocairo-1.0")

$LDFLAGS += " #{`pkg-config --static --libs glib-2.0 gdk-pixbuf-2.0 cairo pango`.chomp} -I#{LASEM_DIR} -I#{ITEX_DIR}"
$CFLAGS += " #{`pkg-config --cflags glib-2.0 gdk-pixbuf-2.0 cairo pango`.chomp} -I#{LASEM_DIR} -I#{ITEX_DIR}"

create_makefile("mathematical/mathematical")
