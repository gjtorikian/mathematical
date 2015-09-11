require 'mkmf'
require 'rbconfig'

HOST_OS = RbConfig::CONFIG['host_os']
LIBDIR     = RbConfig::CONFIG['libdir']
INCLUDEDIR = RbConfig::CONFIG['includedir']

unless find_executable('cmake')
  $stderr.puts "\n\n\n[ERROR]: cmake is required and not installed. Get it here: http://www.cmake.org/\n\n"
  exit 1
end

ROOT_TMP = File.expand_path(File.join(File.dirname(__FILE__), '..', '..', 'tmp'))
LASEM_DIR = File.expand_path(File.join(File.dirname(__FILE__), 'lasem'))
LASEM_SRC_DIR = File.join(LASEM_DIR, 'src')
LASEM_LIB_DIR = File.join(LASEM_SRC_DIR, '.libs')
MTEX2MML_DIR = File.expand_path(File.join(File.dirname(__FILE__), 'mtex2MML'))
MTEX2MML_BUILD_DIR = File.join(MTEX2MML_DIR, 'build')
MTEX2MML_LIB_DIR = File.expand_path(File.join(File.dirname(__FILE__), 'lib'))
MTEX2MML_SRC_DIR = File.expand_path(File.join(MTEX2MML_DIR, 'src'))

if HOST_OS =~ /darwin|mac os/
  ENV['PKG_CONFIG_PATH'] = "/opt/X11/lib/pkgconfig:#{ENV['PKG_CONFIG_PATH']}"
end

# pre-compile checks
have_library('xml2')
have_library('pangocairo-1.0')
find_header('libxml/tree.h', '/include/libxml2', '/usr/include/libxml2', '/usr/local/include/libxml2')
find_header('libxml/parser.h', '/include/libxml2', '/usr/include/libxml2', '/usr/local/include/libxml2')
find_header('libxml/xpath.h', '/include/libxml2', '/usr/include/libxml2', '/usr/local/include/libxml2')
find_header('libxml/xpathInternals.h', '/include/libxml2', '/usr/include/libxml2', '/usr/local/include/libxml2')

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

# build Lasem library
# MUST BE DYNAMICALLY LINKED for potential LGPL copyright issues
Dir.chdir(LASEM_DIR) do
  system './autogen.sh'
  system 'make clean' # being cautious
  system 'make'
end

FileUtils.mkdir_p(MTEX2MML_LIB_DIR)
FileUtils.cp_r(File.join(MTEX2MML_BUILD_DIR, 'libmtex2MML.a'), MTEX2MML_LIB_DIR)

LIB_DIRS = [MTEX2MML_LIB_DIR, LASEM_LIB_DIR]
HEADER_DIRS = [MTEX2MML_SRC_DIR, LASEM_SRC_DIR]

dir_config('mathematical', HEADER_DIRS, LIB_DIRS)

unless Dir.exist?(LASEM_LIB_DIR)
  abort 'liblasem is missing.'
end

find_header('mtex2MML.h', MTEX2MML_SRC_DIR)

$LDFLAGS << " #{`pkg-config --static --libs glib-2.0 gdk-pixbuf-2.0 cairo pango`.chomp} -lmtex2MML -llasem-0.6"
$CFLAGS << " -O2 #{`pkg-config --cflags glib-2.0 gdk-pixbuf-2.0 cairo pango`.chomp} -I#{LASEM_DIR}"

create_makefile('mathematical/mathematical')
