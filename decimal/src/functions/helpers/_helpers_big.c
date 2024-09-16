#include "../../_decimal.h"

void dec_to_big(_decimal *dst, _big_decimal *big_dst) {
  null_big_dec(big_dst);
  if (dst) {
    big_dst->bits[0] = dst->bits[0];
    big_dst->bits[1] = dst->bits[1];
    big_dst->bits[2] = dst->bits[2];
    big_dst->bits[7] = dst->bits[3];
  }
}

_big_decimal *init_big_decimal() {
  _big_decimal *big_dst = malloc(sizeof(_big_decimal));
  for (int i = 0; i < 8; i++) big_dst->bits[i] = 0;
  return big_dst;
}

//возвращает 1 при ошибке
int big_to_dec(_big_decimal *big_dst, _decimal *dst) {
  if (!good_big(*big_dst)) return 1;
  if (!dst) dst = init_decimal();
  if (big_dst) {
    dst->bits[0] = big_dst->bits[0];
    dst->bits[1] = big_dst->bits[1];
    dst->bits[2] = big_dst->bits[2];
    dst->bits[3] = big_dst->bits[7];
  }
  return 0;
}

void null_big_dec(_big_decimal *value) {
  for (int i = 0; i < 8; ++i) value->bits[i] = 0;
}

unsigned get_sign_big(_big_decimal *value) {
  return (value->bits[7] & (1u << 31)) >> 31;
}

//ошибки
void set_sign_big(_big_decimal *value, unsigned sign_value) {
  if (sign_value == 0) {
    value->bits[7] &= ~((1u << 31));
  } else if (sign_value == 1) {
    value->bits[7] |= ((1u << 31));
  }
}

int get_scale_big(_big_decimal *dec) {
  return (~(1 << 31) & (dec->bits[7])) >> 16;
}

//ошибки
int set_scale_big(_big_decimal *dec, int scale_value) {
  if (scale_value > 28 || scale_value < 0) return 1;
  int mask = 1 << 31;
  dec->bits[7] &= mask;
  mask = scale_value << 16;
  dec->bits[7] |= mask;
  return 0;
}

// int shift_left_big(_big_decimal *value, int shift_value) {
//   unsigned memory = 0;
//   int error = 0;
//   if (shift_value <= 0 || shift_value > 96)
//     error = 1;
//   else {
//     for (int i = 0; i < 7; i++) {
//       unsigned temp = value->bits[i];
//       value->bits[i] = value->bits[i] << (shift_value % 32) | memory;
//       memory = temp >> (32 - (shift_value % 32));
//       if (i == 6 && shift_value >= 32) {
//         shift_value -= 32;
//         i = -1;
//       }
//     }
//   }
//   return error;
// }

int shift_left_big(_big_decimal *value, int shift_value) {
  if (shift_value <= 0 || shift_value > 96) {
    return 1;
  }
  for (int i = 32 * 7 - shift_value; i >= 0; i--) {
    set_bit_big(value, i + shift_value, get_bit_big(*value, i));
    set_bit_big(value, i, 0);
  }

  return 0;
}

int shift_right_big(_big_decimal *value, int shift_value) {
  unsigned memory = 0;
  int error = 0;
  if (shift_value < 0 || shift_value > 32)
    error = 1;
  else {
    for (int i = 6; i >= 0; i--) {
      unsigned temp = value->bits[i];
      value->bits[i] >>= shift_value;
      value->bits[i] |= memory;
      memory = temp << (32 - shift_value);
    }
  }
  return error;
}

unsigned get_bit_big(_big_decimal value, int place) {
  if (place < 0 || place > 224) return 0;
  return ((value.bits[place / 32]) >> (place % 32)) %
         2;  //возвращает либо 1, либо 0
}

void set_bit_big(_big_decimal *value, int position, unsigned bit_val) {
  value->bits[position / 32] &= ~(1U << (position % 32));
  value->bits[position / 32] |= bit_val << (position % 32);
}

// void print_dec_big(_big_decimal val) {
//   get_sign_big(&val) ? printf("-") : printf("+");
//   for (int i = 0; i <= 6; ++i) {
//     printf(" %08x", val.bits[i]);
//   }
//   printf(" scale %d\n", get_scale_big(&val));
//   // тут запринтить инт или флоат (после перевода)
// }

// void print_dec_big_bit(_big_decimal dec) {
//   for (int i = 7; i >= 0; --i) {
//     print_bit(dec.bits[i]);
//   }
//   printf("\n");
// }

void great_scale(_big_decimal *val1, int scale2) {
  _big_decimal *temp1 = init_big_decimal(), *temp2 = init_big_decimal();
  for (int i = scale2; i > 0; --i) {
    copy_big_decimal(val1, temp1);
    copy_big_decimal(val1, temp2);
    shift_left_big(temp1, 3);  //домножили на 8
    shift_left_big(temp2, 1);  //домножили на 2
    bitwise_add(*temp1, *temp2, val1);
  }
  free(temp1);
  free(temp2);
}

// на вход только положительные
void normalization_big(_big_decimal *val1, _big_decimal *val2) {
  int scale1 = get_scale_big(val1), scale2 = get_scale_big(val2);
  if (scale1 < scale2) {
    great_scale(val1, scale2 - scale1);
    set_scale_big(val1, scale2);
  } else if (scale1 > scale2) {
    great_scale(val2, scale1 - scale2);
    set_scale_big(val2, scale1);
  }
}

void copy_big_decimal(_big_decimal *sourse, _big_decimal *copy) {
  for (int i = 0; i <= 7; ++i) copy->bits[i] = sourse->bits[i];
}

// -1 less 0 equal 1 greater
int compare_big(_big_decimal *pi, _big_decimal *vo) {
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
  return result;
}

// 1 - yes, 0 - no
int good_big(_big_decimal a) {
  return (a.bits[3] > 0 || a.bits[4] > 0 || a.bits[5] > 0 || a.bits[6] > 0) ? 0
                                                                            : 1;
}

// 1 - yes, 0 - no
int is_zero_big(_big_decimal *a) {
  int k = 1;
  for (int i = 0; i < 7; i++)
    if (a->bits[i] > 0) k = 0;
  return k;
}

// 79540474848027320844250992.98523699556
// 79540474848027320844250992.98
//                          0.00523699556

int overflow(_big_decimal *big_dec, _decimal *dec) {
  int error = 0, sign = get_sign_big(big_dec);
  if (big_dec->bits[3] == 0 && big_dec->bits[4] == 0 && big_dec->bits[5] == 0 &&
      big_dec->bits[6] == 0)
    big_to_dec(big_dec, dec);
  else {
    _big_decimal temp = {0}, trunc = {0}, big_result = {0},
                    ten = {{10, 0, 0, 0}};
    int scale = get_scale_big(big_dec);
    copy_big_decimal(big_dec, &temp);
    copy_big_decimal(big_dec, &trunc);
    set_scale_big(&temp, 0);
    while (scale != 0) {
      null_big_dec(&trunc);
      division(temp, ten, &trunc);
      scale--;
      if (trunc.bits[3] == 0 && trunc.bits[4] == 0 && trunc.bits[5] == 0 &&
          trunc.bits[6] == 0) {
        set_scale_big(&trunc, scale);
        set_scale_big(&temp, scale + 1);
        _big_decimal mode, trunc_temp;
        null_big_dec(&mode);
        copy_big_decimal(&trunc, &trunc_temp);
        copy_big_decimal(big_dec, &temp);
        normalization_big(&temp, &trunc_temp);
        set_scale_big(&mode, get_scale_big(&temp) - scale);
        bitwise_sub(temp, trunc_temp, &mode);
        if (mode.bits[0] == 5 && scale == 1 && mode.bits[1] == 0 &&
            mode.bits[2] == 0 && mode.bits[3] == 0 && mode.bits[4] == 0 &&
            mode.bits[5] == 0 && mode.bits[6] == 0) {
          overflow_help1(trunc, big_result);
        } else
          overflow_help2(&mode, sign, &trunc, &big_result);
        big_to_dec(&big_result, dec);
        break;
      } else {
        null_big_dec(&temp);
        copy_big_decimal(&trunc, &temp);
      }
    }
    error = check_inf(&trunc, sign);
    if (error == ARITHMETIC_ERROR_INF || error == ARITHMETIC_ERROR_NEGINF) {
      copy_big_decimal(&trunc, big_dec);
    }
  }
  return error;
}

int check_inf(_big_decimal *trunc, int sign) {
  int error = 0;
  //число не вмещается и положительное -> +inf
  if ((trunc->bits[3] != 0 || trunc->bits[4] != 0 || trunc->bits[5] != 0 ||
       trunc->bits[6] != 0) &&
      sign == 0)
    error = 1;
  //число не вмещается и отрицательное -> -inf
  else if ((trunc->bits[3] != 0 || trunc->bits[4] != 0 || trunc->bits[5] != 0 ||
            trunc->bits[6] != 0) &&
           sign == 1)
    error = 2;
  return error;
}

void overflow_help1(_big_decimal trunc, _big_decimal big_result) {
  int bit = get_bit_big(trunc, 0);
  if (bit == 1) {
    _big_decimal one = {{1, 0, 0, 0}};
    bitwise_add(trunc, one, &big_result);
  } else
    copy_big_decimal(&trunc, &big_result);
}

void overflow_help2(_big_decimal *mode, int sign, _big_decimal *trunc,
                    _big_decimal *big_result) {
  set_sign_big(mode, 0);
  _big_decimal check_mode = {{5, 0, 0, 0}}, number = {{1, 0, 0, 0}};
  set_scale_big(&check_mode, 1);
  int check = compare_big(mode, &check_mode);
  if (check == 1) {
    if (sign == 0) {
      bitwise_add(*trunc, number, big_result);
    } else {
      set_sign_big(trunc, 0);
      bitwise_add(*trunc, number, big_result);
      set_sign_big(trunc, 1);
    }
  } else {
    copy_big_decimal(trunc, big_result);
  }
  set_sign_big(big_result, sign);
}
