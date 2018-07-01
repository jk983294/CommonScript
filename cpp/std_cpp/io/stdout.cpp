#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    double d1 = 1.2231;
    double d2 = 11.2231;

    cout << std::setprecision(3) << d1 << "\t" << d2 << endl;                // 1.22	11.2
    cout << std::fixed << std::setprecision(3) << d1 << "\t" << d2 << endl;  // 1.223	11.223

    cout << "a              |              b" << endl
         << left << setw(15) << d1 << "|" << right << setw(15) << d2 << endl;
    return 0;
}
