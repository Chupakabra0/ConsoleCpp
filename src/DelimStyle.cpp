#include "DelimStyle.hpp"

namespace console_cpp {
    auto DelimStyle::EmptyLine() -> const Delim& {
        static const Delim delim {
            .horizontalLine  = U" ",
            .verticalLine    = U" ",
            .topLeftLine     = U" ",
            .topRightLine    = U" ",
            .bottomRightLine = U" ",
            .bottomLeftLine  = U" ",
        };

        return delim;
    }

    auto DelimStyle::SingleLine() -> const Delim& {
        static const Delim delim {
            .horizontalLine  = U"─",
            .verticalLine    = U"│",
            .topLeftLine     = U"┌",
            .topRightLine    = U"┐",
            .bottomRightLine = U"┘",
            .bottomLeftLine  = U"└",
        };

        return delim;
    }

    auto DelimStyle::DoubleLine() -> const Delim& {
        static const Delim delim {
            .horizontalLine  = U"═",
            .verticalLine    = U"║",
            .topLeftLine     = U"╔",
            .topRightLine    = U"╗",
            .bottomRightLine = U"╝",
            .bottomLeftLine  = U"╚",
        };

        return delim;
    }

    auto DelimStyle::DoubleHorizontalLine() -> const Delim& {
        static const Delim delim {
            .horizontalLine  = U"═",
            .verticalLine    = U"│",
            .topLeftLine     = U"╒",
            .topRightLine    = U"╕",
            .bottomRightLine = U"╛",
            .bottomLeftLine  = U"╘",
        };

        return delim;
    }

    auto DelimStyle::DoubleVerticalLine() -> const Delim& {
        static const Delim delim {
            .horizontalLine  = U"─",
            .verticalLine    = U"║",
            .topLeftLine     = U"╓",
            .topRightLine    = U"╖",
            .bottomRightLine = U"╜",
            .bottomLeftLine  = U"╙",
        };

        return delim;
    }

    auto DelimStyle::RoundedLine() -> const Delim& {
        static const Delim delim {
            .horizontalLine  = U"─",
            .verticalLine    = U"│",
            .topLeftLine     = U"╭",
            .topRightLine    = U"╮",
            .bottomRightLine = U"╯",
            .bottomLeftLine  = U"╰",
        };

        return delim;
    }
}
