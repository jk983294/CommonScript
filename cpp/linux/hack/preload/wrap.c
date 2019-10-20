#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <stdio.h>

/**
 * gcc -fpic -c wrap.c
 * gcc --share wrap.o -o libwrap.so
 */

void (*f)();
void load_func() __attribute__((constructor));

void load_func() {
    f = (void (*)())dlsym(RTLD_NEXT, "print_message");
    char *error_str;
    error_str = dlerror();
    if (error_str != NULL) {
        printf("%s\n", error_str);
    }
    printf("load func first f=%p\n", f);
}

void print_message() {
    printf("the wrap lib~~\n");
    f();
}
