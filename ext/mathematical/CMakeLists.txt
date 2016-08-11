#
#
#   General project setup
#
#
project(lasem)
enable_language(C)
cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
cmake_policy(SET CMP0015 NEW)

set(LIBRARY "lasem")
set(VERSION 0.6)

find_package(PkgConfig)

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

if(DEFINED $ENV{TRAVIS})
  add_definitions(-DIS_TRAVISCI="true")
endif()

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

include_directories(${LIBRARY}
  ${INCLUDE_DIRS}
  ${GLIB2_INCLUDE_DIRS}
  ${CAIRO_INCLUDE_DIRS}
  ${PANGO_INCLUDE_DIRS}
  ${GDK-PIXBUF2_INCLUDE_DIRS}
  ${LIBXML2_INCLUDE_DIRS}
  ${GIO2_INCLUDE_DIRS}
  ${PANGO_CAIRO_INCLUDE_DIRS}
)

target_link_libraries(${LIBRARY}
  ${GLIB2_LIBRARIES}
  ${CAIRO_LIBRARIES}
  ${PANGO_LIBRARIES}
  ${GDK-PIXBUF2_LIBRARIES}
  ${LIBXML2_LIBRARIES}
  ${GIO2_LIBRARIES}
  ${PANGO_CAIRO_LIBRARIES}
  ${RUBY_LIBRARY}
  ${MTEX2MML_BUILD_DIR}/libmtex2MML.a
)
