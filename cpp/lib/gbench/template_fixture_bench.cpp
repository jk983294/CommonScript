#include <benchmark/benchmark.h>
#include <unistd.h>
#include <thread>
#include <vector>

using namespace std;

template <typename T>
class MyFixture : public benchmark::Fixture {
public:
    void SetUp(const ::benchmark::State& state) { v.reserve(100); }

    void TearDown(const ::benchmark::State& state) { v.clear(); }

    vector<T> v;
};

BENCHMARK_TEMPLATE_F(MyFixture, push_back_test, int)(benchmark::State& st) {
    for (auto _ : st) {
        v.push_back(42);
    }
}

BENCHMARK_TEMPLATE_DEFINE_F(MyFixture, emplace_back_test, double)(benchmark::State& st) {
    for (auto _ : st) {
        v.emplace_back(42.0);
    }
}

// emplace_back_test is NOT registered
BENCHMARK_REGISTER_F(MyFixture, emplace_back_test);
// emplace_back_test is now registered

BENCHMARK_MAIN();
