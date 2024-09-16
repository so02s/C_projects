#ifndef _ROUNDING
#define _ROUNDING

#include "../../_types.h"

int _floor(_decimal value, _decimal *result);
int _round(_decimal value, _decimal *result);
int _truncate(_decimal value, _decimal *result);
int _negate(_decimal value, _decimal *result);

#endif