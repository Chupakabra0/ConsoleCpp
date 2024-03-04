#include <windows.h>
#include <conio.h>

#include "WindowConsole.hpp"

namespace console_cpp {
    auto IsCursorVisible_() -> bool {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo{};
        GetConsoleCursorInfo(out, &cursorInfo);

        return cursorInfo.bVisible;
    }

    auto SetLocale_() -> void {
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    }

    auto WindowConsole::InitSize_() -> void {
        CONSOLE_SCREEN_BUFFER_INFO csbi{};
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        this->width_ = csbi.dwSize.X;
        this->height_ = csbi.dwSize.Y;
    }

    auto WindowConsole::GetKeyPress() -> KeyCode {
        INPUT_RECORD inputRecord{};
        DWORD numEventsRead{};

        for (;;) {
            ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &inputRecord, 1, &numEventsRead);
            if (numEventsRead == 0) {
                continue;
            }

            // process keyboard input
            if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
                const auto virtualKeyCode = inputRecord.Event.KeyEvent.wVirtualKeyCode;

                // numpad processing
                if (!(inputRecord.Event.KeyEvent.dwControlKeyState & ENHANCED_KEY)) {
                    switch (virtualKeyCode) {
                        case VK_END:   return KeyCode::NUMPAD1;
                        case VK_DOWN:  return KeyCode::NUMPAD2;
                        case VK_NEXT:  return KeyCode::NUMPAD3;
                        case VK_LEFT:  return KeyCode::NUMPAD4;
                        case VK_CLEAR: return KeyCode::NUMPAD5;
                        case VK_RIGHT: return KeyCode::NUMPAD6;
                        case VK_HOME:  return KeyCode::NUMPAD7;
                        case VK_UP:    return KeyCode::NUMPAD8;
                        case VK_PRIOR: return KeyCode::NUMPAD9;
                        default:       break;
                    // TODO: rest of numpad keys detection
                    }
                }

                return static_cast<KeyCode>(virtualKeyCode);
            }
        }
    }
}
