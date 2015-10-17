#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include <spuce/filters/design_iir.h>
#include <spuce/filters/iir_df.h>
#include "cfft.h"
using namespace spuce;
#include "plot_fft.h"

//! \brief testing various types for IIR
//! \ingroup examples

int main(int argv, char* argc[]) {
  const long N = 256;
  const long O = 4;
  float_type imp;

  iir_coeff* coeff = design_iir("butterworth", "LOW_PASS", O, 0.1);
  iir_df<float_type> LPF(*coeff);
  std::vector<double> y(N, 0);

  imp = 1.0;
  for (unsigned int i = 0; i < N; i++) {
    y[i] = LPF.clock(imp);
    imp = 0;
  }

  plot_fft(y);
  return 0;
}
