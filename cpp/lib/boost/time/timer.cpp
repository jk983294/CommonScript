#include <boost/timer.hpp>
#include <iostream>

using namespace std;

void function_to_measure() {
    int result = 0;
    for (int i = 0; i < 1000000; i++) {
        result += i;
    }
    cout << "sum is " << result << endl;
}

int main() {
    boost::timer t;
    function_to_measure();
    cout << "time cost:" << t.elapsed() << "s" << endl;
    return 0;
}
