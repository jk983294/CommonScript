#include <iostream>
#include <cstring>

using namespace std;

class X {
public:
    X(){}
    virtual ~X(){}
    void *operator new (size_t size){
        cout << size << " (new)" << endl;
        void *p = ::operator new (size);            // global new
        memset(p, 0, size);
        return p;
    }

    void operator delete(void * addr, size_t size){
        cout << size << " (delete)" << endl;
        ::operator delete (addr);
    }
public:
    int i[100];
};

class Y : public X {
    int j[100];
};

int main() {
    X *x = new X;                                   // 404 (new) because v_table ptr
    delete x;

    X *x1 = new Y;                                  // 804 (new) because v_table ptr
    delete x1;
    return 0;
}