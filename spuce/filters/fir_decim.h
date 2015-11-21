#pragma once
// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include <spuce/filters/fir.h>
namespace spuce {
//! \file
//! \brief template class for fir decimation based on FIR class
//! created to support polyphase FIR decimation
//! \author Tony Kirke
//! \ingroup double_templates fir
template <class Numeric, class Coeff = float_type> class fir_decim : public fir<Numeric, Coeff> {
  using spuce::fir<Numeric, Coeff>::coeff;
  using spuce::fir<Numeric, Coeff>::z;
  using spuce::fir<Numeric, Coeff>::read_taps;
  using spuce::fir<Numeric, Coeff>::number_of_taps;
  typedef typename base_type<Numeric>::btype Numeric_base;
  typedef typename mixed_type<Numeric, Coeff>::dtype sum_type;
  int rate;
  int phase;

 public:
  //! Constructor
  fir_decim<Numeric, Coeff>(void) {}
  fir_decim<Numeric, Coeff>(long n) : fir<Numeric, Coeff>(n) {}
  fir_decim<Numeric, Coeff>(const char* file) { read_taps(file); }
  fir_decim<Numeric, Coeff>(fir_coeff<Coeff> C) : fir<Numeric, Coeff>(C) {
    int i;
    int n = C.number_of_taps();
    if (n > 0) {
      coeff.resize(n);
      z.resize(n);
      for (i = 0; i < n; i++) z[i] = (Numeric)0;
      for (i = 0; i < n; i++) coeff[i] = C.coeff[i];
    }
  }

  void skip() {
    phase++;
    phase = phase % rate;
  }
  //! Set interpolation rate
  void set_rate(long r) {
    rate = r;
  }
  void set_manual(int def_phase = 0) {
    phase = def_phase;
  }


  void input(Numeric in) {
    int i;
    // Update history of inputs
    for (i = number_of_taps() - 1; i > 0; i--) z[i] = z[i - 1];
    // Add new input
    z[0] = in;
  }
  //! Phase increments when in automatic mode
  //! Otherwise phase does not change
  Numeric decim(void) {
    sum_type sum(0);
    // Perform FIR
    Numeric output;
    int i;
    for (i = 0; i < number_of_taps(); i++) sum += coeff[i] * z[i];

    output = (sum);
    return (output);
  }
  void process(const std::vector<Numeric>& in, std::vector<Numeric>& out) {
    out.resize(in.size() - phase + rate - 1 / rate);
    int j = 0;
    for (int i = 0; i < in.size(); i++) {
      input(in[i]);
      phase = (phase + 1) % rate;
      if (phase == 0) { out[j++] = decim(); }
    }
  }
};
}  // namespace spuce
