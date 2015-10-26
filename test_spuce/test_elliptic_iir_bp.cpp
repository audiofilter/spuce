#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include <spuce/filters/iir_coeff.h>
#include <spuce/filters/elliptic_iir.h>
#include <spuce/filters/iir_df.h>
#include "plot_fft.h"

using namespace spuce;
//! \brief testing various types for IIR
//! \ingroup examples

int main(int argc, char* argv[]) {
  const long N = 1024;
  long O = 3;
  float_type imp;
	float_type f_cutoff=0.1;
	float_type ripple = 0.1;
	float_type stopband_atten = 40;

	if (argc > 1) {
    f_cutoff = atof(argv[1]);
	}
	std::cout << "Order used = " << O << ", cut-off = " << f_cutoff 
						<< ", stopband attenuation = " << stopband_atten
						<< ", ripple = " << ripple << "\n";

  iir_coeff BPF(O,filter_type::bandpass);
  elliptic_iir(BPF, f_cutoff, ripple, stopband_atten);
  iir_df<float_type> LPF(BPF);

	BPF.print();
 
  std::vector<double> y(N, 0);

  imp = 1.0;
  double sum = 0;
  for (unsigned int i = 0; i < N; i++) {
    y[i] = LPF.clock(imp);
    imp = 0;
    sum += y[i];
  }

  std::cout << "Impulse response sum = " << sum << "\n";
  plot_fft(y);
  return 0;
}
