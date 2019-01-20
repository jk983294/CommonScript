#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    std::chrono::milliseconds ms{3400};
    // std::chrono::seconds s = ms;   // this won't compile, conversion loss

    // duration_cast provide truncation
    std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
    cout << s.count() << " s" << endl;

    ms = s;  // this can compile, since no conversion loss
    cout << ms.count() << " ms" << endl;
    return 0;
}
