#pragma once
// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include <spuce/typedefs.h>
#include <spuce/filters/fir_coeff.h>
namespace spuce {

enum fil_enum {
  None,
  Hanning,
  Hamming,
  Bartlett,
  Blackman,
  Kaiser,
  Chebyshev
};

class make_filter {

public:
  std::vector<double> taps;
  double cheby_fc;
  double kaiser_ripple;
  double kaiser_tw;
  
  int cheby_taps;
  int remez_taps;
  int hamming_taps;
  int hanning_taps;
  int bartlett_taps;
  int blackman_taps;
  int kaiser_taps;

  int pts;
  fil_enum shape;

  void horiz_swipe(int len);
  void vertical_swipe(int len);
  double update(double *w);
  void change_filter(fil_enum f);
  double limit(double x, double mx, double min);
  make_filter();
  ~make_filter();
  void init(int points);
  void reset();
};
}  // namespace spuce
