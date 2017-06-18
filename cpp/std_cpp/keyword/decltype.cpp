#include <iomanip>
#include <iostream>

using namespace std;

template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u)  // return type depends on template parameters
{
    decltype(t + u) ret = t + u;
    return ret;
}

int main() {
    int i = 42;
    const int ci = i;
    int& ir = i;
    const int& cr = i;
    int&& rr = i++;
    const int&& crr = i++;

    auto ai = i;      // int
    auto aci = ci;    // int
    auto air = ir;    // int
    auto acr = cr;    // int
    auto arr = rr;    // int
    auto acrr = crr;  // int
    cout << ai << " " << aci << " " << air << " " << acr << " " << arr << " " << acrr << endl;

    decltype(i) di{i};        // int
    decltype(ci) dci{i};      // const int
    decltype(ir) dir{ir};     // int&
    decltype(cr) dcr{cr};     // const int&
    decltype(rr) drr{i++};    // int&&
    decltype(crr) dcrr{i++};  // const int&&
    // decltype (rr) drr1{rr};     // cannot bind 'int' lvalue to 'int&&'
    // decltype (crr) dcrr1{crr};     // cannot bind 'const int' lvalue to 'const int&&'
    cout << di << " " << dci << " " << dir << " " << dcr << " " << drr << " " << dcrr << endl;

    cout << add(1, 2) << endl;
    cout << add(1, 2.0) << endl;
    return 0;
}
