#include <iostream>

using namespace std;

// a constant should be surround in parentheses to avoid operator precedence
#define PI_PLUS_ONE (3.14 + 1)

#define MULTIPLY(x, y) ((x) * (y))

// multiply line should surround with {}, also use while loop to avoid end ; not compile issue
#define SWAP(a, b)  do { a ^= b; b ^= a; a ^= b; } while ( 0 )

#define SWAP1(a, b) \
    do {            \
        a ^= b;     \
        b ^= a;     \
        a ^= b;     \
} while (0)

int main() {
    cout << PI_PLUS_ONE << endl;
    cout << MULTIPLY(3 + 2, 5 - 3) << endl;

    int x = 10;
    int y = 5;
    int z = 4;

    if (x < 0)
        SWAP(x, y);
    else
        SWAP1(x, z);
    cout << x << " " << y << " " << z << endl;
    return 0;
}
