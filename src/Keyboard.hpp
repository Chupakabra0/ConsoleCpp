#pragma once

namespace console_cpp {
    enum class KeyCode : int {
        UNKNOWN = -1,

        BACK = 8,
        TAB = 9,
        CLEAR = 12,
        ENTER = 13,

        SHIFT = 16,
        CONTROL = 17,
        MENU = 18,
        PAUSE = 19,
        CAPITAL = 20,

        KANA = 21,
        HANGEUL = 21,
        HANGUL = 21,
        IME_ON = 22,
        JUNJA = 23,
        FINAL = 24,
        HANJA = 25,
        KANJI = 25,
        IME_OFF = 26,

        ESCAPE = 27,

        CONVERT = 28,
        NONCONVERT = 29,
        ACCEPT = 30,
        MODECHANGE = 31,

        SPACE = 32,
        PGUP = 33,
        PGDN = 34,
        END = 35,
        HOME = 36,
        LEFT = 37,
        UP = 38,
        RIGHT = 39,
        DOWN = 40,
        SELECT = 41,
        PRINT = 42,
        EXECUTE = 43,
        SNAPSHOT = 44,
        INSERT = 45,
        DEL = 46,
        HELP = 47,

        LWIN = 91,
        RWIN = 92,
        APPS = 93,

        SLEEP = 95,

        NUMPAD0 = 96,
        NUMPAD1 = 97,
        NUMPAD2 = 98,
        NUMPAD3 = 99,
        NUMPAD4 = 100,
        NUMPAD5 = 101,
        NUMPAD6 = 102,
        NUMPAD7 = 103,
        NUMPAD8 = 104,
        NUMPAD9 = 105,
        MULTIPLY = 106,
        ADD = 107,
        SEPARATOR = 108,
        SUBTRACT = 109,
        DECIMAL = 110,
        DIVIDE = 111,
        F1 = 112,
        F2 = 113,
        F3 = 114,
        F4 = 115,
        F5 = 116,
        F6 = 117,
        F7 = 118,
        F8 = 119,
        F9 = 120,
        F10 = 121,
        F11 = 122,
        F12 = 123,
        F13 = 124,
        F14 = 125,
        F15 = 126,
        F16 = 127,
        F17 = 128,
        F18 = 129,
        F19 = 130,
        F20 = 131,
        F21 = 132,
        F22 = 133,
        F23 = 134,
        F24 = 135,

        NUMLOCK = 144,
        SCROLL = 145,

        OEM_NEC_EQUAL = 146,

        OEM_FJ_JISHO = 146,
        OEM_FJ_MASSHOU = 147,
        OEM_FJ_TOUROKU = 148,
        OEM_FJ_LOYA = 149,
        OEM_FJ_ROYA = 150,

        LSHIFT = 160,
        RSHIFT = 161,
        LCONTROL = 162,
        RCONTROL = 163,
        LMENU = 164,
        RMENU = 165,

        VOLUME_MUTE = 173,
        VOLUME_DOWN = 174,
        VOLUME_UP = 175,

        OEM_1 = 186,
        OEM_PLUS = 187,
        OEM_COMMA = 188,
        OEM_MINUS = 189,
        OEM_PERIOD = 190,
        OEM_2 = 191,
        OEM_3 = 192,

        OEM_4 = 219,
        OEM_5 = 220,
        OEM_6 = 221,
        OEM_7 = 222,
        OEM_8 = 223,

        OEM_AX = 225,
        OEM_102 = 226,
        ICO_HELP = 227,
        ICO_00 = 228,

        PROCESSKEY = 229,
        ICO_CLEAR = 230,

        PACKET = 231,

        OEM_RESET = 233,
        OEM_JUMP = 234,
        OEM_PA1 = 235,
        OEM_PA2 = 236,
        OEM_PA3 = 237,
        OEM_WSCTRL = 238,
        OEM_CUSEL = 239,
        OEM_ATTN = 240,
        OEM_FINISH = 241,
        OEM_COPY = 242,
        OEM_AUTO = 243,
        OEM_ENLW = 244,
        OEM_BACKTAB = 245,

        ATTN = 246,
        CRSEL = 247,
        EXSEL = 248,
        EREOF = 249,
        PLAY = 250,
        ZOOM = 251,
        NONAME = 252,
        PA1 = 253,
        OEM_CLEAR = 254
    };

    
#if defined(WIN32)

#elif defined(__linux__)
    #include <sys/ioctl.h>
    #include <termios.h>

    static int key_press() { // not working: ¹ (251), num lock (-144), caps lock (-20), windows key (-91), context menu key (-93)
        struct termios term {};
        tcgetattr(0, &term);

        while (true) {
            term.c_lflag &= ~(ICANON | ECHO); // turn off line buffering and echoing
            tcsetattr(0, TCSANOW, &term);

            int nbbytes;
            ioctl(0, FIONREAD, &nbbytes); // 0 is STDIN

            while (!nbbytes) {
                sleep(0.01);
                fflush(stdout);
                ioctl(0, FIONREAD, &nbbytes); // 0 is STDIN
            }

            int key = static_cast<int>(getchar());

            if (key == 27 || key == 194 || key == 195) { // escape, 194/195 is escape for °ß´äöüÄÖÜ
                key = static_cast<int>(getchar());

                if (key == 91) { // [ following escape
                    key = static_cast<int>(getchar()); // get code of next char after \e[

                    if (key == 49) { // F5-F8
                        key = 62 + static_cast<int>(getchar()); // 53, 55-57
                        if (key == 115) key++; // F5 code is too low by 1
                        getchar(); // take in following ~ (126), but discard code
                    }
                    else if (key == 50) { // insert or F9-F12
                        key = static_cast<int>(getchar());

                        if (key == 126) { // insert
                            key = 45;
                        }
                        else { // F9-F12
                            key += 71; // 48, 49, 51, 52
                            if (key < 121) key++; // F11 and F12 are too low by 1
                            getchar(); // take in following ~ (126), but discard code
                        }
                    }
                    else if (key == 51 || key == 53 || key == 54) { // delete, page up/down
                        getchar(); // take in following ~ (126), but discard code
                    }
                }
                else if (key == 79) { // F1-F4
                    key = 32 + static_cast<int>(getchar()); // 80-83
                }

                key = -key; // use negative numbers for escaped keys
            }

            term.c_lflag |= (ICANON | ECHO); // turn on line buffering and echoing
            tcsetattr(0, TCSANOW, &term);

            switch (key) {
            case  127: return   8; // backspace
            case  -27: return  27; // escape
            case  -51: return 127; // delete
            case -164: return 132; // ä
            case -182: return 148; // ö
            case -188: return 129; // ü
            case -132: return 142; // Ä
            case -150: return 153; // Ö
            case -156: return 154; // Ü
            case -159: return 225; // ß
            case -181: return 230; // µ
            case -167: return 245; // §
            case -176: return 248; // °
            case -178: return 253; // ²
            case -179: return 252; // ³
            case -180: return 239; // ´
            case  -65: return -38; // up arrow
            case  -66: return -40; // down arrow
            case  -68: return -37; // left arrow
            case  -67: return -39; // right arrow
            case  -53: return -33; // page up
            case  -54: return -34; // page down
            case  -72: return -36; // pos1
            case  -70: return -35; // end
            case    0: continue;
            case    1: continue; // disable Ctrl + a
            case    2: continue; // disable Ctrl + b
            case    3: continue; // disable Ctrl + c (terminates program)
            case    4: continue; // disable Ctrl + d
            case    5: continue; // disable Ctrl + e
            case    6: continue; // disable Ctrl + f
            case    7: continue; // disable Ctrl + g
            case    8: continue; // disable Ctrl + h
                //case    9: continue; // disable Ctrl + i (ascii for tab)
                //case   10: continue; // disable Ctrl + j (ascii for new line)
            case   11: continue; // disable Ctrl + k
            case   12: continue; // disable Ctrl + l
            case   13: continue; // disable Ctrl + m
            case   14: continue; // disable Ctrl + n
            case   15: continue; // disable Ctrl + o
            case   16: continue; // disable Ctrl + p
            case   17: continue; // disable Ctrl + q
            case   18: continue; // disable Ctrl + r
            case   19: continue; // disable Ctrl + s
            case   20: continue; // disable Ctrl + t
            case   21: continue; // disable Ctrl + u
            case   22: continue; // disable Ctrl + v
            case   23: continue; // disable Ctrl + w
            case   24: continue; // disable Ctrl + x
            case   25: continue; // disable Ctrl + y
            case   26: continue; // disable Ctrl + z (terminates program)
            default: return key; // any other ASCII character
            }
        }
    }

#endif // Windows/Linux
}
