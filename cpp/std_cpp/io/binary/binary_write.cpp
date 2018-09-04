#include <fstream>
#include <iostream>

using namespace std;

struct Object {
    int data;
};

struct MyObject {
    int data;

    void save(ofstream& of) { of.write(reinterpret_cast<char*>(&data), sizeof(data)); }

    void load(ifstream& inf) { inf.read(reinterpret_cast<char*>(&data), sizeof(data)); }
};

int main() {
    Object obj{42};
    int x = 123;
    double fx = 34.54;
    ofstream ofs;
    ofs.open("binary.dat", ios::binary | ios::trunc | ios::out);
    ofs.write(reinterpret_cast<char*>(&x), sizeof(int));
    ofs.write(reinterpret_cast<char*>(&fx), sizeof(fx));
    ofs.write(reinterpret_cast<char*>(&obj), sizeof(Object));
    ofs.close();
    return 0;
}
