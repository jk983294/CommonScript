#include <cstdio>
#include <cstdlib>
#include <vector>
#include <lapack.h>

using namespace std;

int main(int argc, char **argv) {
    vector<double> A = {1, 0, 2, 1}; // column major 2 * 2
    vector<double> b = {5, 2}; // column vector 2 * 1
    vector<int> pivs(2, 0);

    int n=2, lda=2, nrhs=1, ldb=2;
    int info;

    F77_NAME(dgesv)(&n, &nrhs, A.data(), &lda, pivs.data(), b.data(), &ldb, &info);

    if(info == 0) {
        printf("successful solution: %.f,%.f\n", b[0], b[1]);
        printf("piv: %d,%d\n", pivs[0], pivs[1]);
    } else if(info < 0) {
        printf("Illegal value at index %d\n", -info);
        return 1;
    } else if(info > 0) {
        printf("Matrix was singular\n");
        return 1;
    } else {
        printf("Unknown Result (Can't happen!)\n");
        return 1;
    }
    return 0;
}