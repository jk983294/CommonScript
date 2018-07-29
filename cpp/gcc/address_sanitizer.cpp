#include <iostream>

using namespace std;

// g++ -fsanitize=address address_sanitizer.cpp -o address_sanitizer

int main() {
    int* array = new int{42};
    cout << *array << endl;
    delete array;
    cout << *array << endl;
    return 0;
}
