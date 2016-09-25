#include <iostream>
#include <thread>

using namespace std;

void thread_function(){
    cout << "hello world." << endl;
}


int main() {
    thread t1(thread_function);
    t1.join();

    return 0;
}