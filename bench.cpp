#include <benchmark/benchmark.h>

#include <string>
#include <filesystem>

#include "bench_helpers.h"
#include "frequency.h"

namespace {

constexpr std::string_view stringviewPrefix = "sv";

void setupBenchWithStringview(const benchmark::State&) {
    setup(stringviewPrefix);
}

void teardownBenchWithStringview(const benchmark::State&) {
    teardown(stringviewPrefix);
}

void benchmarkWithStringView(benchmark::State& state) {
    const auto outPath = fullOutPath(stringviewPrefix);
    for (int i = 0; state.KeepRunning(); ++i) {
        countWordsAndWriteFirst(
            "input",
            outPath / std::to_string(i)
        );
    }
}

}

BENCHMARK(benchmarkWithStringView)->
    Setup(setupBenchWithStringview)->
    Teardown(teardownBenchWithStringview);

BENCHMARK_MAIN();
