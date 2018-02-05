#include <iostream>
#include <string>
#include <utility>
#include <vector>

/**
 * std::move unconditionally casts its argument to an rvalue
 */

int main() {
    std::string foo{"foo"};
    std::string bar{"bar"};
    std::vector<std::string> v;

    v.push_back(foo);  // copy, foo won't lose its content

    /**
     * bar loses its value, and now is in a valid but unspecified state
     */
    v.push_back(std::move(bar));

    std::cout << "vector contains:";
    for (std::string& x : v) std::cout << ' ' << x;
    std::cout << '\n';
    return 0;
}
