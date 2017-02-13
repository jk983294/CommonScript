#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    queue<int> s;
    s.push(4);
    s.push(7);
    cout << s.empty() << endl;                  // false
    cout << s.size() << endl;                   // 2
    cout << s.front() << endl;                  // 4
    cout << s.back() << endl;                   // 7
    s.pop();
    cout << s.empty() << endl;                  // false
    cout << s.size() << endl;                   // 1
    cout << s.front() << endl;                  // 7
    cout << s.back() << endl;                   // 7
    s.pop();
    cout << s.empty() << endl;                  // true
    cout << s.size() << endl;                   // 0
    return 0;
}