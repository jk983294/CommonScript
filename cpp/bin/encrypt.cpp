#include <iostream>
#include <string>

using namespace std;

/**
 * usage:
 * cat x.data | ./encrypt > y.txt
 * cat y.data | ./encrypt > x.txt
 */

int main(int argc, char const *argv[]) {
    string str;
    char c;
    while (cin) {
        getline(cin, str);
        if (cin.eof()) break;

        for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
            c = *it;
            if (c >= '0' && c <= '9') {
                c = (9 - (c - '0')) + '0';
            } else if (c >= 'a' && c <= 'z') {
                c = (25 - (c - 'a')) + 'A';
            } else if (c >= 'A' && c <= 'Z') {
                c = (25 - (c - 'A')) + 'a';
            }
            cout << c;
        }
        cout << endl;
    }
    return 0;
}
