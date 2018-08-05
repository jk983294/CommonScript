#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

int main() {
    double a = std::numeric_limits<double>::max(), b = std::numeric_limits<double>::max();
    double diff;
    while (cin >> a) {
        if (b == std::numeric_limits<double>::max()) {
            b = a;
        } else {
            diff = a - b;
            b = a;
            if (std::abs(diff) < 1.0) {
                cout << std::fixed << setprecision(9) << diff << endl;
            } else {
                cout << diff << endl;
            }
        }
    }
    return 0;
}
