#include <boost/multi_array.hpp>
#include <iostream>

using namespace std;

int main() {
    // create a 3D array that is 3 x 4
    typedef boost::multi_array<double, 2> array_type;
    typedef array_type::index index;
    array_type matrix(boost::extents[3][4]);

    // assign values to the elements
    int values = 0;
    for (index i = 0; i != 3; ++i) {
        for (index j = 0; j != 4; ++j) {
            matrix[i][j] = values++;
        }
    }

    // print matrix
    for (index i = 0; i != 3; ++i) {
        for (index j = 0; j != 4; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
