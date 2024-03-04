#pragma once
#include <ostream>
#include <widecharwidth/widechar_width.h>

#include <cstring>

namespace console_cpp {
    auto IsCursorVisible_() -> bool;

    auto SetLocale_() -> void;

    // Encodes the UTF-32 encoded char into a UTF-8 string. 
    // Stores the result in the buffer and returns the position 
    // of the end of the buffer. If any error occurs, returns nullptr.
    // Be sure to provide a buffer that is at least 5 bytes!
    auto U32CharToU8Char_(char32_t utf32, const char* buffer) -> char*;

    auto U32StringToU8String_(const std::u32string& str) -> std::string;

    static auto U32CharWidth_(char32_t chr) -> size_t {
        const int width = widechar_wcwidth(chr);

        switch (width) {
            // Some sensible defaults
            case widechar_nonprint:
            case widechar_combining:
            case widechar_unassigned:
            case widechar_non_character: {
                return 0;
            }
            case widechar_ambiguous:
            case widechar_private_use: {
                return 1;
            }
            case widechar_widened_in_9: {
                // Our renderer supports Unicode 9
                return 2;
            }
            default: {
                // Use the width widechar_width gave us.
                return width;
            }
        }
    }

    static auto GetStrSize_(const std::string& str) -> size_t {
        return str.size();
    }

    static auto GetStrSize_(const std::u32string& str) -> size_t {
        return str.size();
    }

    static auto GetStrSize_(const char* str) -> size_t {
        return strlen(str);
    }

    static auto GetStrSize_(const char32_t* str) -> size_t {
        size_t size{};
        for (; str[size] != '\0'; ++size);

        return size;
    }
}

static auto operator<<(std::ostream& os, char32_t chr) -> std::ostream& {
    const char buffer[5]{};
    console_cpp::U32CharToU8Char_(chr, buffer);

    if (buffer == nullptr) {
        //throw std::runtime_error("Printing error: ");
        return os;
    }

    return os << buffer;
}

static auto operator<<(std::ostream& os, const std::u32string& str) ->  std::ostream& {
    for (const auto& el : str) {
        os << el;
    }

    return os;
}
