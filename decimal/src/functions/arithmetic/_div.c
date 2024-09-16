#include "../../_decimal.h"

int _div(_decimal v1, _decimal v2, _decimal *result) {
  int error = 0;
  if (is_zero(v2)) return 3;
  null_decimal(result);
  if (is_zero(v1)) return 0;
  error = mod(v1, v2, result);
  return error;
}

//деление двух положительных чисел, целочисленное
void division(_big_decimal val1, _big_decimal val2,
              _big_decimal *res) {
  int sign1 = get_sign_big(&val1), sign2 = get_sign_big(&val2), shift = 0;
  set_sign_big(&val1, 0);
  set_sign_big(&val2, 0);
  normalization_big(&val1, &val2);
  while (compare_big(&val2, &val1) != 1) {
    shift_left_big(&val2, 1);
    shift++;
  }
  while (shift > 0 && !is_zero_big(&val1)) {
    shift_right_big(&val2, 1);
    shift_left_big(res, 1);
    shift--;
    if (compare_big(&val2, &val1) != 1) {
      bitwise_sub(val1, val2, &val1);
      set_bit_big(res, 0, 1);
    } else
      set_bit_big(res, 224, 0);
  }
  while (shift) {
    shift_left_big(res, 1);
    shift--;
  }
  if (sign1 != sign2) set_sign_big(res, 1);
}

int mod(_decimal v1, _decimal v2, _decimal *result) {
  _big_decimal tmp = {0}, val1, val2, res = {0};
  int scale = 0, error = 0;
  dec_to_big(&v1, &val1);
  dec_to_big(&v2, &val2);

  while (!is_zero_big(&val1) && scale < 29) {
    int shift = 0;
    great_scale(&res, 1);
    null_big_dec(&tmp);
    dec_to_big(&v2, &val2);
    set_sign_big(&val1, 0);
    set_sign_big(&val2, 0);
    while (compare_big(&val2, &val1) != 1) {
      shift_left_big(&val2, 1);
      shift++;
    }
    while (shift > 0 && !is_zero_big(&val1)) {
      shift_right_big(&val2, 1);
      shift_left_big(&tmp, 1);
      shift--;
      if (compare_big(&val2, &val1) != 1) {
        bitwise_sub(val1, val2, &val1);
        set_bit_big(&tmp, 0, 1);
      } else
        set_bit_big(&tmp, 224, 0);
    }
    while (shift) {
      shift_left_big(&tmp, 1);
      shift--;
    }
    add_big(tmp, res, &res);
    scale++;
    great_scale(&val1, 1);
  }
  set_scale_big(&res, scale - 1);
  if ((get_sign(v1) != get_sign(v2)) && !is_zero_big(&res))
    set_sign_big(&res, 1);
  error = overflow(&res, result);
  return error;
}
