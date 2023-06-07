#pragma once

#include <filesystem>

#include "words.h"

void writeWordsToFile(const std::filesystem::path& filename,
                      const RawWords& words);
