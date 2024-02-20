#pragma once
#include <string>

namespace console_cpp {
    struct Delim {
    public:
        struct DelimItem {
        public:
            std::u32string str;
        };

        DelimItem horizontalLine{};
        DelimItem verticalLine{};
        DelimItem topLeftLine{};
        DelimItem topRightLine{};
        DelimItem bottomRightLine{};
        DelimItem bottomLeftLine{};
    };
}
