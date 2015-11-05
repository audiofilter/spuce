#include <iostream>
#include <spuce/filters/design_window.h>
using namespace std;
using namespace spuce;
int main(int argv, char* argc[]) {
    int order = 8;

    // hanning,hann,hamming,blackman,bartlett,kaiser,
    std::string win_type = "chebyshev";
    float_type beta = 60.0;
    
    std::vector<float_type> taps = design_window(win_type, order, beta);
    std::cout << "Taps[] = {";
    for (size_t i=0;i<taps.size();i++) std::cout << taps[i] << " ";
    std::cout << "}\n";
    taps = design_window(win_type, order+1, beta);
    std::cout << "Taps[] = {";
    for (size_t i=0;i<taps.size();i++) std::cout << taps[i] << " ";
    std::cout << "}\n";

  return(1);
}
