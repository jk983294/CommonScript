#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>

using namespace std;

int main() {
    std::deque<int> foo, bar;
    for (int i = 1; i <= 5; i++) {
        foo.push_back(i);
        bar.push_back(i * 10);
    }

    std::copy(bar.begin(), bar.end(), std::front_inserter(foo));

    std::cout << "foo contains:";  // 50 40 30 20 10 1 2 3 4 5
    for (std::deque<int>::iterator it = foo.begin(); it != foo.end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
    return 0;
}
