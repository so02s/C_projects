#include "../_matrix.h"

// GOOD - 0, BAD - 1
int _is_incorrect(matrix_t *A){
    if(!A || A->rows < 1 || A->columns < 1 || !A->matrix)
        return 1;
    return 0;
}