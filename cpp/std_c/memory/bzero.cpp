#include <malloc.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bzero(data, 10 * sizeof(int));

    for (size_t i = 0; i < 10; i++) {
        printf("%d\n", data[i]);
    }
    return 0;
}
