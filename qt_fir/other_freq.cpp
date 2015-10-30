#define _USE_MATH_DEFINES
#include <cmath>
#include <complex>
#include "other_freq.h"

// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)

namespace spuce {

void fir_coeff_freq(fir_coeff<double>& MF, int pts, double* w, int freq_off, double inc) {

  double t;
  double w_inc = inc*M_PI/(float)pts; 
  std::complex<double> z_inc, nom;
	
  for (int i=0;i<pts;i++) {
    double wf = w_inc*(i-freq_off);
    std::complex<double> z(1,0);
		z_inc = std::complex<double>(cos(wf),sin(wf));
		nom = 0;
		for (int j=0;j<MF.number_of_taps();j++) {
			nom += z*(std::complex<double>(MF.gettap(j)));
			z *= z_inc;
		}
		t = sqrt(norm(nom));
    if (t==0) t = 0.00001;
    t = 20.0*log(t)/log(10.0);
    w[i] = t;
  }
}

void fir_freq(std::vector<double>& MF, int pts, double* w, double inc) {

  double t;
  double w_inc = inc*M_PI/(float)pts; 
  std::complex<double> z_inc, nom;
	
  for (int i=0;i<pts;i++) {
    double wf = w_inc*i;
    std::complex<double> z(1,0);
		z_inc = std::complex<double>(cos(wf),sin(wf));
		nom = 0;
		for (int j=0;j<MF.size();j++) {
			nom += z*(std::complex<double>(MF[j]));
			z *= z_inc;
		}
		t = sqrt(norm(nom));
    if (t==0) t = 0.00001;
    t = 20.0*log(t)/log(10.0);
    w[i] = t;
  }
}
	
}
	
