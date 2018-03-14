#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * mutable = const = thread safe, bitwise const or internally synchronized, like std::mutex
 * mutable is just as good as const
 */

class ClxTest {
public:
    ClxTest() : m_iTimes(0){};
    void Output() const {
        cout << "try to change something in const function" << endl;
        m_iTimes++;
    }
    int GetOutputTimes() const { return m_iTimes; }

private:
    mutable int m_iTimes;  // mutable can break const keyword
};

int main() {
    /**
     * default lambda function is const, so use mutable to indicate it is not const
     * void f() const {}
     */
    vector<string> v = {"a", "b", "c"};
    int count = 0;
    string suffix = "!";
    auto f = [suffix, count](const string& str) mutable -> string {
        count++;
        return str + suffix;
    };

    transform(v.begin(), v.end(), v.begin(), f);

    for (auto i = v.begin(); i < v.end(); ++i) {
        cout << *i << endl;
    }

    ClxTest clxTest;
    cout << clxTest.GetOutputTimes() << endl;
    clxTest.Output();
    cout << clxTest.GetOutputTimes() << endl;
    return 0;
}
