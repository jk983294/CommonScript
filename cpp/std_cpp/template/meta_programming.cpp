#include <iostream>
#include <algorithm>
#include <type_traits>

using namespace std;

// computing values
template <int i, int j> struct Multiply {
    static const int value = i * j;
};
// factorial
template <int i> struct Factorial {
    static const int value = i * Factorial<i - 1>::value;
};
template <> struct Factorial<0> {
    static const int value = 1;
};
// non negative factorial
template <int i, bool c> struct NegativeArgument {
    static const int value = Factorial<i>::value;
};
// deliberately declared but left undefined to make sure the code that picks this specialization fails to compile
template <int i> struct NegativeArgument<i, false>;
template <int i>struct SafeFactorial {
    static const int value = NegativeArgument<i, (i >= 0)>::value;
};

// computing types
template <typename U> struct my_remove_pointer {
    typedef U type;
};
template <typename T> struct my_remove_pointer<T*> {
    typedef T type;
};
template <typename T>
typename my_remove_pointer<T>::type fun(T val);

// alias templates
template <typename U> struct my_remove_pointer1 {
  using type = U;
};
template <typename T> struct my_remove_pointer1<T*> {
  using type = T;
};
template <typename W>
using RemovePointer1 = typename my_remove_pointer1<W>::type;
template <typename T>
RemovePointer1<T> fun(T val);					        // no need to use typename something::type to define return type

// constexpr idiom
constexpr int factorial( int i ) {
  return (i == 0) ? 1 : i * factorial(i - 1);
}
constexpr int safe_factorial( int i ) {
  return (i < 0) ? throw exception() : factorial(i);
}

int main() {
    cout<<boolalpha;
    int array[ Multiply<3, 4>::value ];
    int array1[ safe_factorial(5) ];
    cout << Factorial<5>::value <<endl;
    cout << SafeFactorial<5>::value <<endl;
    //cout << SafeFactorial<-5>::value <<endl;
    cout << safe_factorial(5) <<endl;
    return 0;
}