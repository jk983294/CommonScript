#include <stdio.h>

/**
* Name Lookup (find best function to call):
* template argument deduction
* overload resolution                           [fun(int), fun(long), ...]
* access control                                [private, protected, public]
* virtual function, dynamic binding
*/

namespace Foo {
	namespace Bar {
		namespace Meow {
			class Kitty{};
		};

		template<typename T> struct M {
			void purr(){
				puts("M<T>::purr();");
			}
		};

		template<> struct M<int> {
			void purr(){
				puts("M<int>::purr();");
			}
		};
	};

	using Bar::M;				                // drag namespace Bar
};
typedef Foo::Bar::Meow::Kitty FBMK;
namespace FBM = Foo::Bar::Meow;


namespace A {
	struct X{ int i; };
	struct Y{ int i; };
	void f( int a){
		puts("A::f(int);");
	}
	void g(X x){
		puts("A::g(X);");
	}
};

namespace B {
	void f( int i ) {
		f( i );				                    // B::f()
	}
	void g( A::X x ) {
		//g( x );			                    // won't compile, two possible calls
	}
	void h( A::Y y ) {
		h( y );				                    // B::h()
	}
 };

int main() {
	using Foo::M;				                // drag namespace Foo

	M<long> l;
	l.purr();

	M<int> i;
	i.purr();
    return 0;
}
