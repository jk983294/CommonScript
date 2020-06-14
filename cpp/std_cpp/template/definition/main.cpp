#include <iostream>
#include "my_type.h"

using namespace std;

/**
 * provide a definition in cpp file
 * espically needed in so
 */
constexpr size_t TypeID<float>::id;
constexpr size_t TypeID<double>::id;

int main() {
    cout << TypeID<double>::id << endl;
    cout << GetTypeID<double>() << endl;  // avoid init static variable issue
    return 0;
}
