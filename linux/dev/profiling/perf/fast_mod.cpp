#include <benchmark/benchmark.h>
#include <vector>

static void generate_arg_pairs(benchmark::internal::Benchmark* b) {
    for (int i = 1 << 4; i <= 1 << 10; i <<= 2) {
        for (int j : {32, 128, 224}) {
            b = b->ArgPair(i, j);
        }
    }
}

static void bench_fast_mod(benchmark::State& state) {
    const int size = state.range(0);
    assert(size >= 16 && "only support 16 integers at a time!");
    const int ceil = state.range(1);
    std::vector<int> input, output;
    input.resize(size, 0);
    output.resize(size, 0);

    for (auto _ : state) {
        for (int i = 0; i < size; ++i) {
            output[i] = input[i] >= ceil ? input[i] % ceil : input[i];
        }
    }
}

BENCHMARK(bench_fast_mod)->Apply(generate_arg_pairs);

BENCHMARK_MAIN();
