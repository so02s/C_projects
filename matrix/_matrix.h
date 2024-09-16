#ifndef _MATRIX
#define _MATRIX

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

//работа с памятью
int _create_matrix(int rows, int columns, matrix_t *result); //создание матрицы
void _remove_matrix(matrix_t *A); //освобождение матрицы
//сравнение
int _eq_matrix(matrix_t *A, matrix_t *B); //сравнение матриц
//арифметика
int _sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result); //сложение матриц
int _sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result); //вычитание матриц
int _mult_number(matrix_t *A, double number, matrix_t *result); //умножение матрицы на число
int _mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result); //умножение матрицы на матрицу
//дополнительная арифметика
int _transpose(matrix_t *A, matrix_t *result); //транспорирование
int _calc_complements(matrix_t *A, matrix_t *result); //матрица алгебраичных дополнений
int _determinant(matrix_t *A, double *result); //определитель
int _inverse_matrix(matrix_t *A, matrix_t *result); //обратная матрица
// вспомогательное
int _is_incorrect(matrix_t *A); //проверка на корректность матрицы
void _print(matrix_t *A); //печать
double recurs_determ(matrix_t*A); //определитель рекурсией
void remove_row_col(matrix_t*A, int row, int column, matrix_t*result); //копировать матрицу без строки и столбца

#endif