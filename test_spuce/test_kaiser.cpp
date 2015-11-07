#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include <spuce/filters/design_window.h>
#include <spuce/filters/fir_coeff.h>
#include <spuce/filters/fir.h>
using namespace spuce;
#include "plot_fft.h"
//! \brief testing various types for IIR
//! \ingroup examples

int main(int argc, char* argv[]) {
  const long N = 1024;
  long O = 30;
  float_type imp;
	float_type ripple = 0.01;
	
  if (argc > 1) {
    ripple = atof(argv[1]);
	}

	float_type beta = kaiser_beta(ripple);
	std::cout << "Order used = " << O << " ripple = " << ripple << " beta = "  << beta << "\n";
	std::vector<float_type> taps = design_window("kaiser", O, beta);

	float_type sum=0;
	for (int i=0;i<taps.size();i++) sum += taps[i];
	for (int i=0;i<taps.size();i++) taps[i] /= sum;
	
  std::vector<double> y(N, 0);
	// Map from std::vector<> to fir_coeff<> and then to fir<>
  fir_coeff<float_type> RF(taps.size());
	for (int i=0;i<taps.size();i++) RF.settap(i,taps[i]);
	fir<double> RFIR(RF);

  imp = 1;
  for (int i=0;i<N;i++) {
		y[i] = RFIR.clock(imp);
		imp = 0;
  }
	
  plot_fft(y);
  return 0;
}
