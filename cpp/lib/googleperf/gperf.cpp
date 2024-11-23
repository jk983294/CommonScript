#include <gperftools/profiler.h>
#include <iomanip>
#include <iostream>
#include <random>
#include <tuple>

using namespace std;

/**
 * apt-get install google-perftools libgoogle-perftools-dev
 * g++ -O3 gperf.cpp -o gperf -L/usr/local/lib/ -lprofiler -Wl,-rpath=/usr/local/lib/
 * google-pprof ./gperf test_capture.prof --web
 */

template <typename T, template <typename> class Dist>
vector<T> generate_random_data(size_t count, T a, T b) {
    random_device rd;
    mt19937 generator(rd());
    Dist<T> uid(a, b);
    vector<T> ret;
    ret.resize(count);
    for (size_t i = 0; i < count; ++i) {
        ret[i] = uid(generator);
    }
    return ret;
}

template <typename T>
vector<T> generate_uniform_float(size_t count, T from = 0.0, T to = 1000000.0) {
    return generate_random_data<T, uniform_real_distribution>(count, from, to);
}

double vec_multiply_vec(const vector<double>& a, const vector<double>& b) {
    double ret = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        ret += a[i] * b[i];
    }
    return ret;
}

int main() {
    size_t count = 10000;

    ProfilerStart("test_capture.prof");
    double ret = 0;
    for (size_t i = 0; i < count; ++i) {
        vector<double> a = generate_uniform_float(count, -10., 10.);
        vector<double> b = generate_uniform_float(count, -10., 10.);
        ret += vec_multiply_vec(a, b);
    }
    ProfilerStop();
    cout << "ret=" << ret << endl;
}