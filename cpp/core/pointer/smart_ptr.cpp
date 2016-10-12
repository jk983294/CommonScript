#include <iostream>
#include <memory>
#include <vector>
#include <cstring>

using namespace std;

unique_ptr<int> clone(int p) {
    unique_ptr<int> pInt(new int(p));
    return pInt;
}

void unique_ptr_demo(){
    unique_ptr<int> fPtr1;
    unique_ptr<int> fPtr2(new int(4));
    unique_ptr<int> fPtr3(new int(5));

    cout << "fPtr2 release before: " << fPtr2.get() << endl;
    int *pF = fPtr2.release();
    cout << "fPtr2 release before: " << fPtr2.get() << " and pF value: " << *pF << endl;
    cout << "move before fPtr1 address: " << fPtr1.get() << " fPtr3 address: " << fPtr3.get() << endl;
    fPtr1 = move(fPtr3);
    cout << "move after fPtr1 address: " << fPtr1.get() << " fPtr3 address: " << fPtr3.get() << endl;
    fPtr1.reset();
    cout << "move after fPtr1 address: " << fPtr1.get() << endl;

    unique_ptr<int> pInt(new int(5));
    cout << *pInt << endl;
    // unique_ptr<int> pInt2(pInt);                             // cannot copy
    // unique_ptr<int> pInt3 = pInt;                            // cannot assign
    unique_ptr<int> pInt2 = move(pInt);                         // transfer custody
    //cout << *pInt << endl;                                    // error£¬original pInt is nullptr
    cout << *pInt2 << endl;

    int p = 5;
    unique_ptr<int> ret = clone(p);
    cout << *ret << endl;

    // manage array
    unique_ptr<int[]> pArray(new int[5] {1, 2, 3, 4, 5});
    pArray[0] = 0;

    // manage point array
    vector<unique_ptr<int>> vec;
    unique_ptr<int> p1(new int(5));
    vec.push_back(move(p1));
}

class A;
class B;

class A {
public:
    weak_ptr<B> b;
    ~A () {
        cout<< "A released" << endl;
    }

};

class B {
public:
    weak_ptr<A> a;
    ~B () {
        cout<< "B released" << endl;
    }

    void output () {
        cout<< "I'm B" << endl;
    }
};

template <typename T>
shared_ptr<T> make_shared_array(size_t size) {
    return shared_ptr<T>(new T[size], default_delete<T[]>());
}

void shared_ptr_demo(){
    auto sp_array = make_shared_array<char>(100);
    strcpy(sp_array.get(), "hello smart pointer");
    sp_array.get()[0] = 'a';
    cout << sp_array << endl;

    shared_ptr<A> a(new A());
    shared_ptr<B> b(new B());

    a->b = b;
    b->a = a;

    if(a->b.expired()){
        // because weak_ptr doesn't overload operator * and ->, so get shared_ptr from weak_ptr to handle data
        shared_ptr<B> b2(a->b.lock());
        b2->output();
    }
}


int main() {
    unique_ptr_demo();
    shared_ptr_demo();
    // weak_ptr won't add reference count of shared_ptr, used in cyclic reference
    return 0;
}