#!/bin/bash

# compile
g++ string_bench.cpp -O3 -lbenchmark

# run
./my_bench --benchmark_filter=BM_memcpy/32          # run subset bench whose name match the regex
./my_bench --benchmark_counters_tabular=true        # show user counter as column
./my_bench --benchmark_format=json
./my_bench --benchmark_format=csv
./my_bench --benchmark_format=csv --benchmark_out=bench.csv

# Disable CPU frequency scaling
# ***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
sudo cpupower frequency-set --governor performance
./my_bench
sudo cpupower frequency-set --governor powersave

# install
git clone https://github.com/google/benchmark.git
cd benchmark
git clone https://github.com/google/googletest.git
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=RELEASE
make
sudo make install


#Install the project...
#-- Install configuration: "RELEASE"
#-- Installing: /usr/local/lib/libbenchmark.a
#-- Installing: /usr/local/lib/libbenchmark_main.a
#-- Installing: /usr/local/include/benchmark
#-- Installing: /usr/local/include/benchmark/benchmark.h
#-- Installing: /usr/local/lib/cmake/benchmark/benchmarkConfig.cmake
#-- Installing: /usr/local/lib/cmake/benchmark/benchmarkConfigVersion.cmake
#-- Installing: /usr/local/lib/pkgconfig/benchmark.pc
#-- Installing: /usr/local/lib/cmake/benchmark/benchmarkTargets.cmake
#-- Installing: /usr/local/lib/cmake/benchmark/benchmarkTargets-release.cmake
