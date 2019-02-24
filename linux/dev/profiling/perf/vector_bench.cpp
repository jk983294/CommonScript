#include <benchmark/benchmark.h>
#include <vector>

// static void escape(void* p) {   // this pointer may be write to somewhere in memory
//    asm volatile("" : : "g"(p) : "memory");
//}
//
// static void clobber() { // write to memory with out any instruction
//    asm volatile("" : : "memory");
//}

static void bench_create(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v;
        benchmark::DoNotOptimize(&v);
        (void)v;
    }
}

BENCHMARK(bench_create);

static void bench_reserve(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v;
        v.reserve(1);
        benchmark::DoNotOptimize(v.data());
    }
}

BENCHMARK(bench_reserve);  // this essentially benchmark malloc

static void bench_push_back(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v;
        v.reserve(1);
        benchmark::DoNotOptimize(v.data());
        v.push_back(42);
        benchmark::ClobberMemory();  // make sure we see 42 write to memory
    }
}

BENCHMARK(bench_push_back);

BENCHMARK_MAIN();
