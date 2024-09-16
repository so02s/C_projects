#include "../../_decimal.h"

int _from_float_to_decimal(float src, _decimal *dst) {
  if (!dst) return 1;
  int error = 0;
  null_decimal(dst);
  if (isinf(src) || isnan(src) || fabsf(src) > MAX_FLOAT_TO_CONVERT ||
      fabsf(src) < MIN_FLOAT_TO_CONVERT)
    error = 1;
  else {
    _decimal result;
    char floater[64];
    sprintf(floater, "%.6E", fabsf(src));
    int expon = get_scale_from_string(floater);  //
    if (expon <= -23) {
      int float_precision = expon + 28;
      sprintf(floater, "%.*E", float_precision, fabsf(src));
    }
    _from_string_to_decimal(floater, &result);  //
    if (signbit(src)) set_sign(&result, 1);
    *dst = result;
  }
  return error;
}

int _from_decimal_to_float(_decimal src, float *dst) {
  if (dst == NULL) {
    return CONVERTATION_ERROR;
  }
  int sign = get_sign(src);
  int power = get_scale(&src);
  long double result = 0;
  for (int i = 0; i < 96; i++) {
    result += pow(2, i) * get_bit(src, i);
  }

  while (power) {
    result /= 10.0;
    power--;
  }
  if (sign) {
    result *= -1.0;
  }

  *dst = result;
  return CONVERTATION_OK;
}