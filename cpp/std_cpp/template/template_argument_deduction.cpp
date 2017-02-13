#include <vector>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <functional>
#include <string>
using namespace std;

/**
* template argument deduction
*/

template <typename T> void meow(T t){
	t *= 2;
	cout << t << endl;
}
template <typename T> void meow1(T one, T two){
	cout << one << " " << two << endl;
}
template <typename T> void meow2(T& t){
	t *= 2;
	cout << t << endl;
}
template <typename T> void meow3(const T& t){
	cout << t << endl;
}
template <typename T> void meow4(T t){
	typedef typename make_unsigned<T>::type U;
	U u = static_cast<U>(t);
	cout << u << endl;
}
template <typename T> void meow5(T t, function<void (T)> f){
	f(t);
}

template <typename T> struct Identity {
	typedef T type;
};
// deduction will skip ::, so f won't be deduced, so T is deduced from T t
template <typename T> void meow6(T t, typename Identity<function<void (T)>>::type f){
	f(t);
}

template <typename T> void meow7(const basic_string<T>& s){
	cout<< s << endl;
}
template <typename T> void meow7(const T * s){
	cout<< "ptr " << s << endl;
}


int main() {
	meow(123);
	meow<int>(123);			                                            // better not to specify type, let compiler to decide
	// meow1(17, 29L);			                                        // ambiguous T type, int or long

	const int n = 123;
	meow(n);				                                            // type deduction will remove const
	// meow2(n);				                                        // ref count const
	meow3(n);

	meow4(-432324);


	function<void (int)> fxn = [](int x) { cout<< "lambda " << x << endl; };
	meow5(124, fxn);

	// meow5(124, [](int x) { cout<< "lambda " << x << endl; });        // lambda type != function<void (int)>
	meow6(124, [](int x) { cout<< "lambda " << x << endl; });

	meow7("abc");
	string s("abc");
	meow7(s);
    return 0;
}
