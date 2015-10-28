#include "des_filter.h"
#include "make_filter.h"

spuce::make_filter LPF;
spuce::make_filter* pLPF = &LPF;

void set_fs(float f) { pLPF->set_fs(f); }
void lpf_init(int pts) { pLPF->init(pts); }
void reset() { pLPF->reset(); }
void lpf_sel(const char* sel) { pLPF->sel_filter(sel); }
void set_filter_type(int t) { pLPF->set_filter_type(t); }
int  get_filter_type() { return pLPF->get_filter_type(); }
void set_center(int len) { pLPF->set_center_freq(len); }

double horiz_swipe(int len, bool in_passband) {  return (pLPF->horiz_swipe(len, in_passband));}
double get_fc(int len, bool in_passband) {  return (pLPF->get_fc(len, in_passband));}
double fc() {  return (pLPF->fcutoff());}
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
