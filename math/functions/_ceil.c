#include "../_math.h"

long double _ceil(double x) {
  long double result;
  if (x == _INF || x == _NEG_INF || x == _DBL_MAX) {
    result = x;
  } else {
    long double c = (long double)x - (int)x;
    if (c > 0)
      x = (x - c) + 1;
    else if (x < 0)
      x = (x + (-c));
    result = (long double)x;
  }
  return result;
}
