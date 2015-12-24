// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)
#define _USE_MATH_DEFINES
#include <spuce/filters/calculate_decimator_taps.h>
#include <cassert>
#include <cmath>
#include <complex>
#include <spuce/filters/design_fir.h>
#include <spuce/filters/design_iir.h>
#include <spuce/filters/remez_estimate.h>
#include <spuce/filters/iir_coeff.h>

// A work in progress, get taps for either a polyphase FIR or an IIR that decimates
namespace spuce {
  std::vector<double> calculate_decimator_taps(unsigned int rate, int low_rate_multipliers, bool use_fir) 
  {
    const size_t IIR_Order = low_rate_multipliers/2;
    const double ripple = 0.1;
    const size_t Order=(2*low_rate_multipliers*rate)+1;
    
    const double fc = 0.5/rate;
    const double pass_edge = 0.8*fc;

    if (use_fir) {
      const double remez_stop_atten = 60.0;
      const double remez_trans  = 2*(fc - pass_edge);
      const double remez_weight = remez_estimate_weight(ripple, remez_stop_atten);
      auto taps = design_fir("remez","LOW_PASS", (int)Order, pass_edge, 0, remez_trans, remez_weight);
      return taps;
    } else {
      iir_coeff* filt = design_iir("chebyshev", "LOW_PASS", (int)IIR_Order, pass_edge, ripple);
      // get the tap from iir_coeff for iir_filter, incorporating the gain to feedforward taps
      std::vector<double> b = filt->get_b();
      std::vector<double> a = filt->get_a();
      // Group together feed forward and feed back taps into 1 vector for transferring to IIR filter
      for (size_t i=0;i<a.size();i++) b.push_back(a[i]);
      return b;
    }
  }
}


