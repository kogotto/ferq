#pragma once

#include <filesystem>

#include "words.h"

template <typename StringView>
void writeWordsToFile(const std::filesystem::path& filename,
                      const RawWords<StringView>& words);

#include "writewords.hpp"
