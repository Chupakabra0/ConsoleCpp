#pragma once
#include "Helpers.hpp"

#include <memory>
#include <functional>

namespace console_cpp {
    class WindowConsole;

    class ConsoleMode {
    public:
        using FunctionType = void(WindowConsole&);

        explicit ConsoleMode() = default;

        explicit ConsoleMode(const std::function<FunctionType>& init, const std::function<FunctionType>& reset);

        explicit ConsoleMode(const std::function<FunctionType>& init, const std::function<FunctionType>& reset, const std::shared_ptr<ConsoleMode>& next);

        ConsoleMode(const ConsoleMode&) = default;

        ConsoleMode(ConsoleMode&&) noexcept = default;

        ConsoleMode& operator=(const ConsoleMode&) = default;

        ConsoleMode& operator=(ConsoleMode&&) = default;

        ~ConsoleMode() = default;

        auto GetNext() const -> const ConsoleMode*;

        auto GetNext() -> ConsoleMode*;

        auto SetNext(ConsoleMode* next) -> void;

        auto SetLastNext(ConsoleMode* next) -> void;

        auto InitExecute(WindowConsole& windowConsole) -> void;

        auto ResetExecute(WindowConsole& windowConsole) -> void;

    private:
        std::function<FunctionType> init_{};
        std::function<FunctionType> reset_{};
        std::shared_ptr<ConsoleMode> next_{};
    };
}
