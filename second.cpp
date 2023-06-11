#include "second.h"

#include <boost/iostreams/device/mapped_file.hpp>

#include "words.h"
#include "writewords.h"

namespace {

using Mmap = boost::iostreams::mapped_file;

Mmap loadText(const std::filesystem::path& inputFilename) {
    Mmap result(inputFilename, Mmap::readonly);
    return result;
}

using WordsOverMmap = Words<Mmap>;

WordsOverMmap countWordsInText(Mmap text) {
    return std::move(text);
}

}

void countWordsAndWriteSecond(const std::filesystem::path &inputFilename,
                              const std::filesystem::path &outputFilename) {
    auto text = loadText(inputFilename);
    auto words = countWordsInText(std::move(text));
    writeWordsToFile(outputFilename, words.getRaw());
}
