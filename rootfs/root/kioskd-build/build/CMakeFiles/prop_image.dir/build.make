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
include CMakeFiles/prop_image.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/prop_image.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/prop_image.dir/flags.make

CMakeFiles/prop_image.dir/props/image.c.o: CMakeFiles/prop_image.dir/flags.make
CMakeFiles/prop_image.dir/props/image.c.o: ../props/image.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/kioskd-build/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/prop_image.dir/props/image.c.o"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/prop_image.dir/props/image.c.o   -c /root/kioskd-build/props/image.c

CMakeFiles/prop_image.dir/props/image.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/prop_image.dir/props/image.c.i"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -E /root/kioskd-build/props/image.c > CMakeFiles/prop_image.dir/props/image.c.i

CMakeFiles/prop_image.dir/props/image.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/prop_image.dir/props/image.c.s"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -S /root/kioskd-build/props/image.c -o CMakeFiles/prop_image.dir/props/image.c.s

CMakeFiles/prop_image.dir/props/image.c.o.requires:
.PHONY : CMakeFiles/prop_image.dir/props/image.c.o.requires

CMakeFiles/prop_image.dir/props/image.c.o.provides: CMakeFiles/prop_image.dir/props/image.c.o.requires
	$(MAKE) -f CMakeFiles/prop_image.dir/build.make CMakeFiles/prop_image.dir/props/image.c.o.provides.build
.PHONY : CMakeFiles/prop_image.dir/props/image.c.o.provides

CMakeFiles/prop_image.dir/props/image.c.o.provides.build: CMakeFiles/prop_image.dir/props/image.c.o

# Object files for target prop_image
prop_image_OBJECTS = \
"CMakeFiles/prop_image.dir/props/image.c.o"

# External object files for target prop_image
prop_image_EXTERNAL_OBJECTS =

libprop_image.so: CMakeFiles/prop_image.dir/props/image.c.o
libprop_image.so: CMakeFiles/prop_image.dir/build.make
libprop_image.so: libkiosk.so
libprop_image.so: CMakeFiles/prop_image.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libprop_image.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prop_image.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/prop_image.dir/build: libprop_image.so
.PHONY : CMakeFiles/prop_image.dir/build

CMakeFiles/prop_image.dir/requires: CMakeFiles/prop_image.dir/props/image.c.o.requires
.PHONY : CMakeFiles/prop_image.dir/requires

CMakeFiles/prop_image.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/prop_image.dir/cmake_clean.cmake
.PHONY : CMakeFiles/prop_image.dir/clean

CMakeFiles/prop_image.dir/depend:
	cd /root/kioskd-build/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/kioskd-build /root/kioskd-build /root/kioskd-build/build /root/kioskd-build/build /root/kioskd-build/build/CMakeFiles/prop_image.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/prop_image.dir/depend
