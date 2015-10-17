CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE "DEBUG")
ENDIF()
PROJECT("spuce tests")
message("Project spuce_tests")

FIND_PACKAGE(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_library(spuce_debug plot_fft.cpp cfft.cpp gen_iir_df)
set_property(TARGET spuce_debug PROPERTY CXX_STANDARD 11)

SET(TARGETS chebyshev_iir chebyshev_iir_hpf elliptic_iir elliptic_iir_hpf butterworth_iir
  butterworth_iir_hpf iir iir_df iir_df2)

ADD_DEFINITIONS(" -fPIC  ")

FOREACH(mod ${TARGETS})
	SET(SRC test_${mod}.cpp)
	ADD_EXECUTABLE(plot_${mod} ${SRC})
  TARGET_LINK_LIBRARIES(plot_${mod} spucelib spuce_debug ${PYTHON_LIBRARY})
	set_property(TARGET plot_${mod} PROPERTY CXX_STANDARD 11)
ENDFOREACH(mod ${EXTS})

