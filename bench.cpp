#include <benchmark/benchmark.h>

#include "work.h"


namespace {

void properBenchWork(benchmark::State& state) {
    for (int i = 0; state.KeepRunning(); ++i) {
        work("input", "out/" + std::to_string(i));
    }
}

}

BENCHMARK(properBenchWork);
BENCHMARK_MAIN();
