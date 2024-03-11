#include "Utils.hpp"

#include "widecharwidth/widechar_width.h"

namespace console_cpp {
    auto U32CharToU8Char_(char32_t utf32, const char* buffer) -> char* {
        char* end = const_cast<char*>(buffer);

        if (utf32 < 0b01111111) {
            *(end++) = static_cast<unsigned>(utf32);
        }
        else if (utf32 < 0b00000111'11111111) {
            *(end++) = 0b11000000 + static_cast<unsigned>(utf32 >> 6);
            *(end++) = 0b10000000 + static_cast<unsigned>(utf32 & 0b00111111);
        }
        else if (utf32 < 0b00000001'00000000'00000000) {
            *(end++) = 0b11100000 + static_cast<unsigned>(utf32 >> 12);
            *(end++) = 0b10000000 + static_cast<unsigned>((utf32 >> 6) & 0b00111111);
            *(end++) = 0b10000000 + static_cast<unsigned>(utf32 & 0b00111111);
        }
        else if (utf32 < 0b00010001'00000000'00000000) {
            *(end++) = 0b11110000 + static_cast<unsigned>(utf32 >> 18);
            *(end++) = 0b10000000 + static_cast<unsigned>((utf32 >> 12) & 0b00111111);
            *(end++) = 0b10000000 + static_cast<unsigned>((utf32 >> 6) & 0b00111111);
            *(end++) = 0b10000000 + static_cast<unsigned>(utf32 & 0b00111111);
        }
        else {
            //throw std::runtime_error("Encoding error: unexpected symbol");
            return nullptr;
        }

        *end = '\0';

        return end;
    }

    auto U32StringToU8String_(const std::u32string& str) -> std::string {
        std::string result{};
        const char buffer[5]{};

        for (const auto& el : str) {
            console_cpp::U32CharToU8Char_(el, buffer);
            result += buffer;
        }

        return result;
    }

    auto U32CharWidth_(char32_t chr) -> size_t {
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

    auto GetStrSize_(const std::string& str) -> size_t {
        return str.size();
    }

    auto GetStrSize_(const std::u32string& str) -> size_t {
        return str.size();
    }

    auto GetStrSize_(const char* str) -> size_t {
        return strlen(str);
    }

    auto GetStrSize_(const char32_t* str) -> size_t {
        size_t size{};
        for (; str[size] != '\0'; ++size);

        return size;
    }
}
