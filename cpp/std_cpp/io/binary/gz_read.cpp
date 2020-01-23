#include <zlib.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * g++ -std=c++11 -Wall -O3 -lz gz_read.cpp -o gz_read
 */

struct Object {
    int data;
};

template <typename T>
int read_from_gz(vector<T>& ret, const string& fname) {
    const size_t BATCH_COUNT = 100;
    gzFile zp = gzopen(fname.c_str(), "rb");
    if (zp == Z_NULL) {
        cerr << "cannot open " << fname << endl;
        return -1;
    }
    int total_count = 0;
    T* cache = new T[BATCH_COUNT];
    while (!gzeof(zp)) {
        int ret_val = gzread(zp, cache, BATCH_COUNT * sizeof(T));
        if (ret_val < 0) {
            cerr << "error when reading " << fname << endl;
            continue;
        }
        int count = ret_val / (int)sizeof(T);
        total_count += count;
        for (int i = 0; i < count; ++i) {
            ret.push_back(cache[i]);
        }
    }
    delete[] cache;
    gzclose(zp);
    return total_count;
}

void single_read_test() {
    string fname = "/tmp/my_test.gz";
    vector<Object> ret;
    int total_count = read_from_gz(ret, fname);
    cout << "total " << total_count << " records" << endl;
    if (total_count > 0) {
        for (int i = 0; i < total_count; ++i) {
            cout << ret[i].data << " ";
        }
        cout << endl;
    }
}

void continous_read_test() {
    string fname = "/tmp/my_test.gz";
    gzFile zp = gzopen(fname.c_str(), "rb");
    if (zp == Z_NULL) {
        cerr << "cannot open " << fname << endl;
        return;
    }
    Object data;
    while (!gzeof(zp)) {
        int ret_val = gzread(zp, &data, sizeof(Object));
        if (ret_val < 0) {
            cerr << "error when reading " << fname << endl;
            continue;
        } else if (ret_val == (int)sizeof(Object)) {
            cout << data.data << endl;
        }
        sleep(1);
    }
    gzclose(zp);
}

int main() {
    //    single_read_test();
    continous_read_test();
    return 0;
}
