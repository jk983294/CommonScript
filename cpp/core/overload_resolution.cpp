#include <vector>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <functional>
#include <string>
#include <memory>
using namespace std;

/**
* overload resolution
*/

void meow(const string&){
	cout<< "const string&" <<endl;
}
void meow(char* arr){
	cout<< "char* arr" <<endl;
}
template <int N> void meow(const char(&arr)[N]){
	cout << "const char(&arr)[N]" <<endl;
}

template <typename T> void foo(const T& t){
	cout << "foo(const T&)" <<endl;
}
template <typename T> void foo(const T*){
	cout << "const T*" <<endl;
}

template <typename T> void helper(const T&, false_type){
	cout << "Not a pointer!" <<endl;
}
template <typename T> void helper(const T&, true_type){
	cout << "I'm a pointer!" <<endl;
}
template <typename T> void bar(const T& t){
	helper(t, typename is_pointer<T>::type());
}

struct Base { };
struct Derived : public Base { };
struct MoreDerived : public Derived { };

void f(Base*){
	cout << "Base*" <<endl;
}
void f(Derived*){
	cout << "Derived*" <<endl;
}
void f(MoreDerived*){
	cout << "MoreDerived*" <<endl;
}
void g(const shared_ptr<Base>&){
	cout << "const shared_ptr<Base>&" <<endl;
}
void g(const shared_ptr<Derived>&){
	cout << "const shared_ptr<Derived>&" <<endl;
}

int main() {
	meow("cat");
	string st("cat");
	meow(st);
	char* ptr = "cat";
	meow(ptr);

	// foo(const T&) => foo(int* const), (int*) convert to (int* const) ahead of (const int*)
	int *p = nullptr;
	foo(p);

	int n = 5;
	int& nRef = n;
	bar(p);
	bar(123);
	bar(nRef);

	MoreDerived *md = nullptr;
	f(md);
	shared_ptr<Derived> spd;

	g(spd);
	shared_ptr<MoreDerived> spmd;
	// g(spmd);							                            // ambiguous
	return 0;
}