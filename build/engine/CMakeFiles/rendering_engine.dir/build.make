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
include engine/CMakeFiles/rendering_engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include engine/CMakeFiles/rendering_engine.dir/compiler_depend.make

# Include the progress variables for this target.
include engine/CMakeFiles/rendering_engine.dir/progress.make

# Include the compile flags for this target's objects.
include engine/CMakeFiles/rendering_engine.dir/flags.make

engine/CMakeFiles/rendering_engine.dir/src/core/camera.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/core/camera.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/core/camera.cpp
engine/CMakeFiles/rendering_engine.dir/src/core/camera.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/core/camera.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/core/camera.cpp.o -MF CMakeFiles/rendering_engine.dir/src/core/camera.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/core/camera.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/core/camera.cpp

engine/CMakeFiles/rendering_engine.dir/src/core/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/core/camera.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/core/camera.cpp > CMakeFiles/rendering_engine.dir/src/core/camera.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/core/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/core/camera.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/core/camera.cpp -o CMakeFiles/rendering_engine.dir/src/core/camera.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/core/game_app.cpp
engine/CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.o -MF CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/core/game_app.cpp

engine/CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/core/game_app.cpp > CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/core/game_app.cpp -o CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/core/light.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/core/light.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/core/light.cpp
engine/CMakeFiles/rendering_engine.dir/src/core/light.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/core/light.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/core/light.cpp.o -MF CMakeFiles/rendering_engine.dir/src/core/light.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/core/light.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/core/light.cpp

engine/CMakeFiles/rendering_engine.dir/src/core/light.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/core/light.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/core/light.cpp > CMakeFiles/rendering_engine.dir/src/core/light.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/core/light.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/core/light.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/core/light.cpp -o CMakeFiles/rendering_engine.dir/src/core/light.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/core/material.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/core/material.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/core/material.cpp
engine/CMakeFiles/rendering_engine.dir/src/core/material.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/core/material.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/core/material.cpp.o -MF CMakeFiles/rendering_engine.dir/src/core/material.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/core/material.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/core/material.cpp

engine/CMakeFiles/rendering_engine.dir/src/core/material.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/core/material.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/core/material.cpp > CMakeFiles/rendering_engine.dir/src/core/material.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/core/material.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/core/material.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/core/material.cpp -o CMakeFiles/rendering_engine.dir/src/core/material.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/core/mesh.cpp
engine/CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.o -MF CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/core/mesh.cpp

engine/CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/core/mesh.cpp > CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/core/mesh.cpp -o CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/core/renderable.cpp
engine/CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.o -MF CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/core/renderable.cpp

engine/CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/core/renderable.cpp > CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/core/renderable.cpp -o CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/core/scene.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/core/scene.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/core/scene.cpp
engine/CMakeFiles/rendering_engine.dir/src/core/scene.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/core/scene.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/core/scene.cpp.o -MF CMakeFiles/rendering_engine.dir/src/core/scene.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/core/scene.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/core/scene.cpp

engine/CMakeFiles/rendering_engine.dir/src/core/scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/core/scene.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/core/scene.cpp > CMakeFiles/rendering_engine.dir/src/core/scene.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/core/scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/core/scene.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/core/scene.cpp -o CMakeFiles/rendering_engine.dir/src/core/scene.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/core/shader.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/core/shader.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/core/shader.cpp
engine/CMakeFiles/rendering_engine.dir/src/core/shader.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/core/shader.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/core/shader.cpp.o -MF CMakeFiles/rendering_engine.dir/src/core/shader.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/core/shader.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/core/shader.cpp

engine/CMakeFiles/rendering_engine.dir/src/core/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/core/shader.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/core/shader.cpp > CMakeFiles/rendering_engine.dir/src/core/shader.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/core/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/core/shader.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/core/shader.cpp -o CMakeFiles/rendering_engine.dir/src/core/shader.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/core/texture.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/core/texture.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/core/texture.cpp
engine/CMakeFiles/rendering_engine.dir/src/core/texture.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/core/texture.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/core/texture.cpp.o -MF CMakeFiles/rendering_engine.dir/src/core/texture.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/core/texture.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/core/texture.cpp

engine/CMakeFiles/rendering_engine.dir/src/core/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/core/texture.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/core/texture.cpp > CMakeFiles/rendering_engine.dir/src/core/texture.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/core/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/core/texture.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/core/texture.cpp -o CMakeFiles/rendering_engine.dir/src/core/texture.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/core/transform.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/core/transform.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/core/transform.cpp
engine/CMakeFiles/rendering_engine.dir/src/core/transform.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/core/transform.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/core/transform.cpp.o -MF CMakeFiles/rendering_engine.dir/src/core/transform.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/core/transform.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/core/transform.cpp

engine/CMakeFiles/rendering_engine.dir/src/core/transform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/core/transform.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/core/transform.cpp > CMakeFiles/rendering_engine.dir/src/core/transform.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/core/transform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/core/transform.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/core/transform.cpp -o CMakeFiles/rendering_engine.dir/src/core/transform.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/ecs/ecs.cpp
engine/CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.o -MF CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/ecs/ecs.cpp

engine/CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/ecs/ecs.cpp > CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/ecs/ecs.cpp -o CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/glad.c.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/glad.c.o: /home/chiara/dev/cpp/rendering_engine/engine/src/glad.c
engine/CMakeFiles/rendering_engine.dir/src/glad.c.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object engine/CMakeFiles/rendering_engine.dir/src/glad.c.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/glad.c.o -MF CMakeFiles/rendering_engine.dir/src/glad.c.o.d -o CMakeFiles/rendering_engine.dir/src/glad.c.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/glad.c

engine/CMakeFiles/rendering_engine.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/rendering_engine.dir/src/glad.c.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/glad.c > CMakeFiles/rendering_engine.dir/src/glad.c.i

engine/CMakeFiles/rendering_engine.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/rendering_engine.dir/src/glad.c.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/glad.c -o CMakeFiles/rendering_engine.dir/src/glad.c.s

engine/CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/input_handler/input_handler.cpp
engine/CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.o -MF CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/input_handler/input_handler.cpp

engine/CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/input_handler/input_handler.cpp > CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/input_handler/input_handler.cpp -o CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/math/mat.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/math/mat.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/math/mat.cpp
engine/CMakeFiles/rendering_engine.dir/src/math/mat.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/math/mat.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/math/mat.cpp.o -MF CMakeFiles/rendering_engine.dir/src/math/mat.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/math/mat.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/math/mat.cpp

engine/CMakeFiles/rendering_engine.dir/src/math/mat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/math/mat.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/math/mat.cpp > CMakeFiles/rendering_engine.dir/src/math/mat.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/math/mat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/math/mat.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/math/mat.cpp -o CMakeFiles/rendering_engine.dir/src/math/mat.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/math/utils.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/math/utils.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/math/utils.cpp
engine/CMakeFiles/rendering_engine.dir/src/math/utils.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/math/utils.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/math/utils.cpp.o -MF CMakeFiles/rendering_engine.dir/src/math/utils.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/math/utils.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/math/utils.cpp

engine/CMakeFiles/rendering_engine.dir/src/math/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/math/utils.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/math/utils.cpp > CMakeFiles/rendering_engine.dir/src/math/utils.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/math/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/math/utils.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/math/utils.cpp -o CMakeFiles/rendering_engine.dir/src/math/utils.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/math/vec.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/math/vec.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/math/vec.cpp
engine/CMakeFiles/rendering_engine.dir/src/math/vec.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/math/vec.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/math/vec.cpp.o -MF CMakeFiles/rendering_engine.dir/src/math/vec.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/math/vec.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/math/vec.cpp

engine/CMakeFiles/rendering_engine.dir/src/math/vec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/math/vec.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/math/vec.cpp > CMakeFiles/rendering_engine.dir/src/math/vec.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/math/vec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/math/vec.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/math/vec.cpp -o CMakeFiles/rendering_engine.dir/src/math/vec.cpp.s

engine/CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.o: engine/CMakeFiles/rendering_engine.dir/flags.make
engine/CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.o: /home/chiara/dev/cpp/rendering_engine/engine/src/resource_manager/resource_manager.cpp
engine/CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.o: engine/CMakeFiles/rendering_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object engine/CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.o"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.o -MF CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.o.d -o CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.o -c /home/chiara/dev/cpp/rendering_engine/engine/src/resource_manager/resource_manager.cpp

engine/CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.i"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chiara/dev/cpp/rendering_engine/engine/src/resource_manager/resource_manager.cpp > CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.i

engine/CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.s"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chiara/dev/cpp/rendering_engine/engine/src/resource_manager/resource_manager.cpp -o CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.s

# Object files for target rendering_engine
rendering_engine_OBJECTS = \
"CMakeFiles/rendering_engine.dir/src/core/camera.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/core/light.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/core/material.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/core/scene.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/core/shader.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/core/texture.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/core/transform.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/glad.c.o" \
"CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/math/mat.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/math/utils.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/math/vec.cpp.o" \
"CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.o"

# External object files for target rendering_engine
rendering_engine_EXTERNAL_OBJECTS =

engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/core/camera.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/core/game_app.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/core/light.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/core/material.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/core/mesh.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/core/renderable.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/core/scene.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/core/shader.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/core/texture.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/core/transform.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/ecs/ecs.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/glad.c.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/input_handler/input_handler.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/math/mat.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/math/utils.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/math/vec.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/src/resource_manager/resource_manager.cpp.o
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/build.make
engine/librendering_engine.a: engine/CMakeFiles/rendering_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/chiara/dev/cpp/rendering_engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX static library librendering_engine.a"
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && $(CMAKE_COMMAND) -P CMakeFiles/rendering_engine.dir/cmake_clean_target.cmake
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rendering_engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
engine/CMakeFiles/rendering_engine.dir/build: engine/librendering_engine.a
.PHONY : engine/CMakeFiles/rendering_engine.dir/build

engine/CMakeFiles/rendering_engine.dir/clean:
	cd /home/chiara/dev/cpp/rendering_engine/build/engine && $(CMAKE_COMMAND) -P CMakeFiles/rendering_engine.dir/cmake_clean.cmake
.PHONY : engine/CMakeFiles/rendering_engine.dir/clean

engine/CMakeFiles/rendering_engine.dir/depend:
	cd /home/chiara/dev/cpp/rendering_engine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chiara/dev/cpp/rendering_engine /home/chiara/dev/cpp/rendering_engine/engine /home/chiara/dev/cpp/rendering_engine/build /home/chiara/dev/cpp/rendering_engine/build/engine /home/chiara/dev/cpp/rendering_engine/build/engine/CMakeFiles/rendering_engine.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : engine/CMakeFiles/rendering_engine.dir/depend

