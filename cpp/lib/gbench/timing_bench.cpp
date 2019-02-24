#include <benchmark/benchmark.h>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

void example_manual_timing(benchmark::State& state) {
    int microseconds = state.range(0);
    std::chrono::duration<double, std::micro> sleep_duration{static_cast<double>(microseconds)};

    for (auto _ : state) {
        auto start = std::chrono::high_resolution_clock::now();
        // Simulate some useful workload with a sleep
        std::this_thread::sleep_for(sleep_duration);
        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        state.SetIterationTime(elapsed_seconds.count());
    }
}

BENCHMARK(example_manual_timing)->Range(1, 1 << 17)->UseManualTime();

BENCHMARK_MAIN();
