# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/DevProjects/ConsoleCpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/DevProjects/ConsoleCpp

# Include any dependencies generated for this target.
include CMakeFiles/ConsoleCppStatic.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ConsoleCppStatic.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ConsoleCppStatic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ConsoleCppStatic.dir/flags.make

CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.o: CMakeFiles/ConsoleCppStatic.dir/flags.make
CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.o: src/UnixCode.cpp
CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.o: CMakeFiles/ConsoleCppStatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DevProjects/ConsoleCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.o -MF CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.o.d -o CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.o -c /mnt/d/DevProjects/ConsoleCpp/src/UnixCode.cpp

CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DevProjects/ConsoleCpp/src/UnixCode.cpp > CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.i

CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DevProjects/ConsoleCpp/src/UnixCode.cpp -o CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.s

CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.o: CMakeFiles/ConsoleCppStatic.dir/flags.make
CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.o: src/WindowConsole.cpp
CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.o: CMakeFiles/ConsoleCppStatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DevProjects/ConsoleCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.o -MF CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.o.d -o CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.o -c /mnt/d/DevProjects/ConsoleCpp/src/WindowConsole.cpp

CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DevProjects/ConsoleCpp/src/WindowConsole.cpp > CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.i

CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DevProjects/ConsoleCpp/src/WindowConsole.cpp -o CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.s

CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.o: CMakeFiles/ConsoleCppStatic.dir/flags.make
CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.o: src/Font.cpp
CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.o: CMakeFiles/ConsoleCppStatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DevProjects/ConsoleCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.o -MF CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.o.d -o CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.o -c /mnt/d/DevProjects/ConsoleCpp/src/Font.cpp

CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DevProjects/ConsoleCpp/src/Font.cpp > CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.i

CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DevProjects/ConsoleCpp/src/Font.cpp -o CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.s

CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.o: CMakeFiles/ConsoleCppStatic.dir/flags.make
CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.o: src/PrintMode.cpp
CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.o: CMakeFiles/ConsoleCppStatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DevProjects/ConsoleCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.o -MF CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.o.d -o CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.o -c /mnt/d/DevProjects/ConsoleCpp/src/PrintMode.cpp

CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DevProjects/ConsoleCpp/src/PrintMode.cpp > CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.i

CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DevProjects/ConsoleCpp/src/PrintMode.cpp -o CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.s

CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.o: CMakeFiles/ConsoleCppStatic.dir/flags.make
CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.o: src/BackgroundColor.cpp
CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.o: CMakeFiles/ConsoleCppStatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DevProjects/ConsoleCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.o -MF CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.o.d -o CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.o -c /mnt/d/DevProjects/ConsoleCpp/src/BackgroundColor.cpp

CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DevProjects/ConsoleCpp/src/BackgroundColor.cpp > CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.i

CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DevProjects/ConsoleCpp/src/BackgroundColor.cpp -o CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.s

CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.o: CMakeFiles/ConsoleCppStatic.dir/flags.make
CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.o: src/ForegroundColor.cpp
CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.o: CMakeFiles/ConsoleCppStatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DevProjects/ConsoleCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.o -MF CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.o.d -o CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.o -c /mnt/d/DevProjects/ConsoleCpp/src/ForegroundColor.cpp

CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DevProjects/ConsoleCpp/src/ForegroundColor.cpp > CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.i

CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DevProjects/ConsoleCpp/src/ForegroundColor.cpp -o CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.s

CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.o: CMakeFiles/ConsoleCppStatic.dir/flags.make
CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.o: src/ConsoleMode.cpp
CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.o: CMakeFiles/ConsoleCppStatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DevProjects/ConsoleCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.o -MF CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.o.d -o CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.o -c /mnt/d/DevProjects/ConsoleCpp/src/ConsoleMode.cpp

CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DevProjects/ConsoleCpp/src/ConsoleMode.cpp > CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.i

CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DevProjects/ConsoleCpp/src/ConsoleMode.cpp -o CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.s

CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.o: CMakeFiles/ConsoleCppStatic.dir/flags.make
CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.o: src/ConsoleAttributes.cpp
CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.o: CMakeFiles/ConsoleCppStatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DevProjects/ConsoleCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.o -MF CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.o.d -o CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.o -c /mnt/d/DevProjects/ConsoleCpp/src/ConsoleAttributes.cpp

CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DevProjects/ConsoleCpp/src/ConsoleAttributes.cpp > CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.i

CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DevProjects/ConsoleCpp/src/ConsoleAttributes.cpp -o CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.s

CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.o: CMakeFiles/ConsoleCppStatic.dir/flags.make
CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.o: src/DelimStyle.cpp
CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.o: CMakeFiles/ConsoleCppStatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DevProjects/ConsoleCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.o -MF CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.o.d -o CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.o -c /mnt/d/DevProjects/ConsoleCpp/src/DelimStyle.cpp

CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DevProjects/ConsoleCpp/src/DelimStyle.cpp > CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.i

CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DevProjects/ConsoleCpp/src/DelimStyle.cpp -o CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.s

CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.o: CMakeFiles/ConsoleCppStatic.dir/flags.make
CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.o: src/Utils.cpp
CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.o: CMakeFiles/ConsoleCppStatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DevProjects/ConsoleCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.o -MF CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.o.d -o CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.o -c /mnt/d/DevProjects/ConsoleCpp/src/Utils.cpp

CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DevProjects/ConsoleCpp/src/Utils.cpp > CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.i

CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DevProjects/ConsoleCpp/src/Utils.cpp -o CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.s

CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.o: CMakeFiles/ConsoleCppStatic.dir/flags.make
CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.o: src/PrintCxx17.cpp
CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.o: CMakeFiles/ConsoleCppStatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DevProjects/ConsoleCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.o -MF CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.o.d -o CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.o -c /mnt/d/DevProjects/ConsoleCpp/src/PrintCxx17.cpp

CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DevProjects/ConsoleCpp/src/PrintCxx17.cpp > CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.i

CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DevProjects/ConsoleCpp/src/PrintCxx17.cpp -o CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.s

# Object files for target ConsoleCppStatic
ConsoleCppStatic_OBJECTS = \
"CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.o" \
"CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.o" \
"CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.o" \
"CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.o" \
"CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.o" \
"CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.o" \
"CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.o" \
"CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.o" \
"CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.o" \
"CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.o" \
"CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.o"

# External object files for target ConsoleCppStatic
ConsoleCppStatic_EXTERNAL_OBJECTS =

libConsoleCppStatic.a: CMakeFiles/ConsoleCppStatic.dir/src/UnixCode.cpp.o
libConsoleCppStatic.a: CMakeFiles/ConsoleCppStatic.dir/src/WindowConsole.cpp.o
libConsoleCppStatic.a: CMakeFiles/ConsoleCppStatic.dir/src/Font.cpp.o
libConsoleCppStatic.a: CMakeFiles/ConsoleCppStatic.dir/src/PrintMode.cpp.o
libConsoleCppStatic.a: CMakeFiles/ConsoleCppStatic.dir/src/BackgroundColor.cpp.o
libConsoleCppStatic.a: CMakeFiles/ConsoleCppStatic.dir/src/ForegroundColor.cpp.o
libConsoleCppStatic.a: CMakeFiles/ConsoleCppStatic.dir/src/ConsoleMode.cpp.o
libConsoleCppStatic.a: CMakeFiles/ConsoleCppStatic.dir/src/ConsoleAttributes.cpp.o
libConsoleCppStatic.a: CMakeFiles/ConsoleCppStatic.dir/src/DelimStyle.cpp.o
libConsoleCppStatic.a: CMakeFiles/ConsoleCppStatic.dir/src/Utils.cpp.o
libConsoleCppStatic.a: CMakeFiles/ConsoleCppStatic.dir/src/PrintCxx17.cpp.o
libConsoleCppStatic.a: CMakeFiles/ConsoleCppStatic.dir/build.make
libConsoleCppStatic.a: CMakeFiles/ConsoleCppStatic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/DevProjects/ConsoleCpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX static library libConsoleCppStatic.a"
	$(CMAKE_COMMAND) -P CMakeFiles/ConsoleCppStatic.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ConsoleCppStatic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ConsoleCppStatic.dir/build: libConsoleCppStatic.a
.PHONY : CMakeFiles/ConsoleCppStatic.dir/build

CMakeFiles/ConsoleCppStatic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ConsoleCppStatic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ConsoleCppStatic.dir/clean

CMakeFiles/ConsoleCppStatic.dir/depend:
	cd /mnt/d/DevProjects/ConsoleCpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/DevProjects/ConsoleCpp /mnt/d/DevProjects/ConsoleCpp /mnt/d/DevProjects/ConsoleCpp /mnt/d/DevProjects/ConsoleCpp /mnt/d/DevProjects/ConsoleCpp/CMakeFiles/ConsoleCppStatic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ConsoleCppStatic.dir/depend
