#include "word_extracter.h"

#include <cassert>
#include <cctype>

namespace {

inline bool isAlpha(unsigned char c) {
    return std::isalpha(c);
}

inline bool isNotAlpha(unsigned char c) {
    return !isAlpha(c);
}

template <typename Pred>
size_t nextCharacter(const std::string& text, size_t start, Pred pred) {
    const auto size = text.size();
    for (size_t i = start; i < size; ++i) {
        if (pred(text[i])) {
            return i;
        }
    }
    return size;
}

size_t nextNonAlpha(const std::string& text, size_t start) {
    return nextCharacter(text, start, isNotAlpha);
}

size_t nextAlpha(const std::string& text, size_t start) {
    return nextCharacter(text, start, isAlpha);
}

} // namespace

WordExtracter::WordExtracter(const std::string& text)
    : text(text)
    , pos(nextAlpha(text, 0))
{}

std::optional<std::string_view> WordExtracter::nextWord() {
    if (pos == text.size()) {
        return std::nullopt;
    }

    assert(isAlpha(text[pos]));

    auto firstNonAlpha = nextNonAlpha(text, pos);
    const auto length = firstNonAlpha - pos;
    std::string_view result{&text[pos], length};

    pos = nextAlpha(text, firstNonAlpha);

    return result;
}
