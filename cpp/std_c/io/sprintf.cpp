#include <stdio.h>
#include <string.h>

char buf[100] = "";

template <typename T>
void sprintf_generic(const char* control, T data) {
    strcpy(buf, "");
    sprintf(buf, control, data);
    printf("%s", buf);
}

int main() {
    int x = 42;
    unsigned int x1 = 42;
    long x2 = 42;
    long long x3 = 42;
    float x4 = 42.424242;
    double x5 = 42.424242;
    long double x6 = 42.424242;

    sprintf_generic("int %d\n", x);
    sprintf_generic("unsigned int Octal %o\n", x1);
    sprintf_generic("unsigned int decimal %u\n", x1);
    sprintf_generic("unsigned int hexadecimal %x\n", x1);
    sprintf_generic("long %ld\n", x2);
    sprintf_generic("long long %lld\n", x3);
    sprintf_generic("float %f\n", x4);
    sprintf_generic("double %lf\n", x5);
    sprintf_generic("scientific %e\n", x5);
    sprintf_generic("double valid bit %5g\n", x5);
    sprintf_generic("double valid bit %5lg\n", x5);
    sprintf_generic("long double %Lf\n", x6);

    // join two string literal without '\0' suffix
    char a1[] = {'a', 'b', 'c', 'd', 'e'};
    char a2[] = {'f', 'g', 'h', 'j'};
    strcpy(buf, "");
    sprintf(buf, "%.5s%.4s", a1, a2);                                    // method one
    sprintf(buf, "%.*s%.*s", 5, a1, 4, a2);                              // method two
    sprintf(buf, "%.*s%.*s", (int)sizeof(a1), a1, (int)sizeof(a2), a2);  // method three

    printf("%s\n", buf);
    return 0;
}
