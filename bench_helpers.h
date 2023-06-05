#pragma once

#include <filesystem>

std::filesystem::path fullOutPath(std::string_view prefix);
void setup(std::string_view prefix);
void teardown(std::string_view prefix);
