#include <benchmark/benchmark.h>
#include <unistd.h>

using namespace std;

void bench_sleep(benchmark::State& state) {
    for (auto _ : state) {
        usleep(1);
    }
}

BENCHMARK(bench_sleep)->Unit(benchmark::kMicrosecond);  // use us instead of ns

void example_user_counters(benchmark::State& state) {
    double numFoos = 0, numBars = 0;
    for (auto _ : state) {
        // ... count Foo,Bar events
        usleep(2);
        numFoos = 42;
        numBars = 4.2;
    }

    state.counters["Foo"] = numFoos;
    state.counters["Bar"] = numBars;
}

/**
 * ./format_bench --benchmark_counters_tabular=true
 * it will display as column instead of at the end after the table
 *
 * In multi-threaded benchmarks, each counter is set on the calling thread only.
 * When the benchmark finishes, the counters from each thread will be summed
 */
BENCHMARK(example_user_counters);  // add columns "Foo", "Bar" in its output

BENCHMARK_MAIN();
