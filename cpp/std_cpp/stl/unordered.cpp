#include <iostream>
#include <unordered_map>

using namespace std;

/**
 * unordered associative container use hash structure, so it doesn't maintain the order of elements
 * unordered_map, unordered_set, unordered_multimap, unordered_multiset
 * unordered associative container use tree structure, so it does maintain the order of elements
 * map, set, multimap, multiset
 *
 * std::map和std::unordered_map，读取谁快，std::unordered_map快，因为O(1) < O(lgn)
 * 如果只有5个data,谁快，还是std::unordered_map快，因为hash table底层实现数组，一般load factor在0.5~0.7之间，
 * 所以数组大概10个元素大小，数组更加cache friendly，所以比指针的std::map快
 */

struct Hen {
    int x;
    int y;
    Hen(int x_, int y_) : x{x_}, y{y_} {}
};

bool operator==(const Hen& left, const Hen& right) { return left.x == right.x && left.y == right.y; }

namespace std {
template <>
struct hash<Hen> {
    size_t operator()(const Hen& hen) const { return hash<int>{}(hen.x) ^ hash<int>{}(hen.y); }
};
}

int main() {
    auto c1 = unordered_map<int, double, hash<int>, equal_to<int> >{};

    auto c = unordered_map<Hen, double>{
        {{1, 2}, 1.1}, {{2, 3}, 2.1}, {{3, 4}, 3.1}, {{4, 5}, 4.1},
    };

    c[{5, 6}] = 5.1;

    auto k = Hen{6, 7};
    c[k] = 6.1;

    c.emplace(Hen{7, 8}, 7.1);

    for (auto& v : c) {
        cout << v.first.x << " " << v.first.y << " " << v.second << endl;
    }
    return 0;
}
