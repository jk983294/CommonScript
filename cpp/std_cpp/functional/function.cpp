#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

void foo(int){
    cout << "void foo(int)" << endl;
}

struct Bar {
    void operator()(int){
        cout << "void Bar::operator()(int)" << endl;
    }
};

int main()
{
    function<void(int)> f;
    f = foo;                                    // function pointer
    f(1);

    Bar bar;
    f = bar;                                    // overload ()
    f(2);

    f = [](int i){                              // lambda function
        cout << "void lambda(int)" << endl;
    };
    f(3);
    return 0;
}