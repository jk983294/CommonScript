#include <benchmark/benchmark.h>
#include <memory.h>

void bench_memcpy(benchmark::State& state) {
    char* src = new char[state.range(0)];
    char* dst = new char[state.range(0)];
    memset(src, 'x', state.range(0));
    for (auto _ : state) {
        memcpy(dst, src, state.range(0));
    }

    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
    delete[] src;
    delete[] dst;
}

BENCHMARK(bench_memcpy)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(8 << 10);

/**
 * By default the arguments in the range are generated in multiples of eight
 * so below will produce [ 8, 64, 512, 4k, 8k ]
 */
BENCHMARK(bench_memcpy)->Range(8, 8 << 10);

// choose your own Multiplier, it produce [ 8, 16, 32, 64, 128, 256, 512, 1024, 2k, 4k, 8k ]
BENCHMARK(bench_memcpy)->RangeMultiplier(2)->Range(8, 8 << 10);

BENCHMARK_MAIN();
