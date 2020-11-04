#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

template <typename Type>
inline std::ostream& operator<<(std::ostream& os, const set<Type>& _set) {
    for (auto itr = _set.begin(); itr != _set.end(); itr++) os << *itr << " ";
    return os;
}

template <typename Type>
inline std::ostream& operator<<(std::ostream& os, const vector<Type>& v) {
    for (auto itr = v.begin(); itr != v.end(); itr++) os << *itr << " ";
    return os;
}
template <typename Type>
inline std::ostream& operator<<(std::ostream& os, const vector<vector<Type> >& v) {
    if (v == nullptr) return os;
    for (auto itr = v.begin(); itr != v.end(); itr++) os << *itr << " ";
    return os;
}

void functor_demo() {
    cout << endl << "functor demo :" << endl;
    greater<int> ig;
    cout << ig(4, 6) << endl;
    cout << greater<int>()(6, 4) << endl;
}
void sort_algorithm_demo() {
    cout << endl << "sort algorithm demo :" << endl;
    int ia[] = {0, 7, 3, 11, 5, 9, 4, 2, 8};
    vector<int> iv(ia, ia + 9);
    vector<int> iv1(9, 0);
    vector<int>::iterator itr;
    cout << iv << endl;

    //内部采用堆算法，保证前面的[first, middle)有序
    partial_sort(iv.begin(), iv.begin() + 5, iv.end());
    partial_sort_copy(iv.begin(), iv.end(), iv1.begin(), iv1.begin() + 4, greater<>());
    cout << "partial sort: " << iv << endl << "partial sort copy: " << iv1 << endl;
    sort(iv.begin(), iv.end());
    cout << "sort from small to big : " << iv << endl;
    sort(iv.begin(), iv.end(), greater<>());
    cout << "sort from big to small : " << iv << endl;

    int ia1[] = {1, 3, 5, 7, 2, 4, 6, 8, 10};
    vector<int> iv2(ia1, ia1 + 9);
    vector<int> iv3(ia1, ia1 + 9);
    // merge [first, middle) + [middle, end) => [first, end)
    inplace_merge(iv2.begin(), iv2.begin() + 4, iv2.end());
    cout << "inplace merge: " << iv2 << endl;
    // 使第n大元素处于第n位置, 并且比这个元素小的元素都排在这个元素之前, 比这个元素大的元素都排在这个元素之后,
    // 但不能保证他们是有序的
    nth_element(iv3.begin(), iv3.begin() + 5, iv3.end());
    cout << "nth element: " << iv3 << endl << "5th element: " << *(iv3.begin() + 5) << endl;
}
void sorted_array_search() {
    cout << endl << "sorted array search :" << endl;
    int ia[] = {0, 1, 3, 4, 4, 4, 4, 5, 8, 11};
    vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));
    vector<int>::iterator itr;
    cout << iv << endl;
    itr = lower_bound(iv.begin(), iv.end(), 8);
    cout << "lower bound: " << *itr << endl;
    itr = upper_bound(iv.begin(), iv.end(), 8);
    cout << "upper bound: " << *itr << endl;
    cout << "binary search: " << binary_search(iv.begin(), iv.end(), 6) << endl;
    vector<int>::iterator lowerb, upperb;
    // equal_range()返回first和last之间等于val的元素区间.返回值是一对迭代器
    pair<vector<int>::iterator, vector<int>::iterator> rst = equal_range(iv.begin(), iv.end(), 4);
    lowerb = rst.first;
    upperb = rst.second;
    cout << "equal range: " << *lowerb << " " << *upperb << endl;
}

void pure_numeric_algorithm() {
    cout << endl << "pure numeric algorithm :" << endl;
    int ia[11] = {0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8};
    vector<int> iv(ia, ia + 11);      // {0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8}
    vector<int> iv2(ia + 6, ia + 8);  // {6, 6}
    vector<int>::iterator itr;
    // 找到相邻元素相等的第一个元素
    itr = adjacent_find(iv.begin(), iv.end(), equal_to<>());
    cout << "adjacent find: " << *itr << endl;
    // 找到元素值等于6的个数
    cout << "count: " << count(iv.begin(), iv.end(), 6) << endl;
    // 找到小于7的元素个数
    cout << "count if: " << count_if(iv.begin(), iv.end(), bind2nd(less<int>(), 7)) << endl;
    // 找到元素等于4的第一个元素位置
    itr = find(iv.begin(), iv.end(), 4);
    cout << "find: " << *itr << endl;
    // 找到元素大于2的第一个元素位置
    itr = find_if(iv.begin(), iv.end(), bind2nd(greater<int>(), 2));
    cout << "find if: " << *itr << endl;
    // 找到iv序列中最后子序列匹配出现的位置
    itr = find_end(iv.begin(), iv.end(), iv2.begin(), iv2.end());
    cout << "find end: " << itr - iv.begin() << endl;
    // 找到iv序列中最先子序列匹配出现的位置
    itr = find_first_of(iv.begin(), iv.end(), iv2.begin(), iv2.end());
    cout << "find first of: " << itr - iv.begin() << endl;
    // 删除元素，向前移，但是容器size不变，后面会剩余数据
    remove(iv.begin(), iv.end(), 6);
    cout << "remove: " << iv << endl;
    vector<int> iv3(12, -1);
    // 删除元素，将数据拷贝到新容器，后面会剩余数据
    remove_copy(iv.begin(), iv.end(), iv3.begin(), 6);
    cout << "remove copy: " << iv3 << endl;
    // 删除小于6的元素，后面会剩余数据
    remove_if(iv.begin(), iv.end(), bind2nd(less<int>(), 6));
    cout << "remove if: " << iv << endl;
    // 删除小于7的元素，并拷贝到新容器
    remove_copy_if(iv.begin(), iv.end(), iv3.begin(), bind2nd(less<int>(), 7));
    cout << "remove copy if: " << iv3 << endl;
    // 将所有元素值为6的改为3
    replace(iv.begin(), iv.end(), 6, 3);
    cout << "replace: " << iv << endl;
    // 将所有元素值为3的改为5，结果保存在新容器中
    replace_copy(iv.begin(), iv.end(), iv3.begin(), 3, 5);
    cout << "replace copy: " << iv3 << endl;
    // 将所有元素值小于5的改为2
    replace_if(iv.begin(), iv.end(), bind2nd(less<int>(), 5), 2);
    cout << "replace if: " << iv << endl;
    // 将所有元素值为8的改为9，结果保存在新容器中
    replace_copy_if(iv.begin(), iv.end(), iv3.begin(), bind2nd(equal_to<int>(), 8), 9);
    cout << "replace copy if: " << iv3 << endl;
    // 反转
    reverse(iv.begin(), iv.end());
    cout << "reverse: " << iv << endl;
    // 反转，结果保存在新容器
    reverse_copy(iv.begin(), iv.end(), iv3.begin());
    cout << "reverse copy: " << iv3 << endl;
    // 互换元素,  [first, middle, last) => [middle, last -1, first, middle - 1], array << shift operator
    rotate(iv.begin(), iv.begin() + 4, iv.end());
    cout << "rotate: " << iv << endl;
    // 互换元素，结果保存在新容器
    rotate_copy(iv.begin(), iv.begin() + 5, iv.end(), iv3.begin());
    cout << "rotate copy: " << iv3 << endl;
    vector<int> iv4 = {2, 8};
    // 查找子序列出现的第一次出现地点
    cout << "search:  " << *search(iv.begin(), iv.end(), iv4.begin(), iv4.end()) << endl;
    // 按区域交换, iv4 <=> iv
    swap_ranges(iv4.begin(), iv4.end(), iv.begin());
    cout << "swap ranges:  " << iv << endl << iv4 << endl;
    // 所有元素减2, iv -2 => iv
    transform(iv.begin(), iv.end(), iv.begin(), bind2nd(minus<int>(), 2));
    cout << "transform:  " << iv << endl;
    // 区间对应元素相加, iv4 + iv => iv4
    transform(iv4.begin(), iv4.end(), iv.begin(), iv4.begin(), plus<>());
    cout << "transform:  " << iv4 << endl;
    /************************************************************************/
    vector<int> iv5(ia, ia + 11);
    vector<int> iv6(ia + 4, ia + 8);
    vector<int> iv7(15);
    // 最大元素游标
    cout << "max element:  " << *max_element(iv5.begin(), iv5.end()) << endl;
    cout << "min element:  " << *min_element(iv5.begin(), iv5.end()) << endl;
    // iv6中元素是不是都在iv5中，这两个必须排过序
    cout << "includes:  " << includes(iv5.begin(), iv5.end(), iv6.begin(), iv6.end()) << endl;
    // 两个排序号的容器合并, iv5 + iv6 => iv7
    merge(iv5.begin(), iv5.end(), iv6.begin(), iv6.end(), iv7.begin());
    cout << "merge:  " << iv7 << endl;
    // 满足条件的放在左边，不满足条件的放在右边
    partition(iv7.begin(), iv7.end(), bind2nd(equal_to<int>(), 5));
    cout << "partition:  " << iv7 << endl;
    // 去重，重复的元素放在后面
    unique(iv5.begin(), iv5.end());
    cout << "unique:  " << iv5 << endl;
    // 去重，结果保存在新容器
    unique_copy(iv5.begin(), iv5.end(), iv7.begin());
    cout << "unique copy:  " << iv7 << endl;
}
void heap_algorithm() {
    cout << endl << "heap algorithm :" << endl;
    int ia1[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    vector<int> iv(ia1, ia1 + 9);
    make_heap(iv.begin(), iv.end(), greater<>());  //默认最大堆,这样就是最小堆
    cout << iv << endl;
    iv.push_back(7);
    push_heap(iv.begin(), iv.end(), greater<>());  //对新加入的元素调整位置
    cout << iv << endl;
    pop_heap(iv.begin(), iv.end(), greater<>());  //堆首删除放到容器尾
    iv.pop_back();
    cout << iv << endl;
    sort_heap(iv.begin(), iv.end(), greater<>());  //堆排序
    cout << iv << endl;
}
void set_algorithm() {
    cout << endl << "set algorithm :" << endl;
    std::set<int> s1 = {1, 3, 5, 6, 7, 8};
    std::set<int> s2 = {0, 2, 4, 5, 6, 7, 8};
    std::set<int> s3;
    vector<int> s4, s5, s6;
    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(s3, s3.begin()));
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(s4));
    set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(s5));
    set_symmetric_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(s6));
    cout << s1 << endl << s2 << endl << s3 << endl << s4 << endl << s5 << endl << s6 << endl;
}
void basic_algorithm() {
    cout << endl << "basic algorithm :" << endl;
    int ia[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> iv1 = {0, 1, 2, 3, 4};
    vector<int> iv2 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    cout << iv1 << endl << iv2 << endl;
    // 返回在游标的哪个位置不匹配
    pair<vector<int>::iterator, vector<int>::iterator> p = mismatch(iv1.begin(), iv1.end(), iv2.begin());
    if (p.first != iv1.end()) cout << *(p.first) << endl;
    if (p.second != iv2.end()) cout << *(p.second) << endl;

    // 比较容器内内容
    cout << equal(iv1.begin(), iv1.end(), iv2.begin()) << endl;
    cout << equal(iv1.begin(), iv1.end(), iv2.begin() + 4) << endl;
    cout << equal(iv1.begin(), iv1.end(), iv2.begin() + 4, less<>()) << endl;

    // 区间填充
    fill(iv1.begin(), iv1.end(), 9);
    cout << iv1 << endl;
    // 区间n填充
    fill_n(iv1.begin(), 3, 7);
    cout << iv1 << endl;
    vector<int>::iterator iter1, iter2;
    iter1 = iter2 = iv1.begin();
    // 游标移动
    advance(iter2, 3);
    // 交换两个游标内容
    iter_swap(iter1, iter2);
    cout << iv1 << endl;
    // 交换两个游标内容
    swap(*iv1.begin(), *iv2.begin());
    cout << iv1 << endl << iv2 << endl;

    string str_a1[] = {"jk", "jK1", "jk2"};
    string str_a2[] = {"jk", "jk1", "jk3"};
    cout << lexicographical_compare(str_a1, str_a1 + 2, str_a2, str_a2 + 2) << endl;
    cout << lexicographical_compare(str_a1, str_a1 + 2, str_a2, str_a2 + 2, greater<>()) << endl;

    // 全部元素向前移一格
    copy(iv2.begin() + 1, iv2.end(), iv2.begin());
    cout << iv2 << endl;
    // 全部元素向后移一格
    copy_backward(iv2.begin(), iv2.end() - 1, iv2.end());
    cout << iv2 << endl;
}

void stl_numeric_algorithm() {
    double array[] = {-2, 2, 4, 4, 5};
    double array1[] = {2, 3, 4, 5, 6};
    vector<double> a(array, array + sizeof(array) / sizeof(double));
    vector<double> b(array1, array1 + sizeof(array1) / sizeof(double));
    vector<double> result(10);

    // sigma ( -a[i] )
    cout << "accumulate func: " << accumulate(a.begin(), a.end(), 0.0, minus<>()) << endl;
    // sigma ( a[i] * b[i] )
    cout << "inner product func: " << inner_product(a.begin(), a.end(), b.begin(), 0.0, plus<>(), multiplies<>())
         << endl;
    adjacent_difference(a.begin(), a.end(), result.begin());
    // result[i] = a[i] - a[i - 1]
    cout << "adjacent difference : " << result << endl;
    // result[i] = (a[0] + ... + a[i])
    partial_sum(result.begin(), result.end(), result.begin());
    cout << "partial sum : " << result << endl;
    ostream_iterator<double> o(cout, " ");
    copy(result.begin(), result.end(), o);
    cout << endl;
}

void clamp_demo() {
    int v = 168;
    cout << v << " " << std::clamp(v, INT8_MIN, INT8_MAX) << " " << std::clamp(v, 0, UINT8_MAX) << '\n';
    v = -137;
    cout << v << " " << std::clamp(v, INT8_MIN, INT8_MAX) << " " << std::clamp(v, 0, UINT8_MAX) << '\n';
}

/**
 * reduce differ from accumulate is that it can be executed parallel by par policy
 */
void reduce_demo() {
    vector<int> a = {0, 1, 2, 3, 4};
    cout << std::reduce(a.begin(), a.end()) << '\n';     // 10
    cout << std::reduce(a.begin(), a.end(), 0) << '\n';  // 10
    // cout << std::reduce(std::execution::par, a.begin(), a.end(), 0) << '\n'; // 10, need tbb
    cout << std::accumulate(a.begin(), a.end(), 0) << '\n';  // 10
}

void scan_demo() {
    vector<int> data = {0, 1, 2, 3, 4};
    vector<int> result;
    std::cout << "exclusive sum: ";  // 0 0 1 3 6
    std::exclusive_scan(data.begin(), data.end(), std::back_inserter(result), 0);
    for (auto d : result) {
        cout << d << " ";
    }
    cout << '\n';

    std::cout << "\ninclusive sum: ";  // 0 1 3 6 10
    result.clear();
    std::inclusive_scan(data.begin(), data.end(), std::back_inserter(result));
    for (auto d : result) {
        cout << d << " ";
    }
    cout << '\n';
}

int main() {
    cout << boolalpha;
    stl_numeric_algorithm();
    basic_algorithm();
    set_algorithm();
    heap_algorithm();
    pure_numeric_algorithm();
    sorted_array_search();
    sort_algorithm_demo();
    functor_demo();
    clamp_demo();
    reduce_demo();
    scan_demo();
    return 0;
}
