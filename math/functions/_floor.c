#include "../_math.h"

long double _floor(double x) {
  long double result = x;
  if (result != result) {
  } else if (result == _INF || result == _NEG_INF ||
             result == _DBL_MAX) {
  } else {
    long double c = result - (long long int)result;
    if (result > 0 && c > 0)
      result = (result - c);
    else if (result < 0 && c != 0)
      result = (result - c) - 1;
  }
  return result;
}
