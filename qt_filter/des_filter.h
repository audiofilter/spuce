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
EXTERNC double get_fc(int len, bool in_passband);
EXTERNC void vertical_swipe(int len, bool in_passband, bool above_stop);
EXTERNC double update_w(double* w, double w_inc);
EXTERNC void set_fs(float fs);
EXTERNC void set_filter_type(int t);
EXTERNC double get_mag(double w);

EXTERNC int get_order();
EXTERNC double stopdB();
EXTERNC double ripple();
EXTERNC double fc();

