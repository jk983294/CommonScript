#include <iostream>
#include <thread>
#include <functional>
#include <chrono>

using namespace std;
using namespace std::chrono;

void thread_function(){
    cout << "hello world from thread." << endl;
}

struct F {
    void operator()() const {
        cout << "hello world from F::operator()." << endl;
    }
};

/**
 * thread argument better to use && > by value > & by reference
 */
void work(string&& msg, int&& delay){
    for (int i = 0; i < 10; ++i) {
        cout << msg << endl;
        this_thread::sleep_for(milliseconds(delay));
    }
}


int main() {
    thread t1(thread_function);                 // create and start, no need to start explicitly like java (t.start())
    thread t2 { F() };                          // anything callable
    thread t3 { [](){
        cout << "hello world from lambda." << endl;
    } };
    cout << "hello world from main." << endl;
    t1.join();
    t2.join();
    t3.join();

    // passing argument to thread
    thread ticker(work, string("tick"), 500);
    thread tocker(work, string("tock"), 750);
    ticker.join();
    tocker.join();
    cerr << "bye..." << endl;

    return 0;
}