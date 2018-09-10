#include <iostream>

using namespace std;

#define MyCondition

#ifdef MyCondition

#define RunSomething() \
    { cout << "run something enabled" << endl; }

#else

#define RunSomething() \
    {}

#endif

void test() { RunSomething(); }

int main() {
    test();
    return 0;
}
