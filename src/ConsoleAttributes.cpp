#include "ConsoleAttributes.hpp"
#include "WindowConsole.hpp"
#include "Utils.hpp"

namespace console_cpp {
    auto ConsoleAttributes::Default() -> const ConsoleMode* {
        static ConsoleMode none(nullptr, nullptr);

        return &none;
    }

    auto ConsoleAttributes::HideCursor() -> const ConsoleMode* {
        static ConsoleMode hide(
            [](WindowConsole& window) {
                window.HideCursor();
            },
            [](WindowConsole& window) {
                IsCursorVisible_() ? window.ShowCursor() : window.HideCursor();
            }
        );

        return &hide;
    }

    auto ConsoleAttributes::ShowCursor() -> const ConsoleMode* {
        static ConsoleMode show(
            [](WindowConsole& window) {
                window.ShowCursor();
            },
            [](WindowConsole& window) {
                IsCursorVisible_() ? window.ShowCursor() : window.HideCursor();
            }
        );

        return &show;
    }

    auto ConsoleAttributes::EnableBuffer() -> const ConsoleMode* {
        static ConsoleMode buffer(
            [](WindowConsole& window) {
                window.EnableBuffer();
            },
            [](WindowConsole& window) {
                window.DisableBuffer();
            }
        );

        return &buffer;
    }

    auto ConsoleAttributes::DisableBuffer() -> const ConsoleMode* {
        static ConsoleMode buffer(
            [](WindowConsole& window) {
                window.DisableBuffer();
            },
            [](WindowConsole& window) {
                window.DisableBuffer();
            }
        );

        return &buffer;
    }

    auto ConsoleAttributes::EnableAlterScreen() -> const ConsoleMode* {
        static ConsoleMode alterscreen(
            [](WindowConsole& window) {
                window.LaunchAlterScreen();
            },
            [](WindowConsole& window) {
                window.CloseAlterScreen();
            }
        );

        return &alterscreen;
    }

    auto ConsoleAttributes::DisableAlterScreen() -> const ConsoleMode* {
        static ConsoleMode alterscreen(
            [](WindowConsole& window) {
                window.CloseAlterScreen();
            },
            [](WindowConsole& window) {
                window.CloseAlterScreen();
            }
        );

        return &alterscreen;
    }
}
