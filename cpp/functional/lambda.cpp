#include <iostream>
#include <algorithm>
#include <bits/stream_iterator.h>

using namespace std;

/*
 * [capture][parameters]->return type { body }
 * []                   no capture
 * [=]                  all by value
 * [&]                  all by reference
 * [=, &y]              all by value, y by reference
 * [&, x]               all by reference, x by value
 * [=, &x, &y]          all by value, x and y by reference
 * [&x, y]              only x by reference, y by value
 */

void capture_local_variable_demo(){
    vector<int> v{1,3,5,7,9,2,4,6,8,10};
    int count = 0;
    for_each(v.begin(), v.end(), [&count](int n){
        if(n % 2 == 0) count++;
    });
    cout << "even number count is " << count << endl;
}


int main() {
    auto f = [] { cout << "hi" << endl; };
    vector<int> v{1,3,5,7,9,2,4,6,8,10};
    for_each(v.begin(), v.end(), [](int& x){ ++x; });
    ostream_iterator<int> os(cout);
    copy_if(v.begin(), v.end(), os, [](int x){ return x > 5; });

    auto foo = []{ return true; };
    auto bar = [](int a, int b) -> int {
        return a > b ? a : b;
    };
    cout<< foo() << endl;
    cout<< bar(1, 2) << endl;


    capture_local_variable_demo();

    return 0;
}