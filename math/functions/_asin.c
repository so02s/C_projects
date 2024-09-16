#include "../_math.h"

long double _asin(double x) {
  long double res = 0, res_prev = 2;
  long double a = 0, b = 0, c = 0, d = 0, e = 0;
  int n = 0;
  if (x == 0 || x == -0)
    res = x;
  else if (x > 1 || x < -1 || _isnan(x))
    res = _NAN;
  else if (x == 1 || x == -1)
    res = x * (_PI / 2);
  else if (x < 0.8 && x > -0.8)
    do {
      res_prev = res;
      a = _factorial(2 * n);
      b = _pow(2, 2 * n);
      c = _pow(_factorial(n), 2);
      e = 2 * n + 1;
      d = _pow(x, e);
      res += (a * d) / (b * c * e);
      n++;
    } while (_fabs(res - res_prev) > PRECISION);
  else {
    res = _acos(_sqrt(1 - x * x));
    res = (x < 0) ? -res : res;
  }
  return res;
}
