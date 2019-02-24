#include <benchmark/benchmark.h>
#include <unistd.h>
#include <chrono>
#include <thread>

using namespace std;

/**
 * reporting the mean, median and standard deviation
 */
void bench_sleep(benchmark::State& state) {
    for (auto _ : state) {
        usleep(1);
    }
}

BENCHMARK(bench_sleep)->Repetitions(5);

/**
 * user defined statistics, calculate the largest observation, because if you have some real-time constraints
 */
BENCHMARK(bench_sleep)->ComputeStatistics("max", [](const std::vector<double>& v) -> double {
    return *(std::max_element(std::begin(v), std::end(v)));
});

BENCHMARK_MAIN();
