#include <iostream>
#include <algorithm>
#include <type_traits>

using namespace std;

/**
 * Think of a trait as a small object whose main purpose is to carry information
 * used by another object or algorithm to determine "policy" or "implementation details".
 */

template< typename T > struct is_void_trait{
    static const bool value = false;
};
template<> struct is_void_trait< void >{				            // use full specilization
    static const bool value = true;
};
template< typename T > struct is_pointer_trait{
    static const bool value = false;
};
template< typename T > struct is_pointer_trait< T* >{               // use partial specilization
    static const bool value = true;
};

/**
 * function f select based on type, one is regular type, the other is pointer type
 */
template< bool b >
struct f_selector {
    template< typename T >
    static void implementation( T t ){
        cout << t << endl;
    }
};
template<> struct f_selector< true > {
    template< typename T >
    static void implementation( T* ptr ) {
        cout << *ptr << endl;
    }
};
template< typename T >
void f( T t ) {
    f_selector< is_pointer_trait< T >::value >::implementation(t);
}

/**
 * function algorithm select based on whether the object support optimised implementation
 */
template< typename T > struct supports_optimised_implementation{
    static const bool value = false;
};
template< bool b > struct algorithm_selector {
    template< typename T >
    static void implementation( T& object ){
        cout << "default implementation." << endl;
    }
};
template<> struct algorithm_selector< true > {
    template< typename T >
    static void implementation( T& object ) {
        object.optimised_implementation();
    }
};
template< typename T > void algorithm( T& object ) {
    algorithm_selector< supports_optimised_implementation< T >::value >::implementation(object);
}
class ObjectA {};
class ObjectB {
public:
    void optimised_implementation() {
        cout << "optimised implementation." << endl;
    }
};
template<> struct supports_optimised_implementation< ObjectB > {
    static const bool value = true;
};

int main() {
    ObjectA a;
    algorithm( a );
    ObjectB b;
    algorithm( b );

    f(1);
    int* ip = new int(1);
    f(ip);
    return 0;
}