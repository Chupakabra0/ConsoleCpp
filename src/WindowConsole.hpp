#pragma once
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

    template<class T>
    concept IsPrintableString = std::is_same_v<T, std::string> || std::is_same_v<T, std::u32string> || std::is_same_v<T, const char*> || std::is_same_v<T, const char32_t*>;

    class WindowConsole {
    public:
        WindowConsole() = delete;

        template<IsConsoleModePtrs... T>
        explicit WindowConsole(std::ostream& out, T... consoleMode)
            : buffer_(std::move(std::make_shared<std::string>())), out_(out),
              cursorX_(0), cursorY_(0), positionX_(0), positionY_(0) {
            SetLocale_();
            this->InitSize_();
            this->InitMode_(std::forward<const ConsoleMode*>(consoleMode)...);
        }

        template<IsConsoleModePtrs... T>
        explicit WindowConsole(std::ostream& out, size_t width, size_t height, T... consoleMode)
            : buffer_(std::move(std::make_shared<std::string>())), out_(out),
              width_(width), height_(height), cursorX_(0), cursorY_(0),
              positionX_(0), positionY_(0) {
            SetLocale_();
            this->InitMode_(std::forward<const ConsoleMode*>(consoleMode)...);
        }

        WindowConsole(const WindowConsole&) = delete;

        WindowConsole(WindowConsole&&) noexcept = default;

        WindowConsole& operator=(const WindowConsole&) = delete;

        WindowConsole& operator=(WindowConsole&&) noexcept = default;

        virtual ~WindowConsole() {
            if (this->consoleMode_ != nullptr) {
                this->consoleMode_->ResetExecute(*this);
            }
        }

        template<IsPrintModePtrs... T>
        auto Print(const Delim::DelimItem& delim, T... printMode) -> void {
            return this->Print(delim.str, std::forward<const PrintMode*>(printMode)...);
        }

        template<IsPrintableString Str, IsPrintModePtrs... T>
        auto Print(Str str, T... printMode) -> void {
            this->UpdateCursorPosition_();
            auto mode = GetPrintMode_(std::forward<const PrintMode*>(printMode)...);

            this->DisplayStr_(mode->CalcStartStr());

            for (int i = 0; str[i] != '\0'; ++i) {
                if (this->CursorGetLocalX() >= this->GetWidth()) {
                    this->CursorMoveDownToBegin(1);
                }
                if (this->CursorGetLocalY() >= this->GetHeight()) {
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
                        if (this->CursorGetLocalX() > 0) {
                            this->CursorMoveLeft(1);

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
                        this->Print(std::string(abs(static_cast<long long>(this->CursorGetLocalX()) % 8 - 8), BLANK_SYMBOL));

                        break;
                    }
                    default: {
                        this->DisplayStr_(str[i]);
                    }
                }
            }

            this->DisplayStr_(mode->CalcResetStr());
        }

        template<IsPrintableString Str, IsPrintModePtrs... T>
        auto PrintLine(Str str, T... printMode) -> void {
            this->Print(str, std::forward<const PrintMode*>(printMode)...);

            while (this->CursorGetLocalX() < this->GetWidth()) {
                this->DisplayStr_(BLANK_SYMBOL);
            }

            this->CursorMoveDownToBegin(1);
        }

        template<IsPrintableString Str, IsPrintModePtrs... T>
        auto MovePrint(Str str, size_t x, size_t y, T... printMode) -> void {
            this->CursorMoveXYTo(x, y);
            this->Print(str, std::forward<const PrintMode*>(printMode)...);
        }

        template<IsPrintableString Str, IsPrintModePtrs... T>
        auto MovePrintLine(Str str, size_t x, size_t y, T... printMode) -> void {
            this->CursorMoveXYTo(x, y);
            this->PrintLine(str, std::forward<const PrintMode*>(printMode)...);
        }

        template<IsPrintableString Str, IsPrintModePtrs... T>
        auto PrintLeft(Str str, T... printMode) -> void {
            auto mode = GetPrintMode_(std::forward<const PrintMode*>(printMode)...);

            this->CursorMoveXTo(0);
            this->DisplayStr_(mode->CalcStartStr());

            for (int i = 0; i < this->GetWidth() && str[i] != '\0'; ++i) {
                this->DisplayStr_(str[i]);
            }

            this->DisplayStr_(mode->CalcResetStr());
        }

        template<IsPrintableString Str, IsPrintModePtrs... T>
        auto PrintLeftLine(Str str, T... printMode) -> void {
            this->PrintLeft(str, std::forward<const PrintMode*>(printMode)...);
            this->CursorMoveDownToBegin(1);
        }

        template<IsPrintableString Str, IsPrintModePtrs... T>
        auto PrintRight(Str str, T... printMode) {
            const size_t size = GetStrSize_(str);
            auto mode         = GetPrintMode_(std::forward<const PrintMode*>(printMode)...);

            this->CursorMoveXTo(this->GetWidth() - 1);
            this->DisplayStr_(mode->CalcStartStr());

            for (int i = 0; i < this->GetWidth() && str[i] != '\0'; ++i) {
                this->DisplayStr_(str[size - i - 1]);
                this->CursorMoveLeftWithOverflow(2); // little hack to prevent CursorMoveRightWithOverflow from DispalyStr_ above
            }

            this->DisplayStr_(mode->CalcResetStr());
        }

        template<IsPrintableString Str, IsPrintModePtrs... T>
        auto PrintRightLine(Str str, T... printMode) -> void {
            this->PrintRight(str, std::forward<const PrintMode*>(printMode)...);
            this->CursorMoveDownToBegin(1);
        }

        template<IsPrintableString Str, IsPrintModePtrs... T>
        auto PrintCenter(Str str, T... printMode) -> void {
            int cursorStartPos = (static_cast<int>(this->GetWidth()) - static_cast<int>(GetStrSize_(str))) / 2;
            
            if (cursorStartPos >= 0) {
                this->CursorMoveXTo(cursorStartPos);
                this->Print(str, std::forward<const PrintMode*>(printMode)...);
            }
            else {
                this->CursorMoveXTo(0);

                for (int i = -cursorStartPos; i < GetStrSize_(str) + cursorStartPos; ++i) {
                    if constexpr (std::is_same_v<Str, const char*> || std::is_same_v<Str, std::string>) {
                        this->Print(std::string(1, str[i]), std::forward<const PrintMode*>(printMode)...);
                    }
                    else {
                        this->Print(std::u32string(1, str[i]), std::forward<const PrintMode*>(printMode)...);
                    }
                }
            }
        }

        template<IsPrintableString Str, IsPrintModePtrs... T>
        auto PrintCenterLine(Str str, T... printMode) -> void {
            this->PrintCenter(str, std::forward<const PrintMode*>(printMode)...);
            this->CursorMoveDownToBegin(1);
        }

        auto ClearScreen() -> void;

        auto DisplayBuffer() -> void;

        auto GetKeyPress() -> KeyCode;

        auto LaunchAlterScreen() -> void;

        auto CloseAlterScreen()  -> void;

        auto EnableBuffer() -> void;

        auto DisableBuffer() -> void;

        auto HideCursor() -> void;

        auto ShowCursor() -> void;

        virtual auto CursorMoveToHomePosition() -> void;

        virtual auto CursorMoveUp(size_t y) -> void;

        virtual auto CursorMoveDown(size_t y) -> void;

        virtual auto CursorMoveRight(size_t x) -> void;

        virtual auto CursorMoveLeft(size_t x) -> void;

        virtual auto CursorMoveRightWithOverflow(size_t x) -> void;

        virtual auto CursorMoveLeftWithOverflow(size_t x) -> void;

        virtual auto CursorMoveDownToBegin(size_t y) -> void;

        virtual auto CursorMoveUpToBegin(size_t y) -> void;

        auto GetWidth() const -> size_t;

        auto SetWidth(size_t limitX) -> void;

        auto GetHeight() const -> size_t;

        auto SetHeight(size_t limitY) -> void;

        auto CursorGetGlobalX() const -> size_t;

        auto CursorGetLocalX() const -> size_t;

        virtual auto CursorMoveXTo(size_t x) -> void;

        auto CursorGetGlobalY() const -> size_t;

        auto CursorGetLocalY() const -> size_t;

        virtual auto CursorMoveYTo(size_t y) -> void;

        auto CursorGetGlobalXY() const -> std::pair<size_t, size_t>;

        auto CursorGetLocalXY() const -> std::pair<size_t, size_t>;

        virtual auto CursorMoveXYTo(size_t x, size_t y) -> void;

        auto GetOutputStream() const -> const std::ostream&;

        auto GetOutputStream() -> std::ostream&;

        auto GetPositionX() const -> size_t;

        auto GetPositionY() const -> size_t;

    protected:
        // TODO: create maybe keyboard handle shared_ptr
        std::shared_ptr<ConsoleMode> consoleMode_{};
        std::shared_ptr<std::string> buffer_{};
        std::reference_wrapper<std::ostream> out_;
        size_t width_{};
        size_t height_{};
        size_t cursorX_{};
        size_t cursorY_{};
        size_t positionX_{};
        size_t positionY_{};
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
