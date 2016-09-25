#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;

/**
* default template type
*/

template <typename T = int> class Blah {};
template <typename T = int> void f(T t){
}

template <typename C, typename F = less<typename C::value_type>> void Sort(C& c, F f = F()){
    sort(c.begin(), c.end(), f);
}
template <typename C> void Print(C& c){
    for (auto& e : c){
        cout << e << " ";
    }
    cout << endl;
}

int main() {
    f(123);

    const int arr[] = { 3, 46, 12, 54, 12};
    vector<int> v(begin(arr), end(arr));
    Print(v);
    Sort(v);
    Print(v);
    Sort(v, greater<int>());
    Print(v);
    return 0;
}