#include "WindowConsole.hpp"
#include "WindowConsole.hpp"
#include "WindowConsole.hpp"
#include "WindowConsole.hpp"

#include "Print.hpp"
#include "Utils.hpp"

namespace console_cpp {
    auto WindowConsole::ClearScreen() -> void {
        // You can't use CursorMove functions 'cause they'll be buffered
        this->buffer_->clear();
        PrintUnicode_(this->out_, AddCsiSymbol("H") + AddCsiSymbol("J") + AddCsiSymbol("H"));

        this->cursorX_ = 0;
        this->cursorY_ = 0;
    }

    auto WindowConsole::DisplayBuffer() -> void {
        PrintUnicode_(this->out_, *this->buffer_);
        this->buffer_->clear();
        // TODO: move pointer
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
        this->cursorX_ = this->positionX_;
        this->cursorY_ = this->positionY_;

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveUp(size_t y) -> void {
        if (this->cursorY_ <= this->positionY_ + y) {
            this->cursorY_ = this->positionY_;
        }
        else {
            this->cursorY_ -= y;
        }

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveDown(size_t y) -> void {
        if (this->cursorY_ + y >= this->height_ + this->positionY_) {
            this->cursorY_ = this->height_ + this->positionY_;
        }
        else {
            this->cursorY_ += y;
        }

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveRight(size_t x) -> void {
        if (this->cursorX_ + x >= this->width_ + this->positionX_) {
            this->cursorX_ = this->width_ + this->positionX_;
        }
        else {
            this->cursorX_ += x;
        }

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveLeft(size_t x) -> void {
        if (this->cursorX_ <= this->positionX_ + x) {
            this->cursorX_ = this->positionX_;
        }
        else {
            this->cursorX_ -= x;
        }

        this->UpdateCursorPosition_();
    }

    //auto WindowConsole::CursorMoveRightWithOverflow(size_t x) -> void {
    //    const size_t newX = (this->CursorGetLocalX() + x) % this->width_;
    //    const size_t addY = (this->CursorGetLocalX() + x) / this->width_;

    //    if (this->cursorY_ + addY >= this->height_ + this->positionY_) {
    //        //this->cursorX_ = this->width_ + this->positionX_ - 1;
    //        this->cursorY_ = this->height_ + this->positionY_;
    //    }
    //    //else if (this->cursorY_ + newY == this->height_) {
    //    //    this->cursorX_ = 0;
    //    //    this->cursorY_ = this->height_;
    //    //}
    //    else {
    //        this->CursorMoveXTo(newX);
    //        this->CursorMoveDown(addY);
    //    }

    //    this->UpdateCursorPosition_();
    //}

    auto WindowConsole::CursorMoveRightWithOverflow(size_t x) -> void {
        for (int i = 0; i < x; ++i) {
            this->CursorMoveRight(1);
            
            if (this->CursorGetLocalX() == this->GetWidth()) {
                this->CursorMoveDown(1);
                this->CursorMoveXTo(0);
            }
        }

        this->UpdateCursorPosition_();
    }

    //auto WindowConsole::CursorMoveLeftWithOverflow(size_t x) -> void {
    //    if (this->cursorX_ + this->cursorY_ * this->width_ < x) {
    //        this->cursorX_ = this->positionX_;
    //        this->cursorY_ = this->positionY_;
    //    }
    //    else {
    //        const size_t newX = (this->CursorGetLocalX() + this->CursorGetLocalY() * this->width_ - x) % this->width_;
    //        const size_t newY = (this->CursorGetLocalX() + this->CursorGetLocalY() * this->width_ - x) / this->width_;

    //        this->CursorMoveXTo(newX);
    //        this->CursorMoveYTo(newY);
    //    }

    //    this->UpdateCursorPosition_();
    //}

    auto WindowConsole::CursorMoveLeftWithOverflow(size_t x) -> void {
        for (int i = 0; i < x; ++i) {
            const auto temp = this->CursorGetLocalX();
            this->CursorMoveLeft(1);
            
            if (this->CursorGetLocalX() == temp) {
                this->CursorMoveUp(1);
                this->CursorMoveXTo(this->GetWidth() - 1);
            }
        }

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveDownToBegin(size_t y) -> void {
        this->CursorMoveDown(y);
        this->CursorMoveXTo(0);
        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorMoveUpToBegin(size_t y) -> void {
        this->CursorMoveUp(y);
        this->CursorMoveXTo(0);
        this->UpdateCursorPosition_();
    }

    auto WindowConsole::GetWidth() const -> size_t {
        return this->width_;
    }

    auto WindowConsole::SetWidth(size_t width) -> void {
        this->width_ = width;
    }

    auto WindowConsole::GetHeight() const -> size_t {
        return this->height_;
    }

    auto WindowConsole::SetHeight(size_t height) -> void {
        this->height_ = height;
    }

    auto WindowConsole::CursorGetGlobalX() const -> size_t {
        return this->cursorX_;
    }

    auto WindowConsole::CursorGetLocalX() const -> size_t {
        return this->cursorX_ - this->positionX_;
    }

    auto WindowConsole::CursorMoveXTo(size_t x) -> void {
        if (x >= this->width_) {
            this->cursorX_ = this->width_ + this->positionX_;
        }

        this->cursorX_ = x + this->positionX_;

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorGetGlobalY() const -> size_t {
        return this->cursorY_;
    }

    auto WindowConsole::CursorGetLocalY() const -> size_t {
        return this->cursorY_ - this->positionY_;
    }

    auto WindowConsole::CursorMoveYTo(size_t y) -> void {
        if (y >= this->height_) {
            this->cursorY_ = this->height_ + this->positionY_;
        }

        this->cursorY_ = y + this->positionY_;

        this->UpdateCursorPosition_();
    }

    auto WindowConsole::CursorGetGlobalXY() const -> std::pair<size_t, size_t> {
        return std::make_pair(this->cursorX_, this->cursorY_);
    }

    auto WindowConsole::CursorGetLocalXY() const -> std::pair<size_t, size_t> {
        return std::make_pair(this->cursorX_ - this->positionX_, this->cursorY_ - this->positionY_);
    }

    auto WindowConsole::CursorMoveXYTo(size_t x, size_t y) -> void {
        this->CursorMoveXTo(x);
        this->CursorMoveYTo(y);
    }

    auto WindowConsole::GetOutputStream() const -> const std::ostream& {
        return this->out_.get();
    }

    auto WindowConsole::GetOutputStream() -> std::ostream& {
        return this->out_.get();
    }

    auto WindowConsole::GetPositionX() const -> size_t {
        return this->positionX_;
    }

    auto WindowConsole::GetPositionY() const -> size_t {
        return this->positionY_;
    }

    auto WindowConsole::UpdateCursorPosition_() -> void {
        this->DisplayStr_(AddCsiSymbol(std::format("{};{}H", this->cursorY_ + 1, this->cursorX_ + 1)));
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
        const size_t chrWidth = U32CharWidth_(chr);

        if (this->isBufferEnabled_) {
            const char buffer[5]{};
            U32CharToU8Char_(chr, buffer);

            *this->buffer_ += buffer;
        }
        else {
            if (this->CursorGetLocalX() + chrWidth > this->width_) {
                this->CursorMoveDownToBegin(1);
            }

            PrintUnicode_(this->out_, std::u32string(1, chr));
        }

        this->CursorMoveRightWithOverflow(chrWidth);
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
