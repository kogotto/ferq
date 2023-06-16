#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <boost/iostreams/device/mapped_file.hpp>

#include "raw_words.h"
#include "cistring_view.h"

inline std::string_view toStringView(std::string& text) {
    return text;
}

inline std::string_view toStringView(const boost::iostreams::mapped_file& mmap) {
    return {
        mmap.const_data(),
        mmap.size()
    };
}


template <typename Text, typename StringView>
class Words {
public:
    using Raw = RawWords<StringView>;

    Words(Text text);

    Words(const Words&) = delete;
    Words(Words&&) = default;

    Words& operator=(const Words&) = delete;
    Words& operator=(Words&&) = delete;

    const Raw& getRaw() const {
        return raw;
    }

private:
    Text text;
    const Raw raw;
};

#include "words.hpp"
