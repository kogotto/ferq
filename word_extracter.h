#pragma once

#include <string>
#include <optional>

class WordExtracter {
public:
    WordExtracter(const std::string& text);

    // Returns next word or std::nullopt if end of string reached
    std::optional<std::string_view> nextWord();

private:
    const std::string& text;
    size_t pos;
};
