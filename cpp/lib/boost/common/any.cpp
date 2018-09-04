#include <boost/any.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Any value stored in a variable of type boost::any must be copy constructible
 * it is not possible to store a C array, since C arrays aren’t copy constructible
 */

void basic();
void bad_cast_example();
void check_type();
void vector_any();

int main() {
    basic();
    bad_cast_example();
    check_type();
    vector_any();
    return 0;
}

void basic() {
    boost::any a = 1;
    std::cout << boost::any_cast<int>(a) << '\n';
    a = 3.14;
    std::cout << boost::any_cast<double>(a) << '\n';
    a = true;
    std::cout << std::boolalpha << boost::any_cast<bool>(a) << '\n';
    a = std::string{"hello"};
    std::cout << std::boolalpha << boost::any_cast<string>(a) << '\n';
}

void bad_cast_example() {
    try {
        boost::any a = 1;
        std::cout << boost::any_cast<float>(a) << '\n';
    } catch (boost::bad_any_cast &e) {
        std::cerr << e.what() << '\n';
    }
}

void check_type() {
    boost::any a = 1;
    if (!a.empty()) {
        const std::type_info &ti = a.type();
        std::cout << "type is " << ti.name() << '\n';
    }
}

void print_any(boost::any &a) {
    if (a.empty()) return;

    if (typeid(int) == a.type()) {
        cout << boost::any_cast<int>(a) << '\n';
    } else if (typeid(double) == a.type()) {
        cout << boost::any_cast<double>(a) << '\n';
    } else if (typeid(std::string) == a.type()) {
        cout << boost::any_cast<std::string>(a) << '\n';
    } else {
        std::cout << "unknown type\n";
    }
}

void vector_any() {
    std::vector<boost::any> v;
    v.push_back(std::string("hello world"));
    v.push_back(3);
    v.push_back(4.2);
    for (auto item : v) {
        print_any(item);
    }
}
