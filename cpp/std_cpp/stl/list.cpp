#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

void print_list(list<int>& a1) {
    list<int>::iterator it;
    for (it = a1.begin(); it != a1.end(); ++it) {
        cout << *it << "\t";
    }
    cout << endl;
}

void init() {
    list<int> l0;
    list<int> l1(3);  // {0, 0, 0}
    print_list(l1);
    list<int> l2(5, 2);  // {2, 2, 2, 2, 2}
    print_list(l2);
    list<int> l4(l2);
    list<int> l5(l1.begin(), l1.end());

    l1.assign(5, 3);  // {3, 3, 3, 3, 3}
    print_list(l1);
    l1.assign(++l2.begin(), l2.end());  // {2, 2, 2, 2}
    print_list(l1);

    l0 = l1;
    print_list(l0);  // {2, 2, 2, 2}

    l0.resize(5);     // {2, 2, 2, 2, 0}
    l0.resize(7, 9);  // {2, 2, 2, 2, 0, 9, 9}
    print_list(l0);

    int ia[] = {0, 7, 3, 11, 5, 9, 4, 2, 8};
    list<int> l6(ia, ia + 9);
    print_list(l6);
}

void iterator_usage() {
    int ia[] = {0, 7, 3, 11, 5, 9, 4, 2, 8};
    list<int> l(ia, ia + 9);
    cout << l.front() << endl;
    cout << l.back() << endl;
    cout << *l.begin() << endl;
    cout << *(--l.end()) << endl;

    for (list<int>::const_iterator cii = l.begin(); cii != l.end(); cii++) {
        cout << *cii << "\t";
    }
    cout << endl;
    for (list<int>::reverse_iterator rii = l.rbegin(); rii != l.rend(); ++rii) {
        cout << *rii << "\t";
    }
    cout << endl;
}

bool myFun(const int& value) { return (value < 2); }

void crud() {
    int ia[] = {1, 2, 3};
    list<int> l(begin(ia), end(ia));

    l.push_back(4);   // {1, 2, 3, 4}
    l.push_front(0);  // {0, 1, 2, 3, 4}
    l.pop_back();     // {0, 1, 2, 3}
    l.pop_front();    // {1, 2, 3}
    print_list(l);

    l.erase(l.begin());             // {2, 3}
    l.erase(++l.begin(), l.end());  // {2}
    print_list(l);
    l.clear();  // {}

    int ia1[] = {4, 1, 2, 3, 4, 5, 5};
    list<int> l1(begin(ia1), end(ia1));

    l1.remove(4);  // {1, 2, 3, 5, 5}
    print_list(l1);
    l1.remove_if(myFun);  // { 2, 3, 5, 5 }
    print_list(l1);

    cout << l1.empty() << endl;
    cout << l1.size() << endl;
    cout << l1.max_size() << endl;

    l1.reverse();  // {5, 5, 3, 2 }
    print_list(l1);
    l1.swap(l);  // {}, {5, 5, 3, 2 }
    print_list(l1);
    print_list(l);

    l.unique();  // {5, 3, 2 }
    print_list(l);
}

void sort_list() {
    int ia1[] = {4, 1, 2, 3, 5};
    list<int> l1(ia1, ia1 + 5);
    l1.sort();
    print_list(l1);  // {1, 2, 3, 4, 5}
    l1.sort(greater<int>());
    print_list(l1);  // {5, 4, 3, 2, 1}
}

void merge_list() {
    list<int> list1{5, 3, 1};
    list<int> list2{6, 2, 4};
    list2.merge(list1);  // {}, {5, 3, 1, 6, 2, 4}
    print_list(list1);
    print_list(list2);

    list<int> list3{3, 2, 1};
    list<int> list4{6, 5, 4};
    list3.merge(list4, greater<int>());  // {3, 2, 1, 6, 5, 4}, {}
    print_list(list3);
    print_list(list4);

    list<int> list5{3, 2, 1};
    list<int> list6{6, 5, 4};
    auto it = list5.begin();
    advance(it, 2);
    list5.splice(it, list6);  // {3, 2, 6, 5, 4, 1}, {}
    print_list(list5);
    print_list(list6);
    it = list5.begin();
    advance(it, 3);
    list6.splice(list6.begin(), list5, it);  // {3, 2, 6, 4, 1}, {5}
    print_list(list5);
    print_list(list6);
    it = list5.begin();
    advance(it, 3);
    list6.splice(list6.begin(), list5, it, list5.end());  // {3, 2, 6}, { 4, 1, 5}
    print_list(list5);
    print_list(list6);
    // splice(target iterator, source list, source list begin iterator, source list end iterator)
}

void insert_list() {
    list<int> list1{1, 2, 3};
    list<int> list2{6, 2, 4};
    list1.insert(++list1.begin(), 9);  // {1, 9, 2, 3}
    print_list(list1);
    list1.insert(list1.begin(), 2, 3);  // {3, 3, 1, 9, 2, 3}
    print_list(list1);
    list1.insert(list1.begin(), list2.begin(), list2.end());  // {6, 2, 4, 3, 3, 1, 9, 2, 3}
    print_list(list1);
}

void insert_sorted_list() {
    list<int> list1{1, 2, 2, 3};
    list1.insert(std::lower_bound(list1.begin(), list1.end(), 2), 2);  // {1, 2, 2, 2, 3}
    print_list(list1);
    list1.insert(std::lower_bound(list1.begin(), list1.end(), 9), 9);  // {1, 2, 2, 2, 3, 9}
    print_list(list1);
    list1.insert(std::lower_bound(list1.begin(), list1.end(), -1), -1);  // {-1, 1, 2, 2, 2, 3, 9}
    print_list(list1);

    list<int> list2{1, 2, 2, 3};
    list2.insert(std::lower_bound(list2.begin(), list2.end(), 2), 2);  // {1, 2, 2, 2, 3}
    print_list(list2);
    list2.insert(std::lower_bound(list2.begin(), list2.end(), 9), 9);  // {1, 2, 2, 2, 3, 9}
    print_list(list2);
    list2.insert(std::lower_bound(list2.begin(), list2.end(), -1), -1);  // {-1, 1, 2, 2, 2, 3, 9}
    print_list(list2);
}

int main() {
    init();
    iterator_usage();
    crud();
    sort_list();
    merge_list();
    insert_list();
    insert_sorted_list();
    return 0;
}
