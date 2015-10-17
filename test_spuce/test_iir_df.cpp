#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include <spuce/filters/design_iir.h>
#include <spuce/filters/iir_df.h>
#include "cfft.h"
using namespace spuce;
#include "plot_fft.h"

//! \brief testing various types for IIR
//! \ingroup examples

typedef std::complex<double> dtype;

int main(int argv, char* argc[]) {
  const long N = 256;

	// First set as 1st order filter
  iir_coeff BPF(1);
  butterworth_iir(BPF, 0.4, 3.0);
	iir_df<dtype, double> IIR(BPF);
	
	// Approximation , set directly, over-riding previous setup of a different order
	std::vector<double> taps = {0.2,0.4,0.2,1,-0.3682,0.1956};
	IIR.set_taps(taps);

	// Check taps
	IIR.print();
	
	dtype imp;
  std::vector<double> y(N, 0);
	
  imp = 1.0;
  double sum = 0;
  for (unsigned int i = 0; i < N; i++) {
    y[i] = std::real(IIR.clock(imp));
		sum += y[i];
    imp = 0;
  }

  std::cout << "Impulse response sum = " << sum << "\n";
	plot_fft(y);
  return 0;
}
