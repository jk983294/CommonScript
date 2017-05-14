#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

int main() {
    std::list<int> foo, bar;
    for (int i = 1; i <= 5; i++) {
        foo.push_back(i);
        bar.push_back(i * 10);
    }

    std::list<int>::iterator it = foo.begin();
    advance(it, 3);

    std::copy(bar.begin(), bar.end(), std::inserter(foo, it));

    std::cout << "foo contains:";  // 1 2 3 10 20 30 40 50 4 5
    for (std::list<int>::iterator it = foo.begin(); it != foo.end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
    return 0;
}
