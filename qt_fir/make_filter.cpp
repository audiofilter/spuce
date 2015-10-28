/*
    Copyright (C) 2014 Tony Kirke

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "make_filter.h"
#define USE_DBL
#include "other_freq.h"
#include <spuce/filters/butterworth_fir.h>
#include <spuce/filters/gaussian_fir.h>
#include <spuce/filters/create_remez_lpfir.h>
#include <spuce/filters/raised_cosine.h>
#include <spuce/filters/root_raised_cosine.h>
namespace spuce {

void make_filter::sel_filter(const char *c_sel) {
  std::string sel(c_sel);
  // std::cout << "Sel = " << sel << "\n";
  if (sel == "Maxflat FIR")
    change_filter(MaxflatFIR);
  else if (sel == "Gaussian FIR")
    change_filter(GaussianFIR);
  else if (sel == "Remez FIR")
    change_filter(RemezFIR);
  else if (sel == "Raised Cosine")
    change_filter(RaisedCosine);
  else if (sel == "Root Raised Cosine")
    change_filter(RootRaisedCosine);
  else if (sel == "None")
    change_filter(None);
  else
    std::cout << "Invalid filter selection\n";
}

void make_filter::change_filter(fil_enum f) {
  last_shape = shape;
  shape = f;
}

void make_filter::set_filter_type(int t) {
	pass_type = low;
}

void make_filter::init(int points) { pts = points; }
void make_filter::set_fs(double f) { fs = f * 1000.0; }

make_filter::~make_filter() {}
make_filter::make_filter() {
  reset();
  fs = 44100;
}

void make_filter::clear_filters() {}

void make_filter::reset() {
  hpf = false;
  pass_type = low;

  maxflat_fc = 0.16;
  gauss_fc = 0.06;
  rc_fc = rrc_fc = 0.5;

  remez_pass_edge = 0.4;
  remez_trans = 0.2;
  remez_stop_edge = remez_pass_edge + remez_trans;
  remez_stop_weight = 50;

  rc_alpha = rrc_alpha = 0.25;

  gauss_taps = 21;
  remez_taps = 33;
  maxflat_taps = 45;
  rc_taps = rrc_taps = 33;
  shape = RemezFIR;
  last_shape = shape;
	bits = 0;
}

double make_filter::limit(double x, double mx, double mn) {
  if (x > mx)
    x = mx;
  else if (x < mn)
    x = mn;
  return x;
}

double make_filter::get_fc(int len, bool in_passband) {
  // Convert swipe to dB inc/decrease
  double fc = 0.5;
  double gain = pow(2, 0.002 * len);

  switch (shape) {
    case MaxflatFIR:
      fc = 2.0 * limit(gain * maxflat_fc, 0.4, 0.001);
      break;
    case GaussianFIR:
      fc = 2.0 * limit(gain * gauss_fc, 0.4, 0.001);
      break;
    case RemezFIR:
      if (in_passband) {
        fc = limit(gain * remez_pass_edge, 1.0 - remez_trans, 0.001);
      } else {
        fc = remez_pass_edge;
      }
      break;
    case RaisedCosine:
      if (in_passband) {
        fc = limit(gain * rc_fc, 0.5, 0.001);
      } else {
        fc = rc_fc;
      }
      break;
    case RootRaisedCosine:      break;
    case None:
      fc = 0;
      break;
  }
  return (fc);
}

int make_filter::get_order() {
  switch (shape) {
	case MaxflatFIR:      return (maxflat_taps);      break;
	case GaussianFIR:      return (gauss_taps);      break;
	case RemezFIR:      return (remez_taps);      break;
	case RaisedCosine:      return (rc_taps);      break;
	case RootRaisedCosine:      return (rrc_taps);      break;
	case None:      return (0);
  }
  return (0);
}
	bool make_filter::is_bpf() { return (false);}

bool make_filter::is_fir() {
  switch (shape) {
    case MaxflatFIR:      return (true);      break;
    case GaussianFIR:      return (true);      break;
    case RemezFIR:      return (true);      break;
    case RaisedCosine:      return (true);      break;
    case RootRaisedCosine:      return (true);      break;
    default:   break;
  }
  return (false);
}
double make_filter::ripple() {
  switch (shape) {
    case RemezFIR:      return (0.0);      break;  // for now
    default:      return (0.0);
  }
  return (0.0);
}

double make_filter::stopdB() {
	return (0.0);
}

double make_filter::horiz_swipe(int len, bool in_passband) {
  // Convert swipe to dB inc/decrease
  const double min_fc = 0.0;

  double gain = pow(2, 0.002 * len);
  double inc;

  if (len < 0)
    inc = 2;
  else
    inc = 0.5;

  switch (shape) {
    case MaxflatFIR:
      maxflat_fc = limit(gain * maxflat_fc, 0.4, 0.001);
      break;
    case GaussianFIR:
      gauss_fc = limit(gain * gauss_fc, 0.4, min_fc);
      break;
    case RemezFIR:
      if (in_passband) {
        remez_pass_edge =
            limit(gain * remez_pass_edge, 0.95 - remez_trans, 0.001);
      } else {
        remez_trans = limit(gain * remez_trans, 0.95 - remez_pass_edge, 0.001);
      }
      remez_stop_edge = remez_pass_edge + remez_trans;
      break;
    case RaisedCosine:
      if (in_passband) {
        rc_fc = limit(gain * rc_fc, 0.5, 0.001);
      } else {
        rc_alpha = limit(gain * rc_alpha, 1, 0.01);
      }
      break;
    case RootRaisedCosine:
      rrc_alpha = limit(gain * rrc_alpha, 1, 0.01);
      break;
    case None:
      break;
  }
  return (0.0);
}
void make_filter::vertical_swipe(int len, bool in_passband, bool above_stop) {
  const int MAX_FIR = 99;
  const int MIN_FIR = 15;
  int inc;

  if (len < 0)
    inc = 1;
  else
    inc = -1;

  // Convert swipe to dB inc/decrease
  double gain = pow(2, 0.002 * len);
  double ogain = 1.0 / gain;

  switch (shape) {
    case MaxflatFIR:
      maxflat_taps = limit(maxflat_taps + 8 * inc, MAX_FIR, MIN_FIR);
      break;
    case GaussianFIR:
      gauss_taps = limit(gauss_taps + inc, MAX_FIR, MIN_FIR);
      break;
    // FIX ME - should change to passband ripple while in passband
    case RemezFIR:
      if (in_passband) {
        remez_stop_weight = limit(ogain * remez_stop_weight, 100, 0.01);
      } else {
        if (above_stop) {
          remez_stop_weight = limit(ogain * remez_stop_weight, 100, 0.01);
        } else {
          remez_taps = limit(remez_taps + inc, MAX_FIR, MIN_FIR);
          break;
        }
      }
    case RootRaisedCosine:
      rrc_taps = limit(rrc_taps + 2 * inc, MAX_FIR, MIN_FIR);
      break;
    case RaisedCosine:
      rc_taps = limit(rc_taps + 2 * inc, MAX_FIR, MIN_FIR);
      break;
    default:
      break;
  }
}
double make_filter::update(double *w) { return (update(w, 1.0)); }
double make_filter::update(double *w, double inc) {
  double fc;
  int freq_off = 0;

  switch (shape) {
	case None:
		for (int i = 0; i < pts; i++) w[i] = 1.0;
		break;
	case MaxflatFIR: {
		fir_coeff<double> Maxflat_Fir(maxflat_taps);
		fc = maxflat_fc;
		butterworth_fir(Maxflat_Fir, fc);
		fir_coeff_freq(Maxflat_Fir, pts, w, freq_off, inc);
	}
		return (maxflat_fc);
		break;
	case RemezFIR: {
		fir_coeff<double> Remez_Fir(remez_taps);
		double pass_edge = remez_pass_edge;
		double stop_edge = remez_stop_edge;
		create_remez_lpfir(Remez_Fir, pass_edge, stop_edge, remez_stop_weight);
		fir_coeff_freq(Remez_Fir, pts, w, freq_off, inc);
	}
		return (remez_pass_edge);
		break;
	case GaussianFIR: {
		fir_coeff<double> Gaussian_Fir(gauss_taps);
		gaussian_fir(Gaussian_Fir, gauss_fc, 8);
		fir_coeff_freq(Gaussian_Fir, pts, w, freq_off, inc);
	}
		return (gauss_fc);
		break;
	case RaisedCosine: {
		fir_coeff<double> RaisedCosine_Fir(rc_taps);
		fc = 1.0 / rc_fc;
		raised_cosine(RaisedCosine_Fir, rc_alpha, fc);
		fir_coeff_freq(RaisedCosine_Fir, pts, w, freq_off, inc);
    }
		return (rc_fc);
		break;
	case RootRaisedCosine: {
		fir_coeff<double> RootRaisedCosine_Fir(rrc_taps);
		root_raised_cosine(RootRaisedCosine_Fir, rrc_alpha, 2);
		fir_coeff_freq(RootRaisedCosine_Fir, pts, w, freq_off, inc);
	}
		return (0.5);
		break;
		
  }
  return (0);
}

}  // namespace spuce
