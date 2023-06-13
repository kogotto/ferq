#pragma once

#include <string_view>
#include <cctype>

template <typename Char>
struct MyCharTraits : public std::char_traits<Char> {
    static bool eq(Char l, Char r) {
        return project(l) == project(r);
    }

    static bool lt(Char l, Char r) {
        return project(l) < project(r);
    }

    static int compare(const Char* l, const Char* r, size_t n) {
        for (; n != 0u; ++l, ++r, --n) {
            if (project(*l) < project(*r)) {
                return -1;
            } else if (project(*l) > project(*r)) {
                return 1;
            }
        }
        return 0;
    }

    static Char* find(Char* p, size_t n, Char c) {
        for (auto a = project(c); n != 0u; --n) {
            if (project(*p) == a) {
                return p;
            }
        }
        return nullptr;
    }

    static auto project(Char c) {
        return std::tolower(c);
    }
};

template <typename Char>
using CIBasicStringView = std::basic_string_view<Char, MyCharTraits<Char>>;

template <typename Char>
std::ostream& operator<<(std::ostream& stream, const CIBasicStringView<Char>& str) {
    for (auto c : str) {
        stream << static_cast<Char>(MyCharTraits<Char>::project(c));
    }
    return stream;
}

namespace std {

template <typename Char>
struct hash<CIBasicStringView<Char>> {
    size_t operator()(const CIBasicStringView<Char>& sv) const {
        constexpr size_t p = 31;
        constexpr size_t m = 1e9 + 9;
        size_t result = 0;
        size_t pow = 1;
        for (auto c : sv) {
            result = (result + toInt(c) * pow) % m;
            pow = (pow * p) % m;
        }
        return result;
    }

    static size_t toInt(Char c) {
        Char p = MyCharTraits<Char>::project(c);
        return p - static_cast<Char>('a') + 1u;
    }
};

} // namespace std

using CIStringView = CIBasicStringView<char>;

inline CIStringView fromStd(std::string_view sv) {
    return {sv.data(), sv.size()};
}

