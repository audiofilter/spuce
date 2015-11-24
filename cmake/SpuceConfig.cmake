if(DEFINED INCLUDED_SPUCE_CONFIG_CMAKE)
  return()
endif()
set(INCLUDED_SPUCE_CONFIG_CMAKE TRUE)

########################################################################
# SpuceConfig - cmake project configuration for client clibraries
#
# The following will be set after find_package(Spuce):
# SPUCE_MODULE_UTIL() - utility function to build modules
# Spuce_LIBRARIES    - development libraries
# Spuce_INCLUDE_DIRS - development includes
########################################################################
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_LIST_DIR})

########################################################################
# select the release build type by default to get optimization flags
########################################################################
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

########################################################################
# Automatic LIB_SUFFIX detection + configuration option
########################################################################
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(LINUX TRUE)
endif()

if(LINUX AND EXISTS "/etc/debian_version")
  set(DEBIAN TRUE)
endif()

if(LINUX AND EXISTS "/etc/redhat-release")
  set(REDHAT TRUE)
endif()

if(LINUX AND EXISTS "/etc/SuSE-release")
  set(SUSE TRUE)
endif()

if(LINUX AND EXISTS "/etc/slackware-version")
  set(SLACKWARE TRUE)
endif()

if(NOT DEFINED LIB_SUFFIX AND (REDHAT OR SUSE OR SLACKWARE) AND CMAKE_SYSTEM_PROCESSOR MATCHES "64$")
  SET(LIB_SUFFIX 64)
endif()
set(LIB_SUFFIX ${LIB_SUFFIX} CACHE STRING "lib directory suffix")

########################################################################
# Provide add_compile_options() when not available
########################################################################
if(CMAKE_VERSION VERSION_LESS "2.8.12")
  function(add_compile_options)
    add_definitions(${ARGN})
  endfunction(add_compile_options)
endif()

########################################################################
# Helpful compiler flags
########################################################################
if(CMAKE_COMPILER_IS_GNUCXX)
  #force a compile-time error when symbols are missing
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--no-undefined")

  #common warnings to help encourage good coding practices
  add_compile_options(-Wall)
  add_compile_options(-Wextra)

  #symbols are only exported from libraries/modules explicitly
  add_compile_options(-fvisibility=hidden)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
endif()

if(APPLE)
  #fixes issue with duplicate module registry when using application bundle
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -flat_namespace")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -flat_namespace")
endif()

if(MSVC)
  #suppress the following warnings which are commonly caused by project headers
  add_compile_options(/wd4251) #disable 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
  add_compile_options(/wd4503) #'identifier' : decorated name length exceeded, name was truncated
  
  add_definitions(-DNOMINMAX) #enables std::min and std::max
endif()

########################################################################
# In-tree settings
########################################################################
if (SPUCE_IN_TREE_SOURCE_DIR)
  if(NOT SPUCE_ROOT)
    set(SPUCE_ROOT ${CMAKE_INSTALL_PREFIX})
  endif(NOT SPUCE_ROOT)
  set(Spuce_INCLUDE_DIRS ${SPUCE_IN_TREE_SOURCE_DIR}/include)
  set(Spuce_LIBRARIES spuce)
  return()
endif (SPUCE_IN_TREE_SOURCE_DIR)

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
