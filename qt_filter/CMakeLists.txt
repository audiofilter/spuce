CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_BUILD_TYPE "DEBUG")
PROJECT("plotdes")
Message("Project spuce plotdes")

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

SET(plotdes_SOURCES main.cpp mainwindow.cpp other_freq.cpp qcustomplot.cpp)
SET(plotdes_HEADERS mainwindow.h other_freq.h qcustomplot.h)

INCLUDE_DIRECTORIES(${QT5_INCLUDES})
ADD_DEFINITIONS(${QT5Widgets_DEFINITIONS})

ADD_LIBRARY(filtlib ${SOURCES})
ADD_EXECUTABLE(plotdes ${plotdes_SOURCES} ${plotdes_HEADERS_MOC})
TARGET_LINK_LIBRARIES(plotdes filtlib ${QT_LIBRARIES} spucelib)
QT5_USE_Modules(plotdes Gui)
QT5_USE_Modules(plotdes Core)
QT5_USE_Modules(plotdes Widgets)
QT5_USE_Modules(plotdes PrintSupport)

