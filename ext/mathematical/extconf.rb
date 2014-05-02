require 'mkmf'
LIBDIR      = RbConfig::CONFIG['libdir']
INCLUDEDIR  = RbConfig::CONFIG['includedir']

extension_name = 'mathematical'

pkg_config("glib-2.0")
pkg_config("gdk-pixbuf-2.0")

have_library("xml2")
find_header("libxml/tree.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/parser.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/xpath.h", "/usr/include/libxml2", "/usr/local/include/libxml2")
find_header("libxml/xpathInternals.h", "/usr/include/libxml2", "/usr/local/include/libxml2")

have_library("cairo")
find_header("cairo.h", "/opt/X11/include/cairo")

begin
  brew_output = %x[brew list pango]
  match = brew_output.match(/(\S+?\/include\/\S+?)\/pango\/pango-\w+\.h/)
  raise ArgumentError if match.nil?
  brew_pango_includes = match[1]
rescue Errno::ENOENT, ArgumentError
  brew_pango_includes = ""
end

have_library("pangocairo")
HEADER_DIRS = [
  # Depend on Homebrew version first
  brew_pango_includes,

  # Then search /opt/local for macports
  '/opt/local/include',

  # Then search /usr/local for people that installed from source
  '/usr/local/include',

  # Check the ruby install locations
  INCLUDEDIR,

  # Finally fall back to /usr
  '/usr/include',
]

begin
  brew_output = %x[brew list pango]
  match = brew_output.match(/(\S+?\/lib\/)/)
  raise ArgumentError if match.nil?
  brew_pango_lib = match
rescue Errno::ENOENT, ArgumentError
  brew_pango_lib = ""
end

LIB_DIRS = [
  # Depend on Homebrew version first
  brew_pango_lib,

  # Then search /opt/local for macports
  '/opt/local/lib',

  # Then search /usr/local for people that installed from source
  '/usr/local/lib',

  # Check the ruby install locations
  LIBDIR,

  # Finally fall back to /usr
  '/usr/lib',
]

dir_config('pango', HEADER_DIRS, LIB_DIRS)
find_header("pango/pangocairo.h")
find_header("pango/pango-font.h")

unless find_library('pango-1.0', 'pango_font_description_new')
  abort "libpango is missing.  please install libpango"
end

dir_config('pangocairo', HEADER_DIRS, LIB_DIRS)
unless find_library('pangocairo-1.0', 'pango_cairo_font_map_get_default')
  abort "libpangocairo is missing.  please install libpangocairo"
end

find_header("pango/pangocairo.h" , "/opt/boxen/homebrew/Cellar/pango/1.36.3/include/pango-1.0/")
find_header("pango/pango-font.h" , "/opt/boxen/homebrew/Cellar/pango/1.36.3/include/pango-1.0/")
find_header("pango/pango-fontmap.h" , "/opt/boxen/homebrew/Cellar/pango/1.36.3/include/pango-1.0/")

create_makefile(extension_name)
