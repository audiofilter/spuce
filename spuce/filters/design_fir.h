#pragma once
// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include <spuce/filters/butterworth_fir.h>
#include <spuce/filters/gaussian_fir.h>
#include <spuce/filters/remez_fir.h>
#include <spuce/filters/raised_cosine.h>
#include <spuce/filters/root_raised_cosine.h>
namespace spuce {
//! \file
//! \brief Design functions for fir filters
//! \author Tony Kirke
//! \ingroup functions fir
std::vector<double> design_fir(const std::string& fir_type,
															 int order, float_type alpha,
															 float_type spb=0.14,
															 float_type bt=1,
															 float_type rate=4) {

	fir_coeff<float_type> filt;
	filt.set_size(order);
	if (fir_type == "butterworth") {
		butterworth_fir(filt, spb);
	}	else if (fir_type == "gaussian") {
		gaussian_fir(filt, bt,spb);
	}	else if (fir_type == "remez") {
		//
	}	else if (fir_type == "raisedcosine") {
		raised_cosine(filt, alpha, rate);
	}	else if (fir_type == "rootraisedcosine") {
		root_raised_cosine(filt, alpha, rate);
  } else {
    std::cout << "Unknown window type\n";
  }
	std::vector<float_type> taps;
	for (int i=0;i<order;i++) taps.push_back(filt.gettap(i));
	return taps;
}
}  // namespace spuce
