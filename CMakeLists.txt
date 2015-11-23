########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.8)
project(spuce)
enable_language(CXX)
include(FeatureSummary)
include(CMakeDependentOption)

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
FIND_PACKAGE(Qt5 COMPONENTS Gui Core Widgets)
if (NOT Qt5_FOUND)
  message(STATUS "QT5 not found - will skip building QT5 Apps")
endif()
cmake_dependent_option(ENABLE_GUI "Enable QT application" ON "Qt5_FOUND" OFF)
add_feature_info(ENABLE_GUI ENABLE_GUI "This enables the QT applications to be built")
if (ENABLE_GUI)
	add_subdirectory(qt_fir)
	add_subdirectory(qt_iir)
	add_subdirectory(qt_window)
	add_subdirectory(qt_other)
endif()
FIND_PACKAGE(PythonLibs)
if (NOT PYTHONLIBS_FOUND)
  message(STATUS "PythonLibs not found - will skip building test programs")
endif()  
cmake_dependent_option(ENABLE_PYTHON "Enable python based tests" ON "PYTHONLIBS_FOUND" OFF)
add_feature_info(ENABLE_PYTHON ENABLE_PYTHON "This enables python testing with matplotlib graphs")
if (ENABLE_PYTHON)
	add_subdirectory(test_spuce)
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
