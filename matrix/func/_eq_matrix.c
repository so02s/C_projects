#include "../_matrix.h"

// YES - 1, NO - 0
int _eq_matrix(matrix_t *A, matrix_t *B){
    int result = SUCCESS;
    if(_is_incorrect(A) || _is_incorrect(B)) result = FAIL;
    else if(A->rows != B->rows || A->columns != B->columns)
        result = FAIL;
    else{
        for(int i = 0; i < A->rows && result == SUCCESS; i++)
            for(int j = 0; j < A->columns && result == SUCCESS; j++)
                if(A->matrix[i][j] != B->matrix[i][j])
                    result = FAIL;
    }
    return result;
}