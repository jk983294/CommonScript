#include <zlib.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * g++ -std=c++11 -Wall -O3 -lz gz_write.cpp -o gz_write
 */

struct Object {
    int data;
};

template <typename T>
int save2gz(const vector<T>& data, const string& fname) {
    gzFile file = gzopen(fname.c_str(), "wb");
    if (file == NULL) {
        cerr << "cannot open " << fname << endl;
        return -1;
    }
    int ret_val = gzwrite(file, data.data(), data.size() * sizeof(T));
    gzclose(file);
    if (ret_val <= 0)
        return -1;
    else
        return ret_val / sizeof(T);
}

void single_write_test() {
    string fname = "/tmp/my_test.gz";
    vector<Object> data(5);
    for (int i = 0; i < 5; ++i) {
        data[i].data = i;
    }

    int count = save2gz(data, fname);
    cout << "write " << fname << " ret=" << count << endl;
}

void continous_write() {
    string fname = "/tmp/my_test.gz";
    gzFile file = gzopen(fname.c_str(), "wb");
    if (file == NULL) {
        cerr << "cannot open " << fname << endl;
        return;
    }

    Object data;
    data.data = 0;
    while (true) {
        ++data.data;
        int ret_val = gzwrite(file, &data, sizeof(Object));

        if (ret_val <= 0) {
            cerr << "write error " << fname << endl;
            return;
        } else {
            cout << "write " << data.data << endl;
        }
        gzflush(file, Z_FINISH);
        sleep(1);
    }
}

int main() {
    // single_write_test();
    continous_write();
    return 0;
}
