#include "Utils.hpp"

namespace console_cpp {
    auto U32CharToU8Char_(char32_t utf32, const char* buffer) -> char* {
        char* end = const_cast<char*>(buffer);

        if (utf32 < 0x7F) {
            *(end++) = static_cast<unsigned>(utf32);
        }
        else if (utf32 < 0x7FF) {
            *(end++) = 0b1100'0000 + static_cast<unsigned>(utf32 >> 6);
            *(end++) = 0b1000'0000 + static_cast<unsigned>(utf32 & 0b0011'1111);
        }
        else if (utf32 < 0x10000) {
            *(end++) = 0b1110'0000 + static_cast<unsigned>(utf32 >> 12);
            *(end++) = 0b1000'0000 + static_cast<unsigned>((utf32 >> 6) & 0b0011'1111);
            *(end++) = 0b1000'0000 + static_cast<unsigned>(utf32 & 0b0011'1111);
        }
        else if (utf32 < 0x110000) {
            *(end++) = 0b1111'0000 + static_cast<unsigned>(utf32 >> 18);
            *(end++) = 0b1000'0000 + static_cast<unsigned>((utf32 >> 12) & 0b0011'1111);
            *(end++) = 0b1000'0000 + static_cast<unsigned>((utf32 >> 6) & 0b0011'1111);
            *(end++) = 0b1000'0000 + static_cast<unsigned>(utf32 & 0b0011'1111);
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
}
