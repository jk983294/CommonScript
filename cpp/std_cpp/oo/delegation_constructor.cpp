#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;

/**
* delegation constructor
*/

class Meow {
public:
    //Meow() : m_n(1), m_x(2), m_d(1.2), m_s("a"){}
    Meow() : Meow(1, 2, 1.2, "a"){}
    //explicit Meow(int n) : m_n(n), m_x(n), m_d(1.2), m_s("a"){}
    explicit Meow(int n) : Meow(n, n, 1.2, "a"){
        cout << "explicit Meow(int n) : Meow(n, n, 1.2, \"a\")" << endl;
    }
    Meow(int n, int x, double d, const string& s) : m_n(n), m_x(x), m_d(d), m_s(s){
        cout << "Meow(int n, int x, double d, const string& s) : m_n(n), m_x(x), m_d(d), m_s(s)" << endl;
    }
private:
    int m_n;
    int m_x;
    double m_d;
    string m_s;
};


int main() {
    Meow m1;
    Meow m2(9);
    Meow(1, 1, 1.2, "sdf");
    return 0;
}