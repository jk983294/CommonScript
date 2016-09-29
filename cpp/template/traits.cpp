// trait idiom
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

// how to selector algorithm based on type
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
template< typename T > struct supports_optimised_implementation{
    static const bool value = false;
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


// trait usage
#include <iostream>
#include <algorithm>
#include <type_traits>

using namespace std;

struct Base {
    virtual void foo() = 0;
};
class A {
public:
	void member() {}
};
struct NonTrivial: public Base {
    NonTrivial() {}
	NonTrivial(NonTrivial&) {}
	int m;
private:
	int n;
};
enum E {};
enum E1: long {};
typedef union {
    int a;
    float b;
} B;
int f(){
    return 1;
}

struct S {
    double operator()(char, int&);
    float operator()(int) { return 1.0; }
};

class Foo {
    int v1;
    double v2;
 public:
    Foo(int n) : v1(n), v2() {}
    Foo(int n, double f) /*noexcept */: v1(n), v2(f) {}
};


template< class T > T findMax(const T const * data, const size_t const numItems) {
  T largest = std::numeric_limits< T >::min();	// Obtain the minimum value for type T
  for(size_t i=0; i < numItems; ++i)
	  if (data[i] > largest)
		largest = data[i];
  return largest;
}

void numeric_limits_demo(){
	// member functions
	cout << "max " << numeric_limits<int>::max() << endl;
	cout << "min " << numeric_limits<int>::min() << endl;
	cout << "lowest " << numeric_limits<int>::lowest() << endl;
	cout << "double min " << numeric_limits<double>::min() << endl;
	cout << "double lowest " << numeric_limits<double>::lowest() << endl;
	cout << "epsilon " << numeric_limits<double>::epsilon() << endl;
	cout << "round_error " << numeric_limits<double>::round_error() << endl;
	cout << "infinity " << numeric_limits<double>::infinity() << endl;					// the special value "positive infinity"
	cout << "quiet_NaN " << numeric_limits<double>::quiet_NaN() << endl;
	cout << "signaling_NaN " << numeric_limits<double>::signaling_NaN() << endl;
	cout << "denorm_min " << numeric_limits<double>::denorm_min() << endl;

	// member constants
	cout << "is_specialized " << numeric_limits<int>::is_specialized << endl;			// true means there exists a specialization of std::numeric_limits.
	cout << "is_signed " << numeric_limits<int>::is_signed << endl;
	cout << "is_integer " << numeric_limits<int>::is_integer << endl;
	cout << "is_exact " << numeric_limits<int>::is_exact << endl;						// floating-point types is not exact representation
	cout << "has_infinity " << numeric_limits<int>::has_infinity << endl;				// true for floating-point types
	cout << "has_quiet_NaN " << numeric_limits<int>::has_quiet_NaN << endl;				// true for all floating-point types which capable of representing the special value NaN
	cout << "has_signaling_NaN " << numeric_limits<int>::has_signaling_NaN << endl;
	cout << "has_denorm " << numeric_limits<int>::has_denorm << endl;
	cout << "has_denorm_loss " << numeric_limits<int>::has_denorm_loss << endl;			// all floating-point types T that detect loss of precision
	cout << "round_style " << numeric_limits<int>::round_style << endl;
	cout << "is_iec559 " << numeric_limits<int>::is_iec559 << endl;						// all floating-point types T which fulfill the requirements of IEC 559 (IEEE 754) standard
	cout << "is_bounded " << numeric_limits<int>::is_bounded << endl;
	cout << "is_modulo " << numeric_limits<int>::is_modulo << endl;						// support %
	cout << "digits " << numeric_limits<int>::digits << endl;							// the number of digits in base-radix that can be represented by the type T without change
	cout << "digits10 " << numeric_limits<int>::digits10 << endl;						// the number of base-10 digits that can be represented by the type T without change
	cout << "max_digits10 " << numeric_limits<int>::max_digits10 << endl;				// the number of base-10 digits that are necessary to uniquely represent all distinct values of the type T
	cout << "radix " << numeric_limits<int>::radix << endl;								// the base of the number system used in the representation of the type
	cout << "min_exponent " << numeric_limits<int>::min_exponent << endl;				// the lowest negative number n such that pow(2, n)
	cout << "min_exponent10 " << numeric_limits<int>::min_exponent10 << endl;			// the lowest negative number n such that pow(10, n)
	cout << "max_exponent " << numeric_limits<int>::max_exponent << endl;				// the largest positive number n such that pow(2, n)
	cout << "max_exponent10 " << numeric_limits<int>::max_exponent10 << endl;
	cout << "traps " << numeric_limits<int>::traps << endl;								// x / 0 will generate a trap
	cout << "tinyness_before " << numeric_limits<int>::tinyness_before << endl;			// all floating-point types T that test results of floating-point expressions for underflow before rounding.

	// helper classes
	cout << "round_toward_zero " << round_toward_zero << endl;
	cout << "denorm_present " << denorm_present << endl << endl;
}

void type_traits_demo(){
	// primary type categories
	cout << "is_void " << is_void<void>::value << " " << is_void<int>::value << endl;
	cout << "is_integral " << is_integral<int>::value << " " << is_integral<float>::value << endl;
	cout << "is_floating_point " << is_floating_point<float>::value << " " << is_floating_point<int>::value << endl;
	cout << "is_array " << is_array<int[]>::value << " " << is_array<int>::value << endl;
	cout << "is_enum " << is_enum<E>::value << " " << is_enum<int>::value << endl;
	cout << "is_union " << is_union<B>::value << " " << is_union<int>::value << endl;
	cout << "is_class " << is_class<A>::value << " " << is_class<int>::value << endl;
	cout << "is_function " << is_function<decltype(f)>::value << " " << is_function<int>::value << " " << is_function<int(int)>::value << endl;
	cout << "is_pointer " << is_pointer<int*>::value << " " << is_pointer<int&>::value << endl;
	cout << "is_lvalue_reference " << is_lvalue_reference<int&>::value << " " << is_lvalue_reference<int>::value << " " << is_lvalue_reference<int&&>::value << endl;
	cout << "is_rvalue_reference " << is_rvalue_reference<int&&>::value << " " << is_rvalue_reference<int&>::value << endl;
	cout << "is_member_object_pointer " << is_member_object_pointer<int(A::*)>::value << " " << is_member_object_pointer<int(A::*)()>::value << endl;
	cout << "is_member_function_pointer " << is_member_function_pointer<decltype(&A::member)>::value << " " << is_member_function_pointer<int>::value << endl;
	// composite type categories
	cout << "is_fundamental " << is_fundamental<int>::value << " " << is_fundamental<A>::value << endl;						// arithmetic type, void, or nullptr_t
	cout << "is_arithmetic " << is_arithmetic<int>::value << " " << is_arithmetic<A>::value << endl;						// integral type or floating-point type
	cout << "is_scalar " << is_scalar<int>::value << " " << is_scalar<A>::value << endl;									// arithmetic, pointer, pointer to member, enumeration, or nullptr_t type
	cout << "is_object " << is_object<A>::value << " " << is_object<int>::value << endl;
	cout << "is_compound " << is_compound<int&>::value << " " << is_compound<int>::value << endl;							// array, function, object pointer, function pointer, member object pointer, member function pointer, reference, class, union, or enumeration, including any cv-qualified variants
	cout << "is_reference " << is_reference<int&>::value << " " << is_reference<int&&>::value << " " << is_reference<int>::value << endl;
	cout << "is_member_pointer " << is_member_pointer<int(A::*)>::value << " " << is_member_pointer<int>::value << endl;	// a pointer to a non-static member function or object
	// type properties
	cout << "is_const " << is_const<int* const>::value << " " << is_const<const int*>::value << endl;
	cout << "is_volatile " << is_volatile<volatile int>::value << " " << is_volatile<int>::value << endl;
	cout << "is_trivial " << is_trivial<A>::value << " " << is_trivial<NonTrivial>::value << endl;								// a scalar type, a trivially copyable class with a trivial default constructor, or array of such type/class, possibly cv-qualified
	cout << "is_trivially_copyable " << is_trivially_copyable<A>::value << " " << is_trivially_copyable<NonTrivial>::value << endl;
	cout << "is_standard_layout " << is_standard_layout<A>::value << " " << is_standard_layout<NonTrivial>::value << endl;			// a scalar type, a standard-layout class, or an array of such type/class, possibly cv-qualified
	cout << "is_pod " << is_pod<A>::value << " " << is_pod<NonTrivial>::value << endl;												// plain old data type, that is, both trivial and standard-layout
	cout << "is_literal_type " << is_literal_type<A>::value << " " << is_literal_type<NonTrivial>::value << endl;
	cout << "is_empty " << is_empty<A>::value << " " << is_empty<NonTrivial>::value << endl;									// a non-union class type with no non-static data members other than bit-fields of size 0, no virtual functions, no virtual base classes, and no non-empty base classes
	cout << "is_polymorphic " << is_polymorphic<NonTrivial>::value << " " << is_polymorphic<A>::value << endl;
	cout << "is_abstract " << is_abstract<Base>::value << " " << is_abstract<A>::value << endl;
	cout << "is_signed " << is_signed<signed int>::value << " " << is_signed<unsigned int>::value << endl;
	cout << "is_unsigned " << is_enum<unsigned int>::value << " " << is_enum<signed int>::value << endl;

	cout << "is_trivially_constructible " << is_trivially_constructible<Foo, const Foo&>::value << endl;
	cout << "is_constructible " << is_constructible<Foo, int>::value << endl;
	cout << "is_nothrow_constructible " << is_nothrow_constructible<Foo, int, double>::value << endl;

	cout << "is_default_constructible " << is_default_constructible<Foo>::value << endl;
	cout << "is_trivially_default_constructible " << is_trivially_default_constructible<Foo>::value << endl;
	cout << "is_nothrow_default_constructible " << is_nothrow_default_constructible<Foo>::value << endl;

	cout << "is_copy_constructible " << is_copy_constructible<Foo>::value << endl;
	cout << "is_trivially_copy_constructible " << is_trivially_copy_constructible<Foo>::value << endl;
	cout << "is_nothrow_copy_constructible " << is_nothrow_copy_constructible<Foo>::value << endl;

	cout << "is_move_constructible " << is_move_constructible<Foo>::value << endl;
	cout << "is_trivially_move_constructible " << is_trivially_move_constructible<Foo>::value << endl;
	cout << "is_nothrow_move_constructible " << is_nothrow_move_constructible<Foo>::value << endl;

	cout << "is_assignable " << is_assignable<int, int>::value << endl;
	cout << "is_trivially_assignable " << is_trivially_assignable<int, int>::value << endl;
	cout << "is_nothrow_assignable " << is_nothrow_assignable<int, double>::value << endl;

	cout << "is_copy_assignable " << is_copy_assignable<int[2]>::value << endl;
	cout << "is_trivially_copy_assignable " << is_trivially_copy_assignable<Foo>::value << endl;
	cout << "is_nothrow_copy_assignable " << is_nothrow_copy_assignable<int>::value << endl;

	cout << "is_move_assignable " << is_move_assignable<int[2]>::value << endl;
	cout << "is_trivially_move_assignable " << is_trivially_move_assignable<Foo>::value << endl;
	cout << "is_nothrow_move_assignable " << is_nothrow_move_assignable<string>::value << endl;

	cout << "is_destructible " << is_destructible<int[2]>::value << endl;
	cout << "is_trivially_destructible " << is_trivially_destructible<Foo>::value << endl;
	cout << "is_nothrow_destructible " << is_nothrow_destructible<string>::value << endl;

	// property queries
	cout << "alignment_of " << alignment_of<A>::value << " " << alignment_of<int>::value << endl;					// the alignment requirement of the type
	cout << "rank " << rank<int[1][2][3]>::value << " " << rank<int[][2]>::value << endl;									// the number of dimensions of the array
	cout << "extent " << extent<int[3]>::value << " " << extent<int[3][4], 1>::value << endl;								// the number of elements along the Nth dimension
	// type relationships
	cout << "is_same " << is_same<int, int>::value << " " << is_same<int, long>::value << endl;
	cout << "is_base_of " << is_base_of<Base, NonTrivial>::value << " " << is_base_of<int, long>::value << endl;		// _2 is derived from _1
	cout << "is_convertible " << is_convertible<NonTrivial*, Base*>::value << " " << is_convertible<Base*, NonTrivial*>::value << endl;
	// type modifications
	cout << "remove_const " << is_same<int, remove_const<const int>::type >::value << endl;
	cout << "remove_volatile " << is_same<int, remove_volatile<volatile int>::type >::value << endl;
	cout << "remove_cv " << is_same<int, remove_cv<const volatile int>::type >::value << endl;
	cout << "remove_cv " << is_same<int*, remove_cv<const volatile int*>::type >::value << endl;
	cout << "remove_cv " << is_same<int*, remove_cv<int * const volatile>::type >::value << endl;

	cout << "add_const " << is_same<const int, add_const<int>::type >::value << endl;
	cout << "add_volatile " << is_same<volatile int, add_volatile<int>::type >::value << endl;
	cout << "add_cv " << is_same<const volatile int, add_cv<int>::type >::value << endl;
	cout << "add_cv " << is_same<const volatile int*, add_cv<int*>::type >::value << endl;
	cout << "add_cv " << is_same<int* const volatile, add_cv<int*>::type >::value << endl;

	cout << "remove_reference " << is_same<int, remove_reference<int&>::type >::value << endl;
	cout << "remove_reference " << is_same<int, remove_reference<int&&>::type >::value << endl;
	cout << "add_lvalue_reference " << is_same<int&, add_lvalue_reference<int>::type >::value << endl;
	cout << "add_rvalue_reference " << is_same<int&&, add_rvalue_reference<int>::type >::value << endl;

	cout << "remove_pointer " << is_same<int, remove_pointer<int*>::type >::value << endl;
	cout << "remove_pointer " << is_same<int*, remove_pointer<int**>::type >::value << endl;
	cout << "add_pointer " << is_same<int*, add_pointer<int>::type >::value << endl;
	cout << "add_pointer " << is_same<int**, add_pointer<int*>::type >::value << endl;

	cout << "make_signed " << is_same<signed int, make_signed<int>::type >::value << endl;
	cout << "make_unsigned " << is_same<unsigned int, make_unsigned<int>::type >::value << endl;

	cout << "remove_extent " << is_same<int, remove_extent<int[]>::type >::value << endl;
	cout << "remove_extent " << is_same<int[3][4], remove_extent<int[2][3][4]>::type >::value << endl;
	cout << "remove_all_extents " << is_same<int, remove_all_extents<int[2][3][4]>::type >::value << endl;
	// miscellaneous transformations
	cout << "decay " << is_same<int, decay<int&&>::type>::value << endl;
	cout << "decay " << is_same<int*, decay<int[2]>::type>::value << endl;
	cout << "decay " << is_same<int(*)(int), decay<int(int)>::type>::value << endl;

	cout << "conditional " << is_same<int, conditional<true, int, double>::type>::value << endl;
	cout << "conditional " << is_same<double, conditional<false, int, double>::type>::value << endl;
	cout << "decay " << is_same<int(*)(int), decay<int(int)>::type>::value << endl;

	cout << "enable_if " << is_same<long, enable_if<is_floating_point<double>::value>::type>::value << endl;
	// cout << "enable_if " << is_same<long, enable_if<is_floating_point<int>::value>::type>::value << endl;	// complain because enable_if<>::type undefined when condition failed

	cout << "common_type " << is_same<long, common_type<int, long>::type>::value << endl;
	cout << "common_type " << is_same<int, common_type<int, double>::type>::value << endl;						// should be double

	cout << "underlying_type " << is_same<int, underlying_type<E>::type>::value << endl;
	cout << "underlying_type " << is_same<long, underlying_type<E1>::type>::value << endl;

	std::result_of<S(char, int&)>::type d = 3.14;
}

int main() {
	cout<<boolalpha;
	const std::size_t N = 10;
	cout << N << endl;

	numeric_limits_demo();
	type_traits_demo();

	return 0;
}


// variadic
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <cstdarg>
//#include <initializer_list>

using namespace std;

// use macro, not type safe
double stddev(int count, ...) {
    double sum = 0;
    double sum_sq = 0;
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        double num = va_arg(args, double);
        sum += num;
        sum_sq += num * num;
    }
    va_end(args);
    return sqrt( sum_sq / count - ( sum / count ) * ( sum / count ) );
}
/*
int sum1(std::initializer_list<int> numbers){
    int total = 0;
    for(auto i = numbers.begin(); i != numbers.end(); i++)
        total += *i;
    return total;
}*/

template<typename T> T sum(T v) {
	cout << __PRETTY_FUNCTION__ << endl;
  return v;
}
template<typename T, typename... Args> T sum(T first, Args... args) {
	cout << __PRETTY_FUNCTION__ << endl;
  return first + sum(args...);
}

// peel off two arguments
template<typename T> bool pair_comparer(T a) {					// for odd number of arguments version
  return false;
}
template<typename T> bool pair_comparer(T a, T b) {
  return a == b;
}
template<typename T, typename... Args> bool pair_comparer(T a, T b, Args... args) {
  return a == b && pair_comparer(args...);
}

// size_t sizeof...(Ts)
// gun(1, forward<Ts>(vs)..., 8);
// expansion rules

// varidic data structures
template <class... Ts> struct tuple {};
template <class T, class... Ts> struct tuple<T, Ts...> : tuple<Ts...> {
  tuple(T t, Ts... ts) : tuple<Ts...>(ts...), tail(t) {}

  T tail;
};
// a helper type that lets us access the type of the k-th element in a tuple
// elem_type_holder<2, some_tuple_type> peels off two types from the beginning of the tuple, and sets its type to the type of the third one
template <class T, class... Ts> struct elem_type_holder<0, tuple<T, Ts...>> {
  typedef T type;
};
template <size_t k, class T, class... Ts> struct elem_type_holder<k, tuple<T, Ts...>> {
  typedef typename elem_type_holder<k - 1, tuple<Ts...>>::type type;
};

template <size_t k, class... Ts>
typename std::enable_if<k == 0, typename elem_type_holder<0, tuple<Ts...>>::type&>::type get(tuple<Ts...>& t) {
  return t.tail;
}
template <size_t k, class T, class... Ts>
typename std::enable_if<k != 0, typename elem_type_holder<k, tuple<T, Ts...>>::type&>::type get(tuple<T, Ts...>& t) {
  tuple<Ts...>& base = t;
  return get<k - 1>(base);
}


// any template parameters can go here
// a function that can print out standard library containers
template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::pair<T, U>& p) {
  out << "[" << p.first << ", " << p.second << "]";
  return out;
}
template <template <typename, typename> class ContainerType, typename ValueType, typename AllocType>
void print_container(const ContainerType<ValueType, AllocType>& c) {
  for (const auto& v : c)
    cout << v << ' ';
  cout << endl;
}
template <template <typename, typename...> class ContainerType, typename ValueType, typename... Args>
void print_container(const ContainerType<ValueType, Args...>& c) {
  for (const auto& v : c)
    cout << v << ' ';
  cout << endl;
}

// forward
template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args){
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main() {
	cout<<boolalpha;
	cout << stddev(4, 25.0, 27.3, 26.9, 25.7) << endl;
	//cout << sum1( { 1, 2, 3, 4, 5 } ) << endl;
	cout << sum( 1, 2, 3, 4, 5, 7.3, 5.2 ) << endl;
	cout << pair_comparer(1.5, 1.5, 2, 2, 6, 6) << endl;
	cout << pair_comparer(1.5, 1.5, 2, 2, 6, 6, 7) << endl;

	tuple<double, int, const char*> t1(12.2, 42, "big");
	cout << "0th elem is " << get<0>(t1) << endl;
	cout << "1th elem is " << get<1>(t1) << endl;
	cout << "2th elem is " << get<2>(t1) << endl;
	get<1>(t1) = 103;
	cout << "1th elem is " << get<1>(t1) << endl;

	std::unique_ptr<FooType> f = std::make_unique<FooType>(1, "str", 2.13);

	return 0;
}
