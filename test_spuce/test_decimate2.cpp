#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <spuce/filters/decimator.h>
using namespace std;
using namespace spuce;
#include "plot_fft.h"
/*
 Compare frequency responses of a FIR decimation filter 
 with an IIR one.
 FIR order = 2*Rate*IIR_Order + 1
 */
int main(int argv, char* argc[]) {
  const size_t IIR_Order = 6;
  const int rate=6;
	const int N=256*rate;

  decimator<double> IDEC(rate, IIR_Order, false);
  decimator<double> FDEC(rate, IIR_Order, true);
  
	std::vector<double> imp(N,0);
	std::vector<double> x;
	std::vector<double> y;
  
  imp[0] = 1.0;
  IDEC.process(imp, x);
  FDEC.process(imp, y);
  
  /*
  std::cout << "print x\n";
  for (size_t i=0;i<x.size();i++)    std::cout << "x[" << i << "]=" << x[i] << "\n";

  std::cout << "print y\n";
  for (size_t i=0;i<y.size();i++)    std::cout << "y[" << i << "]=" << y[i] << "\n";
  */
  
  if ((x.size() > 0) && (y.size() > 0)) {
    std::cout << "Calling compare fft\n";
    compare_fft(x,y);
  }
  
  return(1);
}
