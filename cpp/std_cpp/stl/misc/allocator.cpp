#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void allocator_demo() {
    std::allocator<string> alloc;
    string* str = alloc.allocate(1);
    alloc.construct(str, "hello world");  // placement new
    cout << *str << endl;
    alloc.destroy(str);        // dtor, but memory still there in allocator
    alloc.deallocate(str, 1);  // reclaim memory
}

void allocator_traits_demo() {
    std::allocator<string> alloc;
    using AllocTraits = std::allocator_traits<std::allocator<std::string>>;
    string* str = AllocTraits::allocate(alloc, 1);
    AllocTraits::construct(alloc, str, "hello world");  // placement new
    cout << *str << endl;
    AllocTraits::destroy(alloc, str);        // dtor, but memory still there in allocator
    AllocTraits::deallocate(alloc, str, 1);  // reclaim memory
}

int main() {
    allocator_demo();
    allocator_traits_demo();
    return 0;
}
