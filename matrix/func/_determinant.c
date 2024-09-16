#include "../_matrix.h"


// 0 - SUCCESS, 1 - INCORRECT MATRIX, 2 - CALCULATION ERROR
int _determinant(matrix_t *A, double *result){
    if(_is_incorrect(A)) return 1;
    if(A->rows != A->columns) return 2;
    *result = recurs_determ(A);
    return 0;
}

double recurs_determ(matrix_t*A){
    double det = 0;
    int index = 1;
    if(A->columns == 1)
        det = A->matrix[0][0];
    else if(A->columns == 2)
        det = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    else{
        matrix_t tmp_matrix = {0};
        _create_matrix(A->rows - 1, A->columns - 1, &tmp_matrix);
        for(int i = 0; i<A->rows; i++){
            remove_row_col(A, 0, i, &tmp_matrix);
            det += (index * A->matrix[0][i] * recurs_determ(&tmp_matrix));
            index = -index;
        }
        _remove_matrix(&tmp_matrix);
    }
    return det;
}

void remove_row_col(matrix_t*A, int row, int column, matrix_t*result){
    int offset_col = 0, offset_row = 0;
    for(int i = 0; i < A->rows - 1; i++){
        if(i == row)
            offset_row = 1;
        offset_col = 0;
        for(int j = 0; j < A->columns - 1; j++){
            if(j == column)
                offset_col = 1;
            result->matrix[i][j] = A->matrix[i+offset_row][j+offset_col];
        }
    }
}