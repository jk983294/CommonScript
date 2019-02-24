#include <benchmark/benchmark.h>
#include <stack>

using namespace std;

template <class Q>
void bench_sequential(benchmark::State& state) {
    Q q;
    typename Q::value_type v;
    for (auto _ : state) {
        for (int i = state.range(0); i--;) q.push(v);
        for (int e = state.range(0); e--;) q.pop();
    }
    // actually messages, not bytes:
    state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) * state.range(0));
}

BENCHMARK_TEMPLATE(bench_sequential, stack<int>)->Range(1 << 0, 1 << 10);

BENCHMARK_MAIN();
