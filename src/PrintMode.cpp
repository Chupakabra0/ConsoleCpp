#include "PrintMode.hpp"

namespace console_cpp {
    PrintMode::PrintMode(const std::string& start, const std::string& reset)
        : PrintMode(start, reset, nullptr) {

    }

    PrintMode::PrintMode(const std::string& start, const std::string& reset, const std::shared_ptr<PrintMode>& next)
        : next_(next), start_(start), reset_(reset) {

    }

    auto PrintMode::GetNext() const -> const PrintMode* {
        return this->next_.get();
    }

    auto PrintMode::GetNext() -> PrintMode* {
        return this->next_.get();
    }

    auto PrintMode::SetNext(PrintMode* next) -> void {
        this->next_ = std::shared_ptr<PrintMode>(next);
    }

    auto PrintMode::SetLastNext(PrintMode* next) -> void {
        this->next_ == nullptr ? this->SetNext(next) : this->next_->SetLastNext(next);
    }

    auto PrintMode::CalcStartStr() const -> std::string {
        return this->start_ + (this->next_ == nullptr ? "" : this->next_->CalcStartStr());
    }

    auto PrintMode::CalcResetStr() const -> std::string {
        return (this->next_ == nullptr ? "" : this->next_->CalcResetStr()) + this->reset_;
    }
}
