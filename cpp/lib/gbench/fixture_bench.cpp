#include <benchmark/benchmark.h>
#include <unistd.h>
#include <thread>
#include <vector>

using namespace std;

class MyFixture : public benchmark::Fixture {
public:
    void SetUp(const ::benchmark::State& state) { v.reserve(100); }

    void TearDown(const ::benchmark::State& state) { v.clear(); }

    vector<int> v;
};

BENCHMARK_F(MyFixture, push_back_test)(benchmark::State& st) {
    for (auto _ : st) {
        v.push_back(42);
    }
}

BENCHMARK_DEFINE_F(MyFixture, emplace_back_test)(benchmark::State& st) {
    for (auto _ : st) {
        v.emplace_back(42);
    }
}

// emplace_back_test is NOT registered
BENCHMARK_REGISTER_F(MyFixture, emplace_back_test);
// emplace_back_test is now registered

BENCHMARK_MAIN();
