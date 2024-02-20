#include "Font.hpp"

namespace console_cpp {
    auto Font::None() -> const PrintMode* {
        static PrintMode none(AddCsiSymbol("0m"), AddCsiSymbol("0m"));

        return &none;
    }

    auto Font::Bold() -> const PrintMode* {
        static PrintMode bold(AddCsiSymbol("1m"), AddCsiSymbol("22m"));

        return &bold;
    }

    auto Font::Dim() -> const PrintMode* {
        static PrintMode dim(AddCsiSymbol("2m"), AddCsiSymbol("22m"));

        return &dim;
    }

    auto Font::Italic() -> const PrintMode* {
        static PrintMode italic(AddCsiSymbol("3m"), AddCsiSymbol("23m"));

        return &italic;
    }

    auto Font::Underline() -> const PrintMode* {
        static PrintMode underline(AddCsiSymbol("4m"), AddCsiSymbol("24m"));

        return &underline;
    }

    auto Font::Blinking() -> const PrintMode* {
        static PrintMode blinking(AddCsiSymbol("5m"), AddCsiSymbol("25m"));

        return &blinking;
    }

    auto Font::RapidBlink() -> const PrintMode* {
        static PrintMode rapidBlink(AddCsiSymbol("6m"), AddCsiSymbol("25m"));

        return &rapidBlink;
    }

    auto Font::Invert() -> const PrintMode* {
        static PrintMode invert(AddCsiSymbol("7m"), AddCsiSymbol("27m"));

        return &invert;
    }

    auto Font::Hidden() -> const PrintMode* {
        static PrintMode hidden(AddCsiSymbol("8m"), AddCsiSymbol("28m"));

        return &hidden;
    }

    auto Font::Strikethrough() -> const PrintMode* {
        static PrintMode strikethrough(AddCsiSymbol("9m"), AddCsiSymbol("29m"));

        return &strikethrough;
    }

    auto Font::Default() -> const PrintMode* {
        static PrintMode strikethrough(AddCsiSymbol("10m"), AddCsiSymbol("10m"));

        return &strikethrough;
    }

    auto Font::Fracture() -> const PrintMode* {
        static PrintMode fracture(AddCsiSymbol("20m"), AddCsiSymbol("10m"));

        return &fracture;
    }

    auto Font::DoubleUnderline() -> const PrintMode* {
        static PrintMode doubleUnderline(AddCsiSymbol("21m"), AddCsiSymbol("24m"));

        return &doubleUnderline;
    }

    auto Font::Framed() -> const PrintMode* {
        static PrintMode framed(AddCsiSymbol("51m"), AddCsiSymbol("54m"));

        return &framed;
    }

    auto Font::Encircled() -> const PrintMode* {
        static PrintMode encircled(AddCsiSymbol("52m"), AddCsiSymbol("54m"));

        return &encircled;
    }

    auto Font::Overline() -> const PrintMode* {
        static PrintMode doubleUnderline(AddCsiSymbol("53m"), AddCsiSymbol("55m"));

        return &doubleUnderline;
    }
}
