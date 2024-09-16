#ifndef _MATH_H
#define _MATH_H

#include <stdio.h>
#include <stdlib.h>

#define PRECISION 1e-20
#define PRECISION_test 1e-6
#define _DBL_MAX 1.79769e+308
#ifndef HUGE_VALF
#define HUGE_VALF __builtin_huge_valf()
#endif
#define _PI 3.14159265359
#define _NAN __builtin_nanf("0x7fc00000")
#define _INF HUGE_VALF
#define _NEG_INF _INF*(-1)

// вспомогательные функции
int _isinf(double x);
int _isinff(float x);
int _isnan(double x);
int _isnanf(float x);
long double _factorial(size_t x);
long double _log2(double n);

// основные функции
int _abs(int x);
long double _acos(double x);                
long double _asin(double x);                
long double _atan(double x);                
long double _ceil(double x);                
long double _cos(double x);                 
long double _exp(double x);                 
long double _fabs(double x);                
long double _floor(double x);               
long double _fmod(double x, double y);      
long double _log(double x);                 
long double _pow(double base, double exp);  
long double _sin(double x);                 
long double _sqrt(double x);                
long double _tan(double x);                 

#endif