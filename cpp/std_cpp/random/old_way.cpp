#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main() {
    cout << "The value of RAND_MAX is " << RAND_MAX << endl;  // 32767

    srand((unsigned)time(nullptr));
    int randomInteger;
    int lowest = 1, highest = 10;
    int range = (highest - lowest) + 1;
    for (int index = 0; index < 10; index++) {
        randomInteger = rand() % 10 + 1;
        cout << randomInteger << endl;
    }
    return 0;
}
