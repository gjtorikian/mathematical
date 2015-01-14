require 'mkmf'
require 'rbconfig'
host_os = RbConfig::CONFIG['host_os']

LASEM_DIR = File.join(File.dirname(__FILE__), "lasem", "src")
MTEX_DIR = File.join(File.dirname(__FILE__), "mtex2MML", "src")

if host_os =~ /darwin|mac os/
  ENV['PKG_CONFIG_PATH'] = "/opt/X11/lib/pkgconfig:#{ENV['PKG_CONFIG_PATH']}"
end

have_library("xml2")
find_header("libxml/tree.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/parser.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/xpath.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/xpathInternals.h", "/usr/include/libxml2", "/usr/local/include/libxml2")

# TODO: this is so frakkin' stupid. but I can't seem to get subdirs to compile any other way
# the `destroy_copies` task, immediately after `compile`, will destroy these files
FileUtils.cp_r(Dir.glob("#{LASEM_DIR}/*"), File.dirname(__FILE__))
File.delete(File.join(File.dirname(__FILE__), "lasemrender.c"))

# build mtex2MML Bison files
Dir.chdir(MTEX_DIR) do
  system "make"
end

FileUtils.cp_r(Dir.glob("#{MTEX_DIR}/*.{c,h,cc}"), File.dirname(__FILE__))
FileUtils.cp_r("#{MTEX_DIR}/deps/.", File.dirname(__FILE__))
FileUtils.cp_r(Dir.glob("#{MTEX_DIR}/deps/**/*"), File.dirname(__FILE__))

have_library("pangocairo-1.0")

$LDFLAGS += " #{`pkg-config --static --libs glib-2.0 gdk-pixbuf-2.0 cairo pango`.chomp}"
$CFLAGS += " #{`pkg-config --cflags glib-2.0 gdk-pixbuf-2.0 cairo pango`.chomp} -I#{LASEM_DIR} -I#{MTEX_DIR}"

create_makefile("mathematical/mathematical")
