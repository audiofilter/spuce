// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)
#pragma once
#include <vector>
#include <spuce/typedefs.h>
#include <spuce/filters/fir_decim.h>
#include <spuce/filters/iir_df.h>
#include <spuce/filters/calculate_decimator_taps.h>

namespace spuce {

  template <class Numeric> class decimator {

  private:
    bool m_use_fir;
    int  m_rate;
    int  m_phase;
    spuce::fir_decim<Numeric>  m_if_fir;
    spuce::iir_df<Numeric>     m_if_iir;

  public:
    decimator() {;}
    decimator(unsigned int rate, int low_rate_multipliers, bool use_fir=true) {
      setup(rate,low_rate_multipliers, use_fir);
    }
    void setup(unsigned int rate, int low_rate_multipliers, bool use_fir=true) 
    {
      m_use_fir = use_fir;
      m_rate = rate;
      m_phase = 0;
      auto taps = calculate_decimator_taps(m_rate,low_rate_multipliers,m_use_fir);
      if (m_use_fir) {
        m_if_fir.set_rate(m_rate);
        m_if_fir.set_taps(taps);
      } else {
        m_if_iir.set_taps(taps);
      }
    }
    
    void process(const std::vector<Numeric>& samples_in,
                 std::vector<Numeric>& if_out)
    {
      if (m_use_fir) {
        m_if_fir.process(samples_in, if_out);
      } else {
        std::vector<Numeric> iir_out;
        if_out.resize((samples_in.size() - m_phase + m_rate - 1 )/ m_rate);
        m_if_iir.process(samples_in, iir_out);
        for (size_t i=0;i<if_out.size();i++) {
          if_out[i] = iir_out[m_phase+i*m_rate];
        }
        m_phase = (m_phase + samples_in.size()) % m_rate;
      }    
    }
  };
}



