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
include CMakeFiles/kiosk.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kiosk.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kiosk.dir/flags.make

CMakeFiles/kiosk.dir/src/kioskd.c.o: CMakeFiles/kiosk.dir/flags.make
CMakeFiles/kiosk.dir/src/kioskd.c.o: ../src/kioskd.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/kioskd-build/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/kiosk.dir/src/kioskd.c.o"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/kiosk.dir/src/kioskd.c.o   -c /root/kioskd-build/src/kioskd.c

CMakeFiles/kiosk.dir/src/kioskd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/kiosk.dir/src/kioskd.c.i"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -E /root/kioskd-build/src/kioskd.c > CMakeFiles/kiosk.dir/src/kioskd.c.i

CMakeFiles/kiosk.dir/src/kioskd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/kiosk.dir/src/kioskd.c.s"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -S /root/kioskd-build/src/kioskd.c -o CMakeFiles/kiosk.dir/src/kioskd.c.s

CMakeFiles/kiosk.dir/src/kioskd.c.o.requires:
.PHONY : CMakeFiles/kiosk.dir/src/kioskd.c.o.requires

CMakeFiles/kiosk.dir/src/kioskd.c.o.provides: CMakeFiles/kiosk.dir/src/kioskd.c.o.requires
	$(MAKE) -f CMakeFiles/kiosk.dir/build.make CMakeFiles/kiosk.dir/src/kioskd.c.o.provides.build
.PHONY : CMakeFiles/kiosk.dir/src/kioskd.c.o.provides

CMakeFiles/kiosk.dir/src/kioskd.c.o.provides.build: CMakeFiles/kiosk.dir/src/kioskd.c.o

CMakeFiles/kiosk.dir/src/cJSON.c.o: CMakeFiles/kiosk.dir/flags.make
CMakeFiles/kiosk.dir/src/cJSON.c.o: ../src/cJSON.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/kioskd-build/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/kiosk.dir/src/cJSON.c.o"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/kiosk.dir/src/cJSON.c.o   -c /root/kioskd-build/src/cJSON.c

CMakeFiles/kiosk.dir/src/cJSON.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/kiosk.dir/src/cJSON.c.i"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -E /root/kioskd-build/src/cJSON.c > CMakeFiles/kiosk.dir/src/cJSON.c.i

CMakeFiles/kiosk.dir/src/cJSON.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/kiosk.dir/src/cJSON.c.s"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -S /root/kioskd-build/src/cJSON.c -o CMakeFiles/kiosk.dir/src/cJSON.c.s

CMakeFiles/kiosk.dir/src/cJSON.c.o.requires:
.PHONY : CMakeFiles/kiosk.dir/src/cJSON.c.o.requires

CMakeFiles/kiosk.dir/src/cJSON.c.o.provides: CMakeFiles/kiosk.dir/src/cJSON.c.o.requires
	$(MAKE) -f CMakeFiles/kiosk.dir/build.make CMakeFiles/kiosk.dir/src/cJSON.c.o.provides.build
.PHONY : CMakeFiles/kiosk.dir/src/cJSON.c.o.provides

CMakeFiles/kiosk.dir/src/cJSON.c.o.provides.build: CMakeFiles/kiosk.dir/src/cJSON.c.o

CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o: CMakeFiles/kiosk.dir/flags.make
CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o: ../src/jsonrpc-c.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/kioskd-build/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o   -c /root/kioskd-build/src/jsonrpc-c.c

CMakeFiles/kiosk.dir/src/jsonrpc-c.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/kiosk.dir/src/jsonrpc-c.c.i"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -E /root/kioskd-build/src/jsonrpc-c.c > CMakeFiles/kiosk.dir/src/jsonrpc-c.c.i

CMakeFiles/kiosk.dir/src/jsonrpc-c.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/kiosk.dir/src/jsonrpc-c.c.s"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -S /root/kioskd-build/src/jsonrpc-c.c -o CMakeFiles/kiosk.dir/src/jsonrpc-c.c.s

CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o.requires:
.PHONY : CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o.requires

CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o.provides: CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o.requires
	$(MAKE) -f CMakeFiles/kiosk.dir/build.make CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o.provides.build
.PHONY : CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o.provides

CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o.provides.build: CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o

CMakeFiles/kiosk.dir/src/graphics.c.o: CMakeFiles/kiosk.dir/flags.make
CMakeFiles/kiosk.dir/src/graphics.c.o: ../src/graphics.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/kioskd-build/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/kiosk.dir/src/graphics.c.o"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/kiosk.dir/src/graphics.c.o   -c /root/kioskd-build/src/graphics.c

CMakeFiles/kiosk.dir/src/graphics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/kiosk.dir/src/graphics.c.i"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -E /root/kioskd-build/src/graphics.c > CMakeFiles/kiosk.dir/src/graphics.c.i

CMakeFiles/kiosk.dir/src/graphics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/kiosk.dir/src/graphics.c.s"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -S /root/kioskd-build/src/graphics.c -o CMakeFiles/kiosk.dir/src/graphics.c.s

CMakeFiles/kiosk.dir/src/graphics.c.o.requires:
.PHONY : CMakeFiles/kiosk.dir/src/graphics.c.o.requires

CMakeFiles/kiosk.dir/src/graphics.c.o.provides: CMakeFiles/kiosk.dir/src/graphics.c.o.requires
	$(MAKE) -f CMakeFiles/kiosk.dir/build.make CMakeFiles/kiosk.dir/src/graphics.c.o.provides.build
.PHONY : CMakeFiles/kiosk.dir/src/graphics.c.o.provides

CMakeFiles/kiosk.dir/src/graphics.c.o.provides.build: CMakeFiles/kiosk.dir/src/graphics.c.o

CMakeFiles/kiosk.dir/src/propmanager.c.o: CMakeFiles/kiosk.dir/flags.make
CMakeFiles/kiosk.dir/src/propmanager.c.o: ../src/propmanager.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/kioskd-build/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/kiosk.dir/src/propmanager.c.o"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/kiosk.dir/src/propmanager.c.o   -c /root/kioskd-build/src/propmanager.c

CMakeFiles/kiosk.dir/src/propmanager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/kiosk.dir/src/propmanager.c.i"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -E /root/kioskd-build/src/propmanager.c > CMakeFiles/kiosk.dir/src/propmanager.c.i

CMakeFiles/kiosk.dir/src/propmanager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/kiosk.dir/src/propmanager.c.s"
	/opt/xgcc/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_FLAGS) -S /root/kioskd-build/src/propmanager.c -o CMakeFiles/kiosk.dir/src/propmanager.c.s

CMakeFiles/kiosk.dir/src/propmanager.c.o.requires:
.PHONY : CMakeFiles/kiosk.dir/src/propmanager.c.o.requires

CMakeFiles/kiosk.dir/src/propmanager.c.o.provides: CMakeFiles/kiosk.dir/src/propmanager.c.o.requires
	$(MAKE) -f CMakeFiles/kiosk.dir/build.make CMakeFiles/kiosk.dir/src/propmanager.c.o.provides.build
.PHONY : CMakeFiles/kiosk.dir/src/propmanager.c.o.provides

CMakeFiles/kiosk.dir/src/propmanager.c.o.provides.build: CMakeFiles/kiosk.dir/src/propmanager.c.o

# Object files for target kiosk
kiosk_OBJECTS = \
"CMakeFiles/kiosk.dir/src/kioskd.c.o" \
"CMakeFiles/kiosk.dir/src/cJSON.c.o" \
"CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o" \
"CMakeFiles/kiosk.dir/src/graphics.c.o" \
"CMakeFiles/kiosk.dir/src/propmanager.c.o"

# External object files for target kiosk
kiosk_EXTERNAL_OBJECTS =

libkiosk.so: CMakeFiles/kiosk.dir/src/kioskd.c.o
libkiosk.so: CMakeFiles/kiosk.dir/src/cJSON.c.o
libkiosk.so: CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o
libkiosk.so: CMakeFiles/kiosk.dir/src/graphics.c.o
libkiosk.so: CMakeFiles/kiosk.dir/src/propmanager.c.o
libkiosk.so: CMakeFiles/kiosk.dir/build.make
libkiosk.so: CMakeFiles/kiosk.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libkiosk.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kiosk.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kiosk.dir/build: libkiosk.so
.PHONY : CMakeFiles/kiosk.dir/build

CMakeFiles/kiosk.dir/requires: CMakeFiles/kiosk.dir/src/kioskd.c.o.requires
CMakeFiles/kiosk.dir/requires: CMakeFiles/kiosk.dir/src/cJSON.c.o.requires
CMakeFiles/kiosk.dir/requires: CMakeFiles/kiosk.dir/src/jsonrpc-c.c.o.requires
CMakeFiles/kiosk.dir/requires: CMakeFiles/kiosk.dir/src/graphics.c.o.requires
CMakeFiles/kiosk.dir/requires: CMakeFiles/kiosk.dir/src/propmanager.c.o.requires
.PHONY : CMakeFiles/kiosk.dir/requires

CMakeFiles/kiosk.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kiosk.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kiosk.dir/clean

CMakeFiles/kiosk.dir/depend:
	cd /root/kioskd-build/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/kioskd-build /root/kioskd-build /root/kioskd-build/build /root/kioskd-build/build /root/kioskd-build/build/CMakeFiles/kiosk.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kiosk.dir/depend
