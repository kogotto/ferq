#include "words.h"

#include "word_extracter.h"

namespace {

Words::Raw countWords(const std::string& text) {
    Words::Raw result;

    WordExtracter wordExtracter(text);

    for (auto word = wordExtracter.nextWord();
            static_cast<bool>(word);
            word = wordExtracter.nextWord()) {
        ++result[*word];
    }

    return result;
}

}

Words::Words(std::string inText)
    : text(std::move(inText))
    , raw(countWords(text))
{
}
