#include <iostream>
#include <spuce/filters/remez_estimate.h>
using namespace std;
using namespace spuce;
int main(int argc, char* argv[]) {
  float_type atten = 60.0; // db
  float_type rip_db = 0.1; // db
  float_type trans_bw = 0.0625;
  std::cout << "For passband ripple = " << rip_db << " dB "
            << " and stopband attenuation = "
            << atten << " dB "
            << " and transition width = " << trans_bw << "\n";
  float_type weight = remez_estimate_weight(rip_db, atten);
  std::cout << "weight = " << weight << "\n";
  size_t num_taps = remez_estimate_num_taps(trans_bw, rip_db, atten);
  std::cout << "number of taps needed = " << num_taps << "\n";

  float_type min_trans_bw = remez_estimate_bw(num_taps, rip_db, atten);
  std::cout << "We can handle trans_bw ~= " << min_trans_bw << " ";
  float_type min_atten = remez_estimate_atten(num_taps, trans_bw, rip_db);
  std::cout << "and attenuation of  ~= " << min_atten << " dB\n";
  
  
  return(1);
}
