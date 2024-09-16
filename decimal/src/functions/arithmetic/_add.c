#include "../../_decimal.h"

int bitwise_add(_big_decimal value1, _big_decimal value2,
                _big_decimal *res) {
  unsigned memo = 0;
  for (int i = 0;
       i < (int)(sizeof(_big_decimal) / sizeof(unsigned) - 1) * 32; ++i) {
    unsigned res_bit = get_bit_big(value1, i) + get_bit_big(value2, i) + memo;
    memo = res_bit / 2;
    set_bit_big(res, i, res_bit % 2);
  }
  res->bits[7] = value1.bits[7];
  return 0;
}

//сложение двух положительных чисел
int add_big(_big_decimal value1, _big_decimal value2,
            _big_decimal *res) {
  if (get_sign_big(&value1) == get_sign_big(&value2)) {
    normalization_big(&value1, &value2);
    bitwise_add(value1, value2, res);
  } else
    return 1;
  return 0;
}

int _add(_decimal value_1, _decimal value_2, _decimal *result) {
  int error = 0;
  if (is_zero(value_1)) {
    copy_decimal(&value_2, result);
  } else if (is_zero(value_2)) {
    copy_decimal(&value_1, result);
  } else {
    int sign1 = get_sign(value_1), sign2 = get_sign(value_2);
    if (sign1 != sign2) {
      if (sign1 == 1) {
        set_sign(&value_1, 0);
        error = _sub(value_2, value_1, result);
      } else {
        set_sign(&value_2, 0);
        error = _sub(value_1, value_2, result);
      }
    } else {
      _big_decimal *v1 = init_big_decimal(), *v2 = init_big_decimal(),
                      *res = init_big_decimal();
      dec_to_big(&value_1, v1);
      dec_to_big(&value_2, v2);
      add_big(*v1, *v2, res);
      error = overflow(res, result);
      free(v1);
      free(v2);
      free(res);
    }
  }
  return error;
}