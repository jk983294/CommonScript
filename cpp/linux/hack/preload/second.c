#include <stdio.h>

/**
 * gcc -fpic -c second.c
 * gcc --share second.o -o libsecond.so
 */

void print_message() { printf("the second lib\n"); }

void second() { printf("init second\n"); }
