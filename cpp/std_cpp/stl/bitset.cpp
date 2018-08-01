#include <bitset>
#include <iostream>
#include <string>

using namespace std;

int main() {
    bitset<128> mybitset;

    cout << "default init a bitset:" << endl;
    cout << "check all " << mybitset.all() << endl;
    cout << "check none " << mybitset.none() << endl;
    cout << "check any " << mybitset.any() << endl;
    cout << "check count " << mybitset.count() << endl;

    mybitset.set();  // set all to true
    cout << "set all to true:" << endl;
    cout << "check all " << mybitset.all() << endl;
    cout << "check none " << mybitset.none() << endl;
    cout << "check any " << mybitset.any() << endl;
    cout << "check count " << mybitset.count() << endl;

    mybitset.reset();  // reset all to false
    mybitset.set(2, 1);
    cout << "set only position 2 to true:" << endl;
    cout << "check all " << mybitset.all() << endl;
    cout << "check none " << mybitset.none() << endl;
    cout << "check any " << mybitset.any() << endl;
    cout << "check count " << mybitset.count() << endl;

    cout << "test position 1: " << mybitset.test(1) << endl;
    cout << "test position 2: " << mybitset.test(2) << endl;

    mybitset.flip(2);
    cout << "flip position 2 to false:" << endl;
    cout << "test position 1: " << mybitset.test(1) << endl;
    cout << "test position 2: " << mybitset.test(2) << endl;

    return 0;
}
