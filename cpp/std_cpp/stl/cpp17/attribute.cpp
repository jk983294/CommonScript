#include <iomanip>
#include <iostream>
#include <set>
#include <tuple>

using namespace std;

[[gnu::always_inline]] [[gnu::hot]] [[gnu::const]] [[nodiscard]] inline int f();  // declare f with four attributes

[[gnu::always_inline, gnu::const, gnu::hot, nodiscard]] int
f();  // same as above, but uses a single attr specifier that contains four attributes

[[using gnu: const, always_inline, hot]] [[nodiscard]] int f
    [[gnu::always_inline]] ();  // an attribute may appear in multiple specifiers

int f() { return 0; }

int main() { cout << f() << endl; }
