#include "../../_decimal.h"

int _round(_decimal value, _decimal *result) {
  float dest = 0;
  _decimal *result_sub = init_decimal(), *result_tranc = init_decimal();
  _decimal *number = init_decimal(), *result_add = init_decimal();
  number->bits[0] = 1;
  int sign = get_sign(value);
  _truncate(value, result_tranc);
  _sub(value, *result_tranc, result_sub);
  set_sign(result_sub, 0);
  _from_decimal_to_float(*result_sub, &dest);
  if (dest >= 0.5) {
    if (sign == 0) {
      _add(*result_tranc, *number, result_add);
      copy_decimal(result_add, result);
    } else {
      _sub(*result_tranc, *number, result_sub);
      copy_decimal(result_sub, result);
    }
  } else {
    copy_decimal(result_tranc, result);
  }
  free(result_sub);
  free(result_tranc);
  free(number);
  free(result_add);
  return 0;
}
