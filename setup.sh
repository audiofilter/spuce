#!/bin/bash
rm -rf build
mkdir build && cd build && cmake .. -DPYTHON_LIBRARY=${HOME}/anaconda/lib/libpython2.7.dylib && make -j
# Use anaconda for python setup, modify as desired
export PYTHONHOME=${HOME}/anaconda 
export PYTHONPATH=${HOME}/lib/python2.7/site-packages
