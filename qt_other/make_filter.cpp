// Copyright (c) 2015 Tony Kirke. License MIT  (http://www.opensource.org/licenses/mit-license.php)
#include "make_filter.h"
#include <cmath>
namespace spuce {

void make_filter::change_filter(fil_enum f) {  shape = f;}
void make_filter::init(int points) { pts = points; }
make_filter::~make_filter() {}
make_filter::make_filter() {  reset();}

void make_filter::reset() {
  shape = None;
}

double make_filter::limit(double x, double mx, double mn) {
  if (x > mx)
    x = mx;
  else if (x < mn)
    x = mn;
  return x;
}

void make_filter::vertical_swipe(int len) {
  // Convert swipe to dB inc/decrease
  double gain = pow(2, 0.002 * len);

  switch (shape) {
	case None:
      break;
  }
}
void make_filter::horiz_swipe(int len) {
  int inc = (len < 0) ? 1 : -1;

  switch (shape) {
  case None:	break;
  default:		break;
  }
}
double make_filter::update(double *w) {
  switch (shape) {
  case None:			for (int i = 0; i < pts; i++) w[i] = 1.0;			break;
  }
  return (0);
}



}  // namespace spuce
