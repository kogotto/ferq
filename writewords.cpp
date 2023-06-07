#include "writewords.h"

#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace {

struct Frequency {
    Frequency(int count, std::string_view word)
        : count(count)
        , word(word)
    {}

    int count;
    std::string_view word;
};

bool operator<(const Frequency& lhs, const Frequency& rhs) {
    if (lhs.count != rhs.count) {
        // This sign is inverted because
        // words with more count should appear higher
        return lhs.count > rhs.count;
    }
    // This sign is not inverted because
    // words with same count should appear in alphabetical order
    return lhs.word < rhs.word;
}

using FrequencyMap = std::vector<Frequency>;

auto convertToFrequencyMap(const RawWords& words) {
    FrequencyMap result;
    result.reserve(words.size());
    for ( const auto& [word, count] : words ) {
        result.emplace_back(count, word);
    }
    std::sort(result.begin(), result.end());
    return result;
}

void writeFrequencyMapToFile(const std::filesystem::path& filename,
                             const FrequencyMap& frequencyMap) {
    std::ofstream stream(filename);
    if (!stream.is_open()) {
        std::cout << "Error: Can not open file " <<
            filename << " to write frequency map" << '\n';
        return;
    }

    for (const auto& [count, word] : frequencyMap) {
        stream << count << ' ' << word << '\n';
    }
}
} // namespace

void writeWordsToFile(const std::filesystem::path& filename, const RawWords& words) {
    const FrequencyMap frequencyMap = convertToFrequencyMap(words);
    writeFrequencyMapToFile(filename, frequencyMap);
}
