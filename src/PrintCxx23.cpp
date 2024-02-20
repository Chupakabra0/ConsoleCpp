#include "Print.hpp"
#include "Utils.hpp"

#include <sstream>
#include <print>

namespace console_cpp {
    std::ostream& PrintUnicode_(std::ostream& out, const std::string& str) {
        std::print(out, "{}", str);

        return out;
    }

    std::ostream& PrintUnicode_(std::ostream& out, const std::u32string& str) {
        std::stringstream ss{};

        ss << str;
        std::print(out, "{}", ss.str());

        return out;
    }
}
