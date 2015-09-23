require 'mkmf'
require 'rbconfig'

HOST_OS    = RbConfig::CONFIG['host_os']
LIBDIR     = RbConfig::CONFIG['libdir']
INCLUDEDIR = RbConfig::CONFIG['includedir']
SHARED_EXT = if HOST_OS =~ /darwin|mac os/
               'dylib'
             else
               'so'
             end

unless find_executable('cmake')
  $stderr.puts "\n\n\n[ERROR]: cmake is required and not installed. Get it here: http://www.cmake.org/\n\n"
  exit 1
end

def using_system_lasem?
  arg_config('--use-system-lasem', !!ENV['MATHEMATICAL_USE_SYSTEM_LASEM'])
end

ROOT_TMP = File.expand_path(File.join(File.dirname(__FILE__), '..', '..', 'tmp'))

LASEM_DIR = File.expand_path(File.join(File.dirname(__FILE__), 'lasem'))
LASEM_BUILD_DIR = File.join(LASEM_DIR, 'build')
LASEM_SRC_DIR = File.expand_path(File.join(LASEM_DIR, 'src'))
LASEM_LIB_DIR = File.expand_path(File.join(File.dirname(__FILE__), 'lib'))

MTEX2MML_DIR = File.expand_path(File.join(File.dirname(__FILE__), 'mtex2MML'))
MTEX2MML_BUILD_DIR = File.join(MTEX2MML_DIR, 'build')
MTEX2MML_SRC_DIR = File.expand_path(File.join(MTEX2MML_DIR, 'src'))
MTEX2MML_LIB_DIR = File.expand_path(File.join(File.dirname(__FILE__), 'lib'))

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
def clean_dir(dir)
  if File.directory?(dir) && !File.exist?(ROOT_TMP)
    FileUtils.rm_rf(dir)
  end
  FileUtils.mkdir_p(dir)
end

clean_dir(MTEX2MML_BUILD_DIR)
clean_dir(LASEM_BUILD_DIR)

# build mtex2MML library
Dir.chdir(MTEX2MML_BUILD_DIR) do
  system 'cmake ..'
  system 'make libmtex2MML_static'
end

if !using_system_lasem?
  # build Lasem library
  # SHOULD BE DYNAMICALLY LINKED for potential LGPL copyright issues
  Dir.chdir(LASEM_BUILD_DIR) do
    system 'cmake ../..'
    system 'make'
  end
else
  dir_config('lasem').any? || pkg_config('liblasem') || system('dpkg -s lasem >/dev/null')
end

FileUtils.mkdir_p(MTEX2MML_LIB_DIR)
FileUtils.cp_r(File.join(MTEX2MML_BUILD_DIR, 'libmtex2MML.a'), MTEX2MML_LIB_DIR)

FileUtils.mkdir_p(LASEM_LIB_DIR)
FileUtils.cp_r(File.join(LASEM_BUILD_DIR, "liblasem.#{SHARED_EXT}"), LASEM_LIB_DIR)

LIB_DIRS = [MTEX2MML_LIB_DIR, LASEM_LIB_DIR]
HEADER_DIRS = [MTEX2MML_SRC_DIR, LASEM_SRC_DIR]

dir_config('mathematical', HEADER_DIRS, LIB_DIRS)

find_header('mtex2MML.h', MTEX2MML_SRC_DIR)

$LDFLAGS << " #{`pkg-config --static --libs glib-2.0 gdk-pixbuf-2.0 cairo pango`.chomp}"
$CFLAGS << " -O2 #{`pkg-config --cflags glib-2.0 gdk-pixbuf-2.0 cairo pango`.chomp}"
$LIBS << ' -lmtex2MML -llasem'

create_makefile('mathematical/mathematical')
