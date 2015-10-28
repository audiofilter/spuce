#pragma once

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void lpf_init(int pts);
EXTERNC void reset();
EXTERNC void set_gain(float g);
EXTERNC void lpf_sel(const char* sel);
EXTERNC double horiz_swipe(int len, bool in_passband);
EXTERNC void set_center(int len);
EXTERNC double get_fc(int len, bool in_passband);
EXTERNC void vertical_swipe(int len, bool in_passband, bool above_stop);
EXTERNC double update_w(double* w, double w_inc);
EXTERNC void set_fs(float fs);
EXTERNC void set_filter_type(int t);
EXTERNC int  get_filter_type();
EXTERNC double get_mag(double w);

EXTERNC int get_order();
EXTERNC double stopdB();
EXTERNC double ripple();
EXTERNC double fc();

