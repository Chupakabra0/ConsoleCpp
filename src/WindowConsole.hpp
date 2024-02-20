#pragma once
#include "TwoDimArrWrapper.hpp"
#include "PrintMode.hpp"
#include "ConsoleMode.hpp"
#include "Keyboard.hpp"
#include "Delim.hpp"
#include "Utils.hpp"

#include <format>
#include <ostream>

namespace console_cpp {
    template<class... T>
    concept IsPrintModePtrs = ((std::is_pointer_v<T> && std::is_base_of_v<PrintMode, std::remove_pointer_t<T>>) && ...);

    template<class... T>
    concept IsConsoleModePtrs = ((std::is_pointer_v<T> && std::is_base_of_v<ConsoleMode, std::remove_pointer_t<T>>) && ...);

    class WindowConsole {
    public:
        WindowConsole() = delete;

        template<IsConsoleModePtrs... T>
        explicit WindowConsole(std::ostream& out, T... consoleMode)
            : buffer_(std::move(std::make_shared<std::string>())), out_(out) {
            SetLocale_();
            this->InitSize_();
            this->InitMode_(std::forward<const ConsoleMode*>(consoleMode)...);
        }

        template<IsConsoleModePtrs... T>
        explicit WindowConsole(std::ostream& out, size_t limitX, size_t limitY, T... consoleMode)
            : buffer_(std::move(std::make_shared<std::string>())), out_(out),
              limitX_(limitX), limitY_(limitY) {
            SetLocale_();
            this->InitMode_(std::forward<const ConsoleMode*>(consoleMode)...);
        }

        WindowConsole(const WindowConsole&) = delete;

        WindowConsole(WindowConsole&&) noexcept = default;

        WindowConsole& operator=(const WindowConsole&) = delete;

        WindowConsole& operator=(WindowConsole&&) noexcept = default;

        ~WindowConsole() {
            if (this->consoleMode_ != nullptr) {
                this->consoleMode_->ResetExecute(*this);
            }
        }

        template<IsPrintModePtrs... T>
        auto Print(const Delim::DelimItem& delim, T... printMode) -> void {
            return this->Print(delim.str, std::forward<const PrintMode*>(printMode)...);
        }

        template<IsPrintModePtrs... T>
        auto Print(const std::u32string& str, T... printMode) -> void {
            auto mode = GetPrintMode_(std::forward<const PrintMode*>(printMode)...);

            this->DisplayStr_(mode->CalcStartStr());

            for (int i = 0; i < str.size(); ++i) {
                auto [x, y] = this->CursorGetXY();

                if (y == this->GetLimitY()) {
                    break;
                }

                switch (str[i]) {
                    case U'\n': case U'\v': {
                        this->PrintLine("");

                        break;
                    }
                    case U'\a': {
                        break;
                    }
                    case U'\b': {
                        if (x > 0) {
                            this->CursorMoveLeft(1);
                            auto [x, y] = this->CursorGetXY();

                            if (this->isBufferEnabled_) {
                                *this->buffer_ += '\b';
                            }
                            else {
                                this->out_.get() << BLANK_SYMBOL;
                            }
                        }

                        break;
                    }
                    case U'\t': {
                        this->Print(std::string(abs(static_cast<long long>(x) % 8 - 8), BLANK_SYMBOL));

                        break;
                    }
                    default: {
                        this->DisplayStr_(str[i]);
                        //this->CursorMoveRightWithOverflow(1);
                    }
                }
            }

            this->DisplayStr_(mode->CalcResetStr());
        }

        template<IsPrintModePtrs... T>
        auto Print(const std::string& str, T... printMode) -> void {
            auto mode = GetPrintMode_(std::forward<const PrintMode*>(printMode)...);

            this->DisplayStr_(mode->CalcStartStr());

            for (int i = 0; i < str.size(); ++i) {
                auto [x, y] = this->CursorGetXY();

                if (y == this->GetLimitY()) {
                    break;
                }

                switch (str[i]) {
                    case '\n': case '\v': {
                        this->PrintLine("");

                        break;
                    }
                    case '\a': {
                        break;
                    }
                    case '\b': {
                        if (x > 0) {
                            this->CursorMoveLeft(1);
                            auto [x, y] = this->CursorGetXY();

                            if (this->isBufferEnabled_) {
                                *this->buffer_ += '\b';
                            }
                            else {
                                this->out_.get() << BLANK_SYMBOL;
                            }
                        }

                        break;
                    }
                    case '\t': {
                        this->Print(std::string(abs(static_cast<long long>(x) % 8 - 8), BLANK_SYMBOL));

                        break;
                    }
                    default: {
                        this->DisplayStr_(str[i]);
                        //this->CursorMoveRightWithOverflow(1);
                    }
                }
            }

            this->DisplayStr_(mode->CalcResetStr());
        }

        template<IsPrintModePtrs... T>
        auto PrintLine(const std::string& str, T... printMode) -> void {
            this->Print(str, std::forward<const PrintMode*>(printMode)...);

            for (; this->CursorGetX() != 0; /*this->CursorMoveRightWithOverflow(1)*/) {
                this->DisplayStr_(BLANK_SYMBOL);
            }
        }

        template<IsPrintModePtrs... T>
        auto MovePrint(const std::string& str, size_t x, size_t y, T... printMode) -> void {
            this->CursorMoveXYTo(x, y);
            this->Print(str, std::forward<const PrintMode*>(printMode)...);
        }

        template<IsPrintModePtrs... T>
        auto MovePrintLine(const std::string& str, size_t x, size_t y, T... printMode) -> void {
            this->CursorMoveXYTo(x, y);
            this->PrintLine(str, std::forward<const PrintMode*>(printMode)...);
        }

        template<IsPrintModePtrs... T>
        auto PrintLeft(const std::string& str, T... printMode) -> void {
            auto mode = GetPrintMode_(std::forward<const PrintMode*>(printMode)...);

            this->DisplayStr_(mode->CalcStartStr());

            this->CursorMoveXTo(0);
            for (int i = 0; i < this->GetLimitX() && i < str.size(); ++i) {
                this->DisplayStr_(str[i]);
            }

            this->DisplayStr_(mode->CalcResetStr());
        }

        template<IsPrintModePtrs... T>
        auto PrintLeftLine(const std::string& str, T... printMode) -> void {
            this->PrintLeft(str, std::forward<const PrintMode*>(printMode)...);
            this->PrintLine("");
        }

        template<IsPrintModePtrs... T>
        auto PrintRight(const std::string& str, T... printMode) {
            auto mode = GetPrintMode_(std::forward<const PrintMode*>(printMode)...);

            this->DisplayStr_(mode->CalcStartStr());

            this->CursorMoveXTo(this->GetLimitX() - 1);
            for (int i = 0; i < this->GetLimitX() && i < str.size(); ++i) {
                this->DisplayStr_(str[str.size() - i - 1]);
                this->CursorMoveLeftWithOverflow(2); // little hack to prevent CursorMoveRightWithOverflow from DispalyStr_ above
            }

            this->DisplayStr_(mode->CalcResetStr());
        }

        template<IsPrintModePtrs... T>
        auto PrintRightLine(const std::string& str, T... printMode) -> void {
            this->PrintLine("");
            this->CursorMoveUp(1);
            this->PrintRight(str, std::forward<const PrintMode*>(printMode)...);
        }

        template<IsPrintModePtrs... T>
        auto PrintCenter(const std::string& str, T... printMode) -> void {
            int cursorStartPos = (static_cast<int>(this->GetLimitX()) - static_cast<int>(str.size())) / 2;
            
            if (cursorStartPos >= 0) {
                this->CursorMoveXTo(cursorStartPos);
                this->Print(str, std::forward<const PrintMode*>(printMode)...);
            }
            else {
                this->CursorMoveXTo(this->GetLimitX() - 1);
                this->Print(
                    std::string(str.begin() - cursorStartPos, str.end() - cursorStartPos),
                    std::forward<const PrintMode*>(printMode)...
                );
            }
        }

        template<IsPrintModePtrs... T>
        auto PrintCenterLine(const std::string& str, T... printMode) -> void {
            this->PrintLine("");
            this->CursorMoveUp(1);
            this->PrintCenter(str, std::forward<const PrintMode*>(printMode)...);
        }

        auto ClearScreen() -> void;

        auto DisplayBuffer() -> void;

        auto GetKeyPress() -> KeyCode;

        auto LaunchAlterScreen() -> void;

        auto CloseAlterScreen() -> void;

        auto EnableBuffer() -> void;

        auto DisableBuffer() -> void;

        auto HideCursor() -> void;

        auto ShowCursor() -> void;

        auto CursorMoveToHomePosition() -> void;

        auto CursorMoveUp(size_t y) -> void;

        auto CursorMoveDown(size_t y) -> void;

        auto CursorMoveRight(size_t x) -> void;

        auto CursorMoveLeft(size_t x) -> void;

        auto CursorMoveRightWithOverflow(size_t x) -> void;

        auto CursorMoveLeftWithOverflow(size_t x) -> void;

        auto CursorMoveDownToBegin(size_t y) -> void;

        auto CursorMoveUpToBegin(size_t y) -> void;

        auto GetLimitX() const -> size_t;

        auto SetLimitX(size_t limitX) -> void;

        auto GetLimitY() const -> size_t;

        auto SetLimitY(size_t limitY) -> void;

        auto CursorGetX() const -> size_t;

        auto CursorMoveXTo(size_t x) -> void;

        auto CursorGetY() const -> size_t;

        auto CursorMoveYTo(size_t y) -> void;

        auto CursorGetXY() const -> std::pair<size_t, size_t>;

        auto CursorMoveXYTo(size_t x, size_t y) -> void;

    private:
        // TODO: create maybe keyboard handle shared_ptr
        std::shared_ptr<ConsoleMode> consoleMode_{};
        std::shared_ptr<std::string> buffer_{};
        std::reference_wrapper<std::ostream> out_;
        size_t limitX_{};
        size_t limitY_{};
        size_t x_{};
        size_t y_{};
        bool isBufferEnabled_{};
        bool isCursorVisible_{};

        auto InitSize_() -> void;

        auto UpdateCursorPosition_() -> void;

        auto DisplayStr_(const std::string& ansi) -> void;

        auto DisplayStr_(char32_t chr) -> void;

        auto DisplayStr_(char chr) -> void;

        template<IsConsoleModePtrs... T>
        auto InitMode_(T... inputMode) -> void {
            std::vector<ConsoleMode> p{};
            ((inputMode != nullptr ? (void)p.emplace_back(*inputMode) : (void)p), ...);

            this->consoleMode_ = p.empty() ? std::make_shared<ConsoleMode>() : std::make_shared<ConsoleMode>(p.front());
            auto* curr = this->consoleMode_.get();
            for (int i = 1; i < p.size(); ++i) {
                curr->SetNext(new ConsoleMode(p[i]));
                curr = curr->GetNext();
            }

            if (this->consoleMode_ != nullptr) {
                this->consoleMode_->InitExecute(*this);
            }
        }

        template<IsPrintModePtrs... T>
        auto GetPrintMode_(T... printMode) -> std::shared_ptr<PrintMode> {
            std::vector<PrintMode> p{};
            ((printMode != nullptr ? (void)p.emplace_back(*printMode) : (void)p), ...);

            auto mode = p.empty() ? std::make_shared<PrintMode>() : std::make_shared<PrintMode>(p.front());
            
            auto* curr = mode.get();
            for (int i = 1; i < p.size(); ++i) {
                curr->SetNext(new PrintMode(p[i]));
                curr = curr->GetNext();
            }

            return mode;
        }
    };
}
