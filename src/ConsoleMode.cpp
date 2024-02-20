#include "ConsoleMode.hpp"
#include "WindowConsole.hpp"

namespace console_cpp {
    ConsoleMode::ConsoleMode(const std::function<FunctionType>& init, const std::function<FunctionType>& reset)
        : ConsoleMode(init, reset, nullptr) {

    }

    ConsoleMode::ConsoleMode(const std::function<FunctionType>& init, const std::function<FunctionType>& reset, const std::shared_ptr<ConsoleMode>& next)
        : init_(init), reset_(reset), next_(next) {

    }

    auto ConsoleMode::GetNext() const -> const ConsoleMode* {
        return this->next_.get();
    }

    auto ConsoleMode::GetNext() -> ConsoleMode* {
        return this->next_.get();
    }

    auto ConsoleMode::SetNext(ConsoleMode* next) -> void {
        this->next_ = std::shared_ptr<ConsoleMode>(next);
    }

    auto ConsoleMode::SetLastNext(ConsoleMode* next) -> void {
        this->next_ == nullptr ? this->SetNext(next) : this->next_->SetLastNext(next);
    }

    auto ConsoleMode::InitExecute(WindowConsole& windowConsole) -> void {
        if (this->init_ != nullptr) {
            this->init_(windowConsole);
        }

        if (this->next_ != nullptr) {
            this->next_->InitExecute(windowConsole);
        }
    }

    auto ConsoleMode::ResetExecute(WindowConsole& windowConsole) -> void {
        if (this->reset_ != nullptr) {
            this->reset_(windowConsole);
        }

        if (this->next_ != nullptr) {
            this->next_->ResetExecute(windowConsole);
        }
    }
}
