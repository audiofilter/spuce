#include "other_freq.h"
namespace spuce {
void iir_freq(iir_coeff& MF, int pts, double* w, double inc) {
    double w_inc = inc*M_PI/(float)pts;
    for (int i=0;i<pts;i++) {
        double t = MF.freqz_mag(w_inc*i);
        if (t==0) t = 0.00001;
        w[i] = 20.0*log(t)/log(10.0);
    }
}
}
	
