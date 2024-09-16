#include "../_matrix.h"

void _print(matrix_t *A){
    if(_is_incorrect(A))
        return;
    for (int i = 0; i < A->rows; i++){
        for (int j = 0; j < A->columns; j++)
            printf("%.0f\t", A->matrix[i][j]);
        printf("\n");
    }
}