# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/farsight/netspace/gq

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/farsight/netspace/gq/cmake

# Include any dependencies generated for this target.
include CMakeFiles/gq.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gq.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gq.dir/flags.make

CMakeFiles/gq.dir/gq/log.cc.o: CMakeFiles/gq.dir/flags.make
CMakeFiles/gq.dir/gq/log.cc.o: ../gq/log.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/farsight/netspace/gq/cmake/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gq.dir/gq/log.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gq.dir/gq/log.cc.o -c /home/farsight/netspace/gq/gq/log.cc

CMakeFiles/gq.dir/gq/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gq.dir/gq/log.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/farsight/netspace/gq/gq/log.cc > CMakeFiles/gq.dir/gq/log.cc.i

CMakeFiles/gq.dir/gq/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gq.dir/gq/log.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/farsight/netspace/gq/gq/log.cc -o CMakeFiles/gq.dir/gq/log.cc.s

CMakeFiles/gq.dir/gq/log.cc.o.requires:
.PHONY : CMakeFiles/gq.dir/gq/log.cc.o.requires

CMakeFiles/gq.dir/gq/log.cc.o.provides: CMakeFiles/gq.dir/gq/log.cc.o.requires
	$(MAKE) -f CMakeFiles/gq.dir/build.make CMakeFiles/gq.dir/gq/log.cc.o.provides.build
.PHONY : CMakeFiles/gq.dir/gq/log.cc.o.provides

CMakeFiles/gq.dir/gq/log.cc.o.provides.build: CMakeFiles/gq.dir/gq/log.cc.o

# Object files for target gq
gq_OBJECTS = \
"CMakeFiles/gq.dir/gq/log.cc.o"

# External object files for target gq
gq_EXTERNAL_OBJECTS =

../lib/libgq.so: CMakeFiles/gq.dir/gq/log.cc.o
../lib/libgq.so: CMakeFiles/gq.dir/build.make
../lib/libgq.so: CMakeFiles/gq.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../lib/libgq.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gq.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gq.dir/build: ../lib/libgq.so
.PHONY : CMakeFiles/gq.dir/build

CMakeFiles/gq.dir/requires: CMakeFiles/gq.dir/gq/log.cc.o.requires
.PHONY : CMakeFiles/gq.dir/requires

CMakeFiles/gq.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gq.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gq.dir/clean

CMakeFiles/gq.dir/depend:
	cd /home/farsight/netspace/gq/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/farsight/netspace/gq /home/farsight/netspace/gq /home/farsight/netspace/gq/cmake /home/farsight/netspace/gq/cmake /home/farsight/netspace/gq/cmake/CMakeFiles/gq.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gq.dir/depend

