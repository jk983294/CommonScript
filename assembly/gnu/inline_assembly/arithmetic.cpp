#include <iostream>

using namespace std;

int my_add(int a, int b) {
    int result;
    __asm__(
        "movl %1, %%eax \n\t"
        "movl %2, %%ebx \n\t"
        "addl %%ebx, %%eax"
        : "=g"(result)
        : "g"(a), "g"(b));
    return result;
}

int my_minus(int a, int b) {
    int result;
    __asm__(
        "movl %1, %%eax \n\t"
        "movl %2, %%ebx \n\t"
        "subl %%ebx, %%eax"
        : "=g"(result)
        : "g"(a), "g"(b));
    return result;
}

int my_multiply(int a, int b) {
    int result;
    __asm__(
        "movl %1, %%eax \n\t"
        "movl %2, %%ebx \n\t"
        "imul %%ebx, %%eax"
        : "=g"(result)
        : "g"(a), "g"(b));
    return result;
}

int my_divide(int a, int b) {
    int result;
    __asm__(
        "movl %1, %%eax \n\t"
        "movl %2, %%ebx \n\t"
        "idiv %%ebx, %%eax"
        : "=g"(result)
        : "g"(a), "g"(b));
    return result;
}

double my_add_double(double a, double b) {
    double result;
    __asm__(
        "fldl %2 ;"
        "fldl %1 ;"
        "faddp ;"
        : "=&t"(result)  // First (top of stack) floating point register
        : "g"(a), "g"(b));
    return result;
}

double my_minus_double(double a, double b) {
    double result;
    __asm__(
        "fldl %2 ;"
        "fldl %1 ;"
        "fsubp ;"
        : "=&t"(result)  // First (top of stack) floating point register
        : "g"(a), "g"(b));
    return result;
}

double my_multiply_double(double a, double b) {
    double result;
    __asm__(
        "fldl %2 ;"
        "fldl %1 ;"
        "fmulp ;"
        : "=&t"(result)  // First (top of stack) floating point register
        : "g"(a), "g"(b));
    return result;
}

double my_divide_double(double a, double b) {
    double result;
    __asm__(
        "fldl %2 ;"
        "fldl %1 ;"
        "fdivp ;"
        : "=&t"(result)  // First (top of stack) floating point register
        : "g"(a), "g"(b));
    return result;
}

int main() {
    cout << my_add(2, 3) << endl;
    cout << my_minus(2, 3) << endl;
    cout << my_multiply(2, 3) << endl;
    cout << my_divide(6, 3) << endl;

    cout << my_add_double(2.1, 3.2) << endl;
    cout << my_minus_double(2.1, 3.2) << endl;
    cout << my_multiply_double(2.1, 3.2) << endl;
    cout << my_divide_double(2.1, 3.2) << endl;
    return 0;
}
