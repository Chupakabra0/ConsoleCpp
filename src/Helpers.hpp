#pragma once
#include <string>

#define ESC_SYMBOL '\x1b'
#define BLANK_SYMBOL ' '

inline std::string AddEscSymbol(const std::string& str) {
    return ESC_SYMBOL + str;
}

inline std::string AddCsiSymbol(const std::string& str) {
    return AddEscSymbol("[" + str);
}
