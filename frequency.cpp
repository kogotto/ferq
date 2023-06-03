#include "frequency.h"

#include <string>
#include <optional>
#include <vector>
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
    return static_cast<std::string>(filename) + "some very very very long string to supress short string optimization";  // TODO read all file
}

Words::Raw countWords(const std::string& text) {
    return {
        { text, 666 },
        {"some", 777},
    };
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
    std::cout << "Pretend to write map(" << words.getRaw().size() << ") to file " << filename << '\n';
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

