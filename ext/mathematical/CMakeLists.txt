#
#
#   General project setup
#
#
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(lasem C)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LIBRARY "lasem")
set(VERSION 0.6)

find_package(PkgConfig REQUIRED)

set(LASEM_SRC_DIR ${CMAKE_SOURCE_DIR}/lasem/src/)
set(MTEX2MML_SRC_DIR ${CMAKE_SOURCE_DIR}/mtex2MML/src/)
set(MTEX2MML_BUILD_DIR ${CMAKE_SOURCE_DIR}/mtex2MML/build/)

file(GLOB_RECURSE LASEM_SRC ${LASEM_SRC_DIR}/*.c)
file(GLOB_RECURSE LASEM_HEADERS ${LASEM_SRC_DIR}/*.h)
list(REMOVE_ITEM LASEM_SRC "${LASEM_SRC_DIR}/lasemrender.c")
list(REMOVE_ITEM LASEM_SRC "${LASEM_SRC_DIR}/lsmitex.c")
list(APPEND LASEM_SRC "${CMAKE_SOURCE_DIR}/lasem_overrides.c")

add_definitions(-DPACKAGE_LOCALE_DIR="/usr/share/locale")

# On Windows, when statically linking against glib/pango/gdk-pixbuf DLLs,
# we must tell the headers NOT to use __declspec(dllimport).
if(WIN32)
  add_definitions(
    -DGLIB_STATIC_COMPILATION
    -DGOBJECT_STATIC_COMPILATION
    -DGIO_STATIC_COMPILATION
    -DGDK_PIXBUF_STATIC_COMPILATION
    -DPANGO_STATIC_COMPILATION
    -DCAIRO_WIN32_STATIC_BUILD
  )
endif()

# Build lasem as a STATIC library so it links directly into the Ruby extension.
# Lasem is LGPL-2.1+, but since mathematical is MIT and fully open source,
# LGPL obligations are trivially satisfied (users can rebuild from source).
add_library(${LIBRARY} STATIC
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
pkg_check_modules(GDK_PIXBUF2 REQUIRED gdk-pixbuf-2.0)
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

target_include_directories(${LIBRARY} PRIVATE
  ${MTEX2MML_SRC_DIR}
  ${LASEM_SRC_DIR}
)

target_include_directories(${LIBRARY} PUBLIC
  ${RUBY_INCLUDE_PATH}
  ${GLIB2_INCLUDE_DIRS}
  ${CAIRO_INCLUDE_DIRS}
  ${GDK_PIXBUF2_INCLUDE_DIRS}
  ${LIBXML2_INCLUDE_DIRS}
  ${LIBXML2_MACOS_INCLUDE_DIRS}
  ${GIO2_INCLUDE_DIRS}
  ${PANGO_CAIRO_INCLUDE_DIRS}
)

target_link_libraries(${LIBRARY}
  ${GLIB2_LIBRARIES}
  ${CAIRO_LIBRARIES}
  ${PANGO_LIBRARIES}
  ${GDK_PIXBUF2_LIBRARIES}
  ${LIBXML2_LIBRARIES}
  ${GIO2_LIBRARIES}
  ${PANGO_CAIRO_LIBRARIES}
  ${MTEX2MML_BUILD_DIR}/libmtex2MML.a
)
