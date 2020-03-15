#include <stdio.h>

int main() {
    int x = 42;
    unsigned int x1 = 42;
    long x2 = 42;
    long long x3 = 42;
    float x4 = 42.424242f;
    double x5 = 42.424242;
    long double x6 = 42.424242;
    size_t x7 = 42;
    ssize_t x8 = 42;

    printf("int %d\n", x);
    printf("unsigned int Octal %o\n", x1);
    printf("unsigned int decimal %u\n", x1);
    printf("unsigned int hexadecimal %x\n", x1);
    printf("long %ld\n", x2);
    printf("long long %lld\n", x3);
    printf("float %f\n", x4);
    printf("double %lf\n", x5);
    printf("scientific %e\n", x5);
    printf("double valid bit %5g\n", x5);
    printf("double valid bit %5lg\n", x5);
    printf("long double %Lf\n", x6);
    printf("long unsigned int %zu\n", x7);
    printf("long unsigned int hex %zx\n", x7);
    printf("long signed int %zd\n", x8);  // prints as signed decimal

    printf("pointer %p\n", &x8);

    // fill 0
    printf("600%03d.SSE", 1);
    return 0;
}
