#include <iostream>

using namespace std;

/**
 * __restrict__ means the pointer of content won't be modified via other aliased pointer
 * so compiler can do optimization with this information
 */

void transform(float* __restrict__ dest, float* __restrict__ src, float* __restrict__ matrix, int n) {
    int i;

    // written with aliasing in mind. dest, src and matrix are potentially aliasing,
    // so the compiler is forced to reload the values of matrix and src for each iteration.
    for (i = 0; i < n; i++) {
        dest[0] = src[0] * matrix[0] + src[1] * matrix[1] + src[2] * matrix[2] + src[3] * matrix[3];
        dest[1] = src[0] * matrix[4] + src[1] * matrix[5] + src[2] * matrix[6] + src[3] * matrix[7];
        dest[2] = src[0] * matrix[8] + src[1] * matrix[9] + src[2] * matrix[10] + src[3] * matrix[11];
        dest[3] = src[0] * matrix[12] + src[1] * matrix[13] + src[2] * matrix[14] + src[3] * matrix[15];

        src += 4;
        dest += 4;
    }
}

int main() {
    float srcdata[4 * 10000];
    float dstdata[4 * 10000];

    int i, j;
    float matrix[16];

    // init all source data
    for (i = 0; i < 16; i++) matrix[i] = 1;
    for (i = 0; i < 4 * 10000; i++) srcdata[i] = i;

    // do a bunch of tests for benchmarking.
    for (j = 0; j < 10000; j++) transform(dstdata, srcdata, matrix, 10000);
    return 0;
}
