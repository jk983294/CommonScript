#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

/**
 * unique_lock is a general-purpose mutex ownership wrapper allowing
 * deferred locking, time-constrained attempts at locking,
 * recursive locking, transfer of lock ownership, and use with condition variables.
 */
class BigObject {};
class X
{
private:
    BigObject some_detail;
    std::mutex m;
public:
    X(BigObject const& sd): some_detail(sd){}
    friend void swap(X& lhs, X& rhs);
};
void swap(X& lhs, X& rhs){
    if(&lhs==&rhs) return;
    std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
    std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);
    std::lock(lock_a, lock_b);
    swap(lhs.some_detail, rhs.some_detail);
}

int main(){
    return 0;
}