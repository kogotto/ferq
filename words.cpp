#include "words.h"

#include <iostream>

#include "word_extracter.h"

namespace impl {

RawWords countWords(std::string_view text) {
    RawWords result;

    WordExtracter wordExtracter(text);

    for (auto word = wordExtracter.nextWord();
            static_cast<bool>(word);
            word = wordExtracter.nextWord()) {
        ++result[fromStd(*word)];
    }

    return result;
}

std::ostream& operator<<(std::ostream& stream, const RawWords& words) {
    for (const auto& [count, word] : words) {
        stream << count << ' ' << word << '\n';
    }
    return stream;
}

} // namespace impl
