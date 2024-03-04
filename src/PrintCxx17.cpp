#include "Print.hpp"
#include "Utils.hpp"

#include <sstream>

namespace console_cpp {
    std::ostream& PrintUnicode_(std::ostream& out, const std::string& str) {
        std::stringstream ss{};

        ss << str;
        out << ss.str();

        return out;
    }

    std::ostream& PrintUnicode_(std::ostream& out, const std::u32string& str) {
        std::stringstream ss{};

        ss << str;
        out << ss.str();

        return out;
    }
}
