#include "../_math.h"

long double zero_pow(double base, double exp);
long double inf_base(double base, double exp);
long double _pow_check_limits(double base, double exp);

long double _pow(double base, double exp) {
  int t = 0;
  long double res = _pow_check_limits(base, exp);
  if (res == -1) {
    if (_fmod(exp, 1.0)) {
      res = _exp(exp * _log(base));
    } else {
      t = (exp < 0) ? 1 : 0;
      exp = (exp < 0) ? -exp : exp;
      while (exp > 0) {
        if (_fmod(exp, 2)) {
          res *= base;
          exp--;
        } else {
          base *= base;
          exp /= 2;
        }
      }
      res = (t) ? -1.0 / res : -res;
    }
  }
  return res;
}

long double _pow_check_limits(double base, double exp) {
  long double res = -1;
  if (base < 0 && !_isinf(exp) && _fmod(exp, 1))
    res = _NAN;
  else if (base == 0.0 || base == -0.0)
    res = zero_pow(base, exp);
  else if (base == -1 && _isinf(exp) == 1)
    res = 1;
  else if (base == 1 || exp == -0.0 || exp == 0.0)
    res = 1;
  else if (!_isinf(base) && base < 0 && !_isinf(exp) && _fmod(exp, 1))
    res = _NAN;
  else if (exp == _NEG_INF) {
    if (_isinf(base) || _abs(base) > 1)
      res = 0;
    else
      res = _INF;
  } else if (exp == _INF) {
    if (_isinf(base) || _abs(base) > 1)
      res = _INF;
    else
      res = 0;
  } else if (_isinf(base))
    res = inf_base(base, exp);
  else if ((_isnan(base) || _isnan(exp)) && res == -1)
    res = _NAN;
  return res;
}

long double zero_pow(double base, double exp) {
  long double res = _NAN;
  if (!_isinf(exp)) {
    if (exp == 0)
      res = 1;
    else if (exp < 0 && !_fmod(exp, 2)) {
      if (base == 0)
        res = _INF;
      else
        res = _NEG_INF;
    } else if (exp < 0 && (_fmod(exp, 2) || _fmod(exp, 1)))
      res = _INF;
    else if (exp == _NEG_INF)
      res = _INF;
    else if (exp > 0 && _fmod(exp, 2))
      res = base;
    else if (exp > 0 && (_fmod(exp, 1) || !_fmod(exp, 2)))
      res = 0.0;
  } else {
    if (exp == _NEG_INF)
      res = _INF;
    else
      res = 0.0;
  }
  return res;
}

long double inf_base(double base, double exp) {
  long double res = _NAN;
  if (base == _NEG_INF) {
    if (_fmod(exp, 2) && !_fmod(exp, 1)) {
      if (exp < 0)
        res = -0.0;
      else
        res = _NEG_INF;
    } else if (!_fmod(exp, 2) || _fmod(exp, 1)) {
      if (exp < 0)
        res = 0.0;
      else
        res = _INF;
    }
  } else {
    if (exp < 0)
      res = 0.0;
    else
      res = _INF;
  }
  if (_isnan(res) && _isnan(exp)) res = exp;
  return res;
}