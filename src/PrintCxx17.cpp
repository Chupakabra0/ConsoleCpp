#include "Print.hpp"
#include "Utils.hpp"

#include <sstream>

#include "include/fmt/ostream.h"

namespace console_cpp {
    std::ostream& PrintUnicode_(std::ostream& out, const std::string& str) {
        fmt::print(out, "{}", str);

        return out;
    }

    std::ostream& PrintUnicode_(std::ostream& out, const std::u32string& str) {
        std::stringstream ss{};

        ss << str;
        fmt::print(out, "{}", ss.str());

        return out;
    }
}
