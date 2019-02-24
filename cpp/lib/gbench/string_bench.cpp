#include <benchmark/benchmark.h>

void bench_string_creation(benchmark::State& state) {
    for (auto _ : state) {  // library will measure and report the timing for code within the for loop
        std::string empty_string;
    }
}

// register the function as a benchmark
BENCHMARK(bench_string_creation);

// define another benchmark
void bench_string_copy(benchmark::State& state) {
    std::string x = "hello";
    for (auto _ : state) {
        std::string copy(x);
    }
}

BENCHMARK(bench_string_copy);

BENCHMARK_MAIN();
