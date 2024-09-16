#include "../_math.h"

long double _log_checker(double x);

long double _log(double z) {
  long double res = _log_checker(z);
  if (res != -1) return res;
  long double x = (z - 1) / (z + 1);
  long double last_res, now_step = 3, now_x = x * x * x;
  res = x;
  do {
    last_res = 2 * res;
    res += now_x / now_step;
    now_x *= x * x;
    now_step += 2;
  } while (_fabs(2 * res - last_res) >= PRECISION);
  return 2 * res;
}

long double _log_checker(double x) {
  long double res = -1;
  if (_isnan(x) || x < 0) {
    res = _NAN;
  } else if (_isinf(x)) {
    res = _INF;
  } else if (x == 0.0 || x == -0.0) {
    res = _NEG_INF;
  } else if (x == 1) {
    res = 0;
  }
  return res;
}