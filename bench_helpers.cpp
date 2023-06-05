#include "bench_helpers.h"

#include <filesystem>

namespace {

const std::filesystem::path outDir{"out"};

} // namespace

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
