#include "../_math.h"

long double _exp(double x) {
  long double res = 1, last_res = 1;
  long double now_step = 1, now_x = x, now_fact = 1;

  if (x == -0 || x == 0)
    res = 1;
  else if (_isinf(x) && x < 0)
    res = 0;
  else if (_isinf(x))
    res = _INF;
  else if (_isnan(x))
    res = _NAN;
  else
    do {
      last_res = res;
      res += now_x / now_fact;
      now_step++;
      now_x *= x;
      now_fact *= now_step;
    } while ((_fabs(res - last_res) >= PRECISION) && (res >= -100));
  if (res < 0) res = 0;

  return res;
}