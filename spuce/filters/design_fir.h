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
															 float_type spb,
															 float_type bt) {

	std::vector<float_type> taps;
	fir_coeff<float_type> filt;
	filt.set_size(order);
	if (fir_type == "butterworth") {
		butterworth_fir(filt, spb);
	}	else if (fir_type == "gaussian") {
		gaussian_fir(filt,bt,spb);
	}	else if (fir_type == "remez") {
		std::vector<float_type> e1(4);
		std::vector<float_type> f1(4);
		std::vector<float_type> w1(4);
		taps.resize(order);
		remez_fir Remz;
		w1[0] = 1.0;
		w1[1] = bt;
		e1[0] = 0;
		e1[1] = alpha / 2.0;
		e1[2] = spb / 2.0;
		e1[3] = 0.5;
		f1[0] = 1.0;
		f1[1] = 0.0;
		Remz.remez(taps, order, 2, e1, f1, w1, 1);
		//
	}	else if (fir_type == "raisedcosine") {
		raised_cosine(filt, alpha, spb);
	}	else if (fir_type == "rootraisedcosine") {
		root_raised_cosine(filt, alpha, spb);
  } else {
    std::cout << "Unknown window type\n";
  }
	if (fir_type == "remez") {
		return taps;
	} else {
		for (int i=0;i<order;i++) taps.push_back(filt.gettap(i));
		return taps;
	}
}
}  // namespace spuce
