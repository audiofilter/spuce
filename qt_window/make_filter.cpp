// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include "make_filter.h"
#include <cmath>
#include <complex>
#include <spuce/filters/design_window.h>
namespace spuce {

void fir_freq(std::vector<double>& MF, int pts, double* w, double inc) {
  double t;
  double w_inc = inc*M_PI/(float)pts; 
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
	
void make_filter::change_filter(fil_enum f) {  shape = f;}
void make_filter::init(int points) { pts = points; }
make_filter::~make_filter() {}
make_filter::make_filter() {  reset();}

void make_filter::reset() {
  cheby_atten = 60.0;
  hamming_taps  =23;
  hanning_taps  =23;
  bartlett_taps =23;
  blackman_taps =23;
  kaiser_taps   =23;
  cheby_taps    =23;
  kaiser_beta = 8;
  
  shape = Blackman;
}

double make_filter::limit(double x, double mx, double mn) {
  if (x > mx)
    x = mx;
  else if (x < mn)
    x = mn;
  return x;
}

void make_filter::vertical_swipe(int len) {
  // Convert swipe to dB inc/decrease
  double gain = pow(2, 0.002 * len);

  switch (shape) {
	case Chebyshev:		cheby_atten = limit(gain * cheby_atten, 100, 1.0);	break;
    case Kaiser:		kaiser_beta= limit(gain * kaiser_beta, 100, 1);	break;
	case Hanning:
	case Hamming:
	case Blackman:
	case Bartlett:
	case None:
      break;
  }
}
void make_filter::horiz_swipe(int len) {
  const int MAX_FIR = 99;
  const int MIN_FIR = 5;
  int inc = (len < 0) ? 1 : -1;

  switch (shape) {
  case Hanning:		hanning_taps = limit(hanning_taps + inc, MAX_FIR,MIN_FIR); break;
  case Hamming:		hamming_taps = limit(hamming_taps + inc, MAX_FIR,MIN_FIR); break;
  case Blackman:	blackman_taps = limit(blackman_taps + inc, MAX_FIR,MIN_FIR); break;
  case Bartlett:	bartlett_taps = limit(bartlett_taps + inc, MAX_FIR,MIN_FIR); break;
  case Chebyshev:	cheby_taps = limit(cheby_taps + inc, MAX_FIR, MIN_FIR);		break;
  case Kaiser:	    kaiser_taps = limit(kaiser_taps + inc, MAX_FIR, MIN_FIR);	break;
  case None:	break;
  default:		break;
  }
}
double make_filter::update(double *w) {
  switch (shape) {
  case Chebyshev:        taps = design_window("chebyshev", cheby_taps, cheby_atten);		break;
  case Hanning:		       taps = design_window("hanning", hanning_taps); break;
  case Hamming:		       taps = design_window("hamming", hamming_taps); break;
  case Blackman:	       taps = design_window("blackman", blackman_taps); break;
  case Bartlett:	       taps = design_window("bartlett", bartlett_taps); break;
  case Kaiser:		       taps = design_window("kaiser", kaiser_taps, kaiser_beta); break;
  case None:			for (int i = 0; i < pts; i++) w[i] = 1.0;			break;
  }
	/*
  std::cout << "Taps[] = {";
  for (size_t i=0;i<taps.size();i++) std::cout << taps[i] << " ";
  std::cout << "}\n";
	*/
  fir_freq(taps, pts, w, 1.0);
  return (0);
}



}  // namespace spuce
