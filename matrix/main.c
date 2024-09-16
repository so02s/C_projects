#include "_matrix.h"

int main(){
    matrix_t A = {0};
    int t = 3;
    double determ = 0;

    _create_matrix(t, t, &A);

    A.matrix[0][0] = 0;
    A.matrix[0][1] = 1;
    A.matrix[0][2] = 2;
    A.matrix[1][0] = 9;
    A.matrix[1][1] = 10;
    A.matrix[1][2] = 7;
    A.matrix[2][0] = 4;
    A.matrix[2][1] = 1;
    A.matrix[2][2] = 5;

    _print(&A);

    _determinant(&A, &determ);

    printf("det = %f\n", determ);

    _remove_matrix(&A);
    return 0;
}