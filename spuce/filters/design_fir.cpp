// Copyright (c) 2015 Tony Kirke
// SPDX-License-Identifier: BSL-1.0
#define _USE_MATH_DEFINES
#include <spuce/filters/design_fir.h>
#include <spuce/filters/butterworth_fir.h>
#include <spuce/filters/sinc_fir.h>
#include <spuce/filters/gaussian_fir.h>
#include <spuce/filters/remez_fir.h>
#include <spuce/filters/raised_cosine.h>
#include <spuce/filters/root_raised_cosine.h>
#include <spuce/filters/transform_fir.h>
#include <spuce/filters/sinc_helper.h>
namespace spuce {
//! \file
//! \brief Design functions for fir filters
//! \author Tony Kirke
//! \ingroup functions fir
std::vector<double> design_fir(const std::string& fir_type,
                               const std::string& band_type,                               
															 int order, float_type fl, float_type fu,
                               float_type alpha_beta_stop_edge,
                               float_type weight) {

  std::vector<float_type> taps;
  fir_coeff<float_type> filt;
  filt.set_size(order);

  float_type filt_bw;
  float_type center_frequency = 0;
  
  if (band_type == "BAND_PASS" or
      band_type == "BAND_STOP" or
      band_type == "COMPLEX_BAND_PASS" or
      band_type == "COMPLEX_BAND_STOP") {
    center_frequency = 0.5*(fu+fl);
    // Since bandpass/stop, 1/2 the band-pass filter bandwidth since double sided
    // Also bandwidth is absolute value
    filt_bw = std::abs(0.5*(fu-fl));
  } else if (band_type == "HIGH_PASS") {
    filt_bw = 0.5 - fl;
  } else {
    filt_bw = fl;
  }
  
  if (fir_type == "butterworth") {
    filt_bw = std::max(filt_bw,0.02);
    butterworth_fir(filt, filt_bw);
    taps = get_taps(filt);
  } else if (fir_type == "gaussian") {
    gaussian_fir(filt,filt_bw);
    taps = get_taps(filt);
  } else if (fir_type == "remez") {
    std::vector<float_type> bands(4);
    std::vector<float_type> des(4);
    std::vector<float_type> w(4);
    taps.resize(order);
    remez_fir Remz;
    float_type stop_freq = alpha_beta_stop_edge;
    w[0] = 1.0;
    if (band_type == "BAND_STOP") {
      w[1] = 1.0/weight;
    } else {
      w[1] = weight;
    }
    bands[0] = 0;
    bands[1] = filt_bw / 2.0;
    bands[2] = stop_freq / 2.0;
    bands[3] = 0.5;
    des[0] = 1.0;
    des[1] = 0.0;
    Remz.remez(taps, order, 2, bands, des, w, remez_type::BANDPASS);
  } else if (fir_type == "raisedcosine") {
    raised_cosine(filt, alpha_beta_stop_edge, 1.0/filt_bw);
    taps = get_taps(filt);
  } else if (fir_type == "rootraisedcosine") {
    root_raised_cosine(filt, alpha_beta_stop_edge, 1.0/filt_bw);
    taps = get_taps(filt);
  } else if (fir_type == "sinc") {
    sinc_fir(filt,filt_bw);
    taps = get_taps(filt);
  } else {
    std::cout << "Unknown window type\n";
  }

  // Transform Taps!!
  if (band_type == "HIGH_PASS") taps = transform_fir("HIGH_PASS", taps, center_frequency); 
  else if (band_type == "BAND_PASS") taps = transform_fir("BAND_PASS", taps, center_frequency);
  else if (band_type == "BAND_STOP") {
    // Handle Sinc as a high-pass filter that is later transformed up in frequency
    if (fir_type == "sinc") {
      filt_bw = 0.5 - fl;
      sinc_fir(filt,filt_bw);
      taps = get_taps(filt);
      taps = transform_fir("HIGH_PASS", taps, center_frequency);
      // OR ?
      //taps = sincBSF(order, fl, fu);
    } else {
      taps = transform_fir("BAND_STOP", taps, center_frequency);
    }
  }
 
  return taps;
}
}  // namespace spuce
