#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

class Object
{
public:
    int x, y, z;
    Object(int a, int b, int c): x(a), y(b), z(c) {
    }
};
bool operator < (const Object &t1, const Object &t2)
{
    return t1.z < t2.z;
}
bool operator > (const Object &t1, const Object &t2)
{
    return t1.z > t2.z;
}

int main() {
    priority_queue<int> q;                                          // default big first
    q.push(4);
    q.push(7);
    cout << q.empty() << endl;                                      // false
    cout << q.size() << endl;                                       // 2
    cout << q.top() << endl;                                        // 7
    q.pop();
    cout << q.empty() << endl;                                      // false
    cout << q.size() << endl;                                       // 1
    cout << q.top() << endl;                                        // 4
    q.pop();
    cout << q.empty() << endl;                                      // true
    cout << q.size() << endl;                                       // 0


    priority_queue<int, vector<int>, greater<int> > q1;             // small first
    q1.push(4);
    q1.push(7);
    cout << q1.empty() << endl;                                     // false
    cout << q1.size() << endl;                                      // 2
    cout << q1.top() << endl;                                       // 4
    q1.pop();
    cout << q1.empty() << endl;                                     // false
    cout << q1.size() << endl;                                      // 1
    cout << q1.top() << endl;                                       // 7
    q1.pop();
    cout << q1.empty() << endl;                                     // true
    cout << q1.size() << endl;                                      // 0


    priority_queue<Object, vector<Object>, greater<Object> > q3;    // small first
    q3.push(Object(3, 3, 6));
    q3.push(Object(4, 4, 3));
    q3.push(Object(1, 5, 4));
    q3.push(Object(2, 2, 5));
    while (!q3.empty())
    {
        Object t = q3.top();
        q3.pop();
        cout << t.x << " " << t.y << " " << t.z << endl;
    }
    return 0;
}