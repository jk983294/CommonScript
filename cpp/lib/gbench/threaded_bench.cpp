#include <benchmark/benchmark.h>
#include <atomic>
#include <iostream>

using namespace std;

atomic<int> data;

void BM_MultiThreaded(benchmark::State& state) {
    if (state.thread_index == 0) {
        cout << "thread 1 setup with data " << data.load() << endl;
    } else if (state.thread_index == 1) {
        cout << "thread 2 setup with data " << data.load() << endl;
    }
    for (auto _ : state) {
        if (state.thread_index == 0) {
            data += 1;
        } else if (state.thread_index == 1) {
            data -= 1;
        }
    }

    if (state.thread_index == 0) {
        cout << "thread 1 teardown with data " << data.load() << endl;
    } else if (state.thread_index == 1) {
        cout << "thread 2 teardown with data " << data.load() << endl;
    }
}

/**
 * run one instance of this benchmark concurrently in 2 threads
 * so you need to make sure the thread safety to prevent crash
 */
BENCHMARK(BM_MultiThreaded)->Threads(2);

/**
 * If the code itself uses threads and you want to compare it to single-threaded code,
 * you may want to use real-time ("wallclock") measurements for latency comparisons
 */
// BENCHMARK(BM_test)->Range(8, 8<<10)->UseRealTime();

BENCHMARK_MAIN();
