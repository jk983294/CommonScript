#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    vector<int> foo, bar;
    for (int i = 1; i <= 5; i++) {
        foo.push_back(i);
        bar.push_back(i * 10);
    }

    std::copy(bar.begin(), bar.end(), back_inserter(foo));

    cout << "foo contains:";  // 1 2 3 4 5 10 20 30 40 50
    for (vector<int>::iterator it = foo.begin(); it != foo.end(); ++it) {
        cout << ' ' << *it;
    }
    cout << '\n';
    return 0;
}
