# spuce - SPUC enhanced
A rewrite of spuc with more testing, better code design and c++11 features.

* Uses std::complex instead of custom complex class
* Will focus of floating point instead of fixed-point modules

Most of spuc was written many years ago before C++ compilers had good template support and was primarily written for fixed-point hardware design and simulation.

The rewrite will occur gradually, adding code and features as they are developed.
There will be less concern for fixed-point code initially.

Currently there is some code for IIR Filter Design & Implementation

For testing, python + matplotlib is used.
QT5 needed for test application

[![Build Status](https://travis-ci.org/audiofilter/spuce.png)](https://travis-ci.org/audiofilter/spuce)
