#pragma once
#include "PrintMode.hpp"

namespace console_cpp {
    struct Font {
    public:
        static auto None() -> const PrintMode*;

        static auto Bold() -> const PrintMode*;

        static auto Dim() -> const PrintMode*;

        static auto Italic() -> const PrintMode*;

        static auto Underline() -> const PrintMode*;

        static auto Blinking() -> const PrintMode*;

        static auto RapidBlink() -> const PrintMode*;

        static auto Invert() -> const PrintMode*;

        static auto Hidden() -> const PrintMode*;

        static auto Strikethrough() -> const PrintMode*;

        static auto Default() -> const PrintMode*;

        static auto Fracture() -> const PrintMode*;

        static auto DoubleUnderline() -> const PrintMode*;

        static auto Framed() -> const PrintMode*;

        static auto Encircled() -> const PrintMode*;

        static auto Overline() -> const PrintMode*;
    };
}
