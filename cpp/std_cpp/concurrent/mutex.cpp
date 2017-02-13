#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
using namespace std::chrono;

mutex m3, m4;

void critical_section1(){
    static std::mutex m1;
    m1.lock();
    cout << "I own this mutex in critical_section1." << endl;
    m1.unlock();
}

void critical_section2(){
    static std::mutex m2;
    /**
     * In RAII (Resource Acquisition Is Initialization), holding a resource is tied to object lifetime:
     * resource allocation (acquisition) is done during object creation (specifically initialization),
     * by the constructor, while resource release is done during object destruction, by the destructor.
     * If objects are destructed properly, resource leaks do not occur.
     */
    lock_guard<mutex> guard(m2);                                        // more cheap than unique_lock
    cout << "I own this mutex in critical_section2." << endl;
}

void critical_section3(){
    std::unique_lock<std::mutex> lk1(m3, std::defer_lock);
    std::unique_lock<std::mutex> lk2(m4, std::defer_lock);
    std::lock(lk1, lk2);
    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    cout << "I own multiply locks in critical_section3." << endl;
    lk1.unlock();
    lk2.unlock();
}

int main() {
    thread t1(critical_section1);
    thread t2(critical_section2);
    thread t3(critical_section3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}