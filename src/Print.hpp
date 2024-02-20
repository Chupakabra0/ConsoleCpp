#pragma once
#include <string_view>
#include <ostream>

namespace console_cpp {
    std::ostream& PrintUnicode_(std::ostream& out, const std::string& str);
    std::ostream& PrintUnicode_(std::ostream& out, const std::u32string& str);
}
