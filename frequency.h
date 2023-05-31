#pragma once

#include <string_view>

void work(std::string_view inputFile, std::string_view outputFile);

using FrequencyMap = int;

FrequencyMap countWordFrequencyInFile(std::string_view filename);
void writeToFile(std::string_view filename, const FrequencyMap& map);
