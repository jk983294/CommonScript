#include <iostream>

using namespace std;

/**
 * typedef usage
 */
typedef struct Stuff {} Stuff;      // useful for C code

void typedef_demo(){
    typedef unsigned int Ui;
    typedef int Arri [100];
    typedef char *Arrcp [100];
    Ui big;
    Arri numbers;                   // int numbers[100];
    Arrcp environments;             // char* environments[100]

}

/**
 * alias templates
 */
template <typename U> struct my_remove_pointer1 {
    using type = U;
};
template <typename T> struct my_remove_pointer1<T*> {
    using type = T;
};
template <typename W>
using RemovePointer1 = typename my_remove_pointer1<W>::type;
template <typename T>
RemovePointer1<T> fun(T val);					        // no need to use typename something::type to define return type

int main() {
    cout << boolalpha;
    return 0;
}