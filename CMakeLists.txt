########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.8)
project(spuce)
enable_language(CXX)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_definitions("-std=c++11")

add_subdirectory(spuce)
add_subdirectory(test_spuce)

	
