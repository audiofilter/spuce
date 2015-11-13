#include <iostream>
#include <fstream>
#include <spuce/filters/farrow_upsampler.h>
using namespace spuce;
using namespace std;
#include "plot_fft.h"

int main(int argc, char *argv[]) 
{
	const int N=64;
	std::vector<double> y(N);
  farrow_upsampler INTERP(4);
  double time_inc = 19.0/41.0;
  double x = 1.0;
  int need=0;

  // Show how impulse response is spread out in time
  for (int i=0;i<N;i++) {
    need = INTERP.need_sample(time_inc,x);
    if (need) x = 0;
    y[i] = INTERP.output(time_inc);
  };
  plot_data(y);
  return(1);
}
