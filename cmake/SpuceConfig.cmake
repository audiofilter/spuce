if(DEFINED INCLUDED_SPUCE_CONFIG_CMAKE)
  return()
endif()
set(INCLUDED_SPUCE_CONFIG_CMAKE TRUE)

########################################################################
# SpuceConfig - cmake project configuration for client clibraries
#
# The following will be set after find_package(Spuce):
# Spuce_LIBRARIES    - development libraries
# Spuce_INCLUDE_DIRS - development includes
########################################################################

########################################################################
## installation root
########################################################################
if (UNIX)
  get_filename_component(SPUCE_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../.." ABSOLUTE)
elseif (WIN32)
  get_filename_component(SPUCE_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
endif ()

########################################################################
## locate the library
########################################################################
find_library(
  SPUCE_LIBRARY spuce
  PATHS ${SPUCE_ROOT}/lib${LIB_SUFFIX}
  PATH_SUFFIXES ${CMAKE_LIBRARY_ARCHITECTURE}
  NO_DEFAULT_PATH
  )
if(NOT SPUCE_LIBRARY)
  message(FATAL_ERROR "cannot find spuce library in ${SPUCE_ROOT}/lib${LIB_SUFFIX}")
endif()
set(Spuce_LIBRARIES ${SPUCE_LIBRARY})

########################################################################
## locate the includes
########################################################################
find_path(
  SPUCE_INCLUDE_DIR spuce/typedefs.h
  PATHS ${SPUCE_ROOT}/include
  NO_DEFAULT_PATH
)
if(NOT SPUCE_INCLUDE_DIR)
  message(FATAL_ERROR "cannot find spuce includes in ${SPUCE_ROOT}/include")
endif()
set(Spuce_INCLUDE_DIRS ${SPUCE_INCLUDE_DIR})

