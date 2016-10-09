#include <iostream>

using namespace std;

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
    friend void print(Base*);
    friend class Printer;
private:
    int i;
};

void print(Base* b){
    cout << b->i << endl;
}

class Printer {
public:
    void print(Base* b){
        cout << b->i << endl;
    }
};

int main() {
    Base n(3);
    print(&n);
    Printer p;
    p.print(&n);
    return 0;
}