CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_BUILD_TYPE "DEBUG")
PROJECT("window_plot")
Message("Project spuce window_plot")

set(CMAKE_CXX_FLAGS " -std=c++11 ")
set(CMAKE_PREFIX_PATH "/usr/local/opt/qt5")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5 REQUIRED Gui Core Widgets)

ADD_DEFINITIONS("-Wall -fPIC")
INCLUDE_DIRECTORIES(".." "/usr/local/opt/qt5/include")
LINK_DIRECTORIES("/usr/local/lib")

set(EXECUTABLE_OUTPUT_PATH ..)

set(SOURCES	make_filter.cpp)

SET(window_plot_SOURCES main.cpp mainwindow.cpp qcustomplot.cpp)
SET(window_plot_HEADERS mainwindow.h qcustomplot.h)

INCLUDE_DIRECTORIES(${QT5_INCLUDES})
ADD_DEFINITIONS(${QT5Widgets_DEFINITIONS})

ADD_LIBRARY(winlib ${SOURCES})
ADD_EXECUTABLE(window_plot ${window_plot_SOURCES} ${window_plot_HEADERS_MOC})
set_property(TARGET winlib PROPERTY CXX_STANDARD 11)

TARGET_LINK_LIBRARIES(window_plot winlib ${QT_LIBRARIES} spuce)
set_property(TARGET window_plot PROPERTY CXX_STANDARD 11)
QT5_USE_Modules(window_plot Gui)
QT5_USE_Modules(window_plot Core)
QT5_USE_Modules(window_plot Widgets)
QT5_USE_Modules(window_plot PrintSupport)

