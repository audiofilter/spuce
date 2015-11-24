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
  filters/design_iir.cpp
	# FIR stuff
  filters/design_fir.cpp
	filters/gaussian_fir.cpp
	filters/butterworth_fir.cpp
	filters/raised_cosine_imp.cpp
	filters/root_raised_cosine_imp.cpp
	filters/remez_estimate.cpp
	filters/remez_fir.cpp
	filters/sinc_fir.cpp
	filters/sinc_helper.cpp
	filters/create_remez_lpfir.cpp
	filters/fir_inv_dft.cpp
	filters/transform_fir.cpp
	# Windows
	filters/window.cpp
  filters/design_window.cpp
	# Other filters
	filters/butterworth_allpass.cpp
	filters/elliptic_allpass.cpp
  filters/shelf_allpass1.cpp
  filters/farrow_upsampler.cpp
)

add_library(spuce ${FILT_SRCS})
set_property(TARGET spuce PROPERTY CXX_STANDARD 11)
set_property(TARGET spuce PROPERTY POSITION_INDEPENDENT_CODE TRUE)

set_target_properties(spuce PROPERTIES SOVERSION ${SPUCE_SOVER})
set_target_properties(spuce PROPERTIES VERSION ${SPUCE_LIBVER})
set_target_properties(spuce PROPERTIES DEFINE_SYMBOL "SPUCE_DLL_EXPORTS")


install(TARGETS spuce
  LIBRARY DESTINATION lib${LIB_SUFFIX} # .so file
  ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
  RUNTIME DESTINATION bin              # .dll file
)	

