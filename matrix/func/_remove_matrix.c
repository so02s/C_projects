#include "../_matrix.h"

void _remove_matrix(matrix_t *A){
    if(!A) return;
    for(int i = 0; i < A->rows; i++)
        free(A->matrix[i]);
    free(A->matrix);
    A->columns = 0;
    A->rows = 0;
}