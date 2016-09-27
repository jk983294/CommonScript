#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>
#include <set>
#include <iterator>

using namespace std;

template<typename Type>
inline std::ostream& operator  <<  (std::ostream& os, const set<Type>& _set) {
    for(auto itr = _set.begin(); itr != _set.end(); itr++)
        os << *itr << " ";
    return os;
}

template<typename Type>
inline std::ostream& operator  <<  (std::ostream& os, const vector<Type>& v) {
    for(auto itr = v.begin(); itr != v.end(); itr++)
        os << *itr << " ";
    return os;
}
template<typename Type>
inline std::ostream& operator  <<  (std::ostream& os, const vector< vector<Type> >& v) {
    if(v == nullptr) return os;
    for(auto itr = v.begin(); itr != v.end(); itr++)
        os << *itr << " ";
    return os;
}

void functor_demo(){
    cout << endl << "functor demo :" << endl;
    greater<int> ig;
    cout << ig(4, 6) << endl;
    cout << greater<int>()(6, 4) << endl;
}
void sort_algorithm_demo(){
    cout << endl << "sort algorithm demo :" << endl;
    int ia[] = {0, 7, 3, 11, 5, 9, 4 , 2, 8};
    vector<int> iv(ia, ia + 9);
    vector<int> iv1(9, 0);
    vector<int>::iterator itr;
    cout  <<  iv  <<  endl;

    //�ڲ����ö��㷨����֤ǰ���[first, middle)����
    partial_sort(iv.begin(), iv.begin() + 5, iv.end());
    partial_sort_copy(iv.begin(), iv.end(), iv1.begin(), iv1.begin() + 4, greater<int>());
    cout << "partial sort: " << iv << endl << "partial sort copy: " << iv1 << endl;
    sort(iv.begin(), iv.end());
    cout << "sort from small to big : " << iv << endl;
    sort(iv.begin(), iv.end(), greater<int>());
    cout << "sort from big to small : " << iv << endl;

    int ia1[] = {1, 3,  5, 7, 2, 4, 6 , 8, 10};
    vector<int> iv2(ia1, ia1 + 9);
    vector<int> iv3(ia1, ia1 + 9);
    // merge [first, middle) + [middle, end) => [first, end)
    inplace_merge(iv2.begin(), iv2.begin() + 4, iv2.end());
    cout << "inplace merge: " << iv2 << endl;
    // ʹ��n��Ԫ�ش��ڵ�nλ��, ���ұ����Ԫ��С��Ԫ�ض��������Ԫ��֮ǰ, �����Ԫ�ش��Ԫ�ض��������Ԫ��֮��, �����ܱ�֤�����������
    nth_element(iv3.begin(), iv3.begin() + 5, iv3.end());
    cout << "nth element: " << iv3 << endl << "5th element: " << *(iv3.begin() + 5) << endl;

}
void sorted_array_search(){
    cout << endl << "sorted array search :" << endl;
    int ia[] = {0, 1,  3, 4, 4, 4, 4, 5, 8, 11 };
    vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));
    vector<int>::iterator itr;
    cout << iv << endl;
    itr = lower_bound(iv.begin(), iv.end(), 8);
    cout << "lower bound: " << *itr << endl;
    itr = upper_bound(iv.begin(), iv.end(), 8);
    cout << "upper bound: " << *itr << endl;
    cout << "binary search: " << binary_search(iv.begin(), iv.end(), 6) << endl;
    vector<int>::iterator lowerb, upperb;
    // equal_range()����first��last֮�����val��Ԫ������.����ֵ��һ�Ե�����
    pair<vector<int>::iterator, vector<int>::iterator> rst = equal_range(iv.begin(), iv.end(), 4);
    lowerb = rst.first;
    upperb = rst.second;
    cout << "equal range: " << *lowerb << " " << *upperb << endl;
}

void pure_numeric_algorithm(){
    cout << endl << "pure numeric algorithm :" << endl;
    int ia[11] = {0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8 };
    vector<int> iv(ia, ia + 11);                            // {0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8}
    vector<int> iv2(ia + 6,ia + 8);                         // {6, 6}
    vector<int>::iterator itr;
    // �ҵ�����Ԫ����ȵĵ�һ��Ԫ��
    itr = adjacent_find(iv.begin(), iv.end(), equal_to<int>());
    cout << "adjacent find: " << *itr << endl;
    // �ҵ�Ԫ��ֵ����6�ĸ���
    cout << "count: " << count(iv.begin(), iv.end(), 6) << endl;
    // �ҵ�С��7��Ԫ�ظ���
    cout << "count if: " << count_if(iv.begin(), iv.end(), bind2nd(less<int>(), 7)) << endl;
    // �ҵ�Ԫ�ص���4�ĵ�һ��Ԫ��λ��
    itr = find(iv.begin(), iv.end(), 4);
    cout << "find: " << *itr << endl;
    // �ҵ�Ԫ�ش���2�ĵ�һ��Ԫ��λ��
    itr = find_if(iv.begin(), iv.end(), bind2nd(greater<int>(), 2));
    cout << "find if: " << *itr << endl;
    // �ҵ�iv���������������ƥ����ֵ�λ��
    itr = find_end(iv.begin(), iv.end(), iv2.begin(), iv2.end());
    cout << "find end: " << itr - iv.begin() << endl;
    // �ҵ�iv����������������ƥ����ֵ�λ��
    itr = find_first_of(iv.begin(), iv.end(), iv2.begin(),iv2.end());
    cout << "find first of: " << itr - iv.begin() << endl;
    // ɾ��Ԫ�أ���ǰ�ƣ���������size���䣬�����ʣ������
    remove(iv.begin(), iv.end(), 6);
    cout << "remove: " << iv << endl;
    vector<int> iv3(12,-1);
    // ɾ��Ԫ�أ������ݿ������������������ʣ������
    remove_copy(iv.begin(), iv.end(), iv3.begin(), 6);
    cout << "remove copy: " << iv3 << endl;
    // ɾ��С��6��Ԫ�أ������ʣ������
    remove_if(iv.begin(), iv.end(), bind2nd(less<int>(), 6));
    cout << "remove if: " << iv << endl;
    // ɾ��С��7��Ԫ�أ���������������
    remove_copy_if(iv.begin(), iv.end(), iv3.begin(), bind2nd(less<int>(), 7));
    cout << "remove copy if: " << iv3 << endl;
    // ������Ԫ��ֵΪ6�ĸ�Ϊ3
    replace(iv.begin(), iv.end(), 6, 3);
    cout << "replace: " << iv << endl;
    // ������Ԫ��ֵΪ3�ĸ�Ϊ5�������������������
    replace_copy(iv.begin(), iv.end(), iv3.begin(), 3, 5);
    cout << "replace copy: " << iv3 << endl;
    // ������Ԫ��ֵС��5�ĸ�Ϊ2
    replace_if(iv.begin(), iv.end(), bind2nd(less<int>(),5), 2);
    cout << "replace if: " << iv << endl;
    // ������Ԫ��ֵΪ8�ĸ�Ϊ9�������������������
    replace_copy_if(iv.begin(), iv.end(), iv3.begin(), bind2nd(equal_to<int>(), 8), 9);
    cout << "replace copy if: " << iv3 << endl;
    // ��ת
    reverse(iv.begin(), iv.end());
    cout << "reverse: " << iv << endl;
    // ��ת�����������������
    reverse_copy(iv.begin(), iv.end(), iv3.begin());
    cout << "reverse copy: " << iv3 << endl;
    // ����Ԫ��,  [first, middle, last) => [middle, last -1, first, middle - 1], array << shift operator
    rotate(iv.begin(), iv.begin() + 4, iv.end());
    cout << "rotate: " << iv << endl;
    // ����Ԫ�أ����������������
    rotate_copy(iv.begin(),iv.begin() + 5, iv.end(), iv3.begin());
    cout << "rotate copy: " << iv3 << endl;
    vector<int> iv4 = {2, 8};
    // ���������г��ֵĵ�һ�γ��ֵص�
    cout << "search:  " << *search(iv.begin(), iv.end(), iv4.begin(), iv4.end()) << endl;
    // �����򽻻�, iv4 <=> iv
    swap_ranges(iv4.begin(), iv4.end(), iv.begin());
    cout << "swap ranges:  " << iv << endl << iv4 << endl;
    // ����Ԫ�ؼ�2, iv -2 => iv
    transform(iv.begin(), iv.end(), iv.begin(), bind2nd(minus<int>(), 2));
    cout << "transform:  " << iv << endl;
    // �����ӦԪ�����, iv4 + iv => iv4
    transform(iv4.begin(), iv4.end(), iv.begin(), iv4.begin(), plus<int>());
    cout << "transform:  " << iv4 << endl;
    /************************************************************************/
    vector<int> iv5(ia, ia + 11);
    vector<int> iv6(ia + 4, ia + 8);
    vector<int> iv7(15);
    // ���Ԫ���α�
    cout << "max element:  " << *max_element(iv5.begin(), iv5.end()) << endl;
    cout << "min element:  " << *min_element(iv5.begin(), iv5.end()) << endl;
    // iv6��Ԫ���ǲ��Ƕ���iv5�У������������Ź���
    cout << "includes:  " << includes(iv5.begin(), iv5.end(), iv6.begin(), iv6.end()) << endl;
    // ��������ŵ������ϲ�, iv5 + iv6 => iv7
    merge(iv5.begin(), iv5.end(), iv6.begin(), iv6.end(), iv7.begin());
    cout << "merge:  " << iv7 << endl;
    // ���������ķ�����ߣ������������ķ����ұ�
    partition(iv7.begin(), iv7.end(), bind2nd(equal_to<int>(), 5));
    cout << "partition:  " << iv7 << endl;
    // ȥ�أ��ظ���Ԫ�ط��ں���
    unique(iv5.begin(), iv5.end());
    cout << "unique:  " << iv5 << endl;
    // ȥ�أ����������������
    unique_copy(iv5.begin(), iv5.end(), iv7.begin());
    cout << "unique copy:  " << iv7 << endl;
}
void heap_algorithm(){
    cout << endl << "heap algorithm :" << endl;
    int ia1[9] = {0, 1, 2, 3, 4, 8, 9 , 3 , 5 };
    vector<int> iv(ia1, ia1 + 9);
    make_heap(iv.begin(), iv.end(), greater<int>());		//Ĭ������,����������С��
    cout << iv << endl;
    iv.push_back(7);
    push_heap(iv.begin(), iv.end(), greater<int>());		//���¼����Ԫ�ص���λ��
    cout << iv << endl;
    pop_heap(iv.begin(), iv.end(), greater<int>());			//����ɾ���ŵ�����β
    iv.pop_back();
    cout << iv << endl;
    sort_heap(iv.begin(), iv.end(), greater<int>());        //������
    cout << iv << endl;
}
void set_algorithm(){
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
void basic_algorithm(){
    cout << endl << "basic algorithm :" << endl;
    int ia[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8 };
    vector<int> iv1 = {0, 1, 2, 3, 4};
    vector<int> iv2 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    cout << iv1 << endl << iv2 << endl;
    // �������α���ĸ�λ�ò�ƥ��
    pair<vector<int>::iterator, vector<int>::iterator> p = mismatch(iv1.begin(), iv1.end(), iv2.begin());
    if(p.first != iv1.end())
        cout << *(p.first) << endl;
    if(p.second != iv2.end())
        cout << *(p.second) << endl;

    // �Ƚ�����������
    cout << equal(iv1.begin(), iv1.end(), iv2.begin()) << endl;
    cout << equal(iv1.begin(), iv1.end(), iv2.begin() + 4) << endl;
    cout << equal(iv1.begin(), iv1.end(), iv2.begin() + 4, less<int>()) << endl;

    // �������
    fill(iv1.begin(), iv1.end(), 9);
    cout << iv1 << endl;
    // ����n���
    fill_n(iv1.begin(), 3, 7);
    cout << iv1 << endl;
    vector<int>::iterator iter1, iter2;
    iter1 = iter2 = iv1.begin();
    // �α��ƶ�
    advance(iter2, 3);
    // ���������α�����
    iter_swap(iter1, iter2);
    cout << iv1 << endl;
    // ���������α�����
    swap(*iv1.begin(), *iv2.begin());
    cout << iv1 << endl << iv2 << endl;

    string str_a1[] = {"jk", "jK1", "jk2"};
    string str_a2[] = {"jk", "jk1", "jk3"};
    cout << lexicographical_compare(str_a1, str_a1 + 2, str_a2, str_a2 + 2) << endl;
    cout << lexicographical_compare(str_a1, str_a1 + 2, str_a2, str_a2 + 2, greater<string>()) << endl;

    // ȫ��Ԫ����ǰ��һ��
    copy(iv2.begin() + 1, iv2.end(), iv2.begin());
    cout << iv2 << endl;
    // ȫ��Ԫ�������һ��
    copy_backward(iv2.begin(),iv2.end() - 1,iv2.end());
    cout << iv2 << endl;
}

void stl_numeric_algorithm(){
    double array[] = {-2, 2, 4, 4, 5};
    double array1[] = {2, 3, 4, 5, 6};
    vector<double> a(array, array + sizeof(array) / sizeof(double));
    vector<double> b(array1, array1 + sizeof(array1) / sizeof(double));
    vector<double> result(10);

    // sigma ( -a[i] )
    cout << "accumulate func: " << accumulate(a.begin(), a.end(), 0.0, minus<double>()) << endl;
    // sigma ( a[i] * b[i] )
    cout << "inner product func: " << inner_product(a.begin(), a.end(), b.begin(), 0.0, plus<double>(), multiplies<double>()) << endl;
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

int main()
{
    cout << boolalpha;
    stl_numeric_algorithm();
    basic_algorithm();
    set_algorithm();
    heap_algorithm();
    pure_numeric_algorithm();
    sorted_array_search();
    sort_algorithm_demo();
    functor_demo();
    return 0;
}