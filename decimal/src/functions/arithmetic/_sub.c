#include "../../_decimal.h"

int _sub(_decimal v1, _decimal v2, _decimal *result) {
  int error = 0, sign1 = 0;
  null_decimal(result);
  if (!is_correct(&v1) || !is_correct(&v2))
    error = 1;
  else if (is_zero(v2))
    copy_decimal(&v1, result);
  else if (is_zero(v1)) {
    copy_decimal(&v2, result);
    set_sign(result, !get_sign(v2));
  } else if (!_compare(&v1, &v2))
    null_decimal(result);
  else if (get_sign(v1) != get_sign(v2)) {
    set_sign(&v2, !get_sign(v2));
    error = _add(v1, v2, result);
  } else {
    _big_decimal big_v1, big_v2, big_result = {0};
    dec_to_big(&v1, &big_v1);
    dec_to_big(&v2, &big_v2);
    normalization_big(&big_v1, &big_v2);
    sign1 = get_sign_big(&big_v1);
    set_sign_big(&big_v1, 0);
    set_sign_big(&big_v2, 0);
    if (compare_big(&big_v1, &big_v2) > 0) {
      bitwise_sub(big_v1, big_v2, &big_result);
      if (sign1 == 1) set_sign_big(&big_result, 1);
    } else {
      bitwise_sub(big_v2, big_v1, &big_result);
      if (sign1 == 0) set_sign_big(&big_result, 1);
    }
    set_scale_big(&big_result, get_scale_big(&big_v1));
    error = overflow(&big_result, result);
  }
  return error;
}

//вычитание двух положительных чисел одинакового порядка, v1 > v2
int bitwise_sub(_big_decimal v1, _big_decimal v2,
                _big_decimal *result) {
  int error = 0, x = 0, y = 0, borrow = 0, borrow2 = 0;
  int end = get_first_bit(v1);  //найти старший бит - функция
  for (int i = 0; i <= end; i++) {
    x = get_bit_big(v1, i);  //берем бит из первого децимала
    y = get_bit_big(v2, i);  //берем бит из второго децимала
    unsigned int result_bit = x ^ y;  // 0 если одинаковые, 1 если разные х и у
    if (borrow == 1) {
      borrow2 = (~result_bit) & 1;
      result_bit = result_bit ^ 1;
    }
    borrow = (~x) & y;  //нужно ли нам замещение
    if (borrow2 == 1) borrow = 1;
    set_bit_big(result, i, result_bit);
  }
  return error;
}

//ищет первый ненулевой бит
int get_first_bit(_big_decimal value) {
  int bit = 0, place = 0;
  for (int i = 223; i >= 0; i--) {
    bit = get_bit_big(value, i);
    if (bit == 1) {
      place = i;
      break;
    }
  }
  return place;
}