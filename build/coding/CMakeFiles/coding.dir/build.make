# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wyp/Desktop/qwe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wyp/Desktop/qwe/build

# Include any dependencies generated for this target.
include coding/CMakeFiles/coding.dir/depend.make

# Include the progress variables for this target.
include coding/CMakeFiles/coding.dir/progress.make

# Include the compile flags for this target's objects.
include coding/CMakeFiles/coding.dir/flags.make

coding/CMakeFiles/coding.dir/decoding.cpp.o: coding/CMakeFiles/coding.dir/flags.make
coding/CMakeFiles/coding.dir/decoding.cpp.o: ../coding/decoding.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wyp/Desktop/qwe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object coding/CMakeFiles/coding.dir/decoding.cpp.o"
	cd /home/wyp/Desktop/qwe/build/coding && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/coding.dir/decoding.cpp.o -c /home/wyp/Desktop/qwe/coding/decoding.cpp

coding/CMakeFiles/coding.dir/decoding.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/coding.dir/decoding.cpp.i"
	cd /home/wyp/Desktop/qwe/build/coding && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wyp/Desktop/qwe/coding/decoding.cpp > CMakeFiles/coding.dir/decoding.cpp.i

coding/CMakeFiles/coding.dir/decoding.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/coding.dir/decoding.cpp.s"
	cd /home/wyp/Desktop/qwe/build/coding && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wyp/Desktop/qwe/coding/decoding.cpp -o CMakeFiles/coding.dir/decoding.cpp.s

coding/CMakeFiles/coding.dir/encoding.cpp.o: coding/CMakeFiles/coding.dir/flags.make
coding/CMakeFiles/coding.dir/encoding.cpp.o: ../coding/encoding.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wyp/Desktop/qwe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object coding/CMakeFiles/coding.dir/encoding.cpp.o"
	cd /home/wyp/Desktop/qwe/build/coding && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/coding.dir/encoding.cpp.o -c /home/wyp/Desktop/qwe/coding/encoding.cpp

coding/CMakeFiles/coding.dir/encoding.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/coding.dir/encoding.cpp.i"
	cd /home/wyp/Desktop/qwe/build/coding && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wyp/Desktop/qwe/coding/encoding.cpp > CMakeFiles/coding.dir/encoding.cpp.i

coding/CMakeFiles/coding.dir/encoding.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/coding.dir/encoding.cpp.s"
	cd /home/wyp/Desktop/qwe/build/coding && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wyp/Desktop/qwe/coding/encoding.cpp -o CMakeFiles/coding.dir/encoding.cpp.s

# Object files for target coding
coding_OBJECTS = \
"CMakeFiles/coding.dir/decoding.cpp.o" \
"CMakeFiles/coding.dir/encoding.cpp.o"

# External object files for target coding
coding_EXTERNAL_OBJECTS =

coding/libcoding.a: coding/CMakeFiles/coding.dir/decoding.cpp.o
coding/libcoding.a: coding/CMakeFiles/coding.dir/encoding.cpp.o
coding/libcoding.a: coding/CMakeFiles/coding.dir/build.make
coding/libcoding.a: coding/CMakeFiles/coding.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wyp/Desktop/qwe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libcoding.a"
	cd /home/wyp/Desktop/qwe/build/coding && $(CMAKE_COMMAND) -P CMakeFiles/coding.dir/cmake_clean_target.cmake
	cd /home/wyp/Desktop/qwe/build/coding && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/coding.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
coding/CMakeFiles/coding.dir/build: coding/libcoding.a

.PHONY : coding/CMakeFiles/coding.dir/build

coding/CMakeFiles/coding.dir/clean:
	cd /home/wyp/Desktop/qwe/build/coding && $(CMAKE_COMMAND) -P CMakeFiles/coding.dir/cmake_clean.cmake
.PHONY : coding/CMakeFiles/coding.dir/clean

coding/CMakeFiles/coding.dir/depend:
	cd /home/wyp/Desktop/qwe/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wyp/Desktop/qwe /home/wyp/Desktop/qwe/coding /home/wyp/Desktop/qwe/build /home/wyp/Desktop/qwe/build/coding /home/wyp/Desktop/qwe/build/coding/CMakeFiles/coding.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : coding/CMakeFiles/coding.dir/depend

