#include <iostream>
#include <vector>
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"

using namespace tbb;
using namespace std;

vector<int> Data;

struct Update {
    void operator()(const blocked_range<int>& r) const {
        for (int i = r.begin(); i != r.end(); ++i) Data.at(i) += 1;
    }
};

int main() {
    Data.resize(1000);
    try {
        parallel_for(blocked_range<int>(0, 2000), Update());
    } catch (captured_exception& ex) {
        cout << "captured_exception: " << ex.what() << endl;
    } catch (out_of_range& ex) {
        cout << "out_of_range: " << ex.what() << endl;
    }
    return 0;
}
