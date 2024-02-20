#pragma once
#include "PrintMode.hpp"

namespace console_cpp {
    struct ForegroundColor {
    public:
        static auto Default() -> const PrintMode*;

        static auto Black() -> const PrintMode*;

        static auto Red() -> const PrintMode*;

        static auto Green() -> const PrintMode*;

        static auto Yellow() -> const PrintMode*;

        static auto Blue() -> const PrintMode*;

        static auto Magenta() -> const PrintMode*;

        static auto Cyan() -> const PrintMode*;

        static auto White() -> const PrintMode*;

        static auto BrightBlack() -> const PrintMode*;

        static auto BrightRed() -> const PrintMode*;

        static auto BrightGreen() -> const PrintMode*;

        static auto BrightYellow() -> const PrintMode*;

        static auto BrightBlue() -> const PrintMode*;

        static auto BrightMagenta() -> const PrintMode*;

        static auto BrightCyan() -> const PrintMode*;

        static auto BrightWhite() -> const PrintMode*;

        static auto TrueColor(size_t r, size_t g, size_t b) -> const PrintMode*;

        static auto IndexColor(size_t color) -> const PrintMode*;
    };
}
