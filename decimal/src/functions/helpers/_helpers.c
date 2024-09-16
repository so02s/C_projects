#include "../../_decimal.h"

_decimal *init_decimal() {
  _decimal *dec = malloc(sizeof(_decimal));
  for (int i = 0; i < 4; ++i) dec->bits[i] = 0;
  return dec;
}

int is_zero(_decimal value) {
  return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0);
}

void null_decimal(_decimal *value) {
  for (int i = 0; i < 4; ++i) value->bits[i] = 0;
}

int get_sign(_decimal value) { return (value.bits[3] & (1u << 31)) >> 31; }

void set_sign(_decimal *value, int sign_value) {
  if (sign_value == 0) {
    value->bits[3] = value->bits[3] & ~(1u << 31);
  } else if (sign_value == 1) {
    value->bits[3] = value->bits[3] | (1u << 31);
  }
}

int get_scale(_decimal *dec) { return (~(1 << 31) & (dec->bits[3])) >> 16; }

int set_scale(_decimal *dec, int exp) {
  if (exp > 28 || exp < 0) return 1;
  int mask = 1 << 31;
  dec->bits[3] = dec->bits[3] & mask;  //очищаем биты экспоненты
  mask = exp << 16;
  dec->bits[3] = dec->bits[3] | mask;  //ставим новые биты экспоненты
  return 0;
}

unsigned get_bit(_decimal dec, int place) {
  if (place < 0 || place > 95) return -1;
  return ((dec.bits[place / 32]) >> (place % 32)) % 2;
}

// 1 - если да, 0 - если нет
int is_correct(_decimal *value) {
  int error = 0;
  for (int i = 96; i < 112 && !error; i++) error = get_bit(*value, i);
  for (int i = 120; i < 127 && !error; i++) error = get_bit(*value, i);
  return error;
}

// void print_bit(int bit) {
//   for (int place = 31; place >= 0; place--) {
//     printf("%d", (bit >> place) & 1);
//   }
//   printf("\n");
// }

// void print_decimal_bit(_decimal dec) {
//   print_bit(dec.bits[3]);
//   print_bit(dec.bits[2]);
//   print_bit(dec.bits[1]);
//   print_bit(dec.bits[0]);
//   printf("\n");
// }

void copy_decimal(_decimal *src, _decimal *dest) {
  for (int i = 0; i <= 3; ++i) dest->bits[i] = src->bits[i];
}

float get_rand_float(float left, float right) {
  if (left > right) {
    return get_rand_float(right, left);
  }
  return left + (right - left) * rand() / RAND_MAX;
}
