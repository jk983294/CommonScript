#include <stdio.h>
#include <string.h>

/**
void *memmove(void *dst, const void *src, size_t count) {
    void *address = dst;

    if (dst <= src || (char *)dst >= (char *)src + count) {
        while (count--) {
            *(char *)address = *(char *)src;
            address = (char *)address + 1;
            src = (char *)src + 1;
        }
    } else {
        address = (char *)address + count - 1;
        src = (char *)src + count - 1;
        while (count--) {
            *(char *)address = *(char *)src;
            address = (char *)address - 1;
            src = (char *)src - 1;
        }
    }
    return dst;
}
*/
int main() {
    char str[] = "memmove can be very useful......";
    memmove(str + 20, str + 15, 11);
    puts(str);
    return 0;
}
