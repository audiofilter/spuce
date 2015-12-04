# spuce - A DSP Digital filtering library in C++

- Travis: [![Build Status](https://travis-ci.org/audiofilter/spuce.png)](https://travis-ci.org/audiofilter/spuce)
- AppVeyor: [![Build status](https://ci.appveyor.com/api/projects/status/vmjw8ie1ag7wdfne?svg=true)](https://ci.appveyor.com/project/audiofilter/spuce)

A rewrite of the digital filter components of SPUC with more testing, better code design and c++11 features.

* Uses std::complex instead of custom complex class
* Will focus of floating point instead of fixed-point modules
* Includes Chebyshev2 filter
* Bug fixes for odd order IIR filters
* Adding support for Bandpass and Bandstop designs for both IIR and FIR filters

Most of spuc was written many years ago before C++ compilers had good template support and was primarily written for fixed-point hardware design and simulation.

Currently there is some code for IIR Filter Design & Implementation

* Butterworth
* Chebyshev
* Inverse Chebyshev
* Elliptic
* Maximally flat FIR
* Remez Equiripple
* Raised Cosine FIR/Root Raised Cosine FIR
* Gaussian FIR
* Sinc FIR
* Cascaded Integrate Comb filters (or CIC filters)
* Notch filter
* Cut/Boost Filter
* Halfband/Subband IIR filters consisting of allpass sections
* Irrational resampling with Farrow & Lagrange based filters

**To install via Homebrew**
* brew tap audiofilter/spuce
* brew install spuce  (or brew install -HEAD spuce for latest sources)

**To install for Linux**

The deb package is provided by the MyriadRF SDR Drivers PPA.
The PPAs support the following Ubuntu releases:

* Trusty (14.04 LTS)
* Vivid (15.04)
* Wily (15.10)

Do the following to install on your Ubuntu system

* sudo add-apt-repository -y ppa:myriadrf/drivers
* sudo apt-get update
* sudo apt-get install libspuce-dev

For testing, python + matplotlib is used.


* Most of the test involve using python's matplotlib to show a frequency response of the filter, sometimes impulse responses are used

**There are 4 QT apps for illustration purposes fir_plot, iir_plot, window_plot and other_plot**

QT5 needed for test application

#Please see wiki pages for a Quick Guide to Digital Filters in Spuce

# QT Apps

![Demo App](App.png "IIR Designer")
![Demo App](Fir.png "FIR Designer")
![Demo App](Window.png "Window Designer")
![Demo App](Other.png "Other Filter Designer")
