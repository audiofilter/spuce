#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include <spuce/filters/iir_coeff.h>
#include <spuce/filters/butterworth_iir.h>
#include <spuce/filters/iir_df.h>
#include "plot_fft.h"

using namespace spuce;
//! \brief testing various types for IIR
//! \ingroup examples

int main(int argc, char* argv[]) {
  const long N = 1024;
  long O = 3;
  float_type imp;
	float_type f_cutoff = 0.05;
	float_type f_center = 0.14158;
	// Approximately same params as octave
	// [z0,p0,g0] = butter(3,[0.10015 0.20015]);
	// sqrt(0.10015 * 0.20015) = 0.14158
	// cos(0.14158*pi) = 0.9027
	
  if (argc > 1) {
    f_cutoff = atof(argv[1]);
  }
	std::cout << "Order used = " << O << " cut-off = " << f_cutoff << "\n";

  iir_coeff BPF(O,filter_type::bandpass);
	BPF.set_center(f_center);
  butterworth_iir(BPF, f_cutoff, 3.0);
  BPF.print();

  iir_df<float_type> LPF(BPF);

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
