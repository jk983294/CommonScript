#include <stdio.h>
#include <stdlib.h>

int main() {
    char str[10] = {0};
    int nLen = snprintf(str, sizeof(str), "%s", "0123456789012345678");
    printf("str=%s\n", str);    // str=012345678
    printf("nLen=%d\n", nLen);  // nLen=19
    return 0;
}
