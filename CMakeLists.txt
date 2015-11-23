########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.8)
project(spuce)
enable_language(CXX)
include(FeatureSummary)

if (NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "RELEASE")
endif()

# Shouldn't have to do this
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message(STATUS "Adding -std=c++11")
	add_definitions("-std=c++11")
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(spuce)
option(ENABLE_GUI "Enable QT application" ON)
add_feature_info(ENABLE_GUI ENABLE_GUI "This enables the QT applications to be built")
if (ENABLE_GUI)
  FIND_PACKAGE(Qt5 COMPONENTS Gui Core Widgets)
  if (QT5_FOUND) 
	  add_subdirectory(qt_fir)
	  add_subdirectory(qt_iir)
	  add_subdirectory(qt_window)
	  add_subdirectory(qt_other)
  else()
    message(STATUS "QT5 not found - will skip building QT5 Apps")
  endif()
endif()
option(ENABLE_PYTHON "Enable python testing" ON)
add_feature_info(ENABLE_PYTHON ENABLE_PYTHON "This enables python testing with matplotlib graphs")
if (ENABLE_PYTHON)
  FIND_PACKAGE(PythonLibs)
  if (PythonLibs_FOUND)
    message(STATUS "Found PythonLibs - will build test programs")
	  add_subdirectory(test_spuce)
  else()
    message(STATUS "PythonLibs not found - will skip building test programs")
    endif()
endif()

########################################################################
# install include files
########################################################################
install(
    DIRECTORY spuce
    DESTINATION include
    COMPONENT spuce_dev
    FILES_MATCHING PATTERN "*.h"
)

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)


#########################################################################
# print features summary
#########################################################################
message(STATUS "######################################################")
message(STATUS "## Enabled features")
message(STATUS "######################################################")
feature_summary(WHAT ENABLED_FEATURES)
message(STATUS "######################################################")
message(STATUS "## Disabled features")
message(STATUS "######################################################")
feature_summary(WHAT DISABLED_FEATURES)
