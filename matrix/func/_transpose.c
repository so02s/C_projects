#include "../_matrix.h"

// 0 - SUCCESS, 1 - INCORRECT MATRIX, 2 - CALCULATION ERROR
int _transpose(matrix_t *A, matrix_t *result){
    if(_is_incorrect(A))
        return 1;
    _create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++)
        for (int j = 0; j < result->columns; j++)
            result->matrix[i][j] = A->matrix[j][i];
    return 0;
}