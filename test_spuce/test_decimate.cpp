#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <spuce/filters/iir_coeff.h>
#include <spuce/filters/iir_df.h>
#include <spuce/filters/fir_coeff.h>
#include <spuce/filters/fir.h>
#include <spuce/filters/calculate_decimator_taps.h>
using namespace std;
using namespace spuce;
#include "plot_fft.h"
/*
 Compare frequency responses of a FIR decimation filter 
 with an IIR one.
 FIR order = 2*Rate*IIR_Order + 1
 */
int main(int argv, char* argc[]) {
	const int N=256;
  const size_t IIR_Order = 6;
  const int rate=6;

  auto iir_taps = calculate_decimator_taps(rate, IIR_Order, false);
  auto fir_taps = calculate_decimator_taps(rate, IIR_Order, true);

  iir_df<double, double> IIR;
  IIR.set_taps(iir_taps);

	fir<double> BFIR(fir_taps);
  
	std::vector<double> x(N);
	std::vector<double> y(N);
  
  double imp = 1;
  for (int i=0;i<N;i++) {
		x[i] = BFIR.clock(imp);
		y[i] = IIR.clock(imp);
		imp = 0;
  }
	
	compare_fft(x,y);

  return(1);
}
