########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.8)
project(spuce)
enable_language(CXX)


# Shouldn't have to do this
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message(STATUS "Adding -std=c++11")
	add_definitions("-std=c++11")
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(spuce)
option(ENABLE_GUI "Enable QT application" ON)
if (ENABLE_GUI)
	add_subdirectory(qt_iir)
	add_subdirectory(qt_fir)
endif()
option(ENABLE_PYTHON "Enable python testing" ON)
if (ENABLE_PYTHON)
	add_subdirectory(test_spuce)
endif()
	
