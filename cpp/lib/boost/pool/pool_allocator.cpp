#include <boost/pool/pool_alloc.hpp>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>

class MyClass {
public:
    int x;
    MyClass(int x_) : x(x_) {}
};

int main() {
    std::vector<MyClass, boost::pool_allocator<MyClass>> v;
    for (int i = 0; i < 10000; ++i) v.push_back({i});

    int sum1 = 0;
    for (const auto& item : v) {
        sum1 += item.x;
    }

    std::list<MyClass, boost::fast_pool_allocator<MyClass>> l;
    for (int i = 0; i < 10000; ++i) l.push_back({i});

    int sum2 = 0;
    for (const auto& item : l) {
        sum2 += item.x;
    }

    std::map<int, MyClass, std::less<int>, boost::fast_pool_allocator<std::pair<const int, MyClass>>> m;
    for (int i = 0; i < 10000; ++i) m.insert({i, {i}});

    int sum3 = 0;
    for (const auto& item : m) {
        sum3 += item.second.x;
    }

    using TAlloc = boost::fast_pool_allocator<std::pair<const int, MyClass>>;
    std::unordered_map<int, MyClass, std::hash<int>, std::equal_to<int>, TAlloc> m1;
    for (int i = 0; i < 10000; ++i) m1.insert({i, {i}});

    int sum4 = 0;
    for (const auto& item : m1) {
        sum4 += item.second.x;
    }

    std::cout << sum1 << " " << sum2 << " " << sum3 << " " << sum4 << std::endl;
    return 0;
}
