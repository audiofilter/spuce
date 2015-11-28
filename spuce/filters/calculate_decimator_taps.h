// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)
#include <vector>
namespace spuce {
  std::vector<double> calculate_decimator_taps(unsigned int rate, int low_rate_multipliers, bool use_fir);
}


