#include "make_filter.h"
#include <spuce/filters/design_iir.h>
namespace spuce {

  // Get frequency response for IIR   
  void iir_freq(iir_coeff& MF, int pts, double* w, double inc) {
  double w_inc = inc*M_PI/(float)pts;
  for (int i=0;i<pts;i++) {
    double t = MF.freqz_mag(w_inc*i);
    if (t==0) t = 0.00001;
    w[i] = 20.0*log(t)/log(10.0);
  }
  }
  
  void make_filter::sel_filter(const char *c_sel) {
    std::string sel(c_sel);
    if (sel == "Chebyshev")    change_filter(Chebyshev);
    else if (sel == "Chebyshev2")    change_filter(Chebyshev2);
    else if (sel == "Butterworth")    change_filter(Butterworth);
    else if (sel == "Elliptic")    change_filter(Elliptic);
    else    std::cout << "Invalid filter selection " << c_sel << "\n";
  }

  void make_filter::change_filter(fil_enum f) {
    last_shape = shape;
    shape = f;
  }
  int make_filter::get_filter_type() { return fil_type; }

  void make_filter::set_filter_type(int t) {
    fil_type = t;
    switch (t) {
    case 0: f_type = "LOW_PASS"; break;
    case 1: f_type = "HIGH_PASS"; break;
    case 2: f_type = "BAND_PASS"; break;
    case 3: f_type = "BAND_STOP"; break;
    }
  }
  
  void make_filter::init(int points) { pts = points; }
  void make_filter::set_fs(double f) { fs = f * 1000.0; }

  make_filter::~make_filter() {}
  make_filter::make_filter() {
    reset();
    center = 0.25;
    fs = 44100;
  }

  void make_filter::clear_filters() {}

  void make_filter::reset() {
    f_type = "LOW_PASS";
    fil_type = 0;
    
    elliptic_fc = butterworth_fc = chebyshev_fc = 0.125;
    chebyshev2_fc = 0.2;
    cut_fc = 0.125;
    
    elliptic_pass_edge = 0.125;
    elliptic_trans = 0.1;
    
    elliptic_stop_db = 50;
    chebyshev2_stop_db = 50;
    
    elliptic_ripple = 1.0;
    chebyshev_ripple = 1.0;
    
    elliptic_order = 5;
    butterworth_order = 5;
    chebyshev_order = 5;
    chebyshev2_order = 5;
    
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
    
    switch (shape) {
    case Butterworth:      fc = limit(gain * butterworth_fc, 0.49, 0.001);      break;
    case Chebyshev:        fc = limit(gain * chebyshev_fc, 0.49, 0.001);       break;
    case Chebyshev2:       fc = limit(gain * chebyshev2_fc, 0.49, 0.001);       break;
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
    case Butterworth:    fc = butterworth_fc;      break;
    case Chebyshev:      fc = chebyshev_fc; break;
    case Chebyshev2:     fc = chebyshev2_fc; break;
    case Elliptic:       fc = elliptic_pass_edge;      break;
    case None:      fc = 0;      break;
    }
    return (fc);
  }
  
  int make_filter::get_order() {
    switch (shape) {
    case Butterworth:   return (butterworth_order);      break;
    case Chebyshev:     return (chebyshev_order);      break;
    case Chebyshev2:    return (chebyshev2_order);      break;
    case Elliptic:      return (elliptic_order);       break;
    case None:      return (0);
    }
    return (0);
  }
  double make_filter::ripple() {
    switch (shape) {
    case Elliptic:      return (elliptic_ripple);      break;
    case Chebyshev:     return (chebyshev_ripple);      break;
    default:      return (0.0);
    }
    return (0.0);
  }
  
  double make_filter::stopdB() {
    if (shape == Elliptic)    return (elliptic_stop_db);
    else if (shape == Chebyshev2)    return (chebyshev2_stop_db);
    else    return (0.0);
  }

  void make_filter::set_center_freq(int len) {
    // Convert swipe to centre freq
    double gain = pow(2, 0.002 * len);
    center = limit(gain*center, 0.5, 0.0);
    std::cout << " gain = " << gain << " cen = " << center << "\n";
  }

  double make_filter::horiz_swipe(int len, bool in_passband) {
    // Convert swipe to dB inc/decrease
    const double min_fc = 0.0;
    
    double gain = pow(2, 0.002 * len);
    double ogain = 1.0 / gain;
    
    switch (shape) {
    case Butterworth:    butterworth_fc = limit(gain * butterworth_fc, 0.49, min_fc);      break;
    case Chebyshev:      chebyshev_fc = limit(gain * chebyshev_fc, 0.49, min_fc);      break;
    case Chebyshev2:
      if (in_passband) {
        chebyshev2_fc = limit(gain * chebyshev2_fc, 0.49, min_fc);
      } else {
        chebyshev2_stop_db = limit(ogain * chebyshev2_stop_db, 100, 10.0);
      }
    case Elliptic:
      if (in_passband) {
        elliptic_pass_edge =  limit(gain * elliptic_pass_edge, 0.49 - elliptic_trans, 0.001);
      } else {
        elliptic_stop_db = limit(gain * elliptic_stop_db, 100, 10.0);
        elliptic_trans =   limit(gain * elliptic_trans, 0.49 - elliptic_pass_edge, 0.001);
      }
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
    
    switch (shape) {
    case Butterworth:		butterworth_order = limit(butterworth_order + inc, MAX_IIR, MIN_IIR);		break;
    case Chebyshev:
      if (in_passband) {
        chebyshev_ripple = limit(ogain_r * chebyshev_ripple, 20, 0.0001);
      } else {
        chebyshev_order = limit(chebyshev_order + inc, MAX_IIR, MIN_IIR);
      }
      break;
    case Chebyshev2:
      if (in_passband) {
        chebyshev2_order = limit(chebyshev2_order + inc, MAX_IIR, MIN_IIR);
      } else {
        if (above_stop) {
          chebyshev2_stop_db = limit(ogain * chebyshev2_stop_db, 100, 10.0);
        } else {
          chebyshev2_order = limit(chebyshev2_order + inc, MAX_IIR, MIN_IIR);
        }
      }
      break;
    case Elliptic:
      if (in_passband) {
        elliptic_ripple = limit(ogain_r * elliptic_ripple, 10, 0.0001);
      } else {
        if (above_stop) {
          elliptic_stop_db = limit(ogain * elliptic_stop_db, 100, 10.0);
        } else {
          elliptic_order = limit(elliptic_order + inc, MAX_IIR, MIN_IIR);
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
      cf = design_iir("elliptic",f_type,elliptic_order, elliptic_pass_edge, elliptic_ripple, elliptic_stop_db, center);
      fc =  (elliptic_pass_edge);
      break;
    case Chebyshev: 
      cf = design_iir("chebyshev",f_type,chebyshev_order,chebyshev_fc, chebyshev_ripple, 0, center);
      fc =  (chebyshev_fc);
      break;
    case Chebyshev2:
      cf = design_iir("chebyshev2",f_type,chebyshev2_order,chebyshev2_fc, 0, chebyshev2_stop_db, center);
      fc =  (chebyshev2_fc);
      break;
    case Butterworth:
      fc = butterworth_fc;
      cf = design_iir("butterworth",f_type,butterworth_order,fc, 0, 0, center);
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
      cf = design_iir("elliptic",f_type,elliptic_order, elliptic_pass_edge, elliptic_ripple,	elliptic_stop_db, center);
      break;
    case Chebyshev: 
      cf = design_iir("chebyshev",f_type,chebyshev_order,chebyshev_fc, chebyshev_ripple, 0, center);
      break;
    case Chebyshev2: 
      cf = design_iir("chebyshev2",f_type,chebyshev2_order,chebyshev2_fc, 0, chebyshev2_stop_db, center);
      break;
    case Butterworth:
      cf = design_iir("butterworth",f_type,butterworth_order,butterworth_fc, 0, 0 ,center);
      break;
    }
    mag = 20.0*log(cf->freqz_mag(w))/log(10.0);
    if (cf) delete cf;
    return (mag);
  }

}  // namespace spuce
