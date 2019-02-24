#include <benchmark/benchmark.h>
#include <vector>

using namespace std;

void transpose(vector<int> &matrix, int row, int column) {
    for (int i = 0; i < row * column; i++) {
        int targetPos = (i + (row * column - 1) * (i % row)) / row;
        while (targetPos < i) {
            targetPos = (targetPos + (row * column - 1) * (targetPos % row)) / row;
        }
        std::swap(matrix[i], matrix[targetPos]);
    }
}

void ConstructMatrix(vector<int> &matrix, int row, int column) {
    matrix.resize(row * column);
    for (int i = 0; i < row * column; ++i) {
        matrix[i] = i;
    }
}

void bench_matrix_transpose(benchmark::State &state) {
    vector<int> matrix;
    for (auto _ : state) {
        state.PauseTiming();  // timer control consume 2us overhead
        ConstructMatrix(matrix, state.range(0), state.range(1));
        state.ResumeTiming();  // timer control consume 2us overhead
        transpose(matrix, state.range(0), state.range(1));
    }
}
BENCHMARK(bench_matrix_transpose)
    ->Args({1 << 8, 128})
    ->Args({1 << 9, 128})
    ->Args({1 << 10, 128})
    ->Args({1 << 11, 128})
    ->Args({1 << 8, 512})
    ->Args({1 << 9, 512})
    ->Args({1 << 10, 512})
    ->Args({1 << 11, 512});

BENCHMARK_MAIN();
