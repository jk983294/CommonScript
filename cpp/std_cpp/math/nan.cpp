#include <iostream>
#include <cmath>

using namespace std;

template<typename T>
void test_na(T x, T y) {
    /**
     * for min/max, if x = NAN, then result must be NAN
     * if x != NAN, then result must not be NAN
     */
    cout << "x=" << x << " y=" << y << endl;
    cout << "abs(x)=" << std::abs(x) << " abs(y)=" << std::abs(y) << endl;
    cout << "neg(x)=" << (x * -1) << " neg(y)=" << (y * -1) << endl;
    cout << "sqrt(x)=" << std::sqrt(x) << " sqrt(y)=" << std::sqrt(y) << endl;
    cout << "min(x, y)=" << std::min(x, y) << endl;
    cout << "max(x, y)=" << std::max(x, y) << endl;
    cout << "pow(x, y)=" << std::pow(x, y) << endl;

    cout << "(x + y)=" << (x + y) << endl;
    cout << "(x - y)=" << (x - y) << endl;
    cout << "(x * y)=" << (x * y) << endl;
    cout << "(x / y)=" << (x / y) << endl;
    cout << "(x > y)=" << (x > y) << endl;
    cout << "(x < y)=" << (x < y) << endl;
    cout << "(x == y)=" << (x == y) << endl;
}

int main()
{
    cout << "test float:\n";
    test_na<float>(1, 2);
    cout << "\ntest double:\n";
    test_na<double>(1, 2);

    cout << "\ntest float:\n";
    test_na<float>(1, NAN);
    cout << "\ntest double:\n";
    test_na<double>(1, NAN);

    cout << "\ntest float:\n";
    test_na<float>(NAN, 1);
    cout << "\ntest double:\n";
    test_na<double>(NAN, 1);

    cout << "\ntest float:\n";
    test_na<float>(NAN, NAN);
    cout << "\ntest double:\n";
    test_na<double>(NAN, NAN);
    return 0;
}
