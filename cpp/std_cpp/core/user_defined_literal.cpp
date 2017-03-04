#include <iostream>

using namespace std;

/**
 * invalid argument list issue:
 * The declaration of a literal operator shall have a parameter-declaration-clause equivalent to one of the following:
 * const char*
 * unsigned long long int
 * long double
 * char
 * wchar_t
 * char16_t
 * char32_t
 * const char*, std::size_t
 * const wchar_t*, std::size_t
 * const char16_t*, std::size_t
 * const char32_t*, std::size_t
 */

// used as conversion
constexpr long double operator"" _deg ( long double deg )
{
    return deg * 3.141592 / 180;
}

// used with custom type
struct mytype
{
    mytype ( unsigned long long m): m(m) {}
    unsigned long long m;
};
mytype operator"" _mytype ( unsigned long long n )
{
    return mytype(n);
}

// used for side-effects
void operator"" _print ( const char* str )
{
    std::cout << str;
}

int main(){
    double x = 90.0_deg;
    std::cout << std::fixed << x << '\n';
    mytype y = 123_mytype;
    std::cout << y.m << '\n';
    0x123ABC_print;
    return 0;
}
