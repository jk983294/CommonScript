#include <stdio.h>

int main() {
    int x = 42;
    unsigned int x1 = 42;
    long x2 = 42;
    long long x3 = 42;
    float x4 = 42.424242;
    double x5 = 42.424242;
    long double x6 = 42.424242;

    FILE *out;
    out = fopen("/tmp/output.txt", "w");

    fprintf(out, "int %d\n", x);
    fprintf(out, "unsigned int Octal %o\n", x1);
    fprintf(out, "unsigned int decimal %u\n", x1);
    fprintf(out, "unsigned int hexadecimal %x\n", x1);
    fprintf(out, "long %ld\n", x2);
    fprintf(out, "long long %lld\n", x3);
    fprintf(out, "float %f\n", x4);
    fprintf(out, "double %lf\n", x5);
    fprintf(out, "scientific %e\n", x5);
    fprintf(out, "double valid bit %5g\n", x5);
    fprintf(out, "double valid bit %5lg\n", x5);
    fprintf(out, "long double %Lf\n", x6);
    return 0;
}
