# frozen_string_literal: true

# rubocop:disable Style/GlobalVars

ENV["RC_ARCHS"] = "" if RUBY_PLATFORM.match?(/darwin|mac os/)

require "mkmf"
require "rbconfig"
require "fileutils"

OS = case RbConfig::CONFIG["host_os"]
when /mswin|msys|mingw|cygwin|bccwin|wince|emc/
  :windows
when /darwin|mac os/
  :macos
when /linux/
  :linux
when /solaris|bsd/
  :unix
else
  raise "unknown os: #{RbConfig::CONFIG["host_os"].inspect}"
end

LIBDIR     = RbConfig::CONFIG["libdir"]
INCLUDEDIR = RbConfig::CONFIG["includedir"]

SHARED_EXT = case OS
when :macos then "dylib"
when :windows then "dll"
else "so"
end

# Starting in Catalina, libxml2 was moved elsewhere
SDKROOT = OS == :macos ? %x(/usr/bin/xcrun --show-sdk-path).chomp : ""
RPATH = OS == :macos ? "-rpath @loader_path/../../ext/mathematical/lib" : ""

# Windows needs the MSYS Makefiles generator for cmake
CMAKE_GENERATOR = OS == :windows ? '-G "MSYS Makefiles"' : ""

# Cross-compilation support
CROSS_BUILD = enable_config("cross-build", false)
if CROSS_BUILD
  # In cross-compilation mode, use the cross-compiler
  RbConfig::CONFIG["CC"] = ENV["CC"] if ENV["CC"]
  RbConfig::CONFIG["CXX"] = ENV["CXX"] if ENV["CXX"]
end

unless find_executable("cmake")
  $stderr.puts "\n\n\n[ERROR]: cmake is required and not installed. Get it here: http://www.cmake.org/\n\n"
  exit 1
end

def using_system_lasem?
  arg_config("--use-system-lasem", !!ENV["MATHEMATICAL_USE_SYSTEM_LASEM"])
end

def using_system_mtex2mml?
  arg_config("--use-system-mtex2MML", !!ENV["MATHEMATICAL_USE_SYSTEM_MTEX2MML"])
end

# Check for vendored static dependencies (built by script/build_static_deps)
VENDOR_DIR = File.expand_path(File.join(File.dirname(__FILE__), "..", "..", "vendor"))
if File.directory?(File.join(VENDOR_DIR, "lib"))
  ENV["PKG_CONFIG_PATH"] = "#{File.join(VENDOR_DIR, "lib", "pkgconfig")}:#{File.join(VENDOR_DIR, "lib64", "pkgconfig")}:#{ENV["PKG_CONFIG_PATH"]}"
  ENV["PKG_CONFIG_LIBDIR"] = "" if CROSS_BUILD # Don't search system pkg-config in cross mode
  puts "*** Using vendored static deps from #{VENDOR_DIR} ***"
end

LASEM_DIR = File.expand_path(File.join(File.dirname(__FILE__), "lasem"))
LASEM_BUILD_DIR = File.join(LASEM_DIR, "build")
LASEM_SRC_DIR = File.expand_path(File.join(LASEM_DIR, "src"))
LASEM_LIB_DIR = File.expand_path(File.join(File.dirname(__FILE__), "lib"))

MTEX2MML_DIR = File.expand_path(File.join(File.dirname(__FILE__), "mtex2MML"))
MTEX2MML_BUILD_DIR = File.join(MTEX2MML_DIR, "build")
MTEX2MML_SRC_DIR = File.expand_path(File.join(MTEX2MML_DIR, "src"))
MTEX2MML_LIB_DIR = File.expand_path(File.join(File.dirname(__FILE__), "lib"))

if OS == :macos
  # Homebrew paths must come before X11 so we get newer versions of libs like cairo
  homebrew_prefix = %x(brew --prefix 2>/dev/null).chomp
  homebrew_pkgconfig = "#{homebrew_prefix}/lib/pkgconfig" unless homebrew_prefix.empty?
  ENV["PKG_CONFIG_PATH"] = [homebrew_pkgconfig, "/opt/X11/lib/pkgconfig", ENV["PKG_CONFIG_PATH"]].compact.join(":")
end

# pre-compile checks
have_library("xml2")
have_library("pangocairo-1.0")
find_header("libxml/tree.h", "/include/libxml2", "/usr/include/libxml2", "/usr/local/include/libxml2", "#{SDKROOT}/usr/include/libxml2")
find_header("libxml/parser.h", "/include/libxml2", "/usr/include/libxml2", "/usr/local/include/libxml2", "#{SDKROOT}/usr/include/libxml2")
find_header("libxml/xpath.h", "/include/libxml2", "/usr/include/libxml2", "/usr/local/include/libxml2", "#{SDKROOT}/usr/include/libxml2")
find_header("libxml/xpathInternals.h", "/include/libxml2", "/usr/include/libxml2", "/usr/local/include/libxml2", "#{SDKROOT}/usr/include/libxml2")

def clean_dir(dir)
  if File.directory?(dir)
    FileUtils.rm_rf(dir)
  end
  FileUtils.mkdir_p(dir)
end

clean_dir(MTEX2MML_BUILD_DIR)
clean_dir(LASEM_BUILD_DIR)

# Pass cross-compiler settings to cmake if available
cmake_env = ""
if ENV["CC"]
  cmake_env += " -DCMAKE_C_COMPILER=#{ENV["CC"]}"
end
if ENV["CXX"]
  cmake_env += " -DCMAKE_CXX_COMPILER=#{ENV["CXX"]}"
end

if !using_system_mtex2mml?
  # build mtex2MML library
  Dir.chdir(MTEX2MML_BUILD_DIR) do # rubocop:disable ThreadSafety/DirChdir
    system "cmake #{CMAKE_GENERATOR}#{cmake_env} .."
    system "make libmtex2MML_static"
  end
  FileUtils.mkdir_p(MTEX2MML_LIB_DIR)
  FileUtils.cp_r(File.join(MTEX2MML_BUILD_DIR, "libmtex2MML.a"), MTEX2MML_LIB_DIR)
  $LIBS << " -lmtex2MML"
elsif dir_config("mtex2MML").any? || system("dpkg -s libmtex2MML >/dev/null 2>&1")
  $LIBS << " -lmtex2MML"
else
  pkg_config("libmtex2MML") || pkg_config("mtex2MML")
end

if !using_system_lasem?
  # build Lasem library as STATIC (linked directly into the Ruby extension)
  Dir.chdir(LASEM_BUILD_DIR) do # rubocop:disable ThreadSafety/DirChdir
    system "cmake #{CMAKE_GENERATOR}#{cmake_env} ../.."
    system "make"
  end
  FileUtils.mkdir_p(LASEM_LIB_DIR)
  FileUtils.cp_r(File.join(LASEM_BUILD_DIR, "liblasem.a"), LASEM_LIB_DIR)
  $LIBS << " -llasem"
elsif dir_config("lasem").any? || system("dpkg -s liblasem >/dev/null 2>&1")
  $LIBS << " -llasem"
else
  pkg_config("liblasem") || pkg_config("lasem")
end

puts "*** Library work completed ***"

LIB_DIRS = [MTEX2MML_LIB_DIR, LASEM_LIB_DIR]
HEADER_DIRS = [MTEX2MML_SRC_DIR, LASEM_SRC_DIR]

dir_config("mathematical", HEADER_DIRS, LIB_DIRS)

find_header("mtex2MML.h", MTEX2MML_SRC_DIR)

flag = ENV["CI"] ? "-O0" : "-O2"

# Get link flags — prefer static linking when available
pkg_config_static_flag = File.directory?(VENDOR_DIR) ? "--static" : ""

# Link flags for system libraries must appear AFTER -llasem and -lmtex2MML
# because the linker resolves symbols left-to-right: liblasem.a references
# glib/libxml2 symbols, so those libs must come after -llasem.
# We append directly to $LIBS (which becomes LOCAL_LIBS in the Makefile)
# to guarantee correct ordering on all platforms including Windows.
pkg_packages = "glib-2.0 gdk-pixbuf-2.0 cairo pango pangocairo gio-2.0 libxml-2.0"
pkg_libs = %x(pkg-config #{pkg_config_static_flag} --libs #{pkg_packages}).chomp
puts "*** pkg-config --libs: #{pkg_libs} ***"
$LIBS << " #{pkg_libs}"

$LDFLAGS << " #{RPATH}" unless RPATH.empty?
$CFLAGS << " #{flag} #{%x(pkg-config --cflags glib-2.0 gdk-pixbuf-2.0 cairo pango).chomp}"

# fPIC is needed for linking static libs into the shared extension
$CFLAGS << " -fPIC" unless OS == :windows

create_makefile("mathematical/mathematical")

# rubocop:enable Style/GlobalVars
