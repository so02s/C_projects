#include "../_math.h"

int _abs(int x) {
  if (x < 0)
    x = -x;
  else if (x >= 0)
    x = x;
  return x;
}
