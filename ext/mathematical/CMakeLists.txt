#
#
#   General project setup
#
#
project(lasem)
enable_language(C)
cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
cmake_policy(SET CMP0015 NEW)
set(CMAKE_MACOSX_RPATH 1)

set(LIBRARY "lasem")
set(VERSION 0.6)

find_package(PkgConfig REQUIRED)

set(LASEM_SRC_DIR ${CMAKE_SOURCE_DIR}/lasem/src/)
set(MTEX2MML_SRC_DIR ${CMAKE_SOURCE_DIR}/mtex2MML/src/)
set(MTEX2MML_BUILD_DIR ${CMAKE_SOURCE_DIR}/mtex2MML/build/)
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${RUBY_INCLUDE_PATH} ${MTEX2MML_SRC_DIR} ${LASEM_SRC_DIR})

file(GLOB_RECURSE LASEM_SRC ${LASEM_SRC_DIR}/*.c)
file(GLOB_RECURSE LASEM_HEADERS ${LASEM_SRC_DIR}/*.h)
list(REMOVE_ITEM LASEM_SRC "${LASEM_SRC_DIR}/lasemrender.c")
list(REMOVE_ITEM LASEM_SRC "${LASEM_SRC_DIR}/lsmitex.c")
list(APPEND LASEM_SRC "${CMAKE_SOURCE_DIR}/lasem_overrides.c")

# If you're reading this and it's giving you errors, fix it and send
# me the patch.  Much appreciated.
add_definitions(-DPACKAGE_LOCALE_DIR="/usr/share/locale")

add_library(${LIBRARY} SHARED
            ${LASEM_SRC}
)

#
#
#   Find the `pkg-config` modules
#
#
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(PANGO REQUIRED pango)
pkg_check_modules(GDK-PIXBUF2 REQUIRED gdk-pixbuf-2.0)
pkg_check_modules(LIBXML2 REQUIRED libxml-2.0)
pkg_check_modules(GIO2 REQUIRED gio-2.0)
pkg_check_modules(PANGO_CAIRO REQUIRED pangocairo)

#
#
#   Add the headers and libraries
#
#

# Special MacOS Catalina changes
if(CMAKE_HOST_APPLE AND APPLE)
  if(NOT CMAKE_XCRUN)
    find_program(CMAKE_XCRUN NAMES xcrun)
  endif()
  if(CMAKE_XCRUN)
    execute_process(COMMAND ${CMAKE_XCRUN} --show-sdk-path
      OUTPUT_VARIABLE SDK_PATH
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(LIBXML2_MACOS_INCLUDE_DIRS ${SDK_PATH}/usr/include/libxml2)
    message(STATUS "Found SDK libxml2")
  endif()
endif()

set(GLIB_LIB_SUFFIX 2.0)
set(PANGO_LIB_SUFFIX 1.0)
set(GDK_PIXBUF_LIB_SUFFIX 2.0)

# find dependencies
# glib
find_path(GLIB_INCLUDE_DIR glib.h)
find_library(GLIB_GLIB_LIBRARY glib-${GLIB_LIB_SUFFIX})
find_library(GLIB_GIO_LIBRARY gio-${GLIB_LIB_SUFFIX})
find_library(GLIB_GMODULE_LIBRARY gmodule-${GLIB_LIB_SUFFIX})
find_library(GLIB_GOBJECT_LIBRARY gobject-${GLIB_LIB_SUFFIX})
set(GLIB_LIBRARIES ${GLIB_GLIB_LIBRARY} ${GLIB_GIO_LIBRARY} ${GLIB_GMODULE_LIBRARY} ${GLIB_GOBJECT_LIBRARY})

# pango
find_path(PANGO_INCLUDE_DIR pango/pango.h)
find_library(PANGO_LIBRARY pango-${PANGO_LIB_SUFFIX})
find_library(PANGO_CAIRO_LIBRARY pangocairo-${PANGO_LIB_SUFFIX})
set(PANGO_LIBRARIES ${PANGO_LIBRARY} ${PANGO_CAIRO_LIBRARY})

# cairo
find_library(CAIRO_LIBRARY cairo${CAIRO_LIB_SUFFIX})
find_library(CAIRO_GOBJECT_LIBRARY cairo-gobject${CAIRO_LIB_SUFFIX})
set(CAIRO_LIBRARIES ${CAIRO_LIBRARY} ${CAIRO_GOBJECT_LIBRARY})
find_path(CAIRO_INCLUDE_DIR cairo.h)

# gdk-pixbuf
find_path(GDK_PIXBUF_INCLUDE_DIR gdk-pixbuf/gdk-pixbuf.h)
find_library(GDK_PIXBUF_LIBRARY gdk_pixbuf-${GDK_PIXBUF_LIB_SUFFIX})

include_directories(${LIBRARY}
  ${INCLUDE_DIRS}
  ${GLIB2_INCLUDE_DIRS}
  ${CAIRO_INCLUDE_DIRS}
  ${GDK-PIXBUF2_INCLUDE_DIRS}
  ${LIBXML2_INCLUDE_DIRS}
  ${LIBXML2_MACOS_INCLUDE_DIRS}
  ${GIO2_INCLUDE_DIRS}
  ${PANGO_CAIRO_INCLUDE_DIRS}
)

target_link_libraries(${LIBRARY}
  ${GLIB_LIBRARIES}
  ${CAIRO_LIBRARIES}
  ${PANGO_LIBRARIES}
  ${GDK_PIXBUF_LIBRARY}
  ${LIBXML2_LIBRARIES}
  ${RUBY_LIBRARY}
  ${MTEX2MML_BUILD_DIR}/libmtex2MML.a
)
