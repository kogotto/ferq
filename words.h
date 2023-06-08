#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <boost/iostreams/device/mapped_file.hpp>

using RawWords = std::unordered_map<std::string_view, int>;
std::ostream& operator<<(std::ostream& stream, const RawWords& words);

namespace impl {
RawWords countWords(std::string_view text);
} // namespace impl

inline std::string_view toStringView(std::string& text) {
    return text;
}

inline std::string_view toStringView(const boost::iostreams::mapped_file_source& mmap) {
    return {
        mmap.data(),
        mmap.size()
    };
}


template <typename String>
class Words {
public:
    using Raw = RawWords;

    Words(String text);

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
    String text;
    const Raw raw;
};

template <typename String>
Words<String>::Words(String inText)
    : text(std::move(inText))
    , raw(impl::countWords(toStringView(text)))
{
}
