#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>
#include <initializer_list>
using namespace std;

/**
* uniform initialization
*/

class Base {
public:
    Base(): i(0){};
    explicit Base(int _i): i(_i){};
    Base(const Base& b): i(b.i){};
    Base& operator=(const Base& d){
        if (this == &d) return *this;
        i = d.i;
        return *this;
    };
public:
    int i;
};

int sum1(std::initializer_list<int> numbers){
    int total = 0;
    for(auto i = numbers.begin(); i != numbers.end(); i++)
        total += *i;
    return total;
}

int main() {
    int i{123};
    double d{1.2};
    // int i{1.23};		                                    // do not implicit conversion, compile error
    vector<int> v{1, 2, 3};
    vector<vector<int>> matrix{{9,9,4},
                               {6,6,8},
                               {2,1,1}};
    Base array[] = { Base(0), Base(1), Base(2) };
    cout << sum1( { 1, 2, 3, 4, 5 } ) << endl;
    return 0;
}