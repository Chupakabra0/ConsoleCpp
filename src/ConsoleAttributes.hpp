#pragma once
#include "ConsoleMode.hpp"

namespace console_cpp {
    class ConsoleAttributes {
    public:
        static auto Default() -> const ConsoleMode*;

        static auto HideCursor() -> const ConsoleMode*;

        static auto ShowCursor() -> const ConsoleMode*;

        static auto EnableBuffer() -> const ConsoleMode*;

        static auto DisableBuffer() -> const ConsoleMode*;

        static auto EnableAlterScreen() -> const ConsoleMode*;

        static auto DisableAlterScreen() -> const ConsoleMode*;
    };
}