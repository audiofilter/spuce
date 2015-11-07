#pragma once
// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include <spuce/typedefs.h>
namespace spuce {

enum fil_enum {
  None,
	NotchIIR,
	CutBoost,
	MaxflatSubband,
	EllipticSubband
};

class make_filter {

public:
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
