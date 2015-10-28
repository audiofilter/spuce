CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_BUILD_TYPE "DEBUG")
PROJECT("fir_plot")
Message("Project spuce fir_plot")

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

SET(fir_plot_SOURCES main.cpp mainwindow.cpp other_freq.cpp qcustomplot.cpp)
SET(fir_plot_HEADERS mainwindow.h other_freq.h qcustomplot.h)

INCLUDE_DIRECTORIES(${QT5_INCLUDES})
ADD_DEFINITIONS(${QT5Widgets_DEFINITIONS})

ADD_LIBRARY(firlib ${SOURCES})
ADD_EXECUTABLE(fir_plot ${fir_plot_SOURCES} ${fir_plot_HEADERS_MOC})
set_property(TARGET firlib PROPERTY CXX_STANDARD 11)

TARGET_LINK_LIBRARIES(fir_plot firlib ${QT_LIBRARIES} spucelib)
set_property(TARGET fir_plot PROPERTY CXX_STANDARD 11)
QT5_USE_Modules(fir_plot Gui)
QT5_USE_Modules(fir_plot Core)
QT5_USE_Modules(fir_plot Widgets)
QT5_USE_Modules(fir_plot PrintSupport)

