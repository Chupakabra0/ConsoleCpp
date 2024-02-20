#include "ForegroundColor.hpp"

#include <format>
#include <unordered_map>
#include <tuple>

namespace console_cpp {
    auto ForegroundColor::Default() -> const PrintMode* {
        static PrintMode none(AddCsiSymbol("39m"), AddCsiSymbol("39m"));

        return &none;
    }

    auto ForegroundColor::Black() -> const PrintMode* {
        static PrintMode black(AddCsiSymbol("30m"), AddCsiSymbol("39m"));

        return &black;
    }

    auto ForegroundColor::Red() -> const PrintMode* {
        static PrintMode red(AddCsiSymbol("31m"), AddCsiSymbol("39m"));

        return &red;
    }

    auto ForegroundColor::Green() -> const PrintMode* {
        static PrintMode green(AddCsiSymbol("32m"), AddCsiSymbol("39m"));

        return &green;
    }

    auto ForegroundColor::Yellow() -> const PrintMode* {
        static PrintMode yellow(AddCsiSymbol("33m"), AddCsiSymbol("39m"));

        return &yellow;
    }

    auto ForegroundColor::Blue() -> const PrintMode* {
        static PrintMode blue(AddCsiSymbol("34m"), AddCsiSymbol("39m"));

        return &blue;
    }

    auto ForegroundColor::Magenta() -> const PrintMode* {
        static PrintMode magenta(AddCsiSymbol("35m"), AddCsiSymbol("39m"));

        return &magenta;
    }

    auto ForegroundColor::Cyan() -> const PrintMode* {
        static PrintMode cyan(AddCsiSymbol("36m"), AddCsiSymbol("39m"));

        return &cyan;
    }

    auto ForegroundColor::White() -> const PrintMode* {
        static PrintMode white(AddCsiSymbol("37m"), AddCsiSymbol("39m"));

        return &white;
    }

    auto ForegroundColor::BrightBlack() -> const PrintMode* {
        static PrintMode black(AddCsiSymbol("90m"), AddCsiSymbol("39m"));

        return &black;
    }

    auto ForegroundColor::BrightRed() -> const PrintMode* {
        static PrintMode red(AddCsiSymbol("91m"), AddCsiSymbol("39m"));

        return &red;
    }

    auto ForegroundColor::BrightGreen() -> const PrintMode* {
        static PrintMode green(AddCsiSymbol("92m"), AddCsiSymbol("39m"));

        return &green;
    }

    auto ForegroundColor::BrightYellow() -> const PrintMode* {
        static PrintMode yellow(AddCsiSymbol("93m"), AddCsiSymbol("39m"));

        return &yellow;
    }

    auto ForegroundColor::BrightBlue() -> const PrintMode* {
        static PrintMode blue(AddCsiSymbol("94m"), AddCsiSymbol("39m"));

        return &blue;
    }

    auto ForegroundColor::BrightMagenta() -> const PrintMode* {
        static PrintMode magenta(AddCsiSymbol("95m"), AddCsiSymbol("39m"));

        return &magenta;
    }

    auto ForegroundColor::BrightCyan() -> const PrintMode* {
        static PrintMode cyan(AddCsiSymbol("96m"), AddCsiSymbol("39m"));

        return &cyan;
    }

    auto ForegroundColor::BrightWhite() -> const PrintMode* {
        static PrintMode white(AddCsiSymbol("97m"), AddCsiSymbol("39m"));

        return &white;
    }

    auto ForegroundColor::TrueColor(size_t r, size_t g, size_t b) -> const PrintMode* {
        static const auto tupleHash = [](const std::tuple<size_t, size_t, size_t>& tuple) {
            const auto& [a, b, c] = tuple;

            return c ^ (a ^ (b << 1)) << 1;
        };

        static std::unordered_map<std::tuple<size_t, size_t, size_t>, PrintMode, decltype(tupleHash)> rgbColorHashTable{};

        const auto key = std::make_tuple(r, g, b);
        if (rgbColorHashTable.count(key) == 0) {
            rgbColorHashTable.emplace(key, PrintMode(AddCsiSymbol(std::format("38;2;{};{};{}m", r, g, b)), AddCsiSymbol("39m")));
        }

        return &rgbColorHashTable.at(key);
    }

    auto ForegroundColor::IndexColor(size_t color) -> const PrintMode* {
        static std::unordered_map<size_t, PrintMode> byteColorHashTable{};

        if (byteColorHashTable.count(color) == 0) {
            byteColorHashTable.emplace(color, PrintMode(AddCsiSymbol(std::format("38;5;{}m", color)), AddCsiSymbol("39m")));
        }

        return &byteColorHashTable.at(color);
    }
}
