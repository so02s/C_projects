#include "../_matrix.h"

// 0 - SUCCESS, 1 - INCORRECT MATRIX, 2 - CALCULATION ERROR
int _mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result){
    if(_is_incorrect(A) || _is_incorrect(B))
        return 1;
    if(A->columns != B->rows)
        return 2;
    _create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < B->columns; j++)
            for (int n = 0; n < A->columns; n++)
                result->matrix[i][j] += A->matrix[i][n] * B->matrix[n][j];
    return 0;
}