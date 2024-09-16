#include "../../_decimal.h"

int _floor(_decimal value, _decimal *result) {
  _decimal *result_sub = init_decimal(), *result_tranc = init_decimal();
  _decimal *number = init_decimal();
  number->bits[0] = 1;
  int sign = get_sign(value);
  _truncate(value, result_tranc);
  if (sign == 0) {
    copy_decimal(result_tranc, result);
  } else {
    _sub(*result_tranc, *number, result_sub);
    copy_decimal(result_sub, result);
  }
  free(result_sub);
  free(result_tranc);
  free(number);
  return 0;
}
