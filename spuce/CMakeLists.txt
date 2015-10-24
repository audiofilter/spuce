########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.8)

# Shouldn't have to do this
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
else()
	add_definitions("-std=c++11")
endif()

SET(FILT_SRCS  
	filters/butterworth_iir.cpp
	filters/chebyshev_iir.cpp
	filters/chebyshev2_iir.cpp
	filters/elliptic_iir.cpp
	filters/find_roots.cpp
	filters/fir_coeff.cpp
	filters/iir_coeff.cpp
)

add_library(spucelib ${FILT_SRCS})
set_property(TARGET spucelib PROPERTY CXX_STANDARD 11)

	
