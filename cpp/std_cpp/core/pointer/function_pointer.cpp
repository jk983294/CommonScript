#include <iostream>

using namespace std;

/**
 * $> cdecl
 * cdecl> explain char *(*(*a)(void))[20];
 * declare a as pointer to function (void) returning pointer to array 20 of pointer to char
 * C++右左规则 The right-left rule
 */

typedef void (*FP_OUT)();                       // use typedef to help
typedef int (*FP_IN)(int);
typedef FP_OUT (*BP)(FP_IN, int);


int foo(int);
int bar(int(*)(int), int);
void f1();
// f2 take a function pointer int (*)(int) and int, it returns a function pointer void (*)()
void (*f2( int (*)(int), int ))();
// f3 equals to f2
FP_OUT f3(FP_IN, int);

void zero(int i){
    cout << "zero " << i << endl;
}
void one(int i){
    cout << "one " << i << endl;
}
void two(int i){
    cout << "two " << i << endl;
}
// function pointer array dispatch
void dispatch(int i){
    static void (*lookup[])(int) = { zero, one, two };
    lookup[i](i);
}

int main() {
    int (*p)(int) = foo;                        // p is a function pointer which takes int and return int
    foo(3);
    p(4);
    bar(foo, 1);
    bar(p, 2);

    void (*fp)() = f1;
    void (*(*bp)(int (*)(int), int))() = f2;
    f2(foo, 8)();

    f3(foo, 7)();

    FP_IN fp_in = foo;
    FP_OUT fp1 = f1;
    BP bp1 = f2;
    bp1 (foo, 9)();

    dispatch(1);
    dispatch(2);
    return 0;
}
void f1(){
    cout << "f1" << endl;
}
void (*f2( int (*f)(int), int i))(){
    cout << "f2 " << i << endl;
    f(i);
    return f1;
}
FP_OUT f3(FP_IN fp_in, int i){
    cout << "f3 " << i << endl;
    fp_in(i);
    return f1;
}
int foo(int i){
    cout << "foo " << i << endl;
    return i + 1;
}
int bar(int (*f)(int), int i){
    cout << "bar" << i << endl;
    return f(i + 1);
}
