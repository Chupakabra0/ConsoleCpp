#pragma once
#include "Helpers.hpp"

#include <memory>

namespace console_cpp {
    class PrintMode {
    public:
        explicit PrintMode() = default;

        explicit PrintMode(const std::string& start, const std::string& reset);

        explicit PrintMode(const std::string& start, const std::string& reset, const std::shared_ptr<PrintMode>& next);

        PrintMode(const PrintMode&) = default;

        PrintMode(PrintMode&&) noexcept = default;

        PrintMode& operator=(const PrintMode&) = default;

        PrintMode& operator=(PrintMode&&) noexcept = default;

        virtual ~PrintMode() = default;

        auto GetNext() const -> const PrintMode*;

        auto GetNext() -> PrintMode*;

        auto SetNext(PrintMode* next) -> void;

        auto SetLastNext(PrintMode* next) -> void;

        auto CalcStartStr() const -> std::string;

        auto CalcResetStr() const ->std::string;

    private:
        std::string start_{};
        std::string reset_{};
        std::shared_ptr<PrintMode> next_{};
    };
}
