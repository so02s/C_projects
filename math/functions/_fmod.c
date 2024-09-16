#include "../_math.h"

long double _fmod(double x, double y) {
  long double res = 0;
  if (y == 0 || y == -0)
    res = _NAN;
  else if (x == 0 || x == -0)
    res = x;
  else if (x == _INF || x == _NEG_INF)
    res = _NAN;
  else if (x == _NAN || y == _NAN)
    res = _NAN;
  else if (y == _INF || y == _NEG_INF)
    res = x;
  else
    res = x - ((int)(x / y) * y);
  return res;
}