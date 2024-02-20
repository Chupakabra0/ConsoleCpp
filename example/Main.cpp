#include <iostream>
#include <random>

#include "WindowConsole.hpp"
#include "ForegroundColor.hpp"
#include "BackgroundColor.hpp"
#include "Font.hpp"
#include "Keyboard.hpp"
#include "Subwindow.hpp"
#include "ConsoleAttributes.hpp"
#include "DelimStyle.hpp"

auto TestFormating() -> void {
    console_cpp::WindowConsole console(
        std::cout,
        console_cpp::ConsoleAttributes::HideCursor(),
        console_cpp::ConsoleAttributes::EnableAlterScreen()
    );

    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution<int> distrInt(0, 255);

    console.PrintLine("FUCK", console_cpp::Font::Blinking(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Bold(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Dim(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::DoubleUnderline(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Encircled(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Fracture(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Framed(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Hidden(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Invert(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Italic(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Overline(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::RapidBlink(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Strikethrough(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Underline(), console_cpp::ForegroundColor::IndexColor(distrInt(mt)), console_cpp::BackgroundColor::IndexColor(distrInt(mt)));

    console.PrintLine(std::string(console.GetLimitX(), '-'));

    console.PrintLine("FUCK", console_cpp::Font::Blinking(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Bold(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Dim(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::DoubleUnderline(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Encircled(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Fracture(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Framed(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Hidden(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Invert(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Italic(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Overline(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::RapidBlink(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));
    console.PrintLine("FUCK", console_cpp::Font::Strikethrough(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));
    
    console.GetKeyPress();
    console.ClearScreen();

    console.PrintLine(std::string("FUCK"), console_cpp::Font::Underline(), console_cpp::ForegroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)), console_cpp::BackgroundColor::TrueColor(distrInt(mt), distrInt(mt), distrInt(mt)));

    console.GetKeyPress();
}

auto MoveCursorTest() -> void {
    console_cpp::WindowConsole console(
        std::cout,
        console_cpp::ConsoleAttributes::HideCursor(),
        console_cpp::ConsoleAttributes::EnableAlterScreen()
    );

    console.Print("(0, 0)");
    console.GetKeyPress();

    console.Print("(6, 0)");
    console.GetKeyPress();

    console.CursorMoveXYTo(1, 2);
    console.Print("(1, 2)");
    console.GetKeyPress();

    console.CursorMoveXYTo(10, 10);
    console.Print("(10, 10)");
    console.GetKeyPress();

    console.CursorMoveDown(2);
    console.Print("Down2");
    console.GetKeyPress();

    console.CursorMoveUp(2);
    console.Print("Up2");
    console.GetKeyPress();

    console.CursorMoveRight(2);
    console.Print("Right2");
    console.GetKeyPress();

    console.CursorMoveLeft(2);
    console.Print("Left2");
    console.GetKeyPress();

    console.CursorMoveDownToBegin(2);
    console.Print("DownToBegin2");
    console.GetKeyPress();

    console.CursorMoveUpToBegin(5);
    console.Print("UpToBegin5");
    console.GetKeyPress();

    console.CursorMoveLeft(13);
    console.Print("MoveLeft13");
    console.GetKeyPress();

    console.CursorMoveRight(13);
    console.Print("MoveRight13");
    console.GetKeyPress();

    console.CursorMoveXTo(20);
    console.Print("MoveX20");
    console.GetKeyPress();

    console.CursorMoveYTo(23);
    console.Print("MoveY23");
    console.GetKeyPress();

    console.CursorMoveDownToBegin(2);
    console.Print("MoveDownToBegin2");
    console.GetKeyPress();

    console.CursorMoveUpToBegin(3);
    console.Print("MoveUpToBegin3");
    console.GetKeyPress();

    console.CursorMoveLeft(14);
    console.CursorMoveRight(120);
    console.CursorMoveRightWithOverflow(2);
    console.Print("MoveRightWithOverflow");
    console.GetKeyPress();

    console.CursorMoveLeftWithOverflow(10);
    console.Print("MoveLeftWithOverflow10");
    console.GetKeyPress();

    console.CursorMoveLeftWithOverflow(36);
    console.Print("MoveLeftWithOverflow36");
    console.GetKeyPress();

    console.CursorMoveToHomePosition();
    console.Print("Home");
    console.GetKeyPress();

    console.CursorMoveLeft(10);
    console.Print("Home1");
    console.GetKeyPress();

    console.CursorMoveLeftWithOverflow(10);
    console.Print("Home12");
    console.GetKeyPress();

    console.PrintCenter("Center");
    console.PrintLeft("Left");
    console.PrintRight("Right");
    console.GetKeyPress();

    console.ClearScreen();
}

auto BufferTest() -> void {
    console_cpp::WindowConsole console(
        std::cout,
        console_cpp::ConsoleAttributes::EnableBuffer(),
        console_cpp::ConsoleAttributes::HideCursor()
    );

    console.PrintLine("Hello motherfucker");
    console.PrintLine("Hello dear");
    console.PrintLine("Hello you");
    console.PrintLine("Hello me");

    console.DisplayBuffer();
    console.GetKeyPress();

    console.CursorMoveToHomePosition();
    console.PrintLine("Hello a", console_cpp::BackgroundColor::BrightWhite(), console_cpp::ForegroundColor::BrightBlack());
    console.PrintLine("Hello b", console_cpp::BackgroundColor::BrightWhite(), console_cpp::ForegroundColor::BrightBlack());
    console.PrintLine("Hello c", console_cpp::BackgroundColor::BrightWhite(), console_cpp::ForegroundColor::BrightBlack());
    console.PrintLine("Hello d", console_cpp::BackgroundColor::BrightWhite(), console_cpp::ForegroundColor::BrightBlack());

    console.DisplayBuffer();
    console.GetKeyPress();

    console.ClearScreen();
}

auto KeyboardTest() -> void {
    // TODO!!!!
}

auto AlignTest() -> void {
    console_cpp::WindowConsole console(
        std::cout,
        console_cpp::ConsoleAttributes::HideCursor()
    );

    console.PrintCenter("Center");
    console.PrintLeft("Left");
    console.PrintRight("Right");
    console.GetKeyPress();

    console.ClearScreen();
}

auto WindowTest() -> void {
    console_cpp::WindowConsole console(
        std::cout,
        console_cpp::ConsoleAttributes::HideCursor(),
        console_cpp::ConsoleAttributes::EnableAlterScreen()
    );

    console_cpp::Subwindow subwindow(0, 0, 20, 10, console, console_cpp::DelimStyle::RoundedLine());

    subwindow.PrintWindow();
    console.Print(U"Моё window 💘💘💘🖖💘");

    console.GetKeyPress();
}

//int main() {
//    WindowTest();
//    return EXIT_SUCCESS;
//}

#include <iostream>
#include <clocale>
#include <wchar.h>

int main() {
    std::cout << std::format("{}", "🛡") << std::endl;

    return 0;
}
