CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT("fir_plot")
Message("Project spuce fir_plot")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5 REQUIRED Gui Core Widgets)

set(SOURCES
	make_filter.cpp 
	des_filter.cpp 
)

SET(fir_plot_SOURCES main.cpp mainwindow.cpp qcustomplot.cpp)
SET(fir_plot_HEADERS mainwindow.h other_freq.h qcustomplot.h)

INCLUDE_DIRECTORIES(${QT5_INCLUDES})
ADD_DEFINITIONS(${QT5Widgets_DEFINITIONS})

ADD_LIBRARY(spuce_fir ${SOURCES})
ADD_EXECUTABLE(spuce_fir_plot ${fir_plot_SOURCES} ${fir_plot_HEADERS_MOC})
set_property(TARGET spuce_fir PROPERTY CXX_STANDARD 11)

set_property(TARGET spuce_fir PROPERTY POSITION_INDEPENDENT_CODE TRUE)
set_property(TARGET spuce_fir_plot PROPERTY POSITION_INDEPENDENT_CODE TRUE)
set_property(TARGET spuce_fir_plot PROPERTY CXX_STANDARD 11)

TARGET_LINK_LIBRARIES(spuce_fir_plot spuce_fir ${QT_LIBRARIES} spuce)
QT5_USE_Modules(spuce_fir_plot Gui)
QT5_USE_Modules(spuce_fir_plot Core)
QT5_USE_Modules(spuce_fir_plot Widgets)
QT5_USE_Modules(spuce_fir_plot PrintSupport)

INSTALL(TARGETS spuce_fir_plot DESTINATION bin)

