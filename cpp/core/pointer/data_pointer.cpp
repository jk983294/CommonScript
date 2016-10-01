#include <iostream>

using namespace std;

int main() {
    cout << boolalpha;
    const char *ptr = "hello";                  // const data
    char * const ptr1 = "hello";                // const pointer
    const char * const ptr2 = "hello";          // const pointer & const data

    cout << *ptr << endl;
    cout << *ptr1 << endl;
    cout << *ptr2 << endl;

//    ptr[0] = 'a';
//    ptr1 = nullptr;
//    ptr2 = nullptr;
    return 0;
}