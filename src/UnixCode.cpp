#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

#include "WindowConsole.hpp"
#include "Helpers.hpp"

namespace console_cpp {
    class RawTerminalModeWrapper {
    public:
        explicit RawTerminalModeWrapper() {
            tcgetattr(STDIN_FILENO, &this->originalSettings_);
            termios new_settings = this->originalSettings_;
            new_settings.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
        }

        RawTerminalModeWrapper(const RawTerminalModeWrapper&) = delete;

        RawTerminalModeWrapper(RawTerminalModeWrapper&&) = delete;

        RawTerminalModeWrapper& operator=(const RawTerminalModeWrapper&) = delete;

        RawTerminalModeWrapper& operator=(RawTerminalModeWrapper&&) = delete;

        ~RawTerminalModeWrapper() {
            tcsetattr(STDIN_FILENO, TCSANOW, &this->originalSettings_);
        }

    private:
        termios originalSettings_{};
    };

    class StdinNullBufferModeWrapper {
    public:
        explicit StdinNullBufferModeWrapper()
            : originalBuffer_(*std::cin.rdbuf())  {
            setvbuf(stdin, nullptr, _IONBF, 0);
        }

        StdinNullBufferModeWrapper(const StdinNullBufferModeWrapper&) = delete;

        StdinNullBufferModeWrapper(StdinNullBufferModeWrapper&&) = delete;

        StdinNullBufferModeWrapper& operator=(const StdinNullBufferModeWrapper&) = delete;

        StdinNullBufferModeWrapper& operator=(StdinNullBufferModeWrapper&&) = delete;

        ~StdinNullBufferModeWrapper() {
            std::cin.rdbuf(&this->originalBuffer_.get());
        }

    private:
        std::reference_wrapper<std::streambuf> originalBuffer_;
    };

    auto IsCursorVisible_() -> bool {
        std::cout << AddCsiSymbol("?25$p") << std::flush;

        const RawTerminalModeWrapper terminalModeWrapper{};

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

    auto khbit() -> int {
        const RawTerminalModeWrapper rawTerminalModeWrapper{};
        const StdinNullBufferModeWrapper stdinNullBufferModeWrapper{};

        int bytesWaiting{};
        ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);

        return bytesWaiting;
    }

    enum class InputType : int {
        UTF8_INPUT,
        ESC_SEQUENCE,
        CSI_SEQUENCE
    };

    auto GetUTF8Input() -> std::pair<std::vector<unsigned char>, InputType> {
        std::vector<unsigned char> result{};

        result.emplace_back(getchar());

        while (khbit() != 0) {
            result.emplace_back(getchar());
        }

        std::clog << static_cast<unsigned>(result.front());
        for (int i = 1; i < result.size(); ++i) {
            std::clog << ", " << static_cast<unsigned>(result[i]);
        }
        std::clog << std::endl;

        if (result.size() > 1 && *result.begin() == ESC_SYMBOL) {
            return result.size() > 2 && *std::next(result.begin()) == '[' ?
                   std::make_pair(std::vector(std::next(result.begin(), 2), result.end()), InputType::CSI_SEQUENCE) :
                   std::make_pair(std::vector(std::next(result.begin()), result.end()), InputType::ESC_SEQUENCE);
        }

//        // TODO: handle arrow keys
//        if (result.front() > 193) {
//            result.emplace_back(getchar());
//        }
//        if (result.front() > 223) {
//            result.emplace_back(getchar());
//        }
//        if (result.front() > 239) {
//            result.emplace_back(getchar());
//        }

        return std::make_pair(result, InputType::UTF8_INPUT);
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
            case U'\x1b': {
                return KeyCode::ESCAPE;
            }
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
            case U'\b': case U'\x7f': {
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
            case 46785u: {
                return KeyCode::UP;
            }
            case 46786u: {
                return KeyCode::DOWN;
            }
            case 46787u: {
                return KeyCode::RIGHT;
            }
            case 46788u: {
                return KeyCode::LEFT;
            }
            case 46789u: {
                return KeyCode::NUMPAD5;
            }
            case 46790u: {
                return KeyCode::END;
            }
            case 3677347262u: {
                return KeyCode::PGDN;
            }
            case 46792u: {
                return KeyCode::HOME;
            }
            case 3677347198u: {
                return KeyCode::PGUP;
            }
            case 3677347006u: {
                return KeyCode::INSERT;
            }
            case 3677347070u: {
                return KeyCode::DEL;
            }
            case 46032u: {
                return KeyCode::F1;
            }
            case 46033u: {
                return KeyCode::F2;
            }
            case 46034u: {
                return KeyCode::F3;
            }
            case 46035u: {
                return KeyCode::F4;
            }
            default: {
//                throw std::runtime_error("Unknown utf-8 input");
                return keyCode;
            }
        }
    }

    auto ConvertEscSequenceToKeyCode(const std::vector<unsigned char>& bytes) -> KeyCode {
        auto keyCode = KeyCode::UNKNOWN;

        if (bytes.empty()) {
            return keyCode;
        }

        switch (bytes.front()) {
            case 79: {
                if (bytes.size() > 1) {
                    switch (*std::next(bytes.begin())) {
                        case 80: {
                            keyCode = KeyCode::F1;
                            break;
                        }
                        case 81: {
                            keyCode = KeyCode::F2;
                            break;
                        }
                        case 82: {
                            keyCode = KeyCode::F3;
                            break;
                        }
                        case 83: {
                            keyCode = KeyCode::F4;
                            break;
                        }
                        default: {
                            break;
                        }
                    }
                }
            }
            default: {
                break;
            }
        }

        return keyCode;
    }

    auto ConvertCsiSequenceToKeyCode(const std::vector<unsigned char>& bytes) -> KeyCode {
        auto keyCode = KeyCode::UNKNOWN;

        if (bytes.empty()) {
            return keyCode;
        }

        switch (bytes.front()) {
            case 65: {
                keyCode = KeyCode::UP;
                break;
            }
            case 66: {
                keyCode = KeyCode::DOWN;
                break;
            }
            case 67: {
                keyCode = KeyCode::RIGHT;
                break;
            }
            case 68: {
                keyCode = KeyCode::LEFT;
                break;
            }
            case 69: {
                keyCode = KeyCode::NUMPAD5;
                break;
            }
            case 70: {
                keyCode = KeyCode::END;
                break;
            }
            case 72: {
                keyCode = KeyCode::HOME;
                break;
            }
            case 50: {
                if (bytes.size() > 1) {
                    if (bytes.size() > 2) {
                        switch (*std::next(bytes.begin())) {
                            case 48: {
                                if (*std::next(bytes.begin(), 2) == 126) {
                                    keyCode = KeyCode::F9;
                                }
                                break;
                            }
                            case 49: {
                                if (*std::next(bytes.begin(), 2) == 126) {
                                    keyCode = KeyCode::F10;
                                }
                                break;
                            }
                            case 51: {
                                if (*std::next(bytes.begin(), 2) == 126) {
                                    keyCode = KeyCode::F11;
                                }
                                break;
                            }
                            case 52: {
                                if (*std::next(bytes.begin(), 2) == 126) {
                                    keyCode = KeyCode::F12;
                                }
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                    }
                    else if (*std::next(bytes.begin()) == 126) {
                        keyCode = KeyCode::INSERT;
                    }
                }

                break;
            }
            case 51: {
                if (bytes.size() > 1 && *std::next(bytes.begin()) == 126) {
                    keyCode = KeyCode::DEL;
                }
                break;
            }
            case 53: {
                if (bytes.size() > 1 && *std::next(bytes.begin()) == 126) {
                    keyCode = KeyCode::PGUP;
                }
                break;
            }
            case 54: {
                if (bytes.size() > 1 && *std::next(bytes.begin()) == 126) {
                    keyCode = KeyCode::PGDN;
                }
                break;
            }
            case 49: {
                if (bytes.size() > 2) {
                    switch (*std::next(bytes.begin())) {
                        case 53: {
                            if (*std::next(bytes.begin(), 2) == 126) {
                                keyCode = KeyCode::F5;
                            }
                            break;
                        }
                        case 55: {
                            if (*std::next(bytes.begin(), 2) == 126) {
                                keyCode = KeyCode::F6;
                            }
                            break;
                        }
                        case 56: {
                            if (*std::next(bytes.begin(), 2) == 126) {
                                keyCode = KeyCode::F7;
                            }
                            break;
                        }
                        case 57: {
                            if (*std::next(bytes.begin(), 2) == 126) {
                                keyCode = KeyCode::F8;
                            }
                            break;
                        }
                    }
                }
            }
            default: {
                break;
            }
        }

        return keyCode;
    }

    auto ConvertInputToKeyCode(const std::pair<std::vector<unsigned char>, InputType>& input) -> KeyCode {
        auto keyCode = KeyCode::UNKNOWN;
        const auto& [bytes, inputType] = input;

        switch (inputType) {
            case InputType::UTF8_INPUT: {
                const auto character = ConvertUTF8DecToUTF16BEDec(bytes);
                keyCode = CovertCharacterToKeyCode(character);

                std::cout << character << " = " << static_cast<unsigned>(keyCode) << std::endl;

                break;
            }
            case InputType::ESC_SEQUENCE: {
                keyCode = ConvertEscSequenceToKeyCode(bytes);

                std::cout << "Escape sequence" << " = " << static_cast<unsigned>(keyCode) << std::endl;


                break;
            }
            case InputType::CSI_SEQUENCE: {
                keyCode = ConvertCsiSequenceToKeyCode(bytes);

                std::cout << "CSI sequence" << " = " << static_cast<unsigned>(keyCode) << std::endl;

                break;
            }
            default: {
                break;
            }
        }

        return keyCode;
    }

    auto WindowConsole::GetKeyPress() -> KeyCode {
        const RawTerminalModeWrapper rawTerminalModeWrapper{};
        const StdinNullBufferModeWrapper stdinNullBufferModeWrapper{};

        const auto input = GetUTF8Input();
        const auto keyCode = ConvertInputToKeyCode(input);

        return keyCode;
    }
}
