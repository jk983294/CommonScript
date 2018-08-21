#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <type_traits>
#include <vector>

using namespace std;

namespace {
enum class enabler {};

template <typename If, typename Then, typename Else>
using Conditional = typename std::conditional<If::value, Then, Else>::type;

template <bool B, typename...>
struct dependent_bool_type : std::integral_constant<bool, B> {};

template <bool B, typename... T>
using Bool = typename dependent_bool_type<B, T...>::type;  // type is std::integral_constant<T,v>

template <typename T>
using Not = Bool<!T::value>;  // negator of T::value

template <typename... T>
struct any : Bool<false> {};  // std::integral_constant<bool, false>

// if Head true, then true, else check if any of Tail is true
template <typename Head, typename... Tail>
struct any<Head, Tail...> : Conditional<Head, Bool<true>, any<Tail...>> {};

template <typename... T>
struct all : Bool<true> {};  // std::integral_constant<bool, true>

// if Head false, then false, else check if all of Tail is true
template <typename Head, typename... Tail>
struct all<Head, Tail...> : Conditional<Head, all<Tail...>, Bool<false>> {};

template <typename T>
using Invoke = typename T::type;

template <typename... Condition>
using EnableIf = std::enable_if_t<all<Condition...>::value, enabler>;

template <typename A, A, A>
struct is_of_type {
    typedef void type;
};
template <typename A, A, A, typename B>
struct is_of_type2 {
    typedef void type;
};

template <typename Container, typename = void>
struct is_container : std::false_type {};

template <typename Container, typename = void>
struct is_associative_container : std::false_type {};

template <typename Container, typename = void>
struct is_non_associative_container : std::false_type {};

// Include this then std::string exclude in container check
template <>
struct is_container<std::string> : std::false_type {};

template <typename C>
struct is_container<C, typename is_of_type<typename C::const_iterator (C::*)() const, &C::begin, &C::end>::type>
    : std::is_class<C> {};

template <typename C>
struct is_associative_container<C, typename is_of_type2<typename C::const_iterator (C::*)() const, &C::begin, &C::end,
                                                        typename C::mapped_type>::type> : std::is_class<C> {};

template <typename C>
struct is_non_associative_container<
    C, Conditional<all<is_container<C>, Not<is_associative_container<C>>>, void, Bool<true>>> : std::is_class<C> {};

template <typename T>
using EnableIfContainer = EnableIf<is_container<Invoke<std::decay<T>>>>;
template <typename T>
using EnableIfAssociativeContainer = EnableIf<is_associative_container<Invoke<std::decay<T>>>>;
template <typename T>
using EnableIfNonAssociativeContainer = EnableIf<is_non_associative_container<Invoke<std::decay<T>>>>;
template <typename T>
using EnableIfArithmetic = EnableIf<Invoke<std::is_arithmetic<Invoke<std::decay<T>>>>>;
template <typename T>
using EnableIfFundamental = EnableIf<Invoke<std::is_fundamental<Invoke<std::decay<T>>>>>;
template <typename T>
using EnableIfString = std::enable_if_t<std::is_same<std::string, Invoke<std::decay<T>>>::value>;
template <typename T>
using EnableIfCharPointer = std::enable_if_t<std::is_same<T, char*>::value || std::is_same<T, const char*>::value>;
template <typename T>
using EnableIfNonCharPointer =
    std::enable_if_t<!std::is_array<T>::value && std::is_pointer<T>::value &&
                     !(std::is_same<T, char*>::value || std::is_same<T, const char*>::value)>;
// check array need help of size, refer to template <typename T, std::size_t sz>
// template <typename T> using EnableIfArray = std::enable_if_t<(std::is_array<T>::value)>;
}

template <typename T, EnableIfFundamental<T>...>
void print(T);
// comment this out since this ambiguous with AssociativeContainer and NonAssociativeContainer
// template <typename T, EnableIfContainer<T>...> void print(const T&);
template <typename T, EnableIfAssociativeContainer<T>...>
void print(const T&);
template <typename T, EnableIfNonAssociativeContainer<T>...>
void print(const T&);
template <typename T, std::size_t sz>
void print(const T (&)[sz]);
template <std::size_t sz>
void print(const char (&t)[sz]);  // specialization of char array
template <typename T, EnableIfNonCharPointer<T>...>
void print(T);
template <typename T, EnableIfString<T>...>
void print(const T&);
template <class K, class V>
void print(const std::pair<K, V>&);

template <typename T, EnableIfFundamental<T>...>
void print(T t) {
    cout << "fundamental version: " << t << endl;
}

template <typename T, EnableIfAssociativeContainer<T>...>
void print(const T& t) {
    cout << "associative container version: ";
    for (const auto& itr : t) print(itr);
    cout << endl;
}

template <typename T, EnableIfNonAssociativeContainer<T>...>
void print(const T& t) {
    cout << "non associative container version: [" << endl;
    for (const auto& itr : t) {
        print(itr);
    }
    cout << "]" << endl;
}

template <typename T, std::size_t sz>
void print(const T (&t)[sz]) {
    cout << "array version: [";
    for (auto itr = begin(t); itr != end(t); ++itr) {
        print(*itr);
    }
    cout << "]" << endl;
}

template <std::size_t sz>
void print(const char (&t)[sz]) {
    cout << "char array version: " << t << endl;
}

template <typename T, EnableIfString<T>...>
void print(const T& t) {
    cout << "string version: " << t << endl;
}

template <typename T, EnableIfCharPointer<T>...>
void print(T t) {
    if (t != nullptr) cout << "char* version: " << t << endl;
}

template <typename T, EnableIfNonCharPointer<T>...>
void print(T t) {
    if (t != nullptr) {
        cout << "NonCharPointer: ";
        print(*t);
    }
}

template <class K, class V>
void print(const std::pair<K, V>& t) {
    cout << "[";
    print(t.first);
    cout << " : ";
    print(t.second);
    cout << "]"
         << " ";
}

int main() {
    cout << boolalpha;
    int var1 = 42;
    string str1{"hello world."};
    char* str2 = new char[256];
    strcpy(str2, str1.c_str());
    vector<int> v1{4, 2};
    vector<string> v2{"good", "good", "study"};
    map<int, float> m1{{1, 1.0}, {2, 2.0}, {3, 3.0}};
    map<int, vector<string>> m2{{1, {"1"}}, {2, {"2"}}, {3, {"3"}}};
    array<int, 4> a1{1, 2, 3, 4};
    int a2[3]{3, 2, 1};

    print(41);
    print("hello rvalue.");
    print(var1);
    print(str1);
    print(str2);
    print(v1);
    print(v2);
    print(m1);
    print(m2);
    print(a1);
    print(a2);

    // test pointer
    cout << "----------------------------- test pointer ------------------------------" << endl;
    print(&var1);
    print(&str1);
    print(&str2);
    print(&v1);
    print(&v2);
    print(&m1);

    // !!! warning, no way to check if a pointer points to an array or single element, so try to avoid this
    int* a3 = new int[2]{4, 2};
    print(a3);
    return 0;
}
