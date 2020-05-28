#include <cstdio>
#include <cstdlib>
#include <vector>
#include "lapack.h"

using namespace std;

int main(int argc, char **argv) {
    vector<double> x = {1, 2, 3, 4};
    vector<double> y = {2, 3, 4, 5};
    vector<double> d;
    d.resize(x.size(), 0);

    int len = x.size();
    int incx = 1, incy = 1;
    double scale_factor = 2;

    printf("before swap: %.f,%.f\n", x[0], y[0]);
    F77_CALL(dswap)(&len, x.data(), &incx, y.data(), &incy);
    printf("after swap: %.f,%.f\n", x[0], y[0]);

    printf("before copy: %.f,%.f\n", d[0], d[1]);
    F77_CALL(dcopy)(&len, x.data(), &incx, d.data(), &incy);
    printf("after copy: %.f,%.f\n", d[0], d[1]);

    printf("before scale(d=2*d): %.f,%.f\n", d[0], d[1]);
    F77_CALL(dscal)(&len, &scale_factor, d.data(), &incx);
    printf("after scale(d=2*d): %.f,%.f\n", d[0], d[1]);

    printf("before axpy(d=2*x+d): %.f,%.f\n", d[0], d[1]);
    F77_CALL(daxpy)(&len, &scale_factor, x.data(), &incx, d.data(), &incy);
    printf("after axpy(d=2*x+d): %.f,%.f\n", d[0], d[1]);

    printf("l2-norm of y = %0.6f\n",  F77_CALL(dnrm2)(&len, y.data(), &incy));
    printf("l1-norm of y = %0.6f\n",  F77_CALL(dasum)(&len, y.data(), &incy));
    printf("max-norm of y = |y[%d]|\n",  F77_CALL(idamax)(&len, y.data(), &incy)); // index of max abs value
    printf("x dot y = %0.6f\n",  F77_CALL(ddot)(&len, x.data(), &incx, y.data(), &incy));
    return 0;
}