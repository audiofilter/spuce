#include <spuce/filters/iir_df.h>
using std::complex;
// Test instantiation of various combinations of template parameters 

namespace spuce {
	template class iir_df<complex<float_type> ,float_type >;
	template class iir_df<complex<int64_t> ,float_type >;
	template class iir_df<complex<int32_t> ,float_type >;
	template class iir_df<int32_t,float_type >;

	template class iir_df<complex<int16_t> ,float_type >;
	template class iir_df<int16_t ,float_type >;

	template class iir_df<complex<int8_t> ,float_type >;
	template class iir_df<int8_t ,float_type >;
	
} // namespace SPUC
