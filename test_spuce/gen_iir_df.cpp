#include <spuce/filters/iir_df.h>
using std::complex;
// Test instantiation of various combinations of template parameters 

namespace spuce {
	template class iir_df<complex<double> ,double >;
	template class iir_df<complex<float> ,float >;
	template class iir_df<complex<int64_t> ,double >;
	template class iir_df<complex<int32_t> ,double >;
	template class iir_df<complex<int64_t> ,float >;
	template class iir_df<complex<int32_t> ,float >;
	template class iir_df<int64_t,double >;
	template class iir_df<int32_t,double >;
	template class iir_df<int32_t,float >;
	template class iir_df<double,double >;
	template class iir_df<float,double >;

	template class iir_df<complex<int16_t> ,double >;
	template class iir_df<complex<int16_t> ,float >;
	template class iir_df<int16_t ,double >;
	template class iir_df<int16_t ,float >;

	template class iir_df<complex<int8_t> ,double >;
	template class iir_df<complex<int8_t> ,float >;
	template class iir_df<int8_t ,double >;
	template class iir_df<int8_t ,float >;
	
} // namespace SPUC
