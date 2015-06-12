require 'mkmf'
require 'rbconfig'
host_os = RbConfig::CONFIG['host_os']

unless find_executable('cmake')
  $stderr.puts "\n\n\n[ERROR]: cmake is required and not installed. Get it here: http://www.cmake.org/\n\n"
  exit 1
end

ROOT_TMP = File.expand_path(File.join(File.dirname(__FILE__), '..', '..', 'tmp'))
LASEM_DIR = File.expand_path(File.join(File.dirname(__FILE__), 'lasem', 'src'))
MTEX2MML_DIR = File.expand_path(File.join(File.dirname(__FILE__), 'mtex2MML'))
MTEX2MML_BUILD_DIR = File.join(MTEX2MML_DIR, 'build')

if host_os =~ /darwin|mac os/
  ENV['PKG_CONFIG_PATH'] = "/opt/X11/lib/pkgconfig:#{ENV['PKG_CONFIG_PATH']}"
end

# pre-compile checks
have_library('xml2')
have_library('pangocairo-1.0')
find_header('libxml/tree.h', '/include/libxml2', '/usr/include/libxml2', '/usr/local/include/libxml2')
find_header('libxml/parser.h', '/include/libxml2', '/usr/include/libxml2', '/usr/local/include/libxml2')
find_header('libxml/xpath.h', '/include/libxml2', '/usr/include/libxml2', '/usr/local/include/libxml2')
find_header('libxml/xpathInternals.h', '/include/libxml2', '/usr/include/libxml2', '/usr/local/include/libxml2')

# TODO: this is so frakkin' stupid. but I can't seem to get subdirs to compile any other way
# the `destroy_copies` task, immediately after `compile`, will destroy these files
FileUtils.cp_r(Dir.glob("#{LASEM_DIR}/*"), File.dirname(__FILE__))
File.delete(File.join(File.dirname(__FILE__), 'lasemrender.c'))

# TODO: we need to clear out the build dir that's erroneously getting packaged
# this causes problems, as Linux installation is expecting OS X output
if File.directory?(MTEX2MML_BUILD_DIR) && !File.exist?(ROOT_TMP)
  FileUtils.rm_rf(MTEX2MML_BUILD_DIR)
end
FileUtils.mkdir_p(MTEX2MML_BUILD_DIR)

# build mtex2MML library
Dir.chdir(MTEX2MML_BUILD_DIR) do
  system 'cmake ..'
  system 'make libmtex2MML_static'
end

FileUtils.cp_r(Dir.glob(File.join(MTEX2MML_DIR, 'build', '*.{a,h}')), File.dirname(__FILE__))

$LDFLAGS << " #{`pkg-config --static --libs glib-2.0 gdk-pixbuf-2.0 cairo pango`.chomp}"
$CFLAGS << " -O2 #{`pkg-config --cflags glib-2.0 gdk-pixbuf-2.0 cairo pango`.chomp} -I#{LASEM_DIR}"
$LOCAL_LIBS << "#{MTEX2MML_DIR}/build/libmtex2MML.a"

create_makefile('mathematical/mathematical')
