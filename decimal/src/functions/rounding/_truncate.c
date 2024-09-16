#include "../../_decimal.h"

int _truncate(_decimal value, _decimal *result) {
  int error = 0;
  if (!is_correct(&value))
    error = 1;
  else if (!get_scale(&value)) {
    copy_decimal(&value, result);
    if (is_zero(*result)) set_sign(result, 0);
  } else {
    null_decimal(result);
    int sign = get_sign(value);
    _big_decimal b_val, b_tmp = {{10, 0, 0, 0}}, b_res = {0};
    dec_to_big(&value, &b_val);
    set_scale_big(&b_val, 0);
    for (int scale = get_scale(&value); scale != 0; scale--) {
      division(b_val, b_tmp, &b_res);
      copy_big_decimal(&b_res, &b_val);
      null_big_dec(&b_res);
    }
    big_to_dec(&b_val, result);
    if (sign && !is_zero(*result)) set_sign(result, sign);
    if (is_zero(*result) == 1) set_sign(result, 0);
  }
  return error;
}
