# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /host-rootfs/usr/bin/cmake

# The command to remove a file.
RM = /host-rootfs/usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /host-rootfs/usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/kioskd-build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/kioskd-build/build

# Include any dependencies generated for this target.
include CMakeFiles/kioskd.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kioskd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kioskd.dir/flags.make

CMakeFiles/kioskd.dir/src/main.c.o: CMakeFiles/kioskd.dir/flags.make
CMakeFiles/kioskd.dir/src/main.c.o: ../src/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/kioskd-build/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/kioskd.dir/src/main.c.o"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/kioskd.dir/src/main.c.o   -c /root/kioskd-build/src/main.c

CMakeFiles/kioskd.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/kioskd.dir/src/main.c.i"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -E /root/kioskd-build/src/main.c > CMakeFiles/kioskd.dir/src/main.c.i

CMakeFiles/kioskd.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/kioskd.dir/src/main.c.s"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -S /root/kioskd-build/src/main.c -o CMakeFiles/kioskd.dir/src/main.c.s

CMakeFiles/kioskd.dir/src/main.c.o.requires:
.PHONY : CMakeFiles/kioskd.dir/src/main.c.o.requires

CMakeFiles/kioskd.dir/src/main.c.o.provides: CMakeFiles/kioskd.dir/src/main.c.o.requires
	$(MAKE) -f CMakeFiles/kioskd.dir/build.make CMakeFiles/kioskd.dir/src/main.c.o.provides.build
.PHONY : CMakeFiles/kioskd.dir/src/main.c.o.provides

CMakeFiles/kioskd.dir/src/main.c.o.provides.build: CMakeFiles/kioskd.dir/src/main.c.o

# Object files for target kioskd
kioskd_OBJECTS = \
"CMakeFiles/kioskd.dir/src/main.c.o"

# External object files for target kioskd
kioskd_EXTERNAL_OBJECTS =

kioskd: CMakeFiles/kioskd.dir/src/main.c.o
kioskd: CMakeFiles/kioskd.dir/build.make
kioskd: libkiosk.so
kioskd: CMakeFiles/kioskd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable kioskd"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kioskd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kioskd.dir/build: kioskd
.PHONY : CMakeFiles/kioskd.dir/build

CMakeFiles/kioskd.dir/requires: CMakeFiles/kioskd.dir/src/main.c.o.requires
.PHONY : CMakeFiles/kioskd.dir/requires

CMakeFiles/kioskd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kioskd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kioskd.dir/clean

CMakeFiles/kioskd.dir/depend:
	cd /root/kioskd-build/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/kioskd-build /root/kioskd-build /root/kioskd-build/build /root/kioskd-build/build /root/kioskd-build/build/CMakeFiles/kioskd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kioskd.dir/depend
