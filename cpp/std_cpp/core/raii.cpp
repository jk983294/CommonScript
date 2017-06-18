#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

using namespace std;

int data = 0;
mutex mtx;

void read_file() {
    ifstream ifs{"data.txt"};
    string line;
    while (getline(ifs, line)) {
        cout << line << endl;
    }
    // no need to close manually
}

void update() {
    lock_guard<mutex> lock(mtx);
    data += 1;
}

int main() {
    read_file();
    update();
    cout << data << endl;
    return 0;
}
