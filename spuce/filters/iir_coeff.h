#pragma once
// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include <spuce/typedefs.h>
#include <vector>
namespace spuce {
//!  \file
//!  \brief  Class for iir filter design
//!  \author Tony Kirke
//!  \ingroup classes iir
class iir_coeff {
 public:
  //! ord = Filter order
  iir_coeff(long ord = 1, bool lp = true);
  //! Destructor
  ~iir_coeff();
  //! Do bilinear transformation
  void bilinear();
  void convert_to_ab();
  void z_root_to_ab(std::vector<std::complex<float_type> >& z);
  void pz_to_ap();
  void ab_to_tf();
  std::vector<float_type> p2_to_poly(const std::vector<std::complex<float_type> >& ab);
  std::vector<float_type> pz_to_poly(const std::vector<std::complex<float_type> >& z);
  void set_zero(const std::complex<float_type>& z, long i) { zeros[i] = z; }
  void set_pole(const std::complex<float_type>& z, long i) { poles[i] = z; }
  std::complex<float_type> get_zero(long i);
  std::complex<float_type> get_pole(long i);
  float_type get_a(long i) const;
  float_type get_b(long i) const;
  float_type get_coeff_a(long i) const;
  float_type get_coeff_b(long i) const;
  float_type max_abs_coeff();
  void quantize(int bits) { ; }
  float_type freqz_mag(float_type freq);
  float_type getGain(void) const;
  int getOrder(void) const;
  int getN2(void) const;
  int getState(void) const;
  int isOdd(void) const;
  std::vector<float_type> get_a() const;
  std::vector<float_type> get_b() const;
  bool get_type(void) const { return lpf; }
  void set_type(bool t) { lpf = t; }
  void print() const;
  void print_pz() const;

 private:
  std::vector<std::complex<float_type> > poles;
  std::vector<std::complex<float_type> > zeros;
  float_type gain;
  float_type hpf_gain;
  long n2;
  long odd;
  long order;
  long state;
  long tf_state;
  long ap_state;
  std::vector<float_type> a_tf;
  std::vector<float_type> b_tf;
  bool lpf;
};
// template_instantiations: float_type, std::complex<float_type>
}  // namespace spuce
