#include "../_matrix.h"

// 0 - SUCCESS, 1 - INCORRECT MATRIX, 2 - CALCULATION ERROR
int _inverse_matrix(matrix_t *A, matrix_t *result){
    int res = 0;
    double det = 0;
    matrix_t M = {0};
    if(_is_incorrect(A)) res = 1;
    else if(A->rows != A->columns) res = 2;
    else {
        _create_matrix(A->rows, A->rows, result);
        _determinant(A, &det);
        if(!det)
            res = 2;
        else {
            det = 1.0/det;
            _calc_complements(A, &M);
            for (int i = 0; i < A->rows; i++)
                for (int j = 0; j < A->columns; j++)
                result->matrix[i][j] = det * M.matrix[j][i];
        }
        _remove_matrix(&M);
    }
    return res;
}