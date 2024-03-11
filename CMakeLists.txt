# CMakeList.txt : CMake project for ConsoleCpp, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(ConsoleCpp)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.21)
        message("C++20 is not supported by this compiler")
    else()
        set(CMAKE_CXX_STANDARD 20)
    
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.37)
            message("C++23 is not supported by this compiler")
        else()
            set(CMAKE_CXX_STANDARD 23)
        endif()
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
        message("C++20 is not supported by this compiler")
    else()
        set(CMAKE_CXX_STANDARD 20)

        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14)
            message("C++23 is not supported by this compiler")
        else()
            set(CMAKE_CXX_STANDARD 23)
        endif()
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13)
        message("C++20 is not supported by this compiler")
    else()
        set(CMAKE_CXX_STANDARD 20)

        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18)
            message("C++23 is not supported by this compiler")
        else()
            set(CMAKE_CXX_STANDARD 23)
        endif()
    endif()
endif()

# APPLE : C++20 <=> 13.1.6, C++23 <=> 15.0.0?

message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")

set(MY_APP ConsoleCppApplication)
set(MY_STATIC_LIB ConsoleCppStatic)

if(MSVC)
    add_compile_definitions(
        _CRT_SECURE_NO_WARNINGS
        _CRT_NONSTDC_NO_DEPRECATE
    )

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8 /Zc:__cplusplus")
endif()

add_compile_definitions(FMT_HEADER_ONLY)

# -------------- TEST LIB ----------------

add_executable(${MY_APP})

target_sources(${MY_APP} PRIVATE
    example/Main.cpp
)

target_include_directories(${MY_APP} PRIVATE
    src/
    3rdparty/fmt/include
    3rdparty/widecharwidth/
)

target_link_directories(${MY_APP} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/${MY_STATIC_LIB}/
)

target_link_libraries(${MY_APP} PRIVATE
    ${MY_STATIC_LIB}
)

# ---------------- STATIC LIB -----------------

add_library(${MY_STATIC_LIB} STATIC)

set(LIB_SOURCES
    src/Helpers.hpp
    src/TwoDimArrWrapper.hpp
    src/WindowConsole.cpp
    src/WindowConsole.hpp
    src/Font.cpp
    src/Font.hpp
    src/PrintMode.cpp
    src/PrintMode.hpp
    src/Keyboard.hpp
    src/BackgroundColor.hpp
    src/BackgroundColor.cpp
    src/ForegroundColor.cpp
    src/ForegroundColor.hpp
    src/ConsoleMode.cpp
    src/ConsoleMode.hpp
    src/ConsoleAttributes.cpp
    src/ConsoleAttributes.hpp
    src/Delim.hpp
    src/DelimStyle.cpp
    src/DelimStyle.hpp
    src/Subwindow.hpp
    src/Print.hpp
    src/Utils.hpp
    src/Utils.cpp
)

if(${CMAKE_CXX_STANDARD} EQUAL 23)
    set(LIB_SOURCES ${LIB_SOURCES} src/PrintCxx23.cpp)
else()
    set(LIB_SOURCES ${LIB_SOURCES} src/PrintCxx17.cpp)
endif()

if(WIN32)
    target_sources(${MY_STATIC_LIB} PRIVATE
        src/WinCode.cpp
        ${LIB_SOURCES}
    )
else()
    target_sources(${MY_STATIC_LIB} PRIVATE
        src/UnixCode.cpp
        ${LIB_SOURCES}
    )
endif()

target_include_directories(${MY_STATIC_LIB} PRIVATE
    3rdparty/widecharwidth/
    3rdparty/fmt/include/
)

#target_link_libraries(${MY_STATIC_LIB} PRIVATE
#    fmt::fmt
#)
