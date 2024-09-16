#include "../_math.h"

long double _sin(double x) {
  long double cur = 0, tt = x;
  if (x == 0 || x == -0)
    cur = x;
  else if (_isinf(x) || _isnan(x))
    cur = _NAN;
  else {
    while (tt > 2 * _PI || tt < _PI * -2)
      if (tt > 2 * _PI)
        tt -= 2 * _PI;
      else
        tt += 2 * _PI;
    cur = tt;
    int n = 3;
    long double step = -_pow(tt, n) / _factorial(n);
    long double lstep = cur + 1;
    while (!(cur - lstep < 1e-10 && cur - lstep > -1e-10)) {
      lstep = cur;
      cur += step;
      n += 2;
      step = ((n - 3) / 2 % 2 == 1 ? _pow(tt, n) : -_pow(tt, n)) /
             _factorial(n);
    }
  }
  return cur;
}
