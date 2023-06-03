#include <benchmark/benchmark.h>

#include <string>

#include "frequency.h"


namespace {

void properBenchWork(benchmark::State& state) {
    for (int i = 0; state.KeepRunning(); ++i) {
        auto res = std::to_string(i);
        benchmark::DoNotOptimize(res);
    }
}

}

BENCHMARK(properBenchWork);
BENCHMARK_MAIN();
