#include "../_math.h"

int c = 3;

int _isinf(double x) { return (x == _INF || x == _NEG_INF); }

int _isnan(double x) { return (x != x); }