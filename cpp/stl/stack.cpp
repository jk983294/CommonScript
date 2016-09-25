#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    stack<int> s;
    s.push(4);
    s.push(7);
    cout << s.empty() << endl;                  // false
    cout << s.size() << endl;                   // 2
    cout << s.top() << endl;                    // 7
    s.pop();
    cout << s.empty() << endl;                  // false
    cout << s.size() << endl;                   // 1
    cout << s.top() << endl;                    // 4
    s.pop();
    cout << s.empty() << endl;                  // true
    cout << s.size() << endl;                   // 0
    return 0;
}