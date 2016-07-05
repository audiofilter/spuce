#pragma once
// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include <spuce/dsp_classes/delay.h>
#include <spuce/filters/cic.h>
namespace spuce {
//! \file
//! \brief Implementation for sharped cascaded integrator comb filter
//! Registers are signed long and default number of stages is 2.
//! \author Tony Kirke
//! \ingroup templates fir
template <class Numeric> class scic {
 protected:
  long max_rate;
  size_t stages;
  cic<Numeric> main;
  cic<Numeric> sub;
  delay<Numeric> dly;

 public:
  // Constructor
  scic(size_t n = 2, long r = 4) : max_rate(r), stages(3 * n),
                                   main(3 * n), sub(2 * n) {
    dly.set_size(max_rate);
  }
  // To change the number of stages dynamically
  void num_stages(size_t n, long r) {
    stages = 3 * n;
    max_rate = r;
    main.num_stages(3 * n);
    sub.num_stages(2 * n);
    dly.set_size(max_rate);
  }
  // For SCIC decimation
  Numeric decimate(Numeric in, long rate, bool dump) {
    Numeric result;
    dly.input(in);
    result = (Numeric)2 * main.decimate(in, dump) - (Numeric)3 * sub.decimate(dly.check(rate - 2), dump);
    return (result);
  }
};
}  // namespace spuce
