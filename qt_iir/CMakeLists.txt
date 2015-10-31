CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_BUILD_TYPE "DEBUG")
PROJECT("iir_plot")
Message("Project spuce iir_plot")

set(CMAKE_CXX_FLAGS " -std=c++11 ")
set(CMAKE_PREFIX_PATH "/usr/local/opt/qt5")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5 REQUIRED Gui Core Widgets)

ADD_DEFINITIONS("-Wall -fPIC")
INCLUDE_DIRECTORIES(".." "/usr/local/opt/qt5/include")
LINK_DIRECTORIES("/usr/local/lib")

set(EXECUTABLE_OUTPUT_PATH ..)

set(SOURCES
	make_filter.cpp 	
	des_filter.cpp 
)

SET(iir_plot_SOURCES main.cpp mainwindow.cpp qcustomplot.cpp)
SET(iir_plot_HEADERS mainwindow.h qcustomplot.h)

INCLUDE_DIRECTORIES(${QT5_INCLUDES})
ADD_DEFINITIONS(${QT5Widgets_DEFINITIONS})

ADD_LIBRARY(filtlib ${SOURCES})
ADD_EXECUTABLE(iir_plot ${iir_plot_SOURCES} ${iir_plot_HEADERS_MOC})
set_property(TARGET filtlib PROPERTY CXX_STANDARD 11)

TARGET_LINK_LIBRARIES(iir_plot filtlib ${QT_LIBRARIES} spucelib)
set_property(TARGET iir_plot PROPERTY CXX_STANDARD 11)
QT5_USE_Modules(iir_plot Gui)
QT5_USE_Modules(iir_plot Core)
QT5_USE_Modules(iir_plot Widgets)
QT5_USE_Modules(iir_plot PrintSupport)

