#include <iostream>
#include <cstring>

using namespace std;

void func(char* d, const char *s) {
    // turn warning off locally
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-truncation"
    strncpy(d, s, strlen(s));
#pragma GCC diagnostic pop
}

int main() {
    char d[32] = {};
    const char* src = "src";
    func(d, src);
    cout << d << endl;
}