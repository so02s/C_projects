#include "../../_decimal.h"

// -1 less 0 equal 1 greater
int _compare(_decimal *first, _decimal *second) {
  _big_decimal *pi = init_big_decimal(), *vo = init_big_decimal();
  dec_to_big(first, pi);
  dec_to_big(second, vo);
  normalization_big(pi, vo);
  int sign_1 = 0, sign_2 = 0, result = 0;
  sign_1 = get_sign_big(pi);
  sign_2 = get_sign_big(vo);
  if (sign_1 == 1 && sign_2 == 0) {
    result = -1;
  } else if (sign_1 == 0 && sign_2 == 1) {
    result = 1;
  } else {
    int i = 224;
    unsigned t1 = get_bit_big(*pi, i);
    unsigned t2 = get_bit_big(*vo, i);
    while ((t1 == t2) && (i >= 0)) {
      i--;
      t1 = get_bit_big(*pi, i);
      t2 = get_bit_big(*vo, i);
    }
    if (i == -1) {
      result = 0;
    } else if (sign_1 == 0 && sign_2 == 0) {
      if (t1 > t2)
        result = 1;
      else if (t1 < t2)
        result = -1;
    } else if (sign_1 == 1 && sign_2 == 1) {
      if (t1 > t2)
        result = -1;
      else if (t1 < t2)
        result = 1;
    }
  }
  free(pi);
  free(vo);
  return result;
}
