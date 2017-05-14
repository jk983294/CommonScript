#include <iostream>
#include <iterator>

using namespace std;

// istream iterators read successive elements from an input stream (such as cin, file).

int main() {
    double value1, value2;
    std::cout << "Please, insert two values: ";

    std::istream_iterator<double> iit(std::cin), eos;

    if (iit != eos) value1 = *iit;
    ++iit;
    if (iit != eos) value2 = *iit;

    std::cout << value1 << "*" << value2 << "=" << (value1 * value2) << '\n';
    return 0;
}
