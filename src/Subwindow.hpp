#pragma once
#include "WindowConsole.hpp"
#include "Delim.hpp"

namespace console_cpp {
    class Subwindow {
    public:
        Subwindow() = delete;

        template<IsPrintModePtrs... T>
        explicit Subwindow(size_t x, size_t y, size_t limitX, size_t limitY, WindowConsole& window, const Delim& delim, T... printMode)
            : buffer_(std::move(std::make_shared<std::string>())), delim_(delim), window_(window),
              limitX_(limitX), limitY_(limitY), x_(x), y_(y) {
            // TODO: Init this->printMode_
        }

        Subwindow(const Subwindow&) = default;

        Subwindow(Subwindow&&) noexcept = default;

        Subwindow& operator=(const Subwindow&) = default;

        Subwindow& operator=(Subwindow&&) noexcept = default;

        ~Subwindow() = default;

        auto PrintWindow() -> void {
            auto& window              = this->window_.get();
            const auto [xTemp, yTemp] = window.CursorGetXY();
            const int limitX          = static_cast<int>(this->limitX_);
            constexpr int xOffset     = 2;

            const static auto moveDownFunc = [&limitX, &xOffset](WindowConsole& win) {
                win.CursorMoveLeftWithOverflow(static_cast<size_t>(limitX + xOffset));
                win.CursorMoveDown(1);
            };

            window.CursorMoveXYTo(this->x_, this->y_);
            window.Print(this->delim_.get().topLeftLine);
            for (int i = 1; i < this->limitX_ + xOffset - 1; ++i) {
                window.Print(this->delim_.get().horizontalLine);
            }
            window.Print(this->delim_.get().topRightLine);

            for (int i = 0; i < this->limitY_; ++i) {
                moveDownFunc(window);
                window.Print(this->delim_.get().verticalLine);
                window.Print(std::string(this->limitX_, BLANK_SYMBOL));
                window.Print(this->delim_.get().verticalLine);
            }

            moveDownFunc(window);
            window.Print(this->delim_.get().bottomLeftLine);
            for (int i = 1; i < this->limitX_ + xOffset - 1; ++i) {
                window.Print(this->delim_.get().horizontalLine);
            }
            window.Print(this->delim_.get().bottomRightLine);
            window.CursorMoveXYTo(xTemp, yTemp);
        }

    private:
        std::shared_ptr<PrintMode> printMode_{};
        std::shared_ptr<std::string> buffer_{};
        std::reference_wrapper<const Delim> delim_;
        std::reference_wrapper<WindowConsole> window_;
        size_t limitX_{};
        size_t limitY_{};
        size_t x_{};
        size_t y_{};
    };
}
