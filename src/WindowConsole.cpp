#include "WindowConsole.hpp"
#include "WindowConsole.hpp"

#include "Print.hpp"
#include "Utils.hpp"

namespace console_cpp {
    auto WindowConsole::ClearScreen() -> void {
        // You can't use CursorMove functions 'cause they'll be buffered
        this->buffer_->clear();
        PrintUnicode_(this->out_, AddCsiSymbol("H") + AddCsiSymbol("J") + AddCsiSymbol("H"));

        this->x_ = 0;
        this->y_ = 0;
    }

    auto WindowConsole::DisplayBuffer() -> void {
        PrintUnicode_(this->out_, *this->buffer_);
        this->buffer_->clear();
    }

    auto WindowConsole::LaunchAlterScreen() -> void {
        this->DisplayStr_(AddCsiSymbol("?1049h"));
    }

    auto WindowConsole::CloseAlterScreen() -> void {
        this->DisplayStr_(AddCsiSymbol("?1049l"));
    }

    auto WindowConsole::EnableBuffer() -> void {
        this->isBufferEnabled_ = true;
    }

    auto WindowConsole::DisableBuffer() -> void {
        this->isBufferEnabled_ = false;
    }

    auto WindowConsole::HideCursor() -> void {
        this->isCursorVisible_ = false;
        this->DisplayStr_(AddCsiSymbol("?25l"));
    }

    auto WindowConsole::ShowCursor() -> void {
        this->isCursorVisible_ = true;
        this->DisplayStr_(AddCsiSymbol("?25h"));
    }

    auto WindowConsole::CursorMoveToHomePosition() -> void {
        this->x_ = 0;
        this->y_ = 0;

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveUp(size_t y) -> void {
        if (this->y_ < y) {
            this->y_ = 0;
        }
        else {
            this->y_ -= y;
        }

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveDown(size_t y) -> void {
        if (this->y_ + y > this->limitY_) {
            this->y_ = this->limitY_ - 1;
        }
        else {
            this->y_ += y;
        }

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveRight(size_t x) -> void {
        if (this->x_ + x > this->limitX_) {
            this->x_ = this->limitX_ - 1;
        }
        else {
            this->x_ += x;
        }

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveLeft(size_t x) -> void {
        if (this->x_ < x) {
            this->x_ = 0;
        }
        else {
            this->x_ -= x;
        }

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveRightWithOverflow(size_t x) -> void {
        const size_t newX = (this->x_ + x) % this->limitX_;
        const size_t newY = (this->x_ + x) / this->limitX_;

        if (this->y_ + newY > this->limitY_) {
            this->y_ = this->limitY_;
        }
        else if (this->y_ + newY == this->limitY_) {
            this->x_ = 0;
            this->y_ = this->limitY_;
        }
        else {
            this->x_ = newX;
            this->y_ += newY;
        }

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveLeftWithOverflow(size_t x) -> void {
        if (this->x_ + this->y_ * this->limitX_ < x) {
            this->x_ = 0;
            this->y_ = 0;
        }
        else {
            const size_t newX = (this->x_ + this->y_ * this->limitX_ - x) % this->limitX_;
            const size_t newY = (this->x_ + this->y_ * this->limitX_ - x) / this->limitX_;

            this->x_ = newX; // ????
            this->y_ = newY; // ????
        }

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveDownToBegin(size_t y) -> void {
        if (this->y_ + y >= this->limitY_) {
            this->y_ = this->limitY_ - 1;
        }
        else {
            this->y_ += y;
        }

        this->x_ = 0;

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveUpToBegin(size_t y) -> void {
        if (this->y_ < y) {
            this->y_ = 0;
        }
        else {
            this->y_ -= y;
        }

        this->x_ = 0;

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::GetLimitX() const -> size_t {
        return this->limitX_;
    }

    auto WindowConsole::SetLimitX(size_t limitX) -> void {
        this->limitX_ = limitX;
    }

    auto WindowConsole::GetLimitY() const -> size_t {
        return this->limitY_;
    }

    auto WindowConsole::SetLimitY(size_t limitY) -> void {
        this->limitY_ = limitY;
    }

    auto WindowConsole::CursorGetX() const -> size_t {
        return this->x_;
    }

    auto WindowConsole::CursorMoveXTo(size_t x) -> void {
        if (x >= this->limitX_) {
            this->x_ = this->limitX_ - 1;
        }

        this->x_ = x;

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorGetY() const -> size_t {
        return this->y_;
    }

    auto WindowConsole::CursorMoveYTo(size_t y) -> void {
        if (y > this->limitY_) {
            this->y_ = this->limitY_;
        }

        this->y_ = y;

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorGetXY() const -> std::pair<size_t, size_t> {
        return std::make_pair(this->x_, this->y_);
    }

    auto WindowConsole::CursorMoveXYTo(size_t x, size_t y) -> void {
        this->CursorMoveXTo(x);
        this->CursorMoveYTo(y);
    }

    auto WindowConsole::UpdateCursorPosition_() -> void {
        this->DisplayStr_(AddCsiSymbol(std::format("{};{}H", this->y_ + 1, this->x_ + 1)));
    }

    auto WindowConsole::DisplayStr_(const std::string& ansi) -> void {
        if (this->isBufferEnabled_) {
            *this->buffer_ += ansi;
        }
        else {
            PrintUnicode_(this->out_, ansi);
        }
    }

    auto WindowConsole::DisplayStr_(char32_t chr) -> void {
        if (this->isBufferEnabled_) {
            const char buffer[5]{};
            U32CharToU8Char_(chr, buffer);

            *this->buffer_ += buffer;
        }
        else {
            PrintUnicode_(this->out_, std::u32string(1, chr));
        }

        this->CursorMoveRightWithOverflow(U32CharWidth_(chr));
    }

    auto WindowConsole::DisplayStr_(char chr) -> void {
        if (this->isBufferEnabled_) {
            *this->buffer_ += chr;
        }
        else {
            PrintUnicode_(this->out_, std::string(1, chr));
        }

        this->CursorMoveRightWithOverflow(1);
    }
}
