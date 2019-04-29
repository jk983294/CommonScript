#include <benchmark/benchmark.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

/**
 * it will try several times util the statistics are stable
 * each try will setup a fixture and its SetUp and TearDown will be called exactly once
 */

class MyFixture : public benchmark::Fixture {
public:
    void SetUp(const ::benchmark::State& state) {
        cout << "SetUp " << v.size() << endl;
        v.reserve(100);
    }

    void TearDown(const ::benchmark::State& state) {
        cout << "TearDown " << v.size() << endl;
        v.clear();
    }

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
