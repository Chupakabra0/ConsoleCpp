#include "BackgroundColor.hpp"

#include <format>
#include <unordered_map>
#include <tuple>

namespace console_cpp {
    auto BackgroundColor::Default() -> const PrintMode* {
        static PrintMode none(AddCsiSymbol("49m"), AddCsiSymbol("49m"));

        return &none;
    }

    auto BackgroundColor::Black() -> const PrintMode* {
        static PrintMode black(AddCsiSymbol("40m"), AddCsiSymbol("49m"));

        return &black;
    }

    auto BackgroundColor::Red() -> const PrintMode* {
        static PrintMode red(AddCsiSymbol("41m"), AddCsiSymbol("49m"));

        return &red;
    }

    auto BackgroundColor::Green() -> const PrintMode* {
        static PrintMode green(AddCsiSymbol("42m"), AddCsiSymbol("49m"));

        return &green;
    }

    auto BackgroundColor::Yellow() -> const PrintMode* {
        static PrintMode yellow(AddCsiSymbol("43m"), AddCsiSymbol("49m"));

        return &yellow;
    }

    auto BackgroundColor::Blue() -> const PrintMode* {
        static PrintMode blue(AddCsiSymbol("44m"), AddCsiSymbol("49m"));

        return &blue;
    }

    auto BackgroundColor::Magenta() -> const PrintMode* {
        static PrintMode magenta(AddCsiSymbol("45m"), AddCsiSymbol("49m"));

        return &magenta;
    }

    auto BackgroundColor::Cyan() -> const PrintMode* {
        static PrintMode cyan(AddCsiSymbol("46m"), AddCsiSymbol("49m"));

        return &cyan;
    }

    auto BackgroundColor::White() -> const PrintMode* {
        static PrintMode white(AddCsiSymbol("47m"), AddCsiSymbol("49m"));

        return &white;
    }

    auto BackgroundColor::BrightBlack() -> const PrintMode* {
        static PrintMode black(AddCsiSymbol("100m"), AddCsiSymbol("49m"));

        return &black;
    }

    auto BackgroundColor::BrightRed() -> const PrintMode* {
        static PrintMode red(AddCsiSymbol("101m"), AddCsiSymbol("49m"));

        return &red;
    }

    auto BackgroundColor::BrightGreen() -> const PrintMode* {
        static PrintMode green(AddCsiSymbol("102m"), AddCsiSymbol("49m"));

        return &green;
    }

    auto BackgroundColor::BrightYellow() -> const PrintMode* {
        static PrintMode yellow(AddCsiSymbol("103m"), AddCsiSymbol("49m"));

        return &yellow;
    }

    auto BackgroundColor::BrightBlue() -> const PrintMode* {
        static PrintMode blue(AddCsiSymbol("104m"), AddCsiSymbol("49m"));

        return &blue;
    }

    auto BackgroundColor::BrightMagenta() -> const PrintMode* {
        static PrintMode magenta(AddCsiSymbol("105m"), AddCsiSymbol("49m"));

        return &magenta;
    }

    auto BackgroundColor::BrightCyan() -> const PrintMode* {
        static PrintMode cyan(AddCsiSymbol("106m"), AddCsiSymbol("49m"));

        return &cyan;
    }

    auto BackgroundColor::BrightWhite() -> const PrintMode* {
        static PrintMode white(AddCsiSymbol("107m"), AddCsiSymbol("49m"));

        return &white;
    }

    auto BackgroundColor::TrueColor(size_t r, size_t g, size_t b) -> const PrintMode* {
        static const auto tupleHash = [](const std::tuple<size_t, size_t, size_t>& tuple) {
            const auto& [a, b, c] = tuple;

            return c ^ (a ^ (b << 1)) << 1;
        };

        static std::unordered_map<std::tuple<size_t, size_t, size_t>, PrintMode, decltype(tupleHash)> rgbColorHashTable{};

        const auto key = std::make_tuple(r, g, b);
        if (rgbColorHashTable.count(key) == 0) {
            rgbColorHashTable.emplace(key, PrintMode(AddCsiSymbol(std::format("48;2;{};{};{}m", r, g, b)), AddCsiSymbol("49m")));
        }

        return &rgbColorHashTable.at(key);
    }

    auto BackgroundColor::IndexColor(size_t color) -> const PrintMode* {
        static std::unordered_map<size_t, PrintMode> byteColorHashTable{};

        if (byteColorHashTable.count(color) == 0) {
            byteColorHashTable.emplace(color, PrintMode(AddCsiSymbol(std::format("48;5;{}m", color)), AddCsiSymbol("49m")));
        }

        return &byteColorHashTable.at(color);
    }
}
