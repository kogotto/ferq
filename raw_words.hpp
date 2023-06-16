#pragma once

#include "raw_words.h"
#include "word_extracter.h"

template <typename StringView>
std::ostream& operator<<(std::ostream& stream, const RawWords<StringView>& words) {
    for (const auto& [count, word] : words) {
        stream << count << ' ' << word << '\n';
    }
    return stream;
}

template <typename StringView>
RawWords<StringView> countWords(std::string_view text) {
    RawWords<StringView> result;

    WordExtracter wordExtracter(text);

    for (auto word = wordExtracter.nextWord();
            static_cast<bool>(word);
            word = wordExtracter.nextWord()) {
        ++result[Traits<StringView>::fromStd(*word)];
    }

    return result;
}
