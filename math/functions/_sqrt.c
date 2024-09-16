#include "../_math.h"

long double _sqrt(double x) {
  long double res = 0;
  if (x < -0)
    res = _NAN;
  else if (x == -0 || x == 0 || _isinf(x))
    res = x;
  else if (_isnan(x))
    res = _NAN;
  else
    res = _pow(2, 0.5 * _log2(x));
  return res;
}
