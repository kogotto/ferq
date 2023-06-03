#include <iostream>
#include <string_view>

#include "frequency.h"

namespace {

constexpr int WARNING_WRONG_ARGUMENT_COUNT = 1;

void printHelp() {
    std::cout << "Usage: freq <input_file> <output_file>" << '\n';
}

} // namespace

int main(int argc, char**argv) {
    if (argc != 3) {
        printHelp();
        return WARNING_WRONG_ARGUMENT_COUNT;
    }

    const std::string_view inputFilename = argv[1];
    const std::string_view outputFilename = argv[2];

    std::cout << "input file name is \"" << inputFilename << '\"' << '\n';
    std::cout << "output file name is \"" << outputFilename << '\"' << '\n';

    auto words = countWordsInFile(inputFilename);
    writeWordsToFile(outputFilename, words);

    return 0;
}
