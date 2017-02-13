#include <iostream>
#include <future>
#include <string>

using namespace std;

/**
 * future wait for one-time event
 * std::launch::async, a new thread is launched to execute the task asynchronously
 * std::launch::defered, lazy evaluation when wait() or get() called
 * d::launch::deferred | std::launch::async, choose either one implementation
 */

struct X {
    void foo(int,std::string const&){}
    std::string bar(std::string const&){
        return string("X::bar");
    }
};

struct Y {
    double operator()(double x){
        return x + 1.0;
    }
};

int f(int x){
    return x + 1;
}

int main(){
    X x;
    future<void> f1 = std::async(&X::foo, &x, 42, "hello");		// call p->foo(42, "hello")
    future<string> f2 = std::async(&X::bar, x, "goodbye");		// call tmpx.bar("goodbye"), tmpx is a copy of x

    Y y;
    future<double> f3 = std::async(Y(), 3.141);
    future<double> f4 = std::async(std::ref(y), 2.718);

    future<int> f5 = std::async(f, 1);

    std::cout << f2.get() << std::endl;
    std::cout << f3.get() << std::endl;
    std::cout << f4.get() << std::endl;
    std::cout << f5.get() << std::endl;
    return 0;
}