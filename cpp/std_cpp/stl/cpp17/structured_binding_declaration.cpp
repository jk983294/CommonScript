#include <iomanip>
#include <iostream>
#include <set>
#include <tuple>

using namespace std;

void binding_an_array() {
    int a[2] = {1, 2};
    auto [x, y] = a;     // creates e[2], copies a into e, then x refers to e[0], y refers to e[1]
    auto& [xr, yr] = a;  // xr refers to a[0], yr refers to a[1]
    cout << x << y << xr << yr << endl;
}

void binding_tuple() {
    float x{1};
    char y{'2'};
    int z{3};

    std::tuple<float&, char&&, int> tpl(x, std::move(y), z);
    const auto& [a, b, c] = tpl;
    // a names a structured binding that refers to x; decltype(a) is float&
    // b names a structured binding that refers to y; decltype(b) is char&&
    // c names a structured binding that refers to the 3rd element of tpl; decltype(c) is const int
    cout << a << b << c << endl;
}

void binding_data_members() {
    struct S {
        int x1{1};
        volatile double y1{2};
    };
    S f{};

    const auto [x, y] = f;
    // x is a const int lvalue
    // y is a const volatile double lvalue
    cout << x << y << endl;
}
int main() {
    binding_an_array();
    binding_tuple();
    binding_data_members();

    std::set<std::string> myset{"hello"};
    if (auto [iter, success] = myset.insert("Hello"); success)
        std::cout << "Insert is successful. The value is " << std::quoted(*iter) << ".\n";
    else
        std::cout << "The value " << std::quoted(*iter) << " already exists in the set.\n";
}
