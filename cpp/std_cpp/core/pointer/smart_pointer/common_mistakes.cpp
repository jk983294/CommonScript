#include <iostream>
#include <memory>

using namespace std;

/**
 * Mistake # 1 : Using a shared pointer where an unique pointer suffices !!!
 * Mistake # 2 : Not making resources/objects shared by shared_ptr threadsafe !
 * Mistake # 3 : Using auto_ptr !
 * Mistake # 4 : Not using make_shared to initialize a shared_ptr !
 * Mistake # 5 : Not assigning an object(raw pointer) to a shared_ptr as soon as it is created !
 * Mistake # 6 : Deleting the raw pointer used by the shared_ptr !
 * Mistake # 7 : Not using a custom deleter when using an array of pointers with a shared_ptr !
 * Mistake # 8 : Not avoiding cyclic references when using shared pointers !
 * Mistake # 9 : Not deleting a raw pointer returned by unique_ptr.release() !
 * Mistake # 10 : Not using a expiry check when calling weak_ptr.lock() !
 */
template <class T>
struct array_deleter {
    void operator()(T* p) { delete[] p; }
};

int main() {
    // user defined array deleter
    shared_ptr<int> sp1(new int[10], array_deleter<int>());

    // std provided deleter
    shared_ptr<int> sp2(new int[10], default_delete<int[]>());

    // lambda deleter
    shared_ptr<int> sp3(new int[10], [](int* p) { delete[] p; });
    return 0;
}
