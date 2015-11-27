#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <spuce/filters/iir_coeff.h>
#include <spuce/filters/iir_df.h>
#include <spuce/filters/fir_coeff.h>
#include <spuce/filters/design_iir.h>
#include <spuce/filters/design_fir.h>
#include <spuce/filters/fir.h>
#include <spuce/filters/remez_estimate.h>
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
  const double ripple = 0.1;
  const int rate=6;
  const size_t Order=(2*IIR_Order*rate)+1;
  const double remez_stop_atten = 60.0;

  //auto TAPS = design_fir("remez","LOW_PASS", Order, 0.0625, 0, 0.15, 100.0);

  double fc = 0.5/rate;
  double pass_edge = 0.8*fc;
  double remez_trans  = 2*(fc - pass_edge);
  double remez_weight = remez_estimate_weight(ripple, remez_stop_atten);
  //std::cout << "pass_edge = " << pass_edge << " trans = " << remez_trans << "\n";
	auto BF = design_fir("remez","LOW_PASS", Order, pass_edge, 0, remez_trans, 100); //remez_weight);


  iir_coeff* iirf = design_iir("chebyshev", "LOW_PASS", IIR_Order, pass_edge, ripple);
  iir_df<double, double> IIR(*iirf);

	fir<double> BFIR(BF);
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
