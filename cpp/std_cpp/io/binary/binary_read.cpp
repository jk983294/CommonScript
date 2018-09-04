#include <fstream>
#include <iostream>

using namespace std;

struct Object {
    int data{0};
};

int main() {
    Object obj;
    int x = 0;
    double fx = 0;
    ifstream ifs;
    ifs.open("binary.dat", std::ios::binary | std::ios::in);
    if (ifs.good()) {
        ifs.read(reinterpret_cast<char*>(&x), sizeof(int));
        ifs.read(reinterpret_cast<char*>(&fx), sizeof(fx));
        ifs.read(reinterpret_cast<char*>(&obj), sizeof(Object));
        cout << obj.data << " " << x << " " << fx << endl;

        /**
         * if read out of boundary, the x will still be the last value, no exception will be thrown
         */
        cout << ifs.eof() << endl;  // false
        ifs.read(reinterpret_cast<char*>(&x), sizeof(int));
        cout << ifs.eof() << endl;  // true
    }
    return 0;
}
