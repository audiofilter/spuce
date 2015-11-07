#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include <spuce/filters/fir_coeff.h>
#include <spuce/filters/iir_allpass1_sections.h>
using namespace spuce;
//! \brief testing various types of filters
//
//! \ingroup examples
#include "plot_fft.h"
int main(int argv, char* argc[]) {
	const int N=256;
	const int Order=4;
	const double ripple_factor = 0.4;
  float_type imp;
  iir_allpass1_sections<float_type> AF1(ripple_factor,Order);
	std::vector<double> y(N,0);

  imp = 1;
  for (int i=0;i<N;i++) {
		y[i] = AF1.clock(imp);
		imp = 0;
  }
	
	plot_fft(y);

  return(1);
}
