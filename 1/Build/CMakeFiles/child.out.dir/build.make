# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.27.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.27.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/che4ve/MAI/LabsOSI/1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/che4ve/MAI/LabsOSI/1/Build

# Include any dependencies generated for this target.
include CMakeFiles/child.out.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/child.out.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/child.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/child.out.dir/flags.make

CMakeFiles/child.out.dir/child.cpp.o: CMakeFiles/child.out.dir/flags.make
CMakeFiles/child.out.dir/child.cpp.o: /Users/che4ve/MAI/LabsOSI/1/child.cpp
CMakeFiles/child.out.dir/child.cpp.o: CMakeFiles/child.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/che4ve/MAI/LabsOSI/1/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/child.out.dir/child.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/child.out.dir/child.cpp.o -MF CMakeFiles/child.out.dir/child.cpp.o.d -o CMakeFiles/child.out.dir/child.cpp.o -c /Users/che4ve/MAI/LabsOSI/1/child.cpp

CMakeFiles/child.out.dir/child.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/child.out.dir/child.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/che4ve/MAI/LabsOSI/1/child.cpp > CMakeFiles/child.out.dir/child.cpp.i

CMakeFiles/child.out.dir/child.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/child.out.dir/child.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/che4ve/MAI/LabsOSI/1/child.cpp -o CMakeFiles/child.out.dir/child.cpp.s

# Object files for target child.out
child_out_OBJECTS = \
"CMakeFiles/child.out.dir/child.cpp.o"

# External object files for target child.out
child_out_EXTERNAL_OBJECTS =

child.out: CMakeFiles/child.out.dir/child.cpp.o
child.out: CMakeFiles/child.out.dir/build.make
child.out: CMakeFiles/child.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/che4ve/MAI/LabsOSI/1/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable child.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/child.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/child.out.dir/build: child.out
.PHONY : CMakeFiles/child.out.dir/build

CMakeFiles/child.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/child.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/child.out.dir/clean

CMakeFiles/child.out.dir/depend:
	cd /Users/che4ve/MAI/LabsOSI/1/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/che4ve/MAI/LabsOSI/1 /Users/che4ve/MAI/LabsOSI/1 /Users/che4ve/MAI/LabsOSI/1/Build /Users/che4ve/MAI/LabsOSI/1/Build /Users/che4ve/MAI/LabsOSI/1/Build/CMakeFiles/child.out.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/child.out.dir/depend

