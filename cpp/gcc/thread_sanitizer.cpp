#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

int shared_variable = 42;

void thread_function() {
    ++shared_variable;
    cout << shared_variable << endl;
}

// g++ -fsanitize=thread thread_sanitizer.cpp -o thread_sanitizer -lpthread

int main() {
    thread t1(thread_function);

    ++shared_variable;
    cout << shared_variable << endl;

    t1.join();
    return 0;
}
