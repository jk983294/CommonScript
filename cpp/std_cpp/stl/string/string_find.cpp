#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/**
 * strchr(str, char) returns first occurrence of char in str
 * strrchr(str, char) returns last occurrence of char in str
 * memchr(str, char, len) returns first occurrence of char in str within len
 * strpbrk(str, pat) returns first occurrence of any char of pat in str
 */

int main() {
    char str[] = "This is sample strings";

    char* itr = str;
    while ((itr = strchr(itr, 's')) != nullptr) {
        cout << "find s at position " << (itr - str) << endl;
        ++itr;
    }

    itr = strrchr(str, 's');
    cout << "find last s at position " << (itr - str) << endl;

    itr = str;
    while ((itr = (char*)memchr(itr, 's', strlen(itr))) != nullptr) {
        cout << "find s at position " << (itr - str) << endl;
        ++itr;
    }

    char key[] = "aeiou";
    itr = str;
    while ((itr = strpbrk(itr, key)) != nullptr) {
        cout << "find vowel at position " << (itr - str) << endl;
        ++itr;
    }
    return 0;
}
