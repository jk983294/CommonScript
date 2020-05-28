#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cblas.h>

using namespace std;

int main(int argc, char **argv) {
    vector<double> A = {1, 2, 3, 3, 2, 1}; // row major 2 * 3
    vector<double> B = {3, 2, 1, 1, 2, 3}; // row major 3 * 2
    vector<double> C;
    C.resize(4, 0);

    int m = 2, n = 2, k = 3;
    double alpha = 1, beta = 0;
    int lda = k, ldb = n, ldc = n;

    // C = αAB + βC
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, alpha, A.data(), lda, B.data(), ldb, beta, C.data(), ldc);
    printf("C = αAB + βC: %.f,%.f,%.f,%.f\n", C[0], C[1], C[2], C[3]);
    return 0;
}