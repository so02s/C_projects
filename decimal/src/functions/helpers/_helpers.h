#ifndef _HELPERS
#define _HELPERS

#include "../../_types.h"

_decimal *init_decimal();     //инициализация
int is_zero(_decimal value);  //проверяет, что число ноль
void null_decimal(_decimal *value);              //делает нулем
int get_sign(_decimal value);                    //выдает знак
void set_sign(_decimal *value, int sign_value);  //меняет знак
int get_scale(_decimal *dec);           //выдает порядок
int set_scale(_decimal *dec, int exp);  //меняет порядок
unsigned get_bit(_decimal value, int bit);  //выдает бит на конкретном месте
int is_correct(_decimal *value);  //проверяет корректность decimal
// void print_bit(int bit);                  //вывод int по битам
// void print_decimal_bit(_decimal dec);  //выводит по битам
void copy_decimal(_decimal *src, _decimal *dest);  //копирование decimal
int decimal_mult_positive(_decimal value_1, _decimal value_2,
                          _decimal *result);
//служебки для big_dec
_big_decimal *init_big_decimal();  //инициализация
void dec_to_big(_decimal *dst,
                _big_decimal *big_dst);  //переводит из decimal в big decimal
                                            //(и инициализирует big dec)
int big_to_dec(_big_decimal *big_dst,
               _decimal *dst);  //переводит из big dec в dec
void null_big_dec(_big_decimal *value);      //делает нулем
// void print_dec_big_bit(_big_decimal dec);
unsigned get_sign_big(_big_decimal *value);  //выдает знак
void set_sign_big(_big_decimal *value, unsigned sign_value);  //меняет знак
int get_scale_big(_big_decimal *dec);  //выдает порядок
int set_scale_big(_big_decimal *dec, int scale_value);  //меняет порядок
unsigned get_bit_big(_big_decimal value,
                     int position);  //возвращает нужный бит
void set_bit_big(_big_decimal *value, int position,
                 unsigned bit_val);  // устанавливает бит
int shift_left_big(_big_decimal *value,
                   int shift_value);  //сдвиг влево = * на 2
int shift_right_big(_big_decimal *value,
                    int shift_value);         //сдвиг влево = / на 2
void normalization_big(_big_decimal *val1,
                       _big_decimal *val2);  //нормализация
void copy_big_decimal(_big_decimal *sourse,
                      _big_decimal *copy);  //копирование
int overflow(_big_decimal *big_dec, _decimal *dec);
void overflow_help1(_big_decimal trunc, _big_decimal big_result);
void overflow_help2(_big_decimal *mode, int sign, _big_decimal *trunc, _big_decimal *big_result);
int check_inf(_big_decimal *trunc, int sign);

//арифметика
int bitwise_add(_big_decimal value1, _big_decimal value2,
                _big_decimal *res);  //битовое сложение
int bitwise_sub(_big_decimal value_1, _big_decimal value_2,
                _big_decimal *result);  //битовое вычитание
int add_big(_big_decimal value1, _big_decimal value2,
            _big_decimal *res);  // сложение больших dec
void great_scale(_big_decimal *val1, int scale2);  //умножение на 10
int compare_big(_big_decimal *, _big_decimal *);
int good_big(_big_decimal);  // проверка на правильное состояние big_dec
int is_zero_big(_big_decimal *);  // проверка на ноль
void division(_big_decimal val1, _big_decimal val2, _big_decimal *res);
int get_first_bit(_big_decimal value);
int mod(_decimal v1, _decimal v2, _decimal *result);
float get_rand_float(float left, float right);

#endif
