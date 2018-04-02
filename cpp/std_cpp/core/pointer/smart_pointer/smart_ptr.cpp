#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

/**
 * unique_ptr, exclusively owns object, cannot be copied / assigned, can be moved
 * it is some kind of raw pointer, so you need to deep copy unique_ptr member of a class
 * shared_ptr, reference count, can be copied / assigned, can be moved
 * weak_ptr, circle reference
 * potential use cases for std::weak_ptr include caching, observer lists, and the prevention of std::shared_ptr cycles
 *
 * for observe purpose(no ownership)
 * use weak_ptr for shared_ptr
 * use raw pointer for unique_ptr / solid object
 */

unique_ptr<int> clone(int p) {
    unique_ptr<int> pInt(new int(p));
    return pInt;
}

void destroy_int(int* p) {
    std::cout << "deleting p, value is : " << *p << endl;
    delete p;
}
void unique_ptr_demo() {
    unique_ptr<int, void (*)(int*)> fPtr1(nullptr, destroy_int);
    unique_ptr<int, void (*)(int*)> fPtr2(new int(4), destroy_int);
    unique_ptr<int, void (*)(int*)> fPtr3(new int(5), destroy_int);

    cout << "fPtr2 release before: " << fPtr2.get() << endl;
    int* pF = fPtr2.release();
    cout << "fPtr2 release before: " << fPtr2.get() << " and pF value: " << *pF << endl;
    cout << "move before fPtr1 address: " << fPtr1.get() << " fPtr3 address: " << fPtr3.get() << endl;
    fPtr1 = move(fPtr3);
    cout << "move after fPtr1 address: " << fPtr1.get() << " fPtr3 address: " << fPtr3.get() << endl;
    fPtr1.reset();
    cout << "move after fPtr1 address: " << fPtr1.get() << endl;

    int p = 5;
    unique_ptr<int> ret = clone(p);
    cout << *ret << endl;

    // manage array
    unique_ptr<int[]> pArray(new int[5]{1, 2, 3, 4, 5});
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
    ~A() { cout << "A released" << endl; }
};

class B {
public:
    weak_ptr<A> a;
    ~B() { cout << "B released" << endl; }
    void output() { cout << "I'm B" << endl; }
};

template <typename T>
shared_ptr<T> make_shared_array(size_t size) {
    return shared_ptr<T>(new T[size], default_delete<T[]>());
}

void shared_ptr_demo() {
    shared_ptr<int> sp = shared_ptr<int>(nullptr);
    cout << sp.use_count() << endl;
    cout << sp.unique() << endl;
    sp = make_shared<int>(5);
    cout << sp.use_count() << endl;
    cout << sp.unique() << endl;
    shared_ptr<int> sp1 = sp;
    cout << sp.use_count() << endl;
    cout << sp.unique() << endl;
    cout << (sp == sp1) << endl;

    auto sp_array = make_shared_array<char>(100);
    strcpy(sp_array.get(), "hello smart pointer");
    sp_array.get()[0] = 'a';
    cout << sp_array << endl;
}

void weak_ptr_demo() {
    cout << "weak_ptr_demo" << endl;
    shared_ptr<int> sp = shared_ptr<int>(new int(5));
    weak_ptr<int> wp = weak_ptr<int>(sp);
    cout << "this time not expired " << wp.expired() << endl;
    cout << wp.use_count() << endl;
    if (shared_ptr<int> locked = wp.lock()) {  // get strong reference from weak pointer
        cout << *locked << endl;
    }
    sp = nullptr;
    cout << "this time expired " << wp.expired() << endl;
    cout << wp.use_count() << endl;
    if (shared_ptr<int> locked = wp.lock()) {
        cout << *locked << endl;
    } else {
        wp.reset();  // although manged object is released, this release reference control block
    }

    shared_ptr<A> a(new A());
    shared_ptr<B> b(new B());
    // weak_ptr won't add reference count of shared_ptr, used in cyclic reference
    a->b = b;
    b->a = a;

    if (a->b.expired()) {
        // because weak_ptr doesn't overload operator * and ->, so get shared_ptr from weak_ptr to handle data
        shared_ptr<B> b2(a->b.lock());
        b2->output();
    }
}

auto main() -> int {
    cout << boolalpha;
    unique_ptr_demo();
    shared_ptr_demo();
    weak_ptr_demo();
}
