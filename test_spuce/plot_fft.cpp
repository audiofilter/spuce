#include <memory>
#include "plot_fft.h"
#include "MPLPlot.h"
#include <complex>
#include "cfft.h"
using namespace spuce;
#include <iostream>

void plot_fft(std::vector<double>& data) {
  const size_t N = data.size();
  Dictionary d;
  d.add("lw", 3.1);

  std::unique_ptr<std::complex<double>[]> z(new std::complex<double>[N]);
  for (size_t i = 0; i < N; i++) z[i] = data[i];

  cfft F(N);
  F.fft(z.get());

  std::vector<double> fft(N/2);
  std::vector<double> x(N/2);

  for (size_t i = 0; i < N/2; i++) {
    double val = norm((double)N * z[i]);
    if (val < 1e-6) val = 1e-6;
    fft[i] = 10.0 * log10(val);
		x[i] = (double)i/N;
  }
  PyPlotter plt;
  plt.init();
  plt.plot(x,fft, &d);
  plt.load();
  plt.show();
}
void plot_fft(std::vector<std::complex<double>>& data) {
  const size_t N = data.size();
  Dictionary d;
  d.add("lw", 3.1);

  std::unique_ptr<std::complex<double>[]> z(new std::complex<double>[N]);
  for (size_t i = 0; i < N; i++) z[i] = data[i];

  cfft F(N);
  F.fft(z.get());

  std::vector<double> fft(N);
  std::vector<double> x(N);

  for (size_t i = 0; i < N; i++) {
    double val = norm((double)N * z[i]);
    if (val < 1e-6) val = 1e-6;
    fft[i] = 10.0 * log10(val);
		x[i] = (double)(-(signed)N/2.0 + i)/N;
  }
  PyPlotter plt;
  plt.init();
	plt.plot(x,fft, &d);
  plt.load();
  plt.show();
}

void plot_data(std::vector<double>& data) {
  Dictionary d;
  d.add("lw", 3.1);
  PyPlotter plt;
  plt.init();
  plt.plot_data(data, &d);
  plt.load_data();
  plt.show_data();
}

void compare_fft(std::vector<double>& data1, std::vector<double>& data2)
{
  const size_t N=data1.size();
	Dictionary d;
	d.add("lw", 3.1);

	std::unique_ptr<std::complex<double> []> z(new std::complex<double>[N]);
	for (size_t i = 0; i < N; i++) z[i] = data1[i];
	
  spuce::cfft F(N);
	F.fft(z.get());

	std::vector<double> fft(N/2);

	for (size_t i=0;i<N/2;i++) {
		double val = norm(N*z[i]);
		if (val < 1e-6) val = 1e-6;
		fft[i] = 10.0*log10(val);
	}

	PyPlotter plt;
	plt.init();
	plt.plot_data(fft, &d);

	for (size_t i = 0; i < N; i++) z[i] = data2[i];
	F.fft(z.get());
	
	for (size_t i=0;i<N/2;i++) {
		double val = norm(N*z[i]);
		if (val < 1e-6) val = 1e-6;
		fft[i] = 10.0*log10(val);
	}

	plt.plot_data(fft, &d);
	
	plt.load_data();
	plt.show();
}
