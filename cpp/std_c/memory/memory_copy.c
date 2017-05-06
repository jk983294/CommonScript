
#include <stdio.h>
#include <string.h>

/**
void *memcpy(void *dest, const void *src, size_t count) {
    char *tmp = dest;
    const char *s = src;

    while (count--)
    *tmp++ = *s++;
    return dest;
}
*/
int main() {
    const char *src = "Golden Global View";
    char dest[20];

    memcpy(dest, src, strlen(src));
    dest[strlen(src)] = '\0';
    printf("%s", dest);
    return 0;
}
