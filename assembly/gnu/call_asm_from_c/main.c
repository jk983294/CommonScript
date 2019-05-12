#include <string.h>

extern void print(const char* str, int len);

int main() {
    const char* str = "Hello World\n";
    int len = strlen(str);
    print(str, len);
    return 0;
}
