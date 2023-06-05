#include <benchmark/benchmark.h>

#include <string>
#include <filesystem>

#include "frequency.h"


namespace {

const std::filesystem::path outDir{"out"};

std::filesystem::path fullOutPath(std::string_view prefix) {
    return outDir / prefix;
}

void setup(std::string_view prefix) {
    std::filesystem::create_directories(
        fullOutPath(prefix)
    );
}

void teardown(std::string_view prefix) {
    std::filesystem::remove_all(
        fullOutPath(prefix)
    );
}

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
        countWordsAndWrite(
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
