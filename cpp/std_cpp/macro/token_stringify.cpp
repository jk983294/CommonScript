#include <iostream>

using namespace std;

/**
 * use # to turn a token into a string containing the literal text of the token
 * string literals next to each other are concatenated
 */
#define PRINTOUT(token) cout << #token << " has value " << (token) << endl

int main() {
    int x = 10;
    int y = 5;

    PRINTOUT(x + y);  // x + y has value 15
    return 0;
}
