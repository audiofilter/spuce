#pragma once
#include <vector>
#include <complex>
void plot_fft(std::vector<double>& data);
void plot_fft(std::vector<std::complex<double>>& data);
void plot_data(std::vector<double>& data);
void compare_fft(std::vector<double>& data1, std::vector<double>& data2);
