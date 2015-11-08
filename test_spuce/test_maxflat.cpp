#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <spuce/filters/fir_coeff.h>
#include <spuce/filters/design_fir.h>
#include <spuce/filters/fir.h>
using namespace std;
using namespace spuce;
#include "plot_fft.h"
int main(int argv, char* argc[]) {
	const int N=256;
  int i;
  float_type imp;
  int TAPS = 51;
  float_type fc = 0.02;

  fir_coeff<float_type> filt(TAPS);
  butterworth_fir(filt, fc);
	fir<double> RFIR(filt);
	std::vector<double> y(N);

  imp = 1;
  for (i=0;i<N;i++) {
		y[i] = RFIR.clock(imp);
		imp = 0;
  }
	
	plot_fft(y);

  return(1);
}
