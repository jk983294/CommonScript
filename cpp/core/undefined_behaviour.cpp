#include <iostream>

using namespace std;


/**
 * sequence point
 * a guaranteed point of expression evaluation
 */

void modify_lvalue_more_than_once(){
    int a = 0;
    int b[10];
    int add = (++a) + (++a);
    a = b[a++];
    a = (++a) + 1;
}

int main() {
    cout << boolalpha;
    modify_lvalue_more_than_once();
    return 0;
}