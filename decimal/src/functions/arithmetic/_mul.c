#include "../../_decimal.h"

int big_to_dec_overflow(int scale, _big_decimal* big_result,
                        _decimal* result);

int decimal_mult_positive(_decimal value_1, _decimal value_2,
                          _decimal* result) {
  _big_decimal big_value_1 = {0}, big_value_2 = {0}, big_result = {0},
                  big_tmp = {0};
  int code = ARITHMETIC_OK;
  dec_to_big(&value_1, &big_value_1);
  dec_to_big(&value_2, &big_value_2);
  int res_scale = get_scale_big(&big_value_1) + get_scale_big(&big_value_2);
  for (int bit = 0; bit < 32 * 3; bit++)
    if (get_bit_big(big_value_2, bit)) {
      copy_big_decimal(&big_value_1, &big_tmp);
      shift_left_big(&big_tmp, bit);
      add_big(big_tmp, big_result, &big_result);
    }
  if (!code) code = big_to_dec_overflow(res_scale, &big_result, result);
  return code;
}

int big_to_dec_overflow(int scale, _big_decimal* big_result,
                        _decimal* result) {
  int code = 0;
  if (scale <= 28) {  // 1 случай
    set_scale(result, scale);
    code = overflow(big_result, result);
  } else {
    scale -= 28;
    set_scale(result, 28);
    code = overflow(big_result, result);
    if (code == 0 && get_scale(result) == 0) {  // 2 случай
      set_scale(result, scale);
    } else if (code == 0) {
      // 3 случай делить децимал, пока степень не поместится
      if (scale + get_scale(result) > 28) {
        int new_scale = scale + get_scale(result);
        _big_decimal tmp = {{10, 0, 0, 0}}, tmp2 = {0}, big_result_tmp = {0};
        dec_to_big(result, &big_result_tmp);
        set_scale_big(&big_result_tmp, 0);
        while (new_scale > 28) {
          division(big_result_tmp, tmp, &tmp2);
          new_scale--;
          copy_big_decimal(&tmp2, &big_result_tmp);
          null_big_dec(&tmp2);
        }
        big_to_dec(&big_result_tmp, result);
        set_scale(result, new_scale);
      } else {  // 4 случай
        set_scale(result, scale + get_scale(result));
      }
    } else {
      set_scale_big(big_result, scale);
      code = overflow(big_result, result);
    }
  }
  return code;
}

int _mul(_decimal value_1, _decimal value_2, _decimal* result) {
  int code = ARITHMETIC_OK;
  if (!result) {
    code = ARITHMETIC_ERROR_DIV_ZERO;
  } else if (!is_correct(&value_1) || !is_correct(&value_2)) {
    code = ARITHMETIC_ERROR_DIV_ZERO;
  } else {
    int res_sign = (get_sign(value_1) + get_sign(value_2)) % 2;
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    code = decimal_mult_positive(value_1, value_2, result);
    if (code == ARITHMETIC_ERROR_INF && res_sign == 1)
      code = ARITHMETIC_ERROR_NEGINF;
    set_sign(result, res_sign);
  }
  return code;
}
