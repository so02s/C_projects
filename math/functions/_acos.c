#include "../_math.h"

long double _acos(double x) {
  long double res = 0;
  if (x == 1)
    res = 0;
  else if (x > 1 || x < -1 || _isnan(x))
    res = _NAN;
  else
    res = _PI / 2 - _asin(x);
  return res;
}
