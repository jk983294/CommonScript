#include <benchmark/benchmark.h>
#include <string>

using namespace std;

void bench_string_compare(benchmark::State& state) {
    std::string s1(state.range(0), '-');
    std::string s2(state.range(0), '-');
    for (auto _ : state) {
        benchmark::DoNotOptimize(s1.compare(s2));
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(bench_string_compare)->RangeMultiplier(2)->Range(1 << 10, 1 << 18)->Complexity(benchmark::oN);

/**
 * complexity will be calculated automatically to the best fit
 */
BENCHMARK(bench_string_compare)->RangeMultiplier(2)->Range(1 << 10, 1 << 18)->Complexity();

BENCHMARK_MAIN();
