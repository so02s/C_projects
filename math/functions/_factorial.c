#include "../_math.h"

long double _factorial(size_t x) {
  long double res = 1;
  for (size_t i = 1; i <= x; i++) res *= i;
  return res;
}