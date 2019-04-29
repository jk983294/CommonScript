#include <cstring>
#include <iostream>

using namespace std;

int main() {
    char str1[] = "words separated by spaces -- and, punctuation!";
    char delimiters[] = " .,;:!-";
    char buffer[128] = {};

    char* token = nullptr;
    /**
     * strtok alter the string they is parsing,
     * you should always copy the string to a temporary buffer before parsing it
     */
    strcpy(buffer, str1);
    char* cp = buffer;
    token = strtok(buffer, delimiters);
    while (token != nullptr) {
        cout << token << endl;
        token = strtok(nullptr, delimiters);
    }

    /**
     * return two token address instead of only first token address
     * first call will print like "words_separated by spaces -- and, punctuation!"
     */
    strcpy(buffer, str1);
    cp = buffer;
    char* save = nullptr;
    token = strtok_r(buffer, delimiters, &save);
    while (token != nullptr) {
        cout << token << "_" << save << endl;
        token = strtok_r(nullptr, delimiters, &save);
    }

    strcpy(buffer, str1);
    cp = buffer;
    token = strsep(&cp, delimiters);
    while (token != nullptr) {
        if (strcmp(token, "") != 0) {  // diff from strtok, it need to check empty string if multi-delimiter in a row
            cout << token << endl;
        }
        token = strsep(&cp, delimiters);
    }
    return 0;
}
