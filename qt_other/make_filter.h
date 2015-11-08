#pragma once
// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include <spuce/typedefs.h>
#include <spuce/filters/notch_allpass.h>
#include <spuce/filters/iir_allpass1_sections.h>
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

  double notch_fc;
  double notch_trans;
  double elliptic_ripple;
  int elliptic_rate;
  int maxflat_rate;
  int elliptic_order;
  int maxflat_order;
	
	//cutboost<audio_data_type, double > CUT_B;
  notch_allpass<double,double> notch;

  iir_allpass1_sections<double,double> maxflat;
  iir_allpass1_sections<double,double> elliptic;

  void horiz_swipe(int len);
  void vertical_swipe(int len);
  void update(double *w);
  void change_filter(fil_enum f);
  double limit(double x, double mx, double min);
  make_filter();
  ~make_filter();
  void init(int points);
  void reset();
};
}  // namespace spuce
