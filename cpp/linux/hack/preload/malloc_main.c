#include <stdio.h>
#include <stdlib.h>

/**
 * we generally use memcmp() or strcmp() library functions to compare user access or validate key/data.
 * You can easily generate wrapper around these functions using RTLD_NEXT and manipulate it
 *
 * To protect info leak, hide your symbol by below:
 * strip --strip-all malloc_main
 *
 * for non-intrusive approach:
 * LD_PRELOAD=./libmy_malloc.so ./normal_malloc_main
 */

int main() {
    malloc(1);
    return 0;
}
