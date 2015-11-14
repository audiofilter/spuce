// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include "make_filter.h"
#include <stdexcept>
#include <cmath>
#include <complex>
#include <spuce/filters/design_fir.h>
namespace spuce {

void fir_freq(std::vector<double>& MF, int pts, double* w) {
  double t;
  double w_inc = M_PI/(float)pts; 
  std::complex<double> z_inc, nom;
	
  for (int i=0;i<pts;i++) {
    double wf = w_inc*i;
    std::complex<double> z(1,0);
		z_inc = std::complex<double>(cos(wf),sin(wf));
		nom = 0;
		for (size_t j=0;j<MF.size();j++) {
			nom += z*(std::complex<double>(MF[j]));
			z *= z_inc;
		}
		t = sqrt(norm(nom));
    if (t==0) t = 0.00001;
    t = 20.0*log(t)/log(10.0);
    w[i] = t;
  }
}

void fir_freq(std::vector<std::complex<double>>& MF, int pts, double* w) {
  double t;
  double w_inc = 2.0*M_PI/(float)pts; 
  std::complex<double> z_inc, nom;
	
  for (int i=0;i<pts;i++) {
    double wf = w_inc*i;
    std::complex<double> z(1,0);
		z_inc = std::polar(1.0,wf);
		nom = 0;
		for (size_t j=0;j<MF.size();j++) {
			nom += z*MF[j];
			z *= z_inc;
		}
		t = sqrt(norm(nom));
    if (t==0) t = 0.00001;
    t = 20.0*log(t)/log(10.0);
    w[i] = t;
  }
}
	
void make_filter::sel_filter(const char *c_sel) {
  std::string sel(c_sel);
  if (sel == "Maxflat FIR")    change_filter(MaxflatFIR);
  else if (sel == "Gaussian FIR")    change_filter(GaussianFIR);
  else if (sel == "Remez FIR")    change_filter(RemezFIR);
  else if (sel == "Sinc FIR")    change_filter(SincFIR);
  else if (sel == "Raised Cosine")    change_filter(RaisedCosine);
  else if (sel == "Root Raised Cosine")    change_filter(RootRaisedCosine);
  else if (sel == "None")    change_filter(None);
  else
    std::cout << "Invalid filter selection\n";
}
void make_filter::sel_band(const char *c_sel) {
  std::string sel(c_sel);
  band_type = sel;
}

void make_filter::change_filter(fil_enum f) {  shape = f;}
void make_filter::set_filter_type(int t) {	pass_type = low;}
void make_filter::init(int points) { pts = points; }

make_filter::~make_filter() {}
make_filter::make_filter() {
  reset();
}

void make_filter::reset() {
  pass_type = low;

  maxflat_fc = 0.16;
  gauss_fc = 0.06;
  rc_fc = rrc_fc = 0.125;

  remez_pass_edge = 0.0625;
  remez_trans = 0.1;
  remez_stop_weight = 50;

  rc_alpha = rrc_alpha = 0.25;
	sinc_fc = 0.125;

  gauss_taps = 21;
  remez_taps = 33;
	sinc_taps = 33;
  maxflat_taps = 45;
  rc_taps = rrc_taps = 33;
  shape = RemezFIR;
  band_type = "LOW_PASS";
  center = 0.25;

}

double make_filter::limit(double x, double mx, double mn) {
  if (x > mx)
    x = mx;
  else if (x < mn)
    x = mn;
  return x;
}

int make_filter::get_order() {
  switch (shape) {
	case MaxflatFIR:    return (maxflat_taps);      break;
	case GaussianFIR:   return (gauss_taps);      break;
	case SincFIR:   return (sinc_taps);      break;
	case RemezFIR:      return (remez_taps);      break;
	case RaisedCosine:  return (rc_taps);      break;
	case RootRaisedCosine:      return (rrc_taps);      break;
	case None:      return (0);
  }
  return (0);
}
	bool make_filter::is_bpf() { return (false);}

double make_filter::horiz_swipe(int len, bool in_passband) {
  // Convert swipe to dB inc/decrease
  const double min_fc = 0.0;
  double gain = pow(2, 0.002 * len);

  switch (shape) {
	case MaxflatFIR:
		maxflat_fc = limit(gain * maxflat_fc, 0.4, 0.001);
		break;
	case GaussianFIR:
		gauss_fc = limit(gain * gauss_fc, 0.4, min_fc);
		break;
	case SincFIR:
		sinc_fc = limit(gain * sinc_fc, 0.4, min_fc);
		break;
	case RemezFIR:
		if (in_passband) {
			remez_pass_edge = limit(gain * remez_pass_edge, 0.49 - remez_trans, 0.001);
		} else {
			remez_trans = limit(gain * remez_trans, 0.49 - remez_pass_edge, 0.001);
		}
		break;
	case RaisedCosine:
		if (in_passband) {
			rc_fc = limit(gain * rc_fc, 1.0, 0.001);
		} else {
			rc_alpha = limit(gain * rc_alpha, 1, 0.01);
		}
		break;
	case RootRaisedCosine:
		if (in_passband) {
			rrc_fc = limit(gain * rrc_fc, 0.5, 0.001);
    } else {
      rrc_alpha = limit(gain * rrc_alpha, 1, 0.01);
    }
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
	case SincFIR:
		sinc_taps = limit(sinc_taps + inc, MAX_FIR, MIN_FIR); break;
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
			}
		}
		break;
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

void make_filter::set_center_freq(int len) {
	// Convert swipe to centre freq
	double gain = pow(2, 0.002 * len);
	center = limit(gain*center, 0.5, 0.01);
}
int make_filter::get_filter_type() {
  if ((band_type == "BAND_PASS") || (band_type == "BAND_STOP")) {
    return 1;
  } else {
    return 0;
  }
}

double make_filter::update(double *w) {
  double fl;
  double fu;
  double fc;
  
  switch (shape) {
	case RemezFIR: fc = remez_pass_edge; break;
	case MaxflatFIR:    fc = maxflat_fc; break;
	case GaussianFIR:    fc = gauss_fc;break;
	case SincFIR:    fc = sinc_fc;break;
	case RaisedCosine:    fc = rc_fc;break;
	case RootRaisedCosine:    fc = rrc_fc;break;
  case None: fc = 0.5; break;
	}

  if ((band_type == "LOW_PASS") || (band_type == "HIGH_PASS")) {
    fl = fc;
  } else { // Band_pass/stop
    if (center > fc/2) {
      fl = center - fc/2.0;
    } else {
      fl = fc;
    }
  }
  
  fu = center + fc/2.0;

  try {
    switch (shape) {
    case RemezFIR:
      taps = design_fir("remez", band_type, remez_taps, fl, fu, remez_trans, remez_stop_weight);		break;
    case MaxflatFIR:
      taps = design_fir("maxflat", band_type,  maxflat_taps, fl, fu);		break;
    case GaussianFIR:
      taps = design_fir("gaussian",  band_type, gauss_taps, fl, fu);		break;
    case SincFIR:
      taps = design_fir("sinc",  band_type, sinc_taps, fl , fu);		break;
    case RaisedCosine:
      taps = design_fir("raised_cosine",  band_type, rc_taps, fl, fu, rc_alpha);		break;
    case RootRaisedCosine:
      taps = design_fir("root_raised_cosine",  band_type, rrc_taps, fl, fu, rrc_alpha); break;
    case None:			for (int i = 0; i < pts; i++) w[i] = 1.0;			break;
    }
  }
  catch (const std::runtime_error error) {
    std::cout << "Problem in design_fir("+band_type+"):"+error.what();
    for (int i = 0; i < pts; i++) w[i] = 1.0;
  }

  /* Define TEST_COMPLEX_FIRS To see frequency responses of complex fir, note the frequency plot
     shows -0.5 to 0.5 but labels are still 0 to 0.5 */

  //#define TEST_COMPLEX_FIRS
#ifdef TEST_COMPLEX_FIRS
  if (band_type == "BAND_PASS") band_type = "COMPLEX_BAND_PASS";
  if (band_type == "BAND_STOP") band_type = "COMPLEX_BAND_STOP";
#endif
  
  if ((band_type == "COMPLEX_BAND_PASS") || (band_type == "COMPLEX_BAND_STOP")) {
    std::vector<std::complex<double>> complex_taps;
    try {
      switch (shape) {
      case RemezFIR:
        complex_taps = design_complex_fir("remez", band_type, remez_taps, fl, fu, remez_trans, remez_stop_weight);		break;
      case MaxflatFIR:
        complex_taps = design_complex_fir("maxflat", band_type,  maxflat_taps, fl, fu);		break;
      case GaussianFIR:
        complex_taps = design_complex_fir("gaussian",  band_type, gauss_taps, fl, fu);		break;
      case SincFIR:
        complex_taps = design_complex_fir("sinc",  band_type, sinc_taps, fl , fu);		break;
      case RaisedCosine:
        complex_taps = design_complex_fir("raised_cosine",  band_type, rc_taps, fl, fu, rc_alpha);		break;
      case RootRaisedCosine:
        complex_taps = design_complex_fir("root_raised_cosine",  band_type, rrc_taps, fl, fu, rrc_alpha); break;
      case None: break;
      }
    }
    catch (const std::runtime_error error) {
      std::cout << "Problem in design_complex_fir("+band_type+"):"+error.what();
      for (int i = 0; i < pts; i++) w[i] = 1.0;
    }
    if (complex_taps.size() > 0) 
      fir_freq(complex_taps, pts, w);
  } else {
    if (taps.size() > 0) 
      fir_freq(taps, pts, w);
  }
  return (0);
}
double make_filter::get_mag(double w) {
	std::complex<double> z_inc;
	std::complex<double> z = 1.0;
	z_inc = std::complex<double>(cos(w),sin(w));
	std::complex<double> nom = 0;
  if (taps.size() > 0) {
    for (size_t j=0;j<taps.size();j++) {
      nom += taps[j]*z;
      z *= z_inc;
    }
    double t = sqrt(std::norm(nom));
    if (t==0) t = 0.00001;
    t = 20.0*log(t)/log(10.0);
    return t;
  } else {
    return 0;
  }
}



}  // namespace spuce
