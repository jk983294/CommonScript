#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>

/**
 * std::array is just a class version of the classic C array.
 * That means its size is fixed at compile time and it will be allocated as a single chunk (on the stack)
 *
 * advice would be: Use std::vector unless
 * (a) your profiler tells you that you have a problem and
 * (b) the array is tiny
 */

int main() {
    std::array<int, 3> a1{{1, 2, 3}};
    std::array<int, 3> a2 = {1, 2, 3};
    std::array<std::string, 2> a3 = {{std::string("a"), "b"}};

    std::sort(a1.begin(), a1.end());
    std::reverse_copy(a2.begin(), a2.end(), std::ostream_iterator<int>(std::cout, " "));

    for (auto& s : a3) std::cout << s << ' ';

    const char* cstr = "Test string";
    std::array<char, 12> charray;
    memcpy(charray.data(), cstr, 12);
    std::cout << charray.data() << '\n';
    return 0;
}
