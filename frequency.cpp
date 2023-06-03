#include "frequency.h"

#include <cassert>
#include <cctype>

#include <string>
#include <optional>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace {

std::optional<std::string> loadFile(std::string_view inputFile) {
    std::ifstream stream(inputFile.data());
    if (!stream.is_open()) {
        return std::nullopt;
    }

    std::stringstream out;
    std::string line;

    while (getline(stream, line)) {
        out << std::move(line);
    }

    return out.str();
}

std::string doSomethingUsefull(std::string str) {
    return str;
}

bool writeFile(std::string_view filename, const std::string& str) {
    std::ofstream stream(filename.data());
    if (!stream.is_open()) {
        return false;
    }

    stream << str;

    return true;
}

std::string loadText(std::string_view filename) {
    std::filesystem::path path{filename};
    if (!exists(path)) {
        return {};
    }

    std::ifstream stream(filename.data());
    if (!stream.is_open()) {
        return {};
    }

    std::string result;
    result.reserve(file_size(path));

    getline(stream, result, {});

    return result;
}

inline bool isAlpha(unsigned char c) {
    return std::isalpha(c);
}

inline bool isNotAlpha(unsigned char c) {
    return !isAlpha(c);
}

template <typename Pred>
size_t nextCharacter(const std::string& text, size_t start, Pred pred) {
    const auto size = text.size();
    for (size_t i = start; i < size; ++i) {
        if (pred(text[i])) {
            return i;
        }
    }
    return size;
}

size_t nextNonAlpha(const std::string& text, size_t start) {
    return nextCharacter(text, start, isNotAlpha);
}

size_t nextAlpha(const std::string& text, size_t start) {
    return nextCharacter(text, start, isAlpha);
}

class WordExtracter {
public:
    WordExtracter(const std::string& text)
        : text(text)
        , pos(nextAlpha(text, 0))
    {}

    // Returns next word or std::nullopt if end of string reached
    std::optional<std::string_view> nextWord() {
        if (pos == text.size()) {
            return std::nullopt;
        }

        assert(isAlpha(text[pos]));

        auto firstNonAlpha = nextNonAlpha(text, pos);
        const auto length = firstNonAlpha - pos;
        std::string_view result{&text[pos], length};

        pos = nextAlpha(text, firstNonAlpha);

        return result;
    }

private:
    const std::string& text;
    size_t pos;
};

Words::Raw countWords(const std::string& text) {
    Words::Raw result;

    WordExtracter wordExtracter(text);

    for (auto word = wordExtracter.nextWord();
            static_cast<bool>(word);
            word = wordExtracter.nextWord()) {
        ++result[*word];
    }

    return result;
}

std::ostream& operator<<(std::ostream& stream, const Words::Raw& words) {
    for (const auto& [count, word] : words) {
        stream << count << ' ' << word << '\n';
    }
    return stream;
}

struct Frequency {
    int count;
    std::string_view word;

    friend auto operator<=>(const Frequency& lhs, const Frequency& rhs) = default;
};

using FrequencyMap = std::vector<Frequency>;

auto convertToFrequencyMap(const Words::Raw& words) {
    FrequencyMap result;
    result.reserve(words.size());
    for ( const auto& [word, count] : words ) {
        result.emplace_back(count, word);
    }
    return result;
}

void writeFrequencyMapToFile(std::string_view filename, const FrequencyMap& frequencyMap) {
    std::ofstream stream(filename.data());
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

Words::Words(std::string inText)
    : text(std::move(inText))
    , raw(countWords(text))
{
}

Words countWordFrequencyInFile(std::string_view filename) {
    return {loadText(filename)};
}

void writeWordsToFile(std::string_view filename, const Words& words) {
    const FrequencyMap frequencyMap = convertToFrequencyMap(words.getRaw());
    writeFrequencyMapToFile(filename, frequencyMap);
    std::cout << words.getText() << '\n';
}

void work(std::string_view inputFile, std::string_view outputFile) {
    auto input = loadFile(inputFile);
    if (!input) {
        std::cout << "Error: Can not open file " << inputFile << '\n';
        return;
    }

    auto result = doSomethingUsefull(std::move(input).value());

    bool writeResult = writeFile(outputFile, result);
    if (!writeResult) {
        std::cout << "Error: Can not write result" << '\n';
        return;
    }
}

