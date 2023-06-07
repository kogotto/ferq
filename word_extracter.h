#pragma once

#include <string_view>
#include <optional>

class WordExtracter {
public:
    WordExtracter(std::string_view text);

    // Returns next word or std::nullopt if end of string reached
    std::optional<std::string_view> nextWord();

private:
    std::string_view text;
    size_t pos;
};
