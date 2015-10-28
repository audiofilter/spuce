#pragma once
// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include <spuce/filters/fir_coeff.h>
namespace spuce {
//! \file
//! \brief Calculate coefficients for lowpass FIR assuming equiripple frequency response
//! \author Tony Kirke,  Copyright(c) 2001
//! \ingroup functions fir
void create_remez_lpfir(fir_coeff<float_type>& remezfir, float_type edge, float_type fx, float_type wtx);
}  // namespace spuce
