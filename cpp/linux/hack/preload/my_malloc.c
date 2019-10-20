#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>

void *(*__libc_malloc)(size_t);
void load_func() __attribute__((constructor));

void load_func() {
    __libc_malloc = (void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");
    char *error_str;
    error_str = dlerror();
    if (error_str != NULL) {
        printf("%s\n", error_str);
    }
    printf("load func first __libc_malloc=%p\n", __libc_malloc);
}

void *malloc(size_t size) {
    printf("My Malloc\n");
    return (*__libc_malloc)(size);  // calling original malloc
}
