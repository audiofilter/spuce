// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#define _USE_MATH_DEFINES
#include <cmath>
#include <complex>
#include <memory>
#include "make_filter.h"
namespace spuce {

	template <typename T> void other_freq(T& AP, int pts, double* w) {
    std::unique_ptr<double []> d(new double[pts]);
		double imp = 1;
		double dsum = 0;
		double db=0;
  
		// Calculate equivalent FIR impulse response
		for (int i=0;i<pts;i++) {
			d[i] = (AP.clock(imp));
			dsum += d[i];
			imp = 0;
		}
		dsum = 1.0;
		// Now calculate frequency response using equivalent FIR coefficients
		for (int k=0;k<pts;k++) {
			std::complex<double> sum = 0;
			std::complex<double> z = std::complex<double>(1.0,0.0);
			double wf = M_PI*k/(double)pts;
			std::complex<double> z_inc = std::polar(1.0,(double)wf);
			for (int i=0;i<pts;i++) {
				sum += dsum*d[i]*z;
				z	= z*z_inc;
			}
			db = 10.0*log(norm(sum))/log(10.0);
			w[k] = db;
		}
	}

	
	void make_filter::change_filter(fil_enum f) {  shape = f;}
	void make_filter::init(int points) { pts = points; }
	make_filter::~make_filter() {}
	make_filter::make_filter() : maxflat(0,3,2), elliptic(0.3,3,2) {
		reset();
	}

	void make_filter::reset() {
		shape = None;
		elliptic_order = maxflat_order = 3;
		maxflat_rate = 2;
		elliptic_rate  = 2;
		elliptic_ripple = 0.3;
		notch_fc = 0.25;
		notch_trans = 0.9;
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
		int inc = (len < 0) ? 1 : -1;
		double gain = 	pow(2,0.002*len);

		switch (shape) {
			//case Cic: cic_order = limit(cic_order+inc,5,2); break;
		case EllipticSubband: elliptic_rate = limit(elliptic_rate+inc,30,2); break;
		case MaxflatSubband: maxflat_rate = limit(maxflat_rate+inc,30,2);break;
		case NotchIIR: notch_trans = limit(gain*notch_trans,1,0.001); break;
		case CutBoost:
		case None:
      break;
		}
	}
	void make_filter::horiz_swipe(int len) {
		bool in_passband = true;
		int inc = (len < 0) ? 1 : -1;
		double gain = 	pow(2,0.002*len);
		switch (shape) {
		case EllipticSubband: 
			if (in_passband) {
				elliptic_rate = limit(inc*elliptic_rate,64,2);
			} else {
				elliptic_ripple = limit(elliptic_ripple/gain,0.5,0.001);
			}
			break;
		case MaxflatSubband: 		maxflat_rate = limit(inc*maxflat_rate,64,2);		break;
		case NotchIIR: notch_fc = limit(gain*notch_fc,0.5,0.01); 		break;
		case CutBoost:
		case None:	break;
		default:		break;
		}
	}
	void make_filter::update(double *w) {
		switch (shape) {
		case MaxflatSubband:   other_freq(maxflat,pts,w); break;
		case EllipticSubband:  other_freq(elliptic,pts,w); break;
		case NotchIIR:         other_freq(notch,pts,w); break;
		case CutBoost:
		case None:			for (int i = 0; i < pts; i++) w[i] = 1.0;			break;
		}
}



}  // namespace spuce
