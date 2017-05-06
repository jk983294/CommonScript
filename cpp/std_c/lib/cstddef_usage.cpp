#include <cstddef>
#include <iostream>

using namespace std;

struct MyStruct {
    char singleChar;
    char array[10];
    char anotherChar;
};

int main(int argc, char const* argv[]) {
    size_t size = 10;
    char* pStr = NULL;
    const char* hello = "hello world";
    pStr = (char*)hello + 5;
    ptrdiff_t ptrdiff = pStr - hello;

    cout << size << endl;
    cout << ptrdiff << endl;

    cout << offsetof(MyStruct, singleChar) << endl;
    cout << offsetof(MyStruct, array) << endl;
    cout << offsetof(MyStruct, anotherChar) << endl;

    return 0;
}
