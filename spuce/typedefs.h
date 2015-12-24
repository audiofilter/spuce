#pragma once
// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)
#define _USE_MATH_DEFINES
#include <math.h>
// Putting std::complex here allows possible replacement with custom complex type later
#include <complex>
#include "complex_operators.h"

namespace spuce {
	// if defined USE_FLOAT, default to float type
#ifndef USE_FLOAT
	typedef double float_type;
#else
	typedef float float_type;
#endif

}  // namespace spuce

// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
//! \author = Tony Kirke
//
/*! \mainpage
 <H1>SPUCE</H1>
 <P>This Class Library</P>
 <ul> <li> 1) basic building blocks such as complex data types, Fixed-bit width integer classes, pure-delay
 blocks, etc.
 <li> 2) Basic DSP building blocks such as FIR, IIR, Allpass, farrow and lagrange interpolation filters
 <li> 3) Ability to design several types of FIR and IIR filters
 </ul>
 <P>The classes are designed so that they can be used in a simple straight forward manner. For example, a FIR
 would be initialized with its tap weights and then simply a member function would be called every time a sample is input or an output is required.</p>

*/
//! \namespace spuce - SPUCE using C++ - A DSP library
//! \author Tony Kirke,  Copyright(c) 2015
//! \defgroup base Base classes and functions
//! \defgroup traits Traits classes and functions
//! \defgroup base Base classes and functions
//! \defgroup Allpass Allpass filters
//! \defgroup fir FIR filters
//! \defgroup iir IIR filters
//! \defgroup interpolation Interpolation filters
//! \defgroup misc Miscellaneous DSP
//! \defgroup equalizers Equalization classes And functions
//! \defgroup windfunc Windows
//! \defgroup classes spuce non-template classes
//! \defgroup complex_templates spuce complex templates
//! \defgroup double_templates spuce double templates
//! \defgroup double_utemplates spuce double templates restricted
//! \defgroup functions spuce functions
//! \defgroup misc spuce misc stuff
//! \defgroup n_templates spuce templates with numeric parameters
//! \defgroup real_double_templates spuce double templates with real parameters
//! \defgroup real_templates spuce templates with real parameters
//! \defgroup templates spuce templates
//! \defgroup template_functions spuce templates functions
//! \defgroup types spuce basic types
