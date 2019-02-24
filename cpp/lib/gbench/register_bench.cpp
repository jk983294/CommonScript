#include <benchmark/benchmark.h>
#include <memory.h>

void bench_string_creation(benchmark::State& state) {
    for (auto _ : state) {  // library will measure and report the timing for code within the for loop
        std::string empty_string;
    }
}

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

int main(int argc, char** argv) {
    benchmark::RegisterBenchmark("string_creation", bench_string_creation);

    benchmark::RegisterBenchmark("memcpy", bench_memcpy);

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}
