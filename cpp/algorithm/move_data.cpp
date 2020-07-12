#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;


void move_demo() {
    vector<int> v1(6);
    iota(v1.begin(), v1.end(), 1);  // 1, 2, 3, 4, 5, 6
    /**
     * 把一部分连续数据挪到上面或者下面, 把2, 3挪下去
     */
    rotate(v1.begin() + 1, v1.begin() + 3, v1.begin() + 5); // rotate(first, middle, last)
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(cout, ", ")); // 1, 4, 5, 2, 3, 6
    cout << endl;

    /**
     * 把不连续数据挪到某位置开始, 把3, 5挪到头部位置，其他数据保持相对位置不变
     */
    iota(v1.begin(), v1.end(), 1);
    stable_partition(v1.begin() + 1, v1.end(), [](int d){ return d == 3 || d == 5; });
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(cout, ", ")); // 1, 3, 5, 2, 4, 6
    cout << endl;

    /**
     * 把不连续数据挪到某位置, 把3, 5挪到尾部位置，其他数据保持相对位置不变
     */
    iota(v1.begin(), v1.end(), 1);
    stable_partition(v1.begin() + 1, v1.end(), [](int d){ return !(d == 3 || d == 5); });
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(cout, ", ")); // 1, 2, 4, 6, 3, 5
    cout << endl;
}


int main() {
    move_demo();
    return 0;
}
