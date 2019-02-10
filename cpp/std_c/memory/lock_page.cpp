#include <iostream>
#include <sys/mman.h>
#include <unistd.h>

using namespace std;

/**
 * cause the page to be paged in if it isn’t already and mark it so it will never be paged out
 * and consequently will never cause a page fault. This is called locking a page.
 */

// run as root, otherwise cannot lock such huge memory

const int alloc_size = 32 * 1024 * 1024;

int main() {
    char *memory = (char *)malloc(alloc_size);
    if (mlock(memory, alloc_size) == -1) {
        perror("mlock");
        return (-1);
    }
    int i;
    int page_size = getpagesize();
    for (i = 0; i < alloc_size; i += page_size) {
        printf("i=%d\n", i);
        memory[i] = 0;
    }

    if (munlock(memory, alloc_size) == -1) {
        perror("munlock");
        return (-1);
    }
    return 0;
}
