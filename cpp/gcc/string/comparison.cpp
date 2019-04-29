#include <cstring>
#include <iostream>

using namespace std;

int main() {
    char str1[32] = "hello";
    char str2[32] = "hello";

    // comparison
    strcpy(str1, "hello");
    strcpy(str2, "hello");
    cout << memcmp(str1, str2, strlen(str1)) << " " << strcmp(str1, str2) << endl;  // 0
    str2[0] = 'z';
    cout << memcmp(str1, str2, strlen(str1)) << " " << strcmp(str1, str2) << " " << (str1[0] - str2[0]) << endl;  // -18
    str2[0] = 'a';
    cout << memcmp(str1, str2, strlen(str1)) << " " << strcmp(str1, str2) << " " << (str1[0] - str2[0]) << endl;  // 7
    strcpy(str2, "HELLO");                                                               // case insensitive comparison
    cout << strcasecmp(str1, str2) << " " << strcmp(str1, str2) << endl;                 // 0 32
    cout << strncasecmp(str1, str2, strlen(str1)) << " " << strcmp(str1, str2) << endl;  // 0 32
    strcpy(str2, "hello world");                                                         // sub string comparison
    cout << strncmp(str1, str2, strlen(str1)) << " " << strcmp(str1, str2) << endl;      // 0 -32
    return 0;
}
