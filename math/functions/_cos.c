#include "../_math.h"

long double _cos(double x) {
  long double cur = 1;
  if (x == 0 || x == -0)
    cur = 1;
  else if (_isinf(x) || _isnan(x))
    cur = _NAN;
  else {
    cur = x;
    while (cur > 2 * _PI || cur < _PI * -2)
      if (cur > 2 * _PI)
        cur -= 2 * _PI;
      else
        cur += 2 * _PI;
    cur = ((cur > _PI / 2 && cur < 3 * _PI / 2) ||
           (cur < -_PI / 2 && cur > -3 * _PI / 2))
              ? -_sqrt(1 - _pow(_sin(x), 2))
              : _sqrt(1 - _pow(_sin(x), 2));  // <==== s21
  }
  return cur;
}
