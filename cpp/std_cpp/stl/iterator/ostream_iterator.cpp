#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

// ostream iterator write sequentially to an output stream (such as cout, file).

int main() {
    std::vector<int> myvector;
    for (int i = 1; i < 10; ++i) myvector.push_back(i * 10);

    std::ostream_iterator<int> out_it(std::cout, ", ");
    std::copy(myvector.begin(), myvector.end(), out_it);
    return 0;
}
