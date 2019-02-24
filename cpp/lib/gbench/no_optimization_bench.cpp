#include <benchmark/benchmark.h>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

/**
 * DoNotOptimize(<expr>) forces the result of <expr> to be stored in either memory or a register.
 * it acts as read/write barrier for global memory. More specifically it forces the compiler to flush pending writes
 * to memory and reload any other values as necessary.
 */

void example_no_optimization_1(benchmark::State& state) {
    for (auto _ : state) {
        int x = 0;
        for (int i = 0; i < 64; ++i) {
            benchmark::DoNotOptimize(x += i);
        }
    }
}

BENCHMARK(example_no_optimization_1);

/**
 * ClobberMemory() forces the compiler to perform all pending writes to global memory
 * Memory managed by block scope objects must be "escaped" using DoNotOptimize(...) before it can be clobbered.
 * In the below example ClobberMemory() prevents the call to v.push_back(42) from being optimized away.
 */
void example_no_optimization_2(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v;
        v.reserve(1);
        benchmark::DoNotOptimize(v.data());  // allow v.data() to be clobbered
        v.push_back(42);
        benchmark::ClobberMemory();  // force 42 to be written to memory
    }
}

BENCHMARK(example_no_optimization_2);

BENCHMARK_MAIN();
