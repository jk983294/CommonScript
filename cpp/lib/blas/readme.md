## blas
http://www.netlib.org/blas/

http://www.netlib.org/lapack/

http://www.netlib.org/lapack/explore-html/index.html


 * level-1 BLAS routines for vector operations with O(n) work on O(n) data.
 * level-2 BLAS routines for matrix-vector operations with O(n^2) work on O(n^2) data.
 * level-3 BLAS routines for matrix-matrix operations with O(n^3) work on O(n^2) data.

## data type

| name        | data type   | 
| :----:    | :-----:  |
| s  | single  |
| d  | double  |
| c  | complex-single  |
| z  | complex-double  |


## matrix type
two-letter combination denotes the type of matrix:

| name        | matrix type   | 
| :----:    | :-----:  |
| axpy     |    y = αx + y |
| ge  | general rectangular |
| gb  | general band |
| sy  | symmetric |
| sp  | symmetric, packed storage |
| sb  | symmetric band |
| he  | Hermitian |
| hp  | Hermitian, packed storage |
| hb  | Hermitian band |
| tr  | triangular |
| tp  | triangular, packed storage |
| tb  | triangular band |

## operation
the root specifies the operation:

| name        | operation   | 
| :----:    | :-----:  |
| axpy     |    y = αx + y |
| copy     |    y = x |
| scal   |      scaling x = αx |
| mv       |    matrix-vector multiply, y = αAx + βy |
| mm        |   matrix-matrix multiply, C = αAB + βC |
| rk       |    rank-k update, C = αAAT + βC |
| r2k      |    rank-2k update, C = αABT + αBAT + βC |
| sv       |    matrix-vector solve, Ax = b, A triangular |
| sm       |    matrix-matrix solve, AX = B, A triangular |

## incX / incY
incX: index increment for array x, like index_x += incx, 1 for standard case

## LDA / LDB/ LDC
stride of the matrix

valid to have LDA value which is larger than the leading dimension of the matrix which is being operated on

reason to use a larger LDA value:

1. when you are operating on a sub matrix from a larger dense matrix
2. when hardware or algorithms offer performance advantages when storage is padded to round multiples of some optimal size (cache lines or GPU memory transaction size, or load balance in multiprocessor implementations, for example) 

## LAPACK
 * solving systems of linear equations, least-squares, eigenvalue problems, and singular value problems
 * matrix factorizations (LU, Cholesky, QR, SVD, Schur, generalized Schur)
 * LAPACK addresses moving data problem by reorganizing the algorithms to use block matrix operations