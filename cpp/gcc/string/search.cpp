#include <cstring>
#include <iostream>

using namespace std;

int main() {
    char str1[32] = "hello";
    char needle[8] = "ll";
    const char* skipSet = "hlo";
    const char* stopSet = "e";

    cout << ((char*)memchr(str1, 'o', strlen(str1)) - str1) << endl;  // 4
    cout << ((char*)rawmemchr(str1, 'o') - str1) << endl;             // 4, no size needed, make sure it can be found
    cout << ((char*)rawmemchr(str1, '\0') - str1) << endl;            // 5, good for find string end
    char* pos = (char*)memchr(str1, 'a', strlen(str1));
    cout << (pos == nullptr) << endl;  // true

    cout << (strchr(str1, 'o') - str1) << endl;   // 4
    cout << (strchr(str1, '\0') - str1) << endl;  // 5, '\0' is considered as part of a string
    pos = strchr(str1, 'a');
    cout << (pos == nullptr) << endl;  // true
    pos = strchrnul(str1, 'a');
    cout << (pos - str1) << endl;  // 5, set to end of string if not found

    // reverse search
    cout << ((char*)memrchr(str1, 'o', strlen(str1)) - str1) << endl;  // 4
    cout << (strrchr(str1, 'l') - str1) << endl;                       // 3

    // search for sub string
    cout << ((char*)memmem(str1, strlen(str1), needle, strlen(needle)) - str1) << endl;  // 2
    cout << (strstr(str1, needle) - str1) << endl;                                       // 2
    cout << (strcasestr(str1, "LL") - str1) << endl;                                     // 2
    cout << strspn(str1, skipSet) << endl;            // 1, the first char pos which not in skip set
    cout << (strpbrk(str1, stopSet) - str1) << endl;  // 1, the first char pos which in stop set

    return 0;
}
