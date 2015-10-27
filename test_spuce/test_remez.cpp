#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <spuce/filters/fir_coeff.h>
#include <spuce/filters/remez_fir.h>
#include <spuce/filters/fir.h>
using namespace std;
using namespace spuce;
#include "plot_fft.h"
int main(int argv, char* argc[]) {
	const int N=256;
  int i;
  float_type imp;
  int TAPS = 37;
	float_type stop_weight = 1.0;
  float_type pass_edge = 0.245;
  float_type stop_edge = 0.30625;

  bool ok = true;
  std::vector<float_type> e1(4);
  std::vector<float_type> f1(4);
  std::vector<float_type> w1(4);
  remez_fir Remz;
  w1[0] = 1.0;
  w1[1] = stop_weight;
  e1[0] = 0;
  e1[1] = pass_edge / 2.0;
  e1[2] = stop_edge / 2.0;
  e1[3] = 0.5;
  f1[0] = 1.0;
  f1[1] = 0.0;
  std::vector<float_type> fir_coef(TAPS);
  ok = Remz.remez(fir_coef, TAPS, 2, e1, f1, w1, 1);

	// Map from std::vector<> to fir_coeff<> and then to fir<>
  fir_coeff<float_type> RF(TAPS);
	for (int i=0;i<TAPS;i++) RF.settap(i,fir_coef[i]);
	fir<double> RFIR(RF);
	std::vector<double> y(N);

  imp = 1;
  for (i=0;i<N;i++) {
		y[i] = RFIR.clock(imp);
		imp = 0;
  }
	
	plot_fft(y);

  return(1);
}
