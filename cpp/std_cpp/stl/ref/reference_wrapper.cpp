#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

// frequently used as a mechanism to store references inside standard containers (like std::vector)
// which cannot normally hold references.

int main() {
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);

    std::vector<std::reference_wrapper<int>> v(l.begin(), l.end());
    std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});

    std::cout << "Contents of the list: ";
    for (int n : l) std::cout << n << ' ';
    std::cout << '\n';

    std::cout << "Contents of the list, as seen through a shuffled vector: ";
    for (int i : v) std::cout << i << ' ';
    std::cout << '\n';

    std::cout << "Doubling the values in the initial list...\n";
    for (int& i : l) {
        i *= 2;
    }

    std::cout << "Contents of the list, as seen through a shuffled vector: ";
    for (int i : v) std::cout << i << ' ';
    std::cout << '\n';
}
