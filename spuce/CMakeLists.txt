########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.8)

SET(FILT_SRCS  
	filters/butterworth_iir.cpp
	filters/chebyshev_iir.cpp
	filters/chebyshev2_iir.cpp
	filters/elliptic_iir.cpp
	filters/find_roots.cpp
	filters/fir_coeff.cpp
	filters/iir_coeff.cpp
	# FIR stuff
	filters/gaussian_fir.cpp
	filters/butterworth_fir.cpp
	filters/raised_cosine_imp.cpp
	filters/root_raised_cosine_imp.cpp
	filters/remez_fir.cpp
	filters/sinc_fir.cpp
	filters/create_remez_lpfir.cpp
	filters/fir_inv_dft.cpp
	filters/transform_fir.cpp
	# Windows
	filters/window.cpp
	# Other filters
	filters/butterworth_allpass.cpp
	filters/elliptic_allpass.cpp
  filters/shelf_allpass1.cpp
)

add_library(spuce ${FILT_SRCS})
set_property(TARGET spuce PROPERTY CXX_STANDARD 11)

	
