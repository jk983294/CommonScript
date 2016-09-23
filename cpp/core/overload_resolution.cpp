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




#include <vector>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <functional>
#include <string>
#include <memory>
using namespace std;

/**
* virtual functions
*/

class Shape {
public:
	Shape(){};
	virtual ~Shape(){}
	virtual void draw(int x, int y){
		cout << "Shape::draw(" <<x << ", " << y << ")" << endl;
	}
	void f(int x, int y){
		cout << "not virtual!!! Shape::f(" <<x << ", " << y << ")" << endl;
		do_f(x, y);
		cout << "bye!" << endl;
	}
private:
	virtual void do_f(int x, int y){
		cout << "Shape::do_f(" <<x << ", " << y << ")" << endl;
	}
	Shape(const Shape&);
	Shape& operator=(const Shape&);
};

class Polygon : public Shape {
public:
	virtual void draw(int x, int y) override {
		cout << "Polygon::draw(" <<x << ", " << y << ")" << endl;
	}
private:
	virtual void do_f(int x, int y){
		cout << "Polygon::do_f(" <<x << ", " << y << ")" << endl;
	}
};

class Evilgon : public Shape {
public:
	// override will fail to compile, because no match virtual function found in base class
	virtual void draw(double x, double y){
		cout << "Evilgon::draw(" <<x << ", " << y << ")" << endl;
	}
private:
	virtual void do_f(int x, int y){
		cout << "Evilgon::do_f(" <<x << ", " << y << ")" << endl;
	}
};

// final prevent this class derived
class Triangle final : public Polygon {
public:
	// final prevent this function override
	virtual void draw(int x, int y) final override {
		cout << "Triangle::draw(" <<x << ", " << y << ")" << endl;
	}
};
/*
class BermudaTriangle : public Triangle {
public:
	virtual void draw(int x, int y) override {
		cout << "BermudaTriangle::draw(" <<x << ", " << y << ")" << endl;
	}
};
/**/

int main() {
	shared_ptr<Shape> p = make_shared<Polygon>();
	p->draw(11, 22);
	p->f(11, 22);

	p = make_shared<Evilgon>();
	p->draw(11.1, 22.2);							        // call base function because function signature not match
	return 0;
}



#include <vector>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <functional>
#include <string>
#include <memory>
using namespace std;

/**
* Specialization
*/

template <typename T> struct Kitty {
	static void meow() {
		cout << "Kitty<T>::meow()" << endl;
	}
};
template <> struct Kitty<const char *> {
	static void meow() {
		cout << "Kitty<const char *>::meow()" << endl;
	}
};
template <typename X> struct Kitty<X *> {		            // partial specialization
	static void meow() {
		cout << "Kitty<X *>::meow()" << endl;
	}
};

template <typename T, typename U> struct Kitty1 {};
template <typename A, typename B> struct Kitty1<A *, B> {};
template <typename X, typename Y> struct Kitty1<X, Y *> {};

template <typename T, typename U> struct Foo {};
template <typename X> struct Foo<X, X> {};
template <typename A, typename B, typename C, typename D> struct Foo< pair<A, B>, pair<C, D> > {};

template <typename T> void meow(T){
	cout<< "meow(T)!" << endl;
}
template <> void meow(double){
	cout<< "meow(double) is a explicit specialization." << endl;
}
template <typename X> void meow(X *){
	cout<< "meow(X *) is an overloaded template, not partial specialization." << endl;
}
void meow(long){
	cout<< "meow(long) is an ordinary function." << endl;
}

template <class T> class Formatter
{
   T* m_t;
public:
   Formatter(T* t) : m_t(t) { }
   void print()
   {
      cout << *m_t << endl;
   }
};
// Specialization of template class for type char*
template<> class Formatter<char*>
{
   char** m_t;
public:
   Formatter(char** t) : m_t(t) { }
   void print()
   {
      cout << "Char value: " << **m_t << endl;
   }
};

int main() {
	Kitty<int>::meow();
	Kitty<const char *>::meow();
	Kitty<double *>::meow();

	Kitty1<int, double *> k1;
	Kitty1<int *, double> k2;
	// Kitty1<int *, double *> k3;			                // more than one partial specialization

	meow(123);
	meow(123L);
	meow(123.0);
	meow(static_cast<double *>(nullptr));

	int i = 157;
    // Use the generic template with int as the argument.
    Formatter<int>* formatter1 = new Formatter<int>(&i);
    char str[10] = "string1";
    char* str1 = str;
    // Use the specialized template.
    Formatter<char*>* formatter2 = new Formatter<char*>(&str1);
    formatter1->print();
    formatter2->print();
	return 0;
}






#include <vector>
#include <iostream>
#include <ostream>
#include <algorithm>
#include <type_traits>
#include <functional>
#include <string>
#include <memory>
using namespace std;

/**
* explicit conversion operator
*/

class SmartPtr {
public:
	/*explicit*/ operator bool() const {	                // explicit prevent it from convert to int
		return true;
	}
};

class Example{
public:
    Example();
    Example(int val);
    operator unsigned int();
    ~Example(){}
private:
    int itsVal;
};

Example::Example():itsVal(0){}
Example::Example(int val):itsVal(val){}
Example::operator unsigned int (){
	cout << "conversion: " << itsVal << endl;
    return (itsVal);
}

int main() {
	SmartPtr p;
	bool b(p);
	// cout << p * 123 << endl;			                    // explicit prevent it from convert to int
	if(p){
		cout << "True" << endl;
	} else {
		cout << "False" << endl;
	}

	int theInt = 8;
    Example exObject = theInt;
    Example ctr(5);
    int theInt1 = ctr;
	return 0;
}






#include <vector>
#include <iostream>
#include <ostream>
#include <algorithm>
#include <type_traits>
#include <functional>
#include <string>
#include <memory>
using namespace std;

/**
* default template type
*/

template <typename T = int> class Blah {};
template <typename T = int> void f(T t){
}

template <typename C, typename F = less<typename C::value_type>> void Sort(C& c, F f = F()){
	sort(c.begin(), c.end(), f);
}
template <typename C> void Print(C& c){
	for (auto& e : c){
		cout << e << " ";
	}
	cout << endl;
}


int main() {
	f(123);

	const int arr[] = { 3, 46, 12, 54, 12};
	vector<int> v(begin(arr), end(arr));
	Print(v);
	Sort(v);
	Print(v);
	Sort(v, greater<int>());
	Print(v);
	return 0;
}





#include <vector>
#include <iostream>
#include <ostream>
#include <algorithm>
#include <type_traits>
#include <functional>
#include <string>
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



#include <vector>
#include <iostream>
#include <ostream>
#include <algorithm>
#include <type_traits>
#include <functional>
#include <string>
#include <memory>
using namespace std;

/**
* uniform initialization
*/

int main() {
	int i{123};
	double d{1.2};
	// int i{1.23};		                                    // do not implicit conversion, compile error
	vector<int> v{1, 2, 3};
	return 0;
}
