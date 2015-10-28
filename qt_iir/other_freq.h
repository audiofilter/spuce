#pragma once
#include <spuce/filters/iir_coeff.h>
namespace spuce {
	void iir_freq(iir_coeff& MF, int pts, double* w, double inc);
}
