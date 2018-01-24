#include <boost/pool/pool_alloc.hpp>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>

struct A {
    static inline void* operator new(std::size_t sz) { return pool.allocate(); }

    static inline void operator delete(void* p) { pool.deallocate(static_cast<A*>(p)); }

    char other_data[50];
    static boost::fast_pool_allocator<A> pool;
};

struct B {
    void add(int i, A* a) {
        v.push_back(a);
        m.insert(std::make_pair(i, a));
    }

    std::vector<A*, boost::pool_allocator<A*> > v;
    std::map<int, A*, std::less<int>, boost::fast_pool_allocator<std::pair<const int, A*> > > m;
};

boost::fast_pool_allocator<A> A::pool;

int main() {
    std::clock_t start = std::clock();
    B b;
    for (int i = 0; i < 10000; ++i) {
        for (int j = 0; j < 10000; ++j) {
            A* tmp = new A;
            b.add(i, tmp);
        }

        for (A* a : b.v) {
            delete a;
        }
        b.v.clear();
        b.m.clear();
    }
    std::cout << (std::clock() - start) / double(CLOCKS_PER_SEC) << " secs.\n";
    return 0;
}
