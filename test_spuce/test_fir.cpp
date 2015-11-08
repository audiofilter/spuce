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
  float_type alpha = 0.5;
  float_type spb = 0.1;

  fir_coeff<float_type> filt(TAPS);
  //root_raised_cosine(filt, alpha, 1.0/spb);
  raised_cosine(filt, alpha, 1.0/spb);
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
