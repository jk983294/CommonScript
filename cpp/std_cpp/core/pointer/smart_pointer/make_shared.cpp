#include <iostream>
#include <memory>

using namespace std;

/**
 * why make_shared faster
 * When shared_ptr is created by calling std::make_shared or std::allocate_shared,
 * the memory for both the control block and the managed object is created with a single allocation.
 * The managed object is constructed in-place in a data member of the control block.
 * When shared_ptr is created via one of the shared_ptr constructors,
 * the managed object and the control block must be allocated separately.
 * In this case, the control block stores a pointer to the managed object.
 *
 * void f(const shared_ptr<X>& sp, const vector<int>& v);
 * f(shared_ptr<X>(new X(args)), {1, 2, 3});
 * above is wrong, becasue the order of init of parameter is undefined by standard,
 * so we first new X, then we create vector, during create vector, it throws, then we leak that new X since it han't
 * handle over to shared_pter to manage
 * use below make_shared to fix it
 * f(make_shared<X>(args), {1, 2, 3});
 */

int main() {
    shared_ptr<int> sp = shared_ptr<int>(new int(42));
    shared_ptr<int> sp1 = make_shared<int>(42);
    return 0;
}
