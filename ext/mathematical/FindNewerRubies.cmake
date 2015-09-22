# - Find Ruby
# This module finds if Ruby is installed and determines where the include files
# and libraries are. It also determines what the name of the library is. This
# code sets the following variables:
#
#  RUBY_INCLUDE_PATH = path to where ruby.h can be found
#  RUBY_EXECUTABLE   = full path to the ruby binary

# Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
# See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.


if(RUBY_LIBRARY AND RUBY_INCLUDE_PATH)
   # Already in cache, be silent
   set(RUBY_FIND_QUIETLY TRUE)
endif (RUBY_LIBRARY AND RUBY_INCLUDE_PATH)

FIND_PROGRAM(RUBY_EXECUTABLE NAMES ruby ruby1.9 ruby19 ruby1.9.1 ruby2.1 ruby2.2)

EXECUTE_PROCESS(COMMAND ${RUBY_EXECUTABLE} -r rbconfig -e "print RbConfig::CONFIG['archdir']"
   OUTPUT_VARIABLE RUBY_ARCH_DIR)

 EXECUTE_PROCESS(COMMAND ${RUBY_EXECUTABLE} -r rbconfig -e "print RbConfig::CONFIG['libdir']"
   OUTPUT_VARIABLE RUBY_POSSIBLE_LIB_PATH)

 EXECUTE_PROCESS(COMMAND ${RUBY_EXECUTABLE} -r rbconfig -e "print RbConfig::CONFIG['rubylibdir']"
   OUTPUT_VARIABLE RUBY_RUBY_LIB_PATH)

# site_ruby
EXECUTE_PROCESS(COMMAND ${RUBY_EXECUTABLE} -r rbconfig -e "print RbConfig::CONFIG['sitearchdir']"
   OUTPUT_VARIABLE RUBY_SITEARCH_DIR)

EXECUTE_PROCESS(COMMAND ${RUBY_EXECUTABLE} -r rbconfig -e "print RbConfig::CONFIG['sitelibdir']"
   OUTPUT_VARIABLE RUBY_SITELIB_DIR)


EXECUTE_PROCESS(COMMAND ${RUBY_EXECUTABLE} -r rbconfig -e "print RbConfig::CONFIG['vendorarchdir']"
   OUTPUT_VARIABLE RUBY_VENDORARCH_DIR)

EXECUTE_PROCESS(COMMAND ${RUBY_EXECUTABLE} -r rbconfig -e "print RbConfig::CONFIG['vendorlibdir']"
   OUTPUT_VARIABLE RUBY_VENDORLIB_DIR)

EXECUTE_PROCESS(COMMAND ${RUBY_EXECUTABLE} -r rbconfig -e "print RbConfig::CONFIG['rubyhdrdir']"
  OUTPUT_VARIABLE RUBY_HEADER_DIR)

EXECUTE_PROCESS(COMMAND ${RUBY_EXECUTABLE} -r rbconfig -e "print RbConfig::CONFIG['arch']"
  OUTPUT_VARIABLE RUBY_ARCH)


FIND_PATH(RUBY_INCLUDE_PATH
  NAMES ruby.h
  PATHS
  ${RUBY_HEADER_DIR}
)

FIND_LIBRARY(RUBY_LIBRARY
  NAMES ruby ruby1.9 ruby-1.9.1 ruby2.1 ruby-2.1 ruby-2.2 ruby2.2
  PATHS ${RUBY_POSSIBLE_LIB_PATH}
)

MARK_AS_ADVANCED(
  RUBY_EXECUTABLE
  RUBY_LIBRARY
  RUBY_INCLUDE_PATH
)
