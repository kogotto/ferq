#pragma once

#include "raw_words.h"

#include <filesystem>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "writewords.hpp"

namespace impl {

template <typename StringView>
struct Frequency {
    using Raw = RawWords<StringView>;
    using Word = typename Raw::key_type;
    using Count = typename Raw::mapped_type;

    Frequency(Count count, Word word)
        : count(count)
        , word(word)
    {}

    Count count;
    Word word;
};

template <typename StringView>
bool operator<(const Frequency<StringView>& lhs,
               const Frequency<StringView>& rhs) {
    if (lhs.count != rhs.count) {
        // This sign is inverted because
        // words with more count should appear higher
        return lhs.count > rhs.count;
    }
    // This sign is not inverted because
    // words with same count should appear in alphabetical order
    return lhs.word < rhs.word;
}

template <typename StringView>
using FrequencyMap = std::vector<Frequency<StringView>>;

template <typename StringView>
auto convertToFrequencyMap(const RawWords<StringView>& words) {
    FrequencyMap<StringView> result;
    result.reserve(words.size());
    for ( const auto& [word, count] : words ) {
        result.emplace_back(count, word);
    }
    std::sort(result.begin(), result.end());
    return result;
}

template <typename StringView>
void writeFrequencyMapToFile(const std::filesystem::path& filename,
                             const FrequencyMap<StringView>& frequencyMap) {
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

} // namespace impl

template <typename StringView>
void writeWordsToFile(const std::filesystem::path& filename,
                      const RawWords<StringView>& words) {
    const auto frequencyMap = impl::convertToFrequencyMap(words);
    writeFrequencyMapToFile(filename, frequencyMap);
}
