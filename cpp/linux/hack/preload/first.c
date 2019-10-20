#include <stdio.h>

/**
 * gcc -fpic -c first.c
 * gcc --share first.o -o libfirst.so
 */

void print_message() { printf("the first lib\n"); }
void first() { printf("init first\n"); }
