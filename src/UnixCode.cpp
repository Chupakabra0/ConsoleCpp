#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

#include "WindowConsole.hpp"

#include <fstream>

namespace console_cpp {
    auto IsCursorVisible_() -> bool {
        std::cout << "\x1b[?25$p" << std::flush;

        struct termios oldt{};
        struct termios newt{};
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        char response[10];
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

    auto U32CharWidth_(char32_t chr) -> size_t {
        const int width = wcwidth(chr);
        
        static std::fstream file("log.txt", std::fstream::out);
        file << chr << " = " << width << std::endl;

        return width == -1 ? 0 : width;
    }

    auto WindowConsole::InitSize_() -> void {
        winsize w{};
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        this->SetLimitY(w.ws_row);
        this->SetLimitX(w.ws_col);
    }

    auto WindowConsole::GetKeyPress() -> KeyCode {
        getc(stdin);
        return KeyCode::UNKNOWN;
    }
}
