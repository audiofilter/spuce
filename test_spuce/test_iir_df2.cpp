#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include <spuce/filters/design_iir.h>
#include <spuce/filters/iir_df.h>
#include "cfft.h"
using namespace spuce;
#include "plot_fft.h"

//! \brief testing how IIR filter in Pothos is being setup/used
//! \ingroup examples
typedef std::complex<double> dtype;

int main(int argv, char* argc[]) {
  const long N = 256;
	
	iir_coeff* filt = design_iir("butterworth", "LOW_PASS", 2, 0.2, 0.1, 0.4, 60.0);
	// get the tap from iir_coeff for iir_filter, incorporating the gain to feedforward taps
	std::vector<double> b = filt->get_b();
	std::vector<double> a = filt->get_a();
	// Group together feed forward and feed back taps into 1 vector for transferring to IIR filter
	double gain = filt->getGain();
	for (int i=0;i<b.size();i++) b[i] *= gain;
	for (int i=0;i<a.size();i++) b.push_back(a[i]);
	delete filt;

	// Create the Direct-Form IIR
	iir_df<dtype, double> IIR;

	// Get taps from design
	IIR.set_taps(b);

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
