#include "../_matrix.h"

// 0 - SUCCESS, 1 - INCORRECT MATRIX, 2 - CALCULATION ERROR
int _sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result){
    if(_is_incorrect(A) || _is_incorrect(B))
        return 1;
    if(A->rows != B->rows || A->columns != B->columns)
        return 2;
    _create_matrix(A->rows, A->columns, result);
    for(int i = 0; i < A->rows; i++)
        for(int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    return 0;
}