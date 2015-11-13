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

SET(other_plot_SOURCES main.cpp mainwindow.cpp qcustomplot.cpp)
SET(other_plot_HEADERS mainwindow.h qcustomplot.h)

INCLUDE_DIRECTORIES(${QT5_INCLUDES})
ADD_DEFINITIONS(${QT5Widgets_DEFINITIONS})

ADD_LIBRARY(otherlib ${SOURCES})
ADD_EXECUTABLE(other_plot ${other_plot_SOURCES} ${other_plot_HEADERS_MOC})
set_property(TARGET otherlib PROPERTY CXX_STANDARD 11)

TARGET_LINK_LIBRARIES(other_plot otherlib ${QT_LIBRARIES} spuce)
set_property(TARGET other_plot PROPERTY CXX_STANDARD 11)
QT5_USE_Modules(other_plot Gui)
QT5_USE_Modules(other_plot Core)
QT5_USE_Modules(other_plot Widgets)
QT5_USE_Modules(other_plot PrintSupport)

