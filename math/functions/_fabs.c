#include "../_math.h"

long double _fabs(double x) {
  if (x < 0)
    x = -x;
  else if (x >= 0)
    x = x;
  return (long double)x;
}
