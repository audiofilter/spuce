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
	add_subdirectory(qt_iir)
	add_subdirectory(qt_fir)
endif()
option(ENABLE_PYTHON "Enable python testing" ON)
add_feature_info(ENABLE_PYTHON ENABLE_PYTHON "This enables python testing with matplotlib graphs")
if (ENABLE_PYTHON)
	add_subdirectory(test_spuce)
endif()
	
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
