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
#include <spuce/filters/design_iir.h>
namespace spuce {

void make_filter::sel_filter(const char *c_sel) {
  std::string sel(c_sel);
  if (sel == "Chebyshev")    change_filter(Chebyshev);
  else if (sel == "Butterworth")    change_filter(Butterworth);
  else if (sel == "Elliptic")    change_filter(Elliptic);
  else    std::cout << "Invalid filter selection " << c_sel << "\n";
}

void make_filter::change_filter(fil_enum f) {
  last_shape = shape;
  shape = f;
}

void make_filter::set_filter_type(int t) {
	if (t == 1) {
		pass_type = low;
		f_type = "LOW_PASS";
	} else {
		pass_type = high;
		f_type = "HIGH_PASS";
	}
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

  elliptic_fc = butterworth_fc = chebyshev_fc = 0.25;
  cut_fc = 0.125;

  elliptic_pass_edge = 0.2;
  elliptic_trans = 0.1;
  elliptic_stop_edge = elliptic_pass_edge + elliptic_trans;

  elliptic_stop_db = 50;
  elliptic_ripple = 1.0;
  chebyshev_ripple = 1.0;

  elliptic_order = 4;
  butterworth_order = 4;
  chebyshev_order = 4;

  shape = Chebyshev;
  last_shape = shape;
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

  //	std::cout << "(len) " << len << " gain = " << gain << "\n";

  switch (shape) {
    case Butterworth:
      fc = limit(gain * butterworth_fc, 0.49, 0.001);
      break;
    case Chebyshev:
      fc = limit(gain * chebyshev_fc, 0.49, 0.001);
      break;
    case Elliptic:
      if (in_passband) {
        fc = limit(gain * elliptic_pass_edge, 0.49 - elliptic_trans, 0.001);
      } else {
        fc = elliptic_pass_edge;
      }
      break;
    case None:
      fc = 0;
      break;
  }
  return (fc);
}
double make_filter::fcutoff() {
	double fc;
  switch (shape) {
	case Butterworth:      fc = butterworth_fc;      break;
	case Chebyshev:      fc = chebyshev_fc; break;
	case Elliptic:        fc = elliptic_pass_edge;      break;
	case None:      fc = 0;      break;
  }
  return (fc);
}

int make_filter::get_order() {
  switch (shape) {
	case Butterworth:      return (butterworth_order);      break;
	case Chebyshev:      return (chebyshev_order);      break;
	case Elliptic:      return (elliptic_order);       break;
	case None:      return (0);
  }
  return (0);
}
double make_filter::ripple() {
  switch (shape) {
    case Elliptic:      return (elliptic_ripple);      break;
    case Chebyshev:      return (chebyshev_ripple);      break;
    default:      return (0.0);
  }
  return (0.0);
}

double make_filter::stopdB() {
  if (shape == Elliptic)    return (elliptic_stop_db);
  else    return (0.0);
}

double make_filter::horiz_swipe(int len, bool in_passband) {
  // Convert swipe to dB inc/decrease
  const double min_fc = 0.0;

  double gain = pow(2, 0.002 * len);
  double inc;

  if (len < 0)    inc = 2;
  else    inc = 0.5;

	//	std::cout << "in_pass = " << in_passband << "\n";
	
  switch (shape) {
    case Butterworth:
      butterworth_fc = limit(gain * butterworth_fc, 0.49, min_fc);
      break;
    case Chebyshev:
      chebyshev_fc = limit(gain * chebyshev_fc, 0.49, min_fc);
      break;
    case Elliptic:
      if (in_passband) {
        elliptic_pass_edge =  limit(gain * elliptic_pass_edge, 0.49 - elliptic_trans, 0.001);
      } else {
        elliptic_stop_db = limit(gain * elliptic_stop_db, 100, 10.0);
        elliptic_trans =   limit(gain * elliptic_trans, 0.49 - elliptic_pass_edge, 0.001);
      }
      elliptic_stop_edge = elliptic_pass_edge + elliptic_trans;
      break;
	case None:
      break;
  }
  return (0.0);
}
void make_filter::vertical_swipe(int len, bool in_passband, bool above_stop) {
  const int MAX_IIR = 30;
  const int MIN_IIR = 1;
  int inc;

  if (len < 0)    inc = 1;
  else    inc = -1;

  // Convert swipe to dB inc/decrease
  double gain = pow(2, 0.002 * len);
  double ogain = 1.0 / gain;
  double gain_r = pow(2, 0.004 * len);
  double ogain_r = 1.0 / gain_r;

	//std::cout << "in_pass = " << in_passband << " above = " << above_stop << "\n";
  switch (shape) {
	case Butterworth:
		butterworth_order = limit(butterworth_order + inc, MAX_IIR, MIN_IIR);
		//std::cout << "order = " << butterworth_order << "\n";
		break;
	case Chebyshev:
		if (in_passband) {
			chebyshev_ripple = limit(ogain_r * chebyshev_ripple, 20, 0.0001);
			//std::cout << "ripple = " << chebyshev_ripple << "\n";
		} else {
			chebyshev_order = limit(chebyshev_order + inc, MAX_IIR, MIN_IIR);
			//std::cout << "order = " << chebyshev_order << "\n";
		}
		break;
	case Elliptic:
		if (in_passband) {
			elliptic_ripple = limit(ogain_r * elliptic_ripple, 10, 0.0001);
			//std::cout << "ripple = " << elliptic_ripple << "\n";
		} else {
			if (above_stop) {
				elliptic_stop_db = limit(ogain * elliptic_stop_db, 100, 10.0);
				//std::cout << "stop_db = " << elliptic_stop_db << "\n";
			} else {
				elliptic_order = limit(elliptic_order + inc, MAX_IIR, MIN_IIR);
				//std::cout << "order = " << elliptic_order << "\n";
			}
		}
		break;
	default:
		break;
  }
}
double make_filter::update(double *w) { return (update(w, 1.0)); }
double make_filter::update(double *w, double inc) {
	double fc=0;
	iir_coeff* cf=NULL;
	switch (shape) {
	case None:
		for (int i = 0; i < pts; i++) w[i] = 1.0;
		break;
	case Elliptic: 
		cf = design_iir("elliptic",f_type,elliptic_order, elliptic_pass_edge, elliptic_ripple,	elliptic_stop_edge, elliptic_stop_db);
		fc =  (elliptic_pass_edge);
		break;
	case Chebyshev: 
		cf = design_iir("chebyshev",f_type,chebyshev_order,chebyshev_fc, chebyshev_ripple);
		fc =  (chebyshev_fc);
		break;
	case Butterworth:
		fc = butterworth_fc;
		cf = design_iir("butterworth",f_type,butterworth_order,fc);
		break;
	}
    iir_freq(*cf, pts, w, inc);
	if (cf) delete cf;
    return (fc);
}
double make_filter::get_mag(double w) {
	double mag =0;
	iir_coeff* cf=NULL;
  switch (shape) {
	case None:
		break;
	case Elliptic:
		cf = design_iir("elliptic",f_type,elliptic_order, elliptic_pass_edge, elliptic_ripple,	elliptic_stop_edge, elliptic_stop_db);
		break;
	case Chebyshev: 
		cf = design_iir("chebyshev",f_type,chebyshev_order,chebyshev_fc, chebyshev_ripple);
		break;
	case Butterworth:
		cf = design_iir("butterworth",f_type,butterworth_order,butterworth_fc);
		break;
	}
	mag = 20.0*log(cf->freqz_mag(w))/log(10.0);
	if (cf) delete cf;
  return (mag);
}

}  // namespace spuce
