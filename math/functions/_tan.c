#include "../_math.h"

long double _tan(double x) {
  long double res = 0;
  if (x == 0 || x == -0)
    res = x;
  else if (_isinf(x) || _isnan(x))
    res = _NAN;
  else
    res = _sin(x) / _cos(x);
  return res;
}
