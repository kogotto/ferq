#pragma once

#include <filesystem>

void countWordsAndWrite(const std::filesystem::path& inputFilename,
                        const std::filesystem::path& outputFilename);
