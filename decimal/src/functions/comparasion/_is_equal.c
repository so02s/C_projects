#include "../../_decimal.h"

int _is_equal(_decimal decimal_1, _decimal decimal_2) {
  int result = 0;
  result = (_compare(&decimal_1, &decimal_2) == 0) ? 1 : 0;
  return result;
}