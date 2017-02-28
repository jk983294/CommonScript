#include <iostream>
#include <vector>

using namespace std;

/**
 * qualified name: std::cout
 * unqualified name: cout
 * a dependent name is a name that depends on a template parameter. like T, vector<T>, vector<T>::iterator
 * typename remove the ambiguity
 * typename T::iterator is a type name, not a value
 */

template <class T>
class MyClass {
	int i;								// non-dependent name
	vector<int> vi;						// non-dependent name
	vector<int>::iterator vitr;			// non-dependent name

	T t;									// dependent name
	vector<T> vt;						// dependent name
	typename vector<T>::iterator viter;	// dependent name

	typedef T another_name_for_T;		// another_name_for_T still considered a dependent name
};

template <class T>
void foo() {
	typename T::iterator * iter;
	cout << "T::iterator means nested type name depend on T" << endl;
}

template <class T>
void bar() {
	typename T::iterator * iter;
	cout << "T::iterator means nested type name depend on T" << endl;
}

template <class T>
void meow() {
	typedef typename T::iterator iterator_type;
	iterator_type * iter;
	cout << "T::iterator means nested type name depend on T" << endl;
}

class ContainsType {
public:
	class iterator {
	};
};

class ContainsValue {
public:
	static int iterator;
};

int main(){
	foo<ContainsType>();
	//foo<ContainsValue>();			// won't get compiled
	bar<ContainsType>();
	//bar<ContainsValue>();			// won't get compiled
	return 0;
}
