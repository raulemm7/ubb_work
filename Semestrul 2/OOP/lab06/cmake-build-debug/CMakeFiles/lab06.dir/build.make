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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/oop/lab06

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/oop/lab06/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab06.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lab06.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lab06.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab06.dir/flags.make

CMakeFiles/lab06.dir/main.cpp.o: CMakeFiles/lab06.dir/flags.make
CMakeFiles/lab06.dir/main.cpp.o: /mnt/d/oop/lab06/main.cpp
CMakeFiles/lab06.dir/main.cpp.o: CMakeFiles/lab06.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/oop/lab06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab06.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab06.dir/main.cpp.o -MF CMakeFiles/lab06.dir/main.cpp.o.d -o CMakeFiles/lab06.dir/main.cpp.o -c /mnt/d/oop/lab06/main.cpp

CMakeFiles/lab06.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lab06.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/oop/lab06/main.cpp > CMakeFiles/lab06.dir/main.cpp.i

CMakeFiles/lab06.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lab06.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/oop/lab06/main.cpp -o CMakeFiles/lab06.dir/main.cpp.s

CMakeFiles/lab06.dir/domain.cpp.o: CMakeFiles/lab06.dir/flags.make
CMakeFiles/lab06.dir/domain.cpp.o: /mnt/d/oop/lab06/domain.cpp
CMakeFiles/lab06.dir/domain.cpp.o: CMakeFiles/lab06.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/oop/lab06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lab06.dir/domain.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab06.dir/domain.cpp.o -MF CMakeFiles/lab06.dir/domain.cpp.o.d -o CMakeFiles/lab06.dir/domain.cpp.o -c /mnt/d/oop/lab06/domain.cpp

CMakeFiles/lab06.dir/domain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lab06.dir/domain.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/oop/lab06/domain.cpp > CMakeFiles/lab06.dir/domain.cpp.i

CMakeFiles/lab06.dir/domain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lab06.dir/domain.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/oop/lab06/domain.cpp -o CMakeFiles/lab06.dir/domain.cpp.s

CMakeFiles/lab06.dir/repository.cpp.o: CMakeFiles/lab06.dir/flags.make
CMakeFiles/lab06.dir/repository.cpp.o: /mnt/d/oop/lab06/repository.cpp
CMakeFiles/lab06.dir/repository.cpp.o: CMakeFiles/lab06.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/oop/lab06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/lab06.dir/repository.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab06.dir/repository.cpp.o -MF CMakeFiles/lab06.dir/repository.cpp.o.d -o CMakeFiles/lab06.dir/repository.cpp.o -c /mnt/d/oop/lab06/repository.cpp

CMakeFiles/lab06.dir/repository.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lab06.dir/repository.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/oop/lab06/repository.cpp > CMakeFiles/lab06.dir/repository.cpp.i

CMakeFiles/lab06.dir/repository.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lab06.dir/repository.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/oop/lab06/repository.cpp -o CMakeFiles/lab06.dir/repository.cpp.s

CMakeFiles/lab06.dir/ui.cpp.o: CMakeFiles/lab06.dir/flags.make
CMakeFiles/lab06.dir/ui.cpp.o: /mnt/d/oop/lab06/ui.cpp
CMakeFiles/lab06.dir/ui.cpp.o: CMakeFiles/lab06.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/oop/lab06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/lab06.dir/ui.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab06.dir/ui.cpp.o -MF CMakeFiles/lab06.dir/ui.cpp.o.d -o CMakeFiles/lab06.dir/ui.cpp.o -c /mnt/d/oop/lab06/ui.cpp

CMakeFiles/lab06.dir/ui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lab06.dir/ui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/oop/lab06/ui.cpp > CMakeFiles/lab06.dir/ui.cpp.i

CMakeFiles/lab06.dir/ui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lab06.dir/ui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/oop/lab06/ui.cpp -o CMakeFiles/lab06.dir/ui.cpp.s

CMakeFiles/lab06.dir/service.cpp.o: CMakeFiles/lab06.dir/flags.make
CMakeFiles/lab06.dir/service.cpp.o: /mnt/d/oop/lab06/service.cpp
CMakeFiles/lab06.dir/service.cpp.o: CMakeFiles/lab06.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/oop/lab06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/lab06.dir/service.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab06.dir/service.cpp.o -MF CMakeFiles/lab06.dir/service.cpp.o.d -o CMakeFiles/lab06.dir/service.cpp.o -c /mnt/d/oop/lab06/service.cpp

CMakeFiles/lab06.dir/service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lab06.dir/service.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/oop/lab06/service.cpp > CMakeFiles/lab06.dir/service.cpp.i

CMakeFiles/lab06.dir/service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lab06.dir/service.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/oop/lab06/service.cpp -o CMakeFiles/lab06.dir/service.cpp.s

CMakeFiles/lab06.dir/validators.cpp.o: CMakeFiles/lab06.dir/flags.make
CMakeFiles/lab06.dir/validators.cpp.o: /mnt/d/oop/lab06/validators.cpp
CMakeFiles/lab06.dir/validators.cpp.o: CMakeFiles/lab06.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/oop/lab06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/lab06.dir/validators.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab06.dir/validators.cpp.o -MF CMakeFiles/lab06.dir/validators.cpp.o.d -o CMakeFiles/lab06.dir/validators.cpp.o -c /mnt/d/oop/lab06/validators.cpp

CMakeFiles/lab06.dir/validators.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lab06.dir/validators.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/oop/lab06/validators.cpp > CMakeFiles/lab06.dir/validators.cpp.i

CMakeFiles/lab06.dir/validators.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lab06.dir/validators.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/oop/lab06/validators.cpp -o CMakeFiles/lab06.dir/validators.cpp.s

# Object files for target lab06
lab06_OBJECTS = \
"CMakeFiles/lab06.dir/main.cpp.o" \
"CMakeFiles/lab06.dir/domain.cpp.o" \
"CMakeFiles/lab06.dir/repository.cpp.o" \
"CMakeFiles/lab06.dir/ui.cpp.o" \
"CMakeFiles/lab06.dir/service.cpp.o" \
"CMakeFiles/lab06.dir/validators.cpp.o"

# External object files for target lab06
lab06_EXTERNAL_OBJECTS =

lab06: CMakeFiles/lab06.dir/main.cpp.o
lab06: CMakeFiles/lab06.dir/domain.cpp.o
lab06: CMakeFiles/lab06.dir/repository.cpp.o
lab06: CMakeFiles/lab06.dir/ui.cpp.o
lab06: CMakeFiles/lab06.dir/service.cpp.o
lab06: CMakeFiles/lab06.dir/validators.cpp.o
lab06: CMakeFiles/lab06.dir/build.make
lab06: CMakeFiles/lab06.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/d/oop/lab06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable lab06"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab06.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab06.dir/build: lab06
.PHONY : CMakeFiles/lab06.dir/build

CMakeFiles/lab06.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab06.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab06.dir/clean

CMakeFiles/lab06.dir/depend:
	cd /mnt/d/oop/lab06/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/oop/lab06 /mnt/d/oop/lab06 /mnt/d/oop/lab06/cmake-build-debug /mnt/d/oop/lab06/cmake-build-debug /mnt/d/oop/lab06/cmake-build-debug/CMakeFiles/lab06.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/lab06.dir/depend
