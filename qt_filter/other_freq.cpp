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
void iir_freq(iir_coeff& MF, int pts, double* w, double inc) {
    double w_inc = inc*M_PI/(float)pts;
    for (int i=0;i<pts;i++) {
        double t = MF.freqz_mag(w_inc*i);
        if (t==0) t = 0.00001;
        w[i] = 20.0*log(t)/log(10.0);
    }
}
}
	
