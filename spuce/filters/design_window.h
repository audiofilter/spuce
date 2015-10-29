#pragma once
// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include <spuce/filters/window.h>
namespace spuce {
//! \file
//! \brief Design functions for window functions
//! \author Tony Kirke
//! \ingroup functions fir
std::vector<double> design_window(const std::string& fir_type,
																	int order, float_type alpha, float_type beta=0.1) {

	if (fir_type == "hamming") {
		return hamming(order, alpha, beta);
	}	else if (fir_type == "hanning") {
		return hanning(order);
	}	else if (fir_type == "blackman") {
		return blackman(order);
	}	else if (fir_type == "kaiser") {
		return kaiser(order, beta);
  } else {
    std::cout << "Unknown window type\n";
  }

  return filt;
}
}  // namespace spuce
