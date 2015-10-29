#pragma once
// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include <spuce/typedefs.h>
#include <spuce/filters/fir_coeff.h>
namespace spuce {

#include "des_filter.h"

enum fil_enum {
  None,
  MaxflatFIR,
  GaussianFIR,
  RemezFIR,
  RaisedCosine,
  RootRaisedCosine
};

class make_filter {
  enum fil_type { low, high, band };

 public:
  double remez_pass_edge;
  double remez_stop_edge;
  double remez_stop_weight;
  double rc_fc;
  double rrc_fc;
  double maxflat_fc;
  double gauss_fc;
  double variable_ripple;
  double remez_trans;
  double rc_alpha;
  double rrc_alpha;
  bool hpf;

  int gauss_taps;
  int remez_taps;
  int maxflat_taps;
  int rc_taps;
  int rrc_taps;

  int pts;
  int bits;
  double fs;
	
  typedef double audio_data_type;

  fil_enum shape;
  fil_enum last_shape;
  fil_type pass_type;

  double horiz_swipe(int len, bool in_passband);
  double get_fc(int len, bool in_passband);
  int get_order();
  bool is_fir();
  bool is_bpf();
  double ripple();
  double stopdB();
  void vertical_swipe(int len, bool in_passband, bool above_stop);
  double update(double *w);
  double update(double *w, double w_inc);

  void sel_filter(const char *sel);
  void change_filter(fil_enum f);
  double limit(double x, double mx, double min);

  make_filter();
  ~make_filter();
  void init(int points);
  void reset();
  void clear_filters();
  void set_filter_type(int h);
  void set_fs(double f);
};
}  // namespace spuce
