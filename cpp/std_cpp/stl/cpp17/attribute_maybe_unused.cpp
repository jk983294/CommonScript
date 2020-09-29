#include <cassert>
#include <iomanip>
#include <iostream>
#include <set>
#include <tuple>

using namespace std;

[[maybe_unused]] void f([[maybe_unused]] bool thing1, [[maybe_unused]] bool thing2) {
    [[maybe_unused]] bool b = thing1 && thing2;
    assert(b);  // in release mode, assert is compiled out, and b is unused
    // no warning because it is declared [[maybe_unused]]
}  // parameters thing1 and thing2 are not used, no warning

int main() { f(true, true); }
