#ifndef _CONVERSATION
#define _CONVERSATION

#include "../../_types.h"

int _from_int_to_decimal(int src, _decimal *dst);
int _from_float_to_decimal(float src, _decimal *dst);
int _from_decimal_to_int(_decimal src, int *dst);
int _from_decimal_to_float(_decimal src, float *dst);
int _from_string_to_decimal(char *str, _decimal *dec);
int get_scale_from_string(char* ptr);

#endif