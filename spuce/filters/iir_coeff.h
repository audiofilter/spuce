#pragma once
// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)
#include <spuce/typedefs.h>
#include <vector>
namespace spuce {
//!  \file
//!  \brief  Class for iir filter design
//!  \author Tony Kirke
//!  \ingroup classes iir

// Only low and high are implemented so far	
enum class filter_type {low,high,bandpass,bandstop};
	
class iir_coeff {
 public:
  //! ord = Filter order
  iir_coeff(size_t ord = 1, filter_type lp = filter_type::low);
	void resize(size_t ord);
  //! Destructor
  ~iir_coeff();
  //! Do bilinear transformation
  void bilinear();
  void make_band(float_type center);
  void convert_to_ab();
  void z_root_to_ab(std::vector<std::complex<float_type> >& z);
  void pz_to_ap();
  void ab_to_tf();
  std::vector<float_type> p2_to_poly(const std::vector<std::complex<float_type> >& ab);
  std::vector<float_type> pz_to_poly(const std::vector<std::complex<float_type> >& z);
  void set_zero(const std::complex<float_type>& z, size_t i) { zeros[i] = z; }
  void set_pole(const std::complex<float_type>& z, size_t i) { poles[i] = z; }
  std::complex<float_type> get_zero(size_t i);
  std::complex<float_type> get_pole(size_t i);
  float_type get_a(size_t i) const;
  float_type get_b(size_t i) const;
  float_type get_coeff_a(size_t i) const;
  float_type get_coeff_b(size_t i) const;
  float_type max_abs_coeff();
  void apply_gain(float_type g);
  float_type freqz_mag(float_type freq);
  float_type getGain(void) const;
  size_t getOrder(void) const;
  size_t getN2(void) const;
  bool calculate_biquad_coefficents();
  size_t isOdd(void) const;
  std::vector<float_type> get_a() const;
  std::vector<float_type> get_b() const;
  filter_type get_type(void) const { return lpf; }
  void set_type(filter_type t) { lpf = t; }
  void set_center(float_type c) { center_freq = c; c0 = cos(2*M_PI*c); }
  void set_bandpass_gain();
  float_type get_center() { return center_freq;}
  void print() const;
  void print_pz() const;

 private:
	enum class filter_state {start,z_domain,z_domain_ab,z_domain_allpass};
  std::vector<std::complex<float_type> > poles;
  std::vector<std::complex<float_type> > zeros;
  float_type gain;
  float_type c0;
  float_type center_freq;
  float_type hpf_gain;
  size_t n2;
  size_t odd;
  size_t order;
  filter_state state;
  //long tf_state;
  //long ap_state;
  std::vector<float_type> a_tf;
  std::vector<float_type> b_tf;
  filter_type lpf;
};
// template_instantiations: float_type, std::complex<float_type>
}  // namespace spuce
