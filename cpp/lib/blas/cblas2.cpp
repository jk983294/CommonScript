#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cblas.h>

using namespace std;

int main(int argc, char **argv) {
    vector<double> A = {1, 2, 3, 4, 5, 6}; // row major 2 * 3
    vector<double> x = {1, 2, 3};
    vector<double> y;
    y.resize(2, 0);

    int row = 2, col = 3;
    int incx = 1, incy = 1;
    double alpha = 1, beta = 0;
    int lda = 3; // LDA specifies the first dimension of A

    // y = αAx + βy
    cblas_dgemv(CblasRowMajor, CblasNoTrans, row, col, alpha, A.data(), x.size(), x.data(), incx, beta, y.data(), incy);
    printf("y = αAx + βy: %.f,%.f\n", y[0], y[1]);

    // A = α*x*y' + A
    A = {1, 2, 3, 4, 5, 6}; // matrix 2 * 3
    x = {1, 2};  // vector 2 * 1
    y = {1, 2, 3}; // vector 1 * 3
    cblas_dger(CblasRowMajor, row, col, alpha, y.data(), incy, x.data(), incx, A.data(), lda);
    printf("A = α*x*y' + A: %.f,%.f,%.f,%.f,%.f,%.f\n", A[0], A[1], A[2], A[3], A[4], A[5]);
    return 0;
}