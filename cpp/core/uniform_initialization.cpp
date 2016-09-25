#include <iostream>
#include <ostream>
#include <algorithm>
#include <type_traits>
#include <functional>
#include <string>
#include <memory>
using namespace std;

/**
* uniform initialization
*/

int main() {
    int i{123};
    double d{1.2};
    // int i{1.23};		                                    // do not implicit conversion, compile error
    vector<int> v{1, 2, 3};
    vector<vector<int>> matrix{{9,9,4},
                               {6,6,8},
                               {2,1,1}};
    return 0;
}