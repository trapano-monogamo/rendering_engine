# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/chiara/dev/cpp/rendering_engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chiara/dev/cpp/rendering_engine/build

# Include any dependencies generated for this target.
include demo/CMakeFiles/demo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include demo/CMakeFiles/demo.dir/compiler_depend.make

# Include the progress variables for this target.
include demo/CMakeFiles/demo.dir/progress.make

# Include the compile flags for this target's objects.
include demo/CMakeFiles/demo.dir/flags.make

demo/CMakeFiles/demo.dir/src/main.cpp.o: demo/CMakeFiles/demo.dir/flags.make
demo/CMakeFiles/demo.dir/src/main.cpp.o: /home/chiara/dev/cpp/rendering_engine/demo/src/main.cpp
demo/CMakeFiles/demo.dir/src/main.cpp.o: demo/CMakeFiles/demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object demo/CMakeFiles/demo.dir/src/main.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT demo/CMakeFiles/demo.dir/src/main.cpp.o -MF CMakeFiles/demo.dir/src/main.cpp.o.d -o CMakeFiles/demo.dir/src/main.cpp.o -c /home/chiara/dev/cpp/rendering_engine/demo/src/main.cpp

demo/CMakeFiles/demo.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/main.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/demo/src/main.cpp > CMakeFiles/demo.dir/src/main.cpp.i

demo/CMakeFiles/demo.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/main.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/demo/src/main.cpp -o CMakeFiles/demo.dir/src/main.cpp.s

# Object files for target demo
demo_OBJECTS = \
"CMakeFiles/demo.dir/src/main.cpp.o"

# External object files for target demo
demo_EXTERNAL_OBJECTS =

demo/demo: demo/CMakeFiles/demo.dir/src/main.cpp.o
demo/demo: demo/CMakeFiles/demo.dir/build.make
demo/demo: engine/librendering_engine.a
demo/demo: demo/CMakeFiles/demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable demo"
	cd /home/chiara/dev/cpp/rendering_engine/build/demo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
demo/CMakeFiles/demo.dir/build: demo/demo
.PHONY : demo/CMakeFiles/demo.dir/build

demo/CMakeFiles/demo.dir/clean:
	cd /home/chiara/dev/cpp/rendering_engine/build/demo && $(CMAKE_COMMAND) -P CMakeFiles/demo.dir/cmake_clean.cmake
.PHONY : demo/CMakeFiles/demo.dir/clean

demo/CMakeFiles/demo.dir/depend:
	cd /home/chiara/dev/cpp/rendering_engine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chiara/dev/cpp/rendering_engine /home/chiara/dev/cpp/rendering_engine/demo /home/chiara/dev/cpp/rendering_engine/build /home/chiara/dev/cpp/rendering_engine/build/demo /home/chiara/dev/cpp/rendering_engine/build/demo/CMakeFiles/demo.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : demo/CMakeFiles/demo.dir/depend

