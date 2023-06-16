#pragma once

#include "word_extracter.h"
#include "words.h"

template <typename Text, typename StringView>
Words<Text, StringView>::Words(Text inText)
    : text(std::move(inText))
    , raw(countWords<StringView>(toStringView(text)))
{
}
