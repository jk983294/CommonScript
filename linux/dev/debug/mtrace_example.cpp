#include <mcheck.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

/**
 * g++ -Wall -g mtrace_example.cpp -o mtrace_example
 * ./mtrace_example
 * mtrace mtrace_example mtrace.output
 */
int main() {
    setenv("MALLOC_TRACE", "mtrace.output", 1);
    mtrace();
    int *p1 = new int;
    int *p2 = new int;
    int *p3 = (int *)malloc(sizeof(int));
    int *p4 = (int *)malloc(sizeof(int));

    delete p1;
    free(p3);
    return 0;
}
