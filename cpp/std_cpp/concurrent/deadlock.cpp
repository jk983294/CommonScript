#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

/**
 * usually dead lock caused by circle wait, break the circle to solve the dead lock issue
 */
mutex myMutex1, myMutex2;

class DeadLockObject {
public:
    void f1(int i) {
        lock_guard<mutex> g1(myMutex1);
        lock_guard<mutex> g2(myMutex2);
        cout << " " << i << " ";
    }
    void f2(int i) {
        lock_guard<mutex> g2(myMutex2);
        lock_guard<mutex> g1(myMutex1);
        cout << " " << i << " ";
    }
};

class NoDeadLockObject {
public:
    void f1(int i) {
        std::lock(myMutex1, myMutex2);
        cout << " " << i << " ";
    }
    void f2(int i) {
        std::lock(myMutex1, myMutex2);
        cout << " " << i << " ";
    }
};

/**
 * always low number block high number
 * 1 can be locked when 10 is hold lock
 * 10 cannot be locked when 1 is locked
 */
class HierarchicalMutex {
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;

    void check_for_hierarchy_violation(){
        cout << "check_for_hierarchy_violation " << this_thread_hierarchy_value << " " << hierarchy_value << endl;
        if(this_thread_hierarchy_value <= hierarchy_value)
            throw std::logic_error("mutex hierarchy violated");
    }
    void update_hierarchy_value(){
        cout << "update_hierarchy_value " << this_thread_hierarchy_value << " " << hierarchy_value << endl;
        previous_hierarchy_value = this_thread_hierarchy_value;
        this_thread_hierarchy_value = hierarchy_value;
    }
public:
    explicit HierarchicalMutex(unsigned long value): hierarchy_value(value), previous_hierarchy_value(0){}
    void lock(){
        check_for_hierarchy_violation();
        internal_mutex.lock();
        update_hierarchy_value();
    }
    void unlock(){
        this_thread_hierarchy_value = previous_hierarchy_value;
        internal_mutex.unlock();
    }
    bool try_lock(){
        check_for_hierarchy_violation();
        if(!internal_mutex.try_lock())
            return false;
        update_hierarchy_value();
        return true;
    }
};
thread_local unsigned long HierarchicalMutex::this_thread_hierarchy_value(numeric_limits<unsigned long>::max());

HierarchicalMutex high_level_mutex(10000);
HierarchicalMutex low_level_mutex(5000);

int low_level_func(){
    std::lock_guard<HierarchicalMutex> lk(low_level_mutex);
    return 42;
}
void high_level_func(){
    std::lock_guard<HierarchicalMutex> lk(high_level_mutex);
    low_level_func();
}

int main(){
    high_level_func();
    return 0;
}