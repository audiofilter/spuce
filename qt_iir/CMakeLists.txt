CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT("iir_plot")
Message("Project spuce iir_plot")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5 REQUIRED Gui Core Widgets)

set(SOURCES
	make_filter.cpp 	
	des_filter.cpp 
)

SET(iir_plot_SOURCES main.cpp mainwindow.cpp qcustomplot.cpp)
SET(iir_plot_HEADERS mainwindow.h qcustomplot.h)

INCLUDE_DIRECTORIES(${QT5_INCLUDES})
ADD_DEFINITIONS(${QT5Widgets_DEFINITIONS})

ADD_LIBRARY(spuce_iir STATIC ${SOURCES})
ADD_EXECUTABLE(spuce_iir_plot ${iir_plot_SOURCES} ${iir_plot_HEADERS_MOC})

set_property(TARGET spuce_iir PROPERTY CXX_STANDARD 11)
set_property(TARGET spuce_iir PROPERTY POSITION_INDEPENDENT_CODE TRUE)
set_property(TARGET spuce_iir_plot PROPERTY CXX_STANDARD 11)
set_property(TARGET spuce_iir_plot PROPERTY POSITION_INDEPENDENT_CODE TRUE)

TARGET_LINK_LIBRARIES(spuce_iir_plot spuce_iir ${QT_LIBRARIES} spuce)
QT5_USE_Modules(spuce_iir_plot Gui)
QT5_USE_Modules(spuce_iir_plot Core)
QT5_USE_Modules(spuce_iir_plot Widgets)
QT5_USE_Modules(spuce_iir_plot PrintSupport)

INSTALL(TARGETS spuce_iir_plot DESTINATION bin)
