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
 */

int main() {
    shared_ptr<int> sp = shared_ptr<int>(new int(42));
    shared_ptr<int> sp1 = make_shared<int>(42);
    return 0;
}
