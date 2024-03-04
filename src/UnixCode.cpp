#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

#include "WindowConsole.hpp"

namespace console_cpp {
    class TerminalModeWrapper {
    public:
        explicit TerminalModeWrapper() {
            tcgetattr(STDIN_FILENO, &this->original_settings_);

            // Set terminal to raw mode
            termios new_settings = this->original_settings_;
            new_settings.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
        }

        TerminalModeWrapper(const TerminalModeWrapper&) = delete;

        TerminalModeWrapper(TerminalModeWrapper&&) = delete;

        TerminalModeWrapper& operator=(const TerminalModeWrapper&) = delete;

        TerminalModeWrapper& operator=(TerminalModeWrapper&&) = delete;

        ~TerminalModeWrapper() {
            tcsetattr(STDIN_FILENO, TCSANOW, &this->original_settings_);
        }

    private:
        termios original_settings_{};
    };

    auto IsCursorVisible_() -> bool {
        std::cout << "\x1b[?25$p" << std::flush;

        const TerminalModeWrapper terminalModeWrapper{};

        char response[10]{};
        std::cin.read(response, 9);
        response[9] = '\0';

        switch (response[6] - '0') {
            case 1:  return true;
            case 2:  return false;
            default: return false;
        }
    }

    auto SetLocale_() -> void {

    }

    auto WindowConsole::InitSize_() -> void {
        winsize w{};
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        this->width_ = w.ws_col;
        this->height_ = w.ws_row;
    }

    template<class T1, class T2>
    auto GetFirstFromLast8Bits(T2 val) -> T1 {
        return static_cast<T1>(val & 0b11111111);
    }

    template<class T1, class T2>
    auto GetSecondFromLast8Bits(T2 val) -> T1 {
        return static_cast<T1>((val & 0b11111111'00000000) >> 8);
    }

    template<class T1, class T2>
    auto GetThirdFromLast8Bits(T2 val) -> T1 {
        return static_cast<T1>((val & 0b11111111'00000000'00000000) >> 16);
    }

    template<class T1, class T2>
    auto GetFourthFromLast8Bits(T2 val) -> T1 {
        return static_cast<T1>((val & 0b01111111'00000000'00000000'00000000) >> 24);
    }

    auto GetUTF8Input() -> std::vector<unsigned char> {
        std::vector<unsigned char> result{};

        result.emplace_back(getchar());

        // TODO: handle arrow keys
        if (result.front() > 193) {
            result.emplace_back(getchar());
        }
        if (result.front() > 223) {
            result.emplace_back(getchar());
        }
        if (result.front() > 239) {
            result.emplace_back(getchar());
        }

        return result;
    }

    auto ConvertUTF8DecBytesToDec(const std::vector<unsigned char>& utf8Bytes) -> unsigned {
        unsigned result{};
        int offset{};

        if (utf8Bytes.size() >= 4) {
            result |= utf8Bytes[3] << (offset++ * 8);
        }
        if (utf8Bytes.size() >= 3) {
            result |= utf8Bytes[2] << (offset++ * 8);
        }
        if (utf8Bytes.size() >= 2) {
            result |= utf8Bytes[1] << (offset++ * 8);
        }
        if (utf8Bytes.size() >= 1) {
            result |= utf8Bytes[0] << (offset++ * 8);
        }

        return result;
    }

    auto ConvertUTF8DecToUTF16BEDec(const std::vector<unsigned char>& utf8Bytes) -> char32_t {
        const auto utf8Dec = ConvertUTF8DecBytesToDec(utf8Bytes);

        char32_t character{};
        switch (utf8Bytes.size()) {
            case 1: {
                const auto a = GetFirstFromLast8Bits<char>(utf8Dec);
                character = static_cast<char32_t>(a & 0b01111111);

                break;
            }
            case 2: {
                const auto a = GetFirstFromLast8Bits<char>(utf8Dec);
                const auto b = GetSecondFromLast8Bits<char>(utf8Dec);
                character = static_cast<char32_t>(((b & 0b0011111) << 6) | (a & 0b00111111));

                break;
            }
            case 3: {
                const auto a = GetFirstFromLast8Bits<char>(utf8Dec);
                const auto b = GetSecondFromLast8Bits<char>(utf8Dec);
                const auto c = GetThirdFromLast8Bits<char>(utf8Dec);
                character = static_cast<char32_t>(((c & 0b00001111) << 12) | ((b & 0b00111111) << 6) | (a & 0b00111111));

                break;
            }
            case 4: {
                const auto a = GetFirstFromLast8Bits<char>(utf8Dec);
                const auto b = GetSecondFromLast8Bits<char>(utf8Dec);
                const auto c = GetThirdFromLast8Bits<char>(utf8Dec);
                const auto d = GetFourthFromLast8Bits<char>(utf8Dec);
                const auto cp = static_cast<char32_t>(
                    (((d & 0b00000111) << 18) | ((c & 0b00111111) << 12) | ((b & 0b00111111) << 6) | (a & 0b00111111)) - 0b00000001'00000000'00000000
                );

                const auto highSurrogate = static_cast<char32_t>(0b11011000'00000000 + ((cp >> 10) & 0b00000011'11111111));
                const auto lowSurrogate  = static_cast<char32_t>(0b11011100'00000000 + (cp & 0b00000011'11111111));

                character = static_cast<char32_t>((highSurrogate << 16) | lowSurrogate);

                break;
            }
            default: {
                break;
            }
        }

        return character;
    }

    auto CovertCharacterToKeyCode(char32_t character) -> KeyCode {
        KeyCode keyCode = KeyCode::UNKNOWN;

        // TODO: ru/ua layouts
        switch (character) {
            case U'`': case U'~': {
                return KeyCode::OEM_3;
            }
            case U'1': case U'!': {
                return KeyCode::KEY_1;
            }
            case U'2': case U'@': {
                return KeyCode::KEY_2;
            }
            case U'3': case U'#': {
                return KeyCode::KEY_3;
            }
            case U'4': case U'$': {
                return KeyCode::KEY_4;
            }
            case U'5': case U'%': {
                return KeyCode::KEY_5;
            }
            case U'6': case U'^': {
                return KeyCode::KEY_6;
            }
            case U'7': case U'&': {
                return KeyCode::KEY_7;
            }
            case U'8': case U'*': {
                return KeyCode::KEY_8;
            }
            case U'9': case U'(': {
                return KeyCode::KEY_9;
            }
            case U'0': case U')': {
                return KeyCode::KEY_0;
            }
            case U'-': case U'_': {
                return KeyCode::OEM_MINUS;
            }
            case U'=': case U'+': {
                return KeyCode::OEM_PLUS;
            }
            case U'\b': {
                return KeyCode::BACK;
            }
            case U'\t': {
                return KeyCode::TAB;
            }
            case U'q': case U'Q': {
                return KeyCode::KEY_Q;
            }
            case U'w': case U'W': {
                return KeyCode::KEY_W;
            }
            case U'e': case U'E': {
                return KeyCode::KEY_E;
            }
            case U'r': case U'R': {
                return KeyCode::KEY_R;
            }
            case U't': case U'T': {
                return KeyCode::KEY_T;
            }
            case U'y': case U'Y': {
                return KeyCode::KEY_Y;
            }
            case U'u': case U'U': {
                return KeyCode::KEY_U;
            }
            case U'i': case U'I': {
                return KeyCode::KEY_I;
            }
            case U'o': case U'O': {
                return KeyCode::KEY_O;
            }
            case U'p': case U'P': {
                return KeyCode::KEY_P;
            }
            case U'[': case U'{': {
                return KeyCode::OEM_4;
            }
            case U']': case U'}': {
                return KeyCode::OEM_6;
            }
            case U'\\': case U'|': {
                return KeyCode::OEM_5;
            }
            // CAPS LOCK IS ABSENT
            case U'a': case U'A': {
                return KeyCode::KEY_A;
            }
            case U's': case U'S': {
                return KeyCode::KEY_S;
            }
            case U'd': case U'D': {
                return KeyCode::KEY_D;
            }
            case U'f': case U'F': {
                return KeyCode::KEY_F;
            }
            case U'g': case U'G': {
                return KeyCode::KEY_G;
            }
            case U'h': case U'H': {
                return KeyCode::KEY_H;
            }
            case U'j': case U'J': {
                return KeyCode::KEY_J;
            }
            case U'k': case U'K': {
                return KeyCode::KEY_K;
            }
            case U'l': case U'L': {
                return KeyCode::KEY_L;
            }
            case U';': case U':': {
                return KeyCode::OEM_1;
            }
            case U'\'': case U'\"': {
                return KeyCode::OEM_7;
            }
            case U'\n': {
                return KeyCode::ENTER;
            }
            // LEFT SHIFT IS ABSENT
            case U'z': case U'Z': {
                return KeyCode::KEY_Z;
            }
            case U'x': case U'X': {
                return KeyCode::KEY_X;
            }
            case U'c': case U'C': {
                return KeyCode::KEY_C;
            }
            case U'v': case U'V': {
                return KeyCode::KEY_V;
            }
            case U'b': case U'B': {
                return KeyCode::KEY_B;
            }
            case U'n': case U'N': {
                return KeyCode::KEY_N;
            }
            case U'm': case U'M': {
                return KeyCode::KEY_M;
            }
            case U',': case U'<': {
                return KeyCode::OEM_COMMA;
            }
            case U'.': case U'>': {
                return KeyCode::OEM_PERIOD;
            }
            case U'/': case U'?': {
                return KeyCode::OEM_2;
            }
            // RIGHT SHIFT IS ABSENT
            // LEFT CTRL IS ABSENT
            // WIN/SUPER IS ABSENT
            // LEFT ALT IS ABSENT
            case U' ': {
                return KeyCode::SPACE;
            }
            // RIGHT ALT IS ABSENT
            // RIGHT ALT IS ABSENT
            // MENU IS ABSENT
            // LEFT CTRL IS ABSENT
            // TODO numpad
            // TODO arrows
            default: {
                return keyCode;
            }
        }
    }

    auto WindowConsole::GetKeyPress() -> KeyCode {
        const TerminalModeWrapper terminalModeWrapper{};

        const auto utf8Bytes = GetUTF8Input();
        const auto character = ConvertUTF8DecToUTF16BEDec(utf8Bytes);
        const auto keyCode   = CovertCharacterToKeyCode(character);

        std::cout << character << " = " << static_cast<int>(character) << std::endl;

        return keyCode;
    }
}
