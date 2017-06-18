#include <iostream>
#include <string>
#include <valarray>

using namespace std;

/**
 * It supports element-wise mathematical operations and various forms of generalized subscript operators,
 * slicing and indirect access.
 */

int main() {
    valarray<int> a{0, 1, 2}, b{3, 4, 5}, c;
    a = std::pow(a, 2);
    c = a + b;
    c *= 2;
    cout << a.min() << " " << b.max() << " " << c.sum() << endl;

    b = c.apply([](int x) { return x + 3; });

    for (auto i : b) cout << i << " ";
    cout << endl;

    valarray<int> d{1, 2, 3, 4, 5, 6, 7, 8, 9};
    // slice(start, size, stride) extract data[start + (size-1)*stride]
    valarray<int> d1(d[std::slice(0, 4, 2)]);  // get four even index elements
    for (auto i : d1) cout << i << " ";
    cout << endl;  // [1 3 5 7]

    // mask_array
    d[d % 2 == 0] = -1;  // mark all even element to -1
    for (auto i : d) cout << i << " ";
    cout << endl;

    // indirect_array
    std::valarray<std::size_t> idx = {0, 2, 4, 6, 8};
    d[idx] *= d[idx];  // power those data
    for (auto i : d) cout << i << " ";
    cout << endl;
    return 0;
}
