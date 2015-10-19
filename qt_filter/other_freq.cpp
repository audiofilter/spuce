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
#include "other_freq.h"
namespace spuce {
	void iir_freq(iir_coeff& MF, bool hpf, int pts, double* w, double inc) {
		double h0;
		h0 = MF.freqz_mag(0);
		double h,t,tl;
		
		if (h0 < 0.01) h0 = 1.0;
		if (hpf) h0 = 1.0/MF.getGain();
		
		double w_inc = inc*M_PI/(float)pts;
		for (int i=0;i<pts;i++) {
			h = MF.freqz_mag(w_inc*i);
			t = h/h0;
			if (t==0) t = 0.00001;
			tl = 20.0*log(t)/log(10.0);
			w[i] = tl;
		}
	}
}
	
