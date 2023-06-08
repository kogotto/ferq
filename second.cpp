#include "second.h"

#include <string>

namespace {

auto loadText(const std::filesystem::path& inputFilename) {
    // TODO replace with mmap
    return inputFilename.string();
}

auto countWordsInText(std::string text) {
    return text;
}

}

void countWordsAndWriteSecond(const std::filesystem::path &inputFilename,
                              const std::filesystem::path &outputFilename) {
    auto text = loadText(inputFilename);
    auto words = countWordsInText(std::move(text));
}
