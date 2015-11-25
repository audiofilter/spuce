CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT("window_plot")
Message("Project spuce window_plot")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5 REQUIRED Gui Core Widgets)

set(SOURCES	make_filter.cpp)
ADD_LIBRARY(spuce_other STATIC ${SOURCES})
set_property(TARGET spuce_other PROPERTY CXX_STANDARD 11)
set_property(TARGET spuce_other PROPERTY POSITION_INDEPENDENT_CODE TRUE)

SET(other_plot_SOURCES main.cpp mainwindow.cpp qcustomplot.cpp)
SET(other_plot_HEADERS mainwindow.h qcustomplot.h)

INCLUDE_DIRECTORIES(${QT5_INCLUDES})
ADD_DEFINITIONS(${QT5Widgets_DEFINITIONS})

ADD_EXECUTABLE(spuce_other_plot ${other_plot_SOURCES} ${other_plot_HEADERS_MOC})
set_property(TARGET spuce_other_plot PROPERTY CXX_STANDARD 11)
set_property(TARGET spuce_other_plot PROPERTY POSITION_INDEPENDENT_CODE TRUE)

TARGET_LINK_LIBRARIES(spuce_other_plot spuce_other ${QT_LIBRARIES} spuce)
QT5_USE_Modules(spuce_other_plot Gui)
QT5_USE_Modules(spuce_other_plot Core)
QT5_USE_Modules(spuce_other_plot Widgets)
QT5_USE_Modules(spuce_other_plot PrintSupport)

INSTALL(TARGETS spuce_other_plot DESTINATION bin)
