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

        //std::clog << static_cast<unsigned>(result.front());
        //for (int i = 1; i < result.size(); ++i) {
        //    std::clog << ", " << static_cast<unsigned>(result[i]);
        //}
        //std::clog << std::endl;
        if (result.size() > 1 && (result.front() == ESC_SYMBOL || result.front() == '^')) {
            if (result.size() > 2 && result[1] == '[') {
                return std::make_pair(std::vector(std::next(result.begin(), 2), result.end()), InputType::CSI_SEQUENCE);
            }
            else {
                return std::make_pair(std::vector(std::next(result.begin()), result.end()), InputType::ESC_SEQUENCE);
            }
        }

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
                return KeyCode::GRAVE_ACCENT;
            }
            case U'1': case U'!': {
                return KeyCode::NUM1;
            }
            case U'2': case U'@': {
                return KeyCode::NUM2;
            }
            case U'3': case U'#': {
                return KeyCode::NUM3;
            }
            case U'4': case U'$': {
                return KeyCode::NUM4;
            }
            case U'5': case U'%': {
                return KeyCode::NUM5;
            }
            case U'6': case U'^': {
                return KeyCode::NUM6;
            }
            case U'7': case U'&': {
                return KeyCode::NUM7;
            }
            case U'8': case U'*': {
                return KeyCode::NUM8;
            }
            case U'9': case U'(': {
                return KeyCode::NUM9;
            }
            case U'0': case U')': {
                return KeyCode::NUM0;
            }
            case U'-': case U'_': {
                return KeyCode::MINUS;
            }
            case U'=': case U'+': {
                return KeyCode::PLUS;
            }
            case U'\b': case U'\x7f': {
                return KeyCode::BACKSPACE;
            }
            case U'\t': {
                return KeyCode::TAB;
            }
            case U'q': case U'Q': {
                return KeyCode::Q;
            }
            case U'w': case U'W': {
                return KeyCode::W;
            }
            case U'e': case U'E': {
                return KeyCode::E;
            }
            case U'r': case U'R': {
                return KeyCode::R;
            }
            case U't': case U'T': {
                return KeyCode::T;
            }
            case U'y': case U'Y': {
                return KeyCode::Y;
            }
            case U'u': case U'U': {
                return KeyCode::U;
            }
            case U'i': case U'I': {
                return KeyCode::I;
            }
            case U'o': case U'O': {
                return KeyCode::O;
            }
            case U'p': case U'P': {
                return KeyCode::P;
            }
            case U'[': case U'{': {
                return KeyCode::LEFT_BRACKET;
            }
            case U']': case U'}': {
                return KeyCode::RIGHT_BRACKET;
            }
            case U'\\': case U'|': {
                return KeyCode::BACKSLASH;
            }
            // CAPS LOCK IS ABSENT
            case U'a': case U'A': {
                return KeyCode::A;
            }
            case U's': case U'S': {
                return KeyCode::S;
            }
            case U'd': case U'D': {
                return KeyCode::D;
            }
            case U'f': case U'F': {
                return KeyCode::F;
            }
            case U'g': case U'G': {
                return KeyCode::G;
            }
            case U'h': case U'H': {
                return KeyCode::H;
            }
            case U'j': case U'J': {
                return KeyCode::J;
            }
            case U'k': case U'K': {
                return KeyCode::K;
            }
            case U'l': case U'L': {
                return KeyCode::L;
            }
            case U';': case U':': {
                return KeyCode::SEMICOLON;
            }
            case U'\'': case U'\"': {
                return KeyCode::QUOTE;
            }
            case U'\n': {
                return KeyCode::ENTER;
            }
            // LEFT SHIFT IS ABSENT
            case U'z': case U'Z': {
                return KeyCode::Z;
            }
            case U'x': case U'X': {
                return KeyCode::X;
            }
            case U'c': case U'C': {
                return KeyCode::C;
            }
            case U'v': case U'V': {
                return KeyCode::V;
            }
            case U'b': case U'B': {
                return KeyCode::B;
            }
            case U'n': case U'N': {
                return KeyCode::N;
            }
            case U'm': case U'M': {
                return KeyCode::M;
            }
            case U',': case U'<': {
                return KeyCode::COMMA;
            }
            case U'.': case U'>': {
                return KeyCode::PERIOD;
            }
            case U'/': case U'?': {
                return KeyCode::SLASH;
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
            default: {
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
            case 'O': {
                if (bytes.size() > 1) {
                    switch (bytes[1]) {
                        case 'P': {
                            keyCode = KeyCode::F1;
                            break;
                        }
                        case 'Q': {
                            keyCode = KeyCode::F2;
                            break;
                        }
                        case 'R': {
                            keyCode = KeyCode::F3;
                            break;
                        }
                        case 'S': {
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
            case 'A': {
                keyCode = KeyCode::UP;
                break;
            }
            case 'B': {
                keyCode = KeyCode::DOWN;
                break;
            }
            case 'C': {
                keyCode = KeyCode::RIGHT;
                break;
            }
            case 'D': {
                keyCode = KeyCode::LEFT;
                break;
            }
            case 'E': {
                keyCode = KeyCode::NUMPAD5;
                break;
            }
            case 'F': {
                keyCode = KeyCode::END;
                break;
            }
            case 'H': {
                keyCode = KeyCode::HOME;
                break;
            }
            case '1': {
                if (bytes.size() > 2) {
                    if (bytes.size() > 4 && bytes[2] == ';' && bytes[3] == '2' && bytes[4] == '~') {
                        switch (bytes[1]) {
                            case '5': {
                                keyCode = KeyCode::F17;
                                break;
                            }
                            case '7': {
                                keyCode = KeyCode::F18;
                                break;
                            }
                            case '8': {
                                keyCode = KeyCode::F19;
                                break;
                            }
                            case '9': {
                                keyCode = KeyCode::F20;
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                    }
                    else if (bytes.size() > 3 && bytes[1] == ';' && bytes[2] == '2') {
                        switch (bytes[3]) {
                            case 'P': {
                                keyCode = KeyCode::F13;
                                break;
                            }
                            case 'Q': {
                                keyCode = KeyCode::F14;
                                break;
                            }
                            case 'R': {
                                keyCode = KeyCode::F15;
                                break;
                            }
                            case 'S': {
                                keyCode = KeyCode::F16;
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                    }
                    else if (bytes[2] == '~') {
                        switch (bytes[1]) {
                            case '5': {
                                keyCode = KeyCode::F5;
                                break;
                            }
                            case '7': {
                                keyCode = KeyCode::F6;
                                break;
                            }
                            case '8': {
                                keyCode = KeyCode::F7;
                                break;
                            }
                            case '9': {
                                keyCode = KeyCode::F8;
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                    }
                }
            }
            case '2': {
                if (bytes.size() > 4 && bytes[2] == ';' && bytes[3] == '2' && bytes[4] == '~') {
                    switch (bytes[1]) {
                        case '0': {
                            keyCode = KeyCode::F21;
                            break;
                        }
                        case '1': {
                            keyCode = KeyCode::F22;
                            break;
                        }
                        case '3': {
                            keyCode = KeyCode::F23;
                            break;
                        }
                        case '4': {
                            keyCode = KeyCode::F24;
                            break;
                        }
                        default: {
                            break;
                        }
                    }
                }
                else if (bytes.size() > 1) {
                    if (bytes[2] == '~') {
                        if (bytes.size() > 2) {
                            switch (bytes[1]) {
                                case '0': {
                                    keyCode = KeyCode::F9;
                                    break;
                                }
                                case '1': {
                                    keyCode = KeyCode::F10;
                                    break;
                                }
                                case '3': {
                                    keyCode = KeyCode::F11;
                                    break;
                                }
                                case '4': {
                                    keyCode = KeyCode::F12;
                                    break;
                                }
                                default: {
                                    break;
                                }
                            }
                        }
                        else {
                            keyCode = KeyCode::INSERT;
                        }
                    }
                }

                break;
            }
            case '3': {
                if (bytes.size() > 1 && bytes[1] == '~') {
                    keyCode = KeyCode::DEL;
                }

                break;
            }
            case '5': {
                if (bytes.size() > 1 && bytes[1] == '~') {
                    keyCode = KeyCode::PGUP;
                }

                break;
            }
            case '6': {
                if (bytes.size() > 1 && bytes[1] == '~') {
                    keyCode = KeyCode::PGDN;
                }

                break;
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

                //std::cout << character << " = " << static_cast<unsigned>(keyCode) << std::endl;

                break;
            }
            case InputType::ESC_SEQUENCE: {
                keyCode = ConvertEscSequenceToKeyCode(bytes);

                //std::cout << "Escape sequence" << " = " << static_cast<unsigned>(keyCode) << std::endl;


                break;
            }
            case InputType::CSI_SEQUENCE: {
                keyCode = ConvertCsiSequenceToKeyCode(bytes);

                //std::cout << "CSI sequence" << " = " << static_cast<unsigned>(keyCode) << std::endl;

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
