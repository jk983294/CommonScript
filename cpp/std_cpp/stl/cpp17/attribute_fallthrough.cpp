#include <iomanip>
#include <iostream>
#include <set>
#include <tuple>

using namespace std;

void g() { cout << "g\n"; }
void h() { cout << "h\n"; }
void i() { cout << "i\n"; }

void f(int n) {
    switch (n) {
        case 1:
        case 2:
            g();
            [[fallthrough]];
        case 3:  // no warning on fallthrough
            h();
        case 4:  // compiler may warn on fallthrough
            if (n < 3) {
                i();
                [[fallthrough]];  // OK
            } else {
                return;
            }
        case 5:
            cout << "5\n";
    }
}

int main() { f(1); }
