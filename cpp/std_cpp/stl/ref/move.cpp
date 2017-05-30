#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    std::string foo = "foo-string";
    std::string bar = "bar-string";
    std::vector<std::string> myvector;

    myvector.push_back(foo);  // copy, foo won't lose its content

    // this transfers bar's content into the vector
    // while bar loses its value, and now is in a valid but unspecified state
    myvector.push_back(std::move(bar));

    std::cout << "myvector contains:";
    for (std::string& x : myvector) std::cout << ' ' << x;
    std::cout << '\n';
    return 0;
}
