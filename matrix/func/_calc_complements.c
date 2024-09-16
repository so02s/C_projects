#include "../_matrix.h"

// 0 - SUCCESS, 1 - INCORRECT MATRIX, 2 - CALCULATION ERROR
int _calc_complements(matrix_t *A, matrix_t *result){
    matrix_t tmp = {0};
    double double_tmp = 0;
    if(_is_incorrect(A)) return 1;
    if(A->rows != A->columns) return 2;
    _create_matrix(A->rows, A->rows, result);
    if(A->rows == 1)
        result->matrix[0][0] = A->matrix[0][0];
    else {
        _create_matrix(A->rows-1, A->rows-1, &tmp);
        for (int i = 0; i < A->rows; i++) 
            for (int j = 0; j < A->rows; j++) {
                remove_row_col(A, i, j, &tmp);
                _determinant(&tmp, &double_tmp); //поспрашивать как исправить этот костыль
                result->matrix[i][j] = double_tmp;
            }
        _remove_matrix(&tmp);
    }
    return 0;
}
