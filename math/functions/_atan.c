#include "../_math.h"

long double _atan(double x) {
  long double res = 0, res_prev = 0;
  long double a = 0, b = 0, c = 0;
  int n = 1;
  if (x == -0 || x == 0)
    res = x;
  else if (_isinf(x))
    res = (x > 0) ? _PI / 2 : -_PI / 2;
  else if (_isnan(x))
    res = _NAN;
  else if (x < 1 && x > -1)
    do {
      res_prev = res;
      a = _pow(-1, n - 1);
      c = 2 * n - 1;
      b = _pow(x, c);
      res += (a * b) / c;
      n++;
    } while (_fabs(res - res_prev) > PRECISION);
  else
    res = _asin(x / (_sqrt(x * x + 1)));
  return res;
}