#pragma once
#include "Delim.hpp"

namespace console_cpp {
    class DelimStyle {
    public:
        static auto EmptyLine() -> const Delim&;

        static auto SingleLine() -> const Delim&;

        static auto DoubleLine() -> const Delim&;

        static auto DoubleHorizontalLine() -> const Delim&;

        static auto DoubleVerticalLine() -> const Delim&;

        static auto RoundedLine() -> const Delim&;
    };
}
