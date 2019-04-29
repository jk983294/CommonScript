#include <string.h>
#include <iostream>

using namespace std;

int main() {
    char str1[32] = "hello";
    char str2[32] = "hello";

    // length
    cout << sizeof(str1) << " " << strlen(str1) << endl;  // 32 5
    cout << strnlen(str1, 3) << endl;  // 3    this equivalent to (strlen (s) < maxlen ? strlen (s) : maxlen)

    /**
     * copy
     * Ranking the functions according to level of sanity: strcpy < strncpy < snprintf
     */
    strcpy(str1 + strlen(str1), " world");
    cout << str1 << endl;  // "hello world"
    strncpy(str1 + strlen(str1), " worldworld", 5);
    char* dup1 = strdup(str1);  // copy to a new malloc memory space, need to free the space after use
    cout << dup1 << endl;       // "hello world worl"
    free(dup1);
    char* dup2 = strndup(str1, 10);
    cout << dup2 << endl;  // "hello worl"
    free(dup2);

    char* pEnd = stpcpy(str1, "hello");  // like strcpy, but return the end of the dest string, good for concat
    cout << str1 << " " << (pEnd - str1) << endl;  // "hello" 5
    pEnd = stpncpy(pEnd, " worldworld", 6);
    *pEnd = '\0';
    cout << str1 << " " << (pEnd - str1) << endl;  // "hello world" 11

    snprintf(str1, sizeof(str1), "%s", "hello");  // "hello"
    cout << str1 << endl;

    // concat
    strcpy(str1, "hello");
    strcat(str1, " world");
    cout << str1 << endl;  // "hello world"
    strncat(str1, " worldworld", 6);
    cout << str1 << endl;  // "hello world world"
    return 0;
}
