#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <spuce/filters/design_fir.h>
#include <spuce/filters/fir.h>
using namespace std;
using namespace spuce;
#include "plot_fft.h"
int main(int argc, char* argv[]) {
	const int N=256;
  int i;
  float_type imp;
  int TAPS = 51;
  float_type alpha = 0.2;
  float_type fl = 0.1;
  float_type fu = 0.2;
  float_type weight = 100;
  int sel = 0;
  if (argc > 1) {
    sel = atoi(argv[1]);
  }
  std::string band_type = "LOW_PASS";
  switch (sel) {
  case 0: band_type = "LOW_PASS"; break;
  case 1: band_type = "HIGH_PASS"; break;
  case 2: band_type = "BAND_PASS"; break;
  case 3: band_type = "BAND_STOP"; break;
  }
  std::cout << "Band type is " << band_type << "\n";

  std::string filt_type = "remez";
  auto taps = design_fir(filt_type, band_type, TAPS, fl, fu, alpha, weight);

	fir<double> RFIR(taps);
	std::vector<double> y(N);

  imp = 1;
  for (i=0;i<N;i++) {
		y[i] = RFIR.clock(imp);
		imp = 0;
  }
	
	plot_fft(y);

  return(1);
}
