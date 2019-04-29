#include <unistd.h>
#include <cstdio>
#include <iostream>

using namespace std;

void foo(FILE *fp) {
    if (ftrylockfile(fp) == 0) {
        fputs("in foo\n", fp);
        funlockfile(fp);
    }
}

void reduce_lock_impact(FILE *fp, char *buf) {
    flockfile(fp);
    while (*buf != '/') {
        putc_unlocked(*buf++, fp);
    }
    funlockfile(fp);
}

int main() { return 0; }
