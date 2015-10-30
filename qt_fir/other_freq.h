#pragma once
// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include <spuce/typedefs.h>
#include <spuce/filters/fir_coeff.h>
namespace spuce {
	void fir_coeff_freq(fir_coeff<double>& MF, int pts, double* w, int freq_off, double inc);
	void fir_freq(std::vector<double>& MF, int pts, double* w, double inc);
} //
