#include "words.h"

#include "word_extracter.h"

namespace impl {

RawWords countWords(std::string_view text) {
    RawWords result;

    WordExtracter wordExtracter(text);

    for (auto word = wordExtracter.nextWord();
            static_cast<bool>(word);
            word = wordExtracter.nextWord()) {
        ++result[*word];
    }

    return result;
}

} // namespace impl
