#include <iostream>
#include <fstream>
#include <iomanip>
#include <spuce/filters/notch_iir.h>
#include <spuce/filters/notch_allpass.h>
using namespace std;
using namespace spuce;
//! \brief testing of notch filter based on allpass section
//
//! \ingroup examples
#include "plot_fft.h"

int main(int argv, char* argc[]) {

	const int N=256;
  int i;
  double imp;
	std::vector<double> y(N);
  notch_allpass<double,double> Notch(0.42822);

  imp = 1.0;
  for (i=0;i<N;i++) {
		y[i] = Notch.clock(imp);
		imp = 0;
  }
	plot_fft(y);
	
  return(1);
}
