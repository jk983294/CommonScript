#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v{1, 2, 3};
    for (auto& i : v) {
        cout << i << endl;
    }

    for (const auto i : {4, 5, 6}) {
        cout << i << endl;
    }
    return 0;
}
