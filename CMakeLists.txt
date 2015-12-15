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

SET(SPUCE_LIBVER "0.4.2")
SET(SPUCE_SOVER "${SPUCE_LIBVER}")
set(SPUCE_VERSION "${SPUCE_LIBVER}")

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
cmake_dependent_option(BUILD_TESTING "Enable python based tests" ON "PYTHONLIBS_FOUND" OFF)
add_feature_info(BUILD_TESTING BUILD_TESTING "This enables python testing with matplotlib graphs")
if (BUILD_TESTING)
	add_subdirectory(test_spuce)
endif()



########################################################################
# Install cmake helper modules
########################################################################
configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/SpuceConfigVersion.in.cmake
    ${PROJECT_BINARY_DIR}/SpuceConfigVersion.cmake
@ONLY)
set(cmake_files
    ${PROJECT_SOURCE_DIR}/cmake/SpuceConfig.cmake
    ${PROJECT_BINARY_DIR}/SpuceConfigVersion.cmake)
if (UNIX)
    install(FILES ${cmake_files} DESTINATION share/cmake/${PROJECT_NAME})
elseif (WIN32)
    install(FILES ${cmake_files} DESTINATION cmake)
endif ()

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

# only add uninstall if this is the main project  
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
 add_custom_target(uninstall
   COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
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
