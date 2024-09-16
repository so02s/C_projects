#include "../_matrix.h"

// 0 - SUCCESS, 1 - INCORRECT MATRIX, 2 - CALCULATION ERROR
int _mult_number(matrix_t *A, double number, matrix_t *result){
    if(_is_incorrect(A))
        return 1;
    _create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            //мб проверка на слишком большое число при умножении
            result->matrix[i][j] = A->matrix[i][j] * number;
    return 0;
}