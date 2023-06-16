#pragma once

#include <unordered_map>
#include <iostream>

template <typename StringView>
using RawWords = std::unordered_map<StringView, int>;

template <typename StringView>
std::ostream& operator<<(std::ostream& stream, const RawWords<StringView>& words);

/// This traits struct should have public members:
/// static StringView fromStd(std::string_view sv);
template <typename StringView>
struct Traits;

template <typename StringView>
RawWords<StringView> countWords(std::string_view text);

#include "raw_words.hpp"
