#include <iostream>
#include <set>

using namespace std;

void delete_demo(){
    set<int> s;
    set<int>::iterator first;
    set<int>::iterator second;
    for(int i = 1 ; i <= 10 ; ++i) {
        s.insert(i);
    }
    // first kind of delete
    s.erase(s.begin());
    // second kind of delete
    first = s.begin();
    second = s.begin();
    second++;
    second++;
    s.erase(first,second);                              // [2, 4)
    // third kind of delete
    s.erase(8);
    cout<<"elements in set: ";
    for(set<int>::const_iterator iter = s.begin() ; iter != s.end() ; ++iter) {
        cout << *iter << " ";
    }
    cout << endl;
}

void bound_demo(){
    set<int> s;
    for (int i=1; i<10; i++) s.insert(i*10);            // 10 20 30 40 50 60 70 80 90
    std::set<int>::iterator itlow = s.lower_bound (30);
    std::set<int>::iterator itup = s.upper_bound (60);
    s.erase(itlow,itup);                                // 10 20 70 80 90
}

int main()
{
    cout<<boolalpha;
    set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(1);
    s.insert(4);
    s.insert(5);
    cout << s.size() << endl;
    cout << s.max_size() << endl;
    cout << *s.begin() << endl;
    cout << *s.end() << endl;
    cout <<"number 1 occurrence time: " << s.count(1) << endl;
    cout <<"number 1 occurrence time: " << s.count(9) << endl;

    cout << endl;
    pair<set<int>::const_iterator,set<int>::const_iterator> pr;
    pr = s.equal_range(3);
    cout << "first number equal to 3 is " << *pr.first << endl;
    cout << "first number bigger than 3 is " << *pr.second << endl;

    pr = s.equal_range(6);
    cout << "cannot find first number equal to 6 : " << (pr.first == s.end()) << endl;
    cout << "cannot find first number bigger than 6 : " << (pr.second == s.end()) << endl;

    // query
    set<int>::iterator iter;
    if((iter = s.find(2)) != s.end()) {
        cout << *iter << endl;
    }
    /**
     * lower_bound return first iterator which value is >= key
     * upper_bound return first iterator which value is <= key
     */
    cout << *s.lower_bound(2) << endl;                  // 2
    cout << *s.lower_bound(-1) << endl;                 // 1
    cout << *s.upper_bound(3) << endl;                  // 4
    cout << *s.upper_bound(-1) << endl;                 // 1
    bound_demo();

    // insertion
    pair<set<int>::iterator,bool> insertion_result;
    insertion_result = s.insert(2);
    if(!insertion_result.second) {
        cout << "insertion failed." << endl;
    }
    insertion_result = s.insert(6);
    if(insertion_result.second) {
        cout << "insertion success. value is " << *pr.first << endl;
    }
    // range insert
    int a[] = {1, 2, 6, 7, 10, 11};
    s.insert(a, a + 6);


    s.clear();
    if(s.empty()) {
        cout << "set is empty!" << endl;
    }
    cout << s.size() << endl;
    cout << s.max_size() << endl;

    delete_demo();
    return 0;
}