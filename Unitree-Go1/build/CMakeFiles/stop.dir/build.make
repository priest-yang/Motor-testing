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
CMAKE_SOURCE_DIR = /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/build

# Include any dependencies generated for this target.
include CMakeFiles/stop.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/stop.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/stop.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stop.dir/flags.make

CMakeFiles/stop.dir/example/stop.cpp.o: CMakeFiles/stop.dir/flags.make
CMakeFiles/stop.dir/example/stop.cpp.o: ../example/stop.cpp
CMakeFiles/stop.dir/example/stop.cpp.o: CMakeFiles/stop.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stop.dir/example/stop.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/stop.dir/example/stop.cpp.o -MF CMakeFiles/stop.dir/example/stop.cpp.o.d -o CMakeFiles/stop.dir/example/stop.cpp.o -c /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/example/stop.cpp

CMakeFiles/stop.dir/example/stop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stop.dir/example/stop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/example/stop.cpp > CMakeFiles/stop.dir/example/stop.cpp.i

CMakeFiles/stop.dir/example/stop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stop.dir/example/stop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/example/stop.cpp -o CMakeFiles/stop.dir/example/stop.cpp.s

CMakeFiles/stop.dir/example/preprogrammed.cpp.o: CMakeFiles/stop.dir/flags.make
CMakeFiles/stop.dir/example/preprogrammed.cpp.o: ../example/preprogrammed.cpp
CMakeFiles/stop.dir/example/preprogrammed.cpp.o: CMakeFiles/stop.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/stop.dir/example/preprogrammed.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/stop.dir/example/preprogrammed.cpp.o -MF CMakeFiles/stop.dir/example/preprogrammed.cpp.o.d -o CMakeFiles/stop.dir/example/preprogrammed.cpp.o -c /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/example/preprogrammed.cpp

CMakeFiles/stop.dir/example/preprogrammed.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stop.dir/example/preprogrammed.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/example/preprogrammed.cpp > CMakeFiles/stop.dir/example/preprogrammed.cpp.i

CMakeFiles/stop.dir/example/preprogrammed.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stop.dir/example/preprogrammed.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/example/preprogrammed.cpp -o CMakeFiles/stop.dir/example/preprogrammed.cpp.s

# Object files for target stop
stop_OBJECTS = \
"CMakeFiles/stop.dir/example/stop.cpp.o" \
"CMakeFiles/stop.dir/example/preprogrammed.cpp.o"

# External object files for target stop
stop_EXTERNAL_OBJECTS =

stop: CMakeFiles/stop.dir/example/stop.cpp.o
stop: CMakeFiles/stop.dir/example/preprogrammed.cpp.o
stop: CMakeFiles/stop.dir/build.make
stop: CMakeFiles/stop.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable stop"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stop.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stop.dir/build: stop
.PHONY : CMakeFiles/stop.dir/build

CMakeFiles/stop.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stop.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stop.dir/clean

CMakeFiles/stop.dir/depend:
	cd /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/build /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/build /home/xuzhekai/FA23/motors/Unitree_motor_SDK_Linux/build/CMakeFiles/stop.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stop.dir/depend

