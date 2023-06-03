#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

class Words {
public:
    using Raw = std::unordered_map<std::string_view, int>;

    Words(std::string text);

    const std::string& getText() const {
        return text;
    }

    const Raw& getRaw() const {
        return raw;
    }

private:
    const std::string text;
    const Raw raw;
};

Words countWordsInFile(std::string_view filename);
void writeWordsToFile(std::string_view filename, const Words& words);
