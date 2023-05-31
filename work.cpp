#include "work.h"

#include <string>
#include <optional>
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

} // namespace

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

