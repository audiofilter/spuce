#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <spuce/filters/cic.h>
using namespace std;
using namespace spuce;
#include "plot_fft.h"
int main(int argv, char* argc[]) {
	const int N=256;
  int i;
  int rate = 16;
  long imp;
  const long O=2;

  cic<long> F(O);
	std::vector<double> y(N);

  imp = 1;
	signed char dump = 1;
  for (i=0;i<N;i++) {
		dump = ((i % rate) == 0);
    y[i] = (F.interpolate(imp, dump))*pow(rate,-O);
		imp = 0;
  }

  // Expect 1st sidelobe to be down by -13 * O dB
	plot_fft(y);

  return(1);
}
