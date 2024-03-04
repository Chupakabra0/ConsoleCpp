#pragma once
#include "WindowConsole.hpp"
#include "Delim.hpp"

namespace console_cpp {
    class Subwindow : public WindowConsole {
    public:
        Subwindow() = delete;

        template<IsPrintModePtrs... T>
        explicit Subwindow(WindowConsole& window, size_t x, size_t y, size_t width, size_t height, const Delim& delim, T... printMode)
            : WindowConsole(window.GetOutputStream(), width, height, std::forward<ConsoleMode*>(printMode)...), buffer_(std::move(std::make_shared<std::string>())),
              delim_(delim), parentWindow_(window) {
            this->positionX_ = x;
            this->positionY_ = y;

            this->cursorX_   = this->positionX_;
            this->cursorY_   = this->positionY_;
        }

        Subwindow(const Subwindow&) = default;

        Subwindow(Subwindow&&) noexcept = default;

        Subwindow& operator=(const Subwindow&) = default;

        Subwindow& operator=(Subwindow&&) noexcept = default;

        ~Subwindow() override = default;

        auto PrintWindow() -> void {
            this->PrintLeftTop_();
            this->PrintTop_();
            this->PrintRightTop_();
            this->PrintLeft_();
            this->PrintRight_();
            this->PrintLeftBottom_();
            this->PrintBottom_();
            this->PrintRightBottom_();
            this->CursorMoveToHomePosition();
        }

        auto CursorMoveToHomePosition() -> void override {
            return WindowConsole::CursorMoveToHomePosition();
        }

        auto CursorMoveUp(size_t y) -> void override {
            if (this->cursorY_ <= this->positionY_ + y ||
                this->cursorY_ <= this->parentWindow_.get().GetPositionY() + y) {
                this->cursorY_ = this->positionY_;
            }
            else {
                this->cursorY_ -= y;
            }

            this->UpdateCursorPosition_();
        }

        auto CursorMoveDown(size_t y) -> void override {
            if (this->cursorY_ + y >= this->height_ + this->positionY_ ||
                this->cursorY_ + y >= this->parentWindow_.get().GetHeight() + this->parentWindow_.get().GetPositionY()) {
                this->cursorY_ = this->height_ + this->positionY_;
            }
            else {
                this->cursorY_ += y;
            }

            this->UpdateCursorPosition_();
        }

        auto CursorMoveRight(size_t x) -> void override {
            if (this->cursorX_ + x >= this->width_ + this->positionX_ ||
                this->cursorX_ + x >= this->parentWindow_.get().GetWidth() + this->parentWindow_.get().GetPositionX()) {
                this->cursorX_ = this->width_ + this->positionX_;
            }
            else {
                this->cursorX_ += x;
            }

            this->UpdateCursorPosition_();
        }

        auto CursorMoveLeft(size_t x) -> void override {
            if (this->cursorX_ <= this->positionX_ + x ||
                this->cursorX_ <= this->parentWindow_.get().GetPositionX() + x) {
                this->cursorX_ = this->positionX_;
            }
            else {
                this->cursorX_ -= x;
            }

            this->UpdateCursorPosition_();
        }

        auto CursorMoveXTo(size_t x) -> void override {
            if (x >= this->width_ ||
                x + this->positionX_ >= this->parentWindow_.get().GetWidth()) {
                this->cursorX_ = this->width_ + this->positionX_;
            }

            this->cursorX_ = x + this->positionX_;

            this->UpdateCursorPosition_();
        }

        auto CursorMoveYTo(size_t y) -> void override {
            if (y >= this->height_ ||
                y + this->positionY_ >= this->parentWindow_.get().GetHeight()) {
                this->cursorY_ = this->height_ + this->positionY_;
            }

            this->cursorY_ = y + this->positionY_;

            this->UpdateCursorPosition_();
        }

        auto PrintLeftTop_() -> void {
            if (this->positionX_ < this->parentWindow_.get().GetPositionX() + 1 ||
                this->positionY_ < this->parentWindow_.get().GetPositionY() + 1) {
                return;
            }

            this->out_.get() << AddCsiSymbol(std::format("{};{}H", this->positionY_, this->positionX_));
            this->out_.get() << this->delim_.get().topLeftLine.str[0];
        }

        auto PrintRightTop_() -> void {
            if (this->positionX_ + this->width_ + 1 > this->parentWindow_.get().GetWidth() ||
                this->positionY_ < this->parentWindow_.get().GetPositionY() + 1) {
                return;
            }

            this->out_.get() << AddCsiSymbol(std::format("{};{}H", this->positionY_, this->positionX_ + this->width_ + 1));
            this->out_.get() << this->delim_.get().topRightLine.str[0];
        }

        auto PrintRightBottom_() -> void {
            if (this->positionX_ + this->width_ + 1 > this->parentWindow_.get().GetWidth() ||
                this->positionY_ + this->height_ + 1 > this->parentWindow_.get().GetHeight()) {
                return;
            }

            this->out_.get() << AddCsiSymbol(std::format("{};{}H", this->positionY_ + this->height_ + 1, this->positionX_ + this->width_ + 1));
            this->out_.get() << this->delim_.get().bottomRightLine.str[0];
        }

        auto PrintLeftBottom_() -> void {
            if (this->positionX_ < this->parentWindow_.get().GetPositionX() + 1 ||
                this->positionY_ + this->height_ + 1 > this->parentWindow_.get().GetHeight()) {
                return;
            }

            this->out_.get() << AddCsiSymbol(std::format("{};{}H", this->positionY_ + this->height_ + 1, this->positionX_));
            this->out_.get() << this->delim_.get().bottomLeftLine.str[0];
        }

        auto PrintTop_() -> void {
            if (this->positionY_ < this->parentWindow_.get().GetPositionY() + 1) {
                return;
            }

            for (int i = 0; i < this->width_; ++i) {
                this->out_.get() << AddCsiSymbol(std::format("{};{}H", this->positionY_, this->positionX_ + 1 + i));
                this->out_.get() << this->delim_.get().horizontalLine.str[0];
            }
        }

        auto PrintBottom_() -> void {
            if (this->positionY_ + this->height_ + 1 > this->parentWindow_.get().GetHeight()) {
                return;
            }

            for (int i = 0; i < this->width_; ++i) {
                if (this->positionX_ + i > this->parentWindow_.get().GetWidth()) {
                    return;
                }

                this->out_.get() << AddCsiSymbol(std::format("{};{}H", this->positionY_ + this->height_ + 1, this->positionX_ + 1 + i));
                this->out_.get() << this->delim_.get().horizontalLine.str[0];
            }
        }

        auto PrintLeft_() -> void {
            if (this->positionX_ < 1) {
                return;
            }

            for (int i = 0; i < this->height_; ++i) {
                this->out_.get() << AddCsiSymbol(std::format("{};{}H", this->positionY_ + i + 1, this->positionX_));
                this->out_.get() << this->delim_.get().verticalLine.str[0];
            }
        }

        auto PrintRight_() -> void {
            if (this->positionX_ + this->width_ + 1 > this->parentWindow_.get().GetWidth()) {
                return;
            }

            for (int i = 0; i < this->height_; ++i) {
                if (this->positionY_ + i > this->parentWindow_.get().GetHeight()) {
                    return;
                }

                this->out_.get() << AddCsiSymbol(std::format("{};{}H", this->positionY_ + i + 1, this->positionX_ + this->width_ + 1));
                this->out_.get() << this->delim_.get().verticalLine.str[0];
            }
        }

    private:
        std::shared_ptr<PrintMode> printMode_{};
        std::shared_ptr<std::string> buffer_{};
        std::reference_wrapper<const Delim> delim_;
        std::reference_wrapper<const WindowConsole> parentWindow_;
    };
}
