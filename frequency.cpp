#include "frequency.h"

#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>

#include "writewords.h"

template <>
struct Traits<std::string_view> {
    static std::string_view fromStd(std::string_view sv) {
        return sv;
    }
};

namespace {

void toLower(std::string& str) {
    std::transform(
        str.begin(), str.end(), str.begin(),
        [] (unsigned char c) {
            return std::tolower(c);
        }
    );
}

std::string loadText(const std::filesystem::path& filename) {
    if (!exists(filename)) {
        return {};
    }

    std::ifstream stream(filename);
    if (!stream.is_open()) {
        return {};
    }

    std::string result;
    result.reserve(file_size(filename));

    getline(stream, result, {});
    toLower(result);

    return result;
}

using WordsOverString = Words<std::string, std::string_view>;

WordsOverString countWordsInText(std::string text) {
    return {std::move(text)};
}

} // namespace

void countWordsAndWriteFirst(const std::filesystem::path& inputFilename,
                             const std::filesystem::path& outputFilename) {
    auto text = loadText(inputFilename);
    auto words = countWordsInText(std::move(text));
    writeWordsToFile(outputFilename, words.getRaw());
}
