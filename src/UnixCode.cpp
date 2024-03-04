#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

#include "WindowConsole.hpp"

#include <iostream>
#include <vector>
#include <cstdint>
#include <locale>
#include <codecvt>

namespace console_cpp {
    auto IsCursorVisible_() -> bool {
        std::cout << "\x1b[?25$p" << std::flush;

        struct termios oldt{};
        struct termios newt{};
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        char response[10]{};
        std::cin.read(response, 9);
        response[9] = '\0';

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

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

    auto WindowConsole::GetKeyPress() -> KeyCode {
        // Store the original terminal settings
        termios original_settings{};
        tcgetattr(STDIN_FILENO, &original_settings);

        // Set terminal to raw mode
        termios new_settings = original_settings;
        new_settings.c_lflag &= ~(ICANON | ECHO);
        new_settings.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

        const auto a = [](int num) -> char {
            return num & 0b11111111;
        };
        const auto b = [](int num) -> char {
            return (num & 0b11111111'00000000) >> 8;
        };
        const auto c = [](int num) -> char {
            return (num & 0b11111111'00000000'00000000) >> 16;
        };
        const auto d = [](int num) -> char {
            return (num & 0b01111111'00000000'00000000'00000000) >> 24;
        };

        int key1{};
        int key2{};
        int key3{};
        int key4{};

        key1 = getchar();
        std::clog << (int)key1 << std::endl;
        int temp = 1;

        if (key1 > 193) {
            key2 = getchar();
            std::clog << (int)key2 << std::endl;
            ++temp;
        }
        if (key1 > 223) {
            key3 = getchar();
            std::clog << (int)key3 << std::endl;
            ++temp;
        }
        if (key1 > 239) {
            key4 = getchar();
            std::clog << (int)key4 << std::endl;
            ++temp;
        }

        int result{};
        int offset{};
        if (key4 != 0) {
            result |= key4 << offset;
            offset += 8;
        }
        if (key3 != 0) {
            result |= key3 << offset;
            offset += 8;
        }
        if (key2 != 0) {
            result |= key2 << offset;
            offset += 8;
        }
        if (key1 != 0) {
            result |= key1 << offset;
            offset += 8;
        }
        
        //const auto testFunc = [](int bytes) {
        //    if ((bytes & 0xF8) == 0xF0) {
        //        return 4;
        //    }
        //    else if ((bytes & 0xF0) == 0xE0) {
        //        return 3;
        //    }
        //    else if ((bytes & 0xE0) == 0xC0) {
        //        return 2;
        //    }
        //    else /*if ((bytes & 0x80) == 0x00)*/ {
        //        return 1;
        //    }
        //};

        char32_t character{};
        switch (temp) {
            case 1: {
                character = (char32_t)(a(result) & 0x7F);
                break;
            }
            case 2: {
                character = (char32_t)(((a(result) & 0x1F) << 6) | (b(result) & 0x3F));
                break;
            }
            case 3: {
                character = (char32_t)(((a(result) & 0x0F) << 12) | ((b(result) & 0x3F) << 6) | ((c(result) & 0x3F)));
                break;
            }
            case 4: {
                character = 0;
                break;
            }
            default: {
                break;
            }
        }

        std::cout << "Character: " << (char32_t)character << " = " << (int)character << std::endl;

        tcsetattr(STDIN_FILENO, TCSANOW, &original_settings);

        return KeyCode::UNKNOWN;
    }
}
