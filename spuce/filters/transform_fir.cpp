#include <spuce/filters/transform_fir.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)
namespace spuce {
//! \author Tony Kirke
//! \ingroup functions fir
std::vector<float_type> transform_fir(const std::string& band_type, const std::vector<float_type>& taps, float_type f) {
	std::vector<float_type> out(taps.size());
  if (band_type == "LOW_PASS") {
		// just copy
		for (size_t i=0;i<taps.size();i++) {
			out[i] = taps[i];
		}
  } else if (band_type == "HIGH_PASS") {
		float_type h = 1;
		// Alternate multiplying by +1,-1
		for (size_t i=0;i<taps.size();i++) {
			out[i] = h*taps[i];
			h *= -1;
		}
  } else if (band_type == "BAND_PASS") {
		// Modulate taps up to band center frequency
		for (size_t i=0;i<taps.size();i++) {
			out[i] = cos(2.0*M_PI*f*i) * taps[i];
		}
  } else {
    std::cout << "Unsupported band type :" << band_type << "\n";
  }
	return out;
}
std::vector<std::complex<float_type>> transform_complex_fir(const std::string& band_type, const std::vector<float_type>& taps, float_type f) {
	std::vector<std::complex<float_type>> out(taps.size());
  if (band_type == "COMPLEX_BAND_PASS") {
		// Modulate taps up to band center frequency
		for (size_t i=0;i<taps.size();i++) {
			out[i] = std::polar(taps[i], 2.0*M_PI*f*i);
		}
  } else {
    std::cout << "Unsupported band type :" << band_type << "\n";
  }
	return out;
}
}  // namespace spuce
