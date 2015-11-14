#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <spuce/filters/design_fir.h>
#include <spuce/filters/transform_fir.h>
#include <spuce/filters/fir.h>
using namespace std;
using namespace spuce;
#include "plot_fft.h"
int main(int argv, char* argc[]) {
	const int N=256;
  int i;
  float_type imp;
  int TAPS = 51;
  float_type alpha = 0.125;
  float_type spb = 0.125;

  auto filt = design_fir("raisedcosine", "LOW_PASS", TAPS, spb, alpha);
  auto tf_taps = transform_fir("BAND_STOP", filt, 0.125);
  fir<double> BSFIR(tf_taps);
	std::vector<double> y(N);

  imp = 1;
  for (i=0;i<N;i++) {
		y[i] = BSFIR.clock(imp);
		imp = 0;
  }
	
	plot_fft(y);

  return(1);
}
