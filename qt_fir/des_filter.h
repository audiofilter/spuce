#pragma once
// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)

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
EXTERNC void vertical_swipe(int len, bool in_passband, bool above_stop);
EXTERNC double update_w(double* w);
EXTERNC void set_fs(float fs);
EXTERNC void set_filter_type(int t);
EXTERNC double get_mag(double w);

EXTERNC bool is_bpf();
EXTERNC int get_order();

