#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

class Words {
public:
    using Raw = std::unordered_map<std::string_view, int>;

    Words(std::string text);

    Words(const Words&) = delete;
    Words(Words&&) = default;

    Words& operator=(const Words&) = delete;
    Words& operator=(Words&&) = delete;

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
