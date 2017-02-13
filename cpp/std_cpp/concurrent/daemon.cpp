#include <iostream>
#include <thread>

using namespace std;

void thread_function(){
    cout << "hello world from thread." << endl;
}


int main() {
    /**
     * if t1 not detach, when main thread terminate before child thread, it raise exception
     */
    thread t1(thread_function);
    t1.detach();
    cout << "hello world from main." << endl;

    return 0;
}