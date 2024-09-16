#include "../_matrix.h"

// SUCCESS - 0, FAIL - 1
int _create_matrix(int rows, int columns, matrix_t *result){
    if(!result || rows < 1 || columns < 1)
        return 1;
    if(result->matrix)
        _remove_matrix(result);
    result->columns = columns;
    result->rows = rows;
    result->matrix = (double**)calloc(rows, sizeof(double*));
    for(int i = 0; i < rows; i++)
        result->matrix[i] = (double*)calloc(columns, sizeof(double));
    return 0;
}