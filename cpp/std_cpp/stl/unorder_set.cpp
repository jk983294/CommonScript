#include <iostream>
#include <unordered_set>

using namespace std;

void delete_demo() {
    unordered_set<int> s;
    unordered_set<int>::iterator first;
    unordered_set<int>::iterator second;
    for (int i = 1; i <= 10; ++i) {
        s.insert(i);
    }

    // delete by iterator
    cout << "going to delete first element which is " << *s.begin() << endl;
    s.erase(s.begin());
    // delete by value
    cout << "going to delete key 8" << endl;
    s.erase(8);
    cout << "elements in unordered_set: ";
    for (unordered_set<int>::const_iterator iter = s.begin(); iter != s.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;
}

int main() {
    cout << boolalpha;
    unordered_set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(1);
    s.insert(4);
    s.insert(5);
    cout << s.size() << endl;
    cout << "number 1 occurrence time: " << s.count(1) << endl;
    cout << "number 1 occurrence time: " << s.count(9) << endl;

    // query
    unordered_set<int>::iterator iter;
    if ((iter = s.find(2)) != s.end()) {
        cout << *iter << endl;
    }

    // insertion
    pair<unordered_set<int>::iterator, bool> insertion_result;
    insertion_result = s.insert(2);
    if (!insertion_result.second) {
        cout << "insertion failed, key 2 already exists" << endl;
    }
    insertion_result = s.insert(6);
    if (insertion_result.second) {
        cout << "insertion success. inserted key is " << *insertion_result.first << endl;
    }
    // range insert
    int a[] = {1, 2, 6, 7, 10, 11};
    s.insert(a, a + 6);

    s.clear();
    if (s.empty()) {
        cout << "unordered_set is empty!" << endl;
    }
    cout << s.size() << endl;

    delete_demo();
    return 0;
}
