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
#include "des_filter.h"
#include "make_filter.h"

spuce::make_filter LPF;
spuce::make_filter* pLPF = &LPF;

void set_fs(float f) { pLPF->set_fs(f); }
void lpf_init(int pts) { pLPF->init(pts); }
void reset() { pLPF->reset(); }
void lpf_sel(const char* sel) { pLPF->sel_filter(sel); }
void set_filter_type(int t) { pLPF->set_filter_type(t); }
double horiz_swipe(int len, bool in_passband) {  return (pLPF->horiz_swipe(len, in_passband));}
double get_fc(int len, bool in_passband) {  return (pLPF->get_fc(len, in_passband));}
int get_order() { return (pLPF->get_order()); }
double ripple() { return (pLPF->ripple()); }
double stopdB() { return (pLPF->stopdB()); }
void vertical_swipe(int len, bool in_passband, bool above_stop) {  pLPF->vertical_swipe(len, in_passband, above_stop);}
double update_w(double* w, double inc) {
  double x = pLPF->update(w, inc);
  return (x);
}
double get_mag(double w) {
	return pLPF->get_mag(w);
}
