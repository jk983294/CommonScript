#include <cstdlib>
#include <iostream>

using namespace std;

#ifndef NO_MY_SPECIAL_ASSERT

void DoMySpecialAssert(bool invariant, string statement, string file, int line) {
    if (!invariant) {
        cerr << "SpecialAssert Failed!" << endl;
        cerr << "Expression: " << statement << endl;
        cerr << "File: " << file << endl;
        cerr << "Line: " << line << endl;
        std::abort();  // Quits program and signals error to the OS.
    }
}

#define SpecialAssert(expr) DoMySpecialAssert(expr, #expr, __FILE__, __LINE__)

#else
#define DoMySepcialAssert(expr) /* nothing */
#endif

int main() {
    int* myPtr = nullptr;

    SpecialAssert(myPtr != nullptr);
    return 0;
}
