# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\systemc-2.3.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\systemc-2.3.3\build

# Include any dependencies generated for this target.
include examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/depend.make

# Include the progress variables for this target.
include examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/progress.make

# Include the compile flags for this target's objects.
include examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/flags.make

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_main.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/flags.make
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_main.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/includes_CXX.rsp
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_main.cpp.obj: ../examples/sysc/simple_bus/simple_bus_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\systemc-2.3.3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_main.cpp.obj"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\simple_bus.dir\simple_bus_main.cpp.obj -c C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_main.cpp

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simple_bus.dir/simple_bus_main.cpp.i"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_main.cpp > CMakeFiles\simple_bus.dir\simple_bus_main.cpp.i

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simple_bus.dir/simple_bus_main.cpp.s"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_main.cpp -o CMakeFiles\simple_bus.dir\simple_bus_main.cpp.s

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_blocking.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/flags.make
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_blocking.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/includes_CXX.rsp
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_blocking.cpp.obj: ../examples/sysc/simple_bus/simple_bus_master_blocking.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\systemc-2.3.3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_blocking.cpp.obj"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\simple_bus.dir\simple_bus_master_blocking.cpp.obj -c C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_master_blocking.cpp

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_blocking.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simple_bus.dir/simple_bus_master_blocking.cpp.i"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_master_blocking.cpp > CMakeFiles\simple_bus.dir\simple_bus_master_blocking.cpp.i

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_blocking.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simple_bus.dir/simple_bus_master_blocking.cpp.s"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_master_blocking.cpp -o CMakeFiles\simple_bus.dir\simple_bus_master_blocking.cpp.s

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_non_blocking.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/flags.make
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_non_blocking.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/includes_CXX.rsp
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_non_blocking.cpp.obj: ../examples/sysc/simple_bus/simple_bus_master_non_blocking.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\systemc-2.3.3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_non_blocking.cpp.obj"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\simple_bus.dir\simple_bus_master_non_blocking.cpp.obj -c C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_master_non_blocking.cpp

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_non_blocking.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simple_bus.dir/simple_bus_master_non_blocking.cpp.i"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_master_non_blocking.cpp > CMakeFiles\simple_bus.dir\simple_bus_master_non_blocking.cpp.i

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_non_blocking.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simple_bus.dir/simple_bus_master_non_blocking.cpp.s"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_master_non_blocking.cpp -o CMakeFiles\simple_bus.dir\simple_bus_master_non_blocking.cpp.s

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_direct.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/flags.make
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_direct.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/includes_CXX.rsp
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_direct.cpp.obj: ../examples/sysc/simple_bus/simple_bus_master_direct.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\systemc-2.3.3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_direct.cpp.obj"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\simple_bus.dir\simple_bus_master_direct.cpp.obj -c C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_master_direct.cpp

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_direct.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simple_bus.dir/simple_bus_master_direct.cpp.i"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_master_direct.cpp > CMakeFiles\simple_bus.dir\simple_bus_master_direct.cpp.i

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_direct.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simple_bus.dir/simple_bus_master_direct.cpp.s"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_master_direct.cpp -o CMakeFiles\simple_bus.dir\simple_bus_master_direct.cpp.s

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/flags.make
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/includes_CXX.rsp
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus.cpp.obj: ../examples/sysc/simple_bus/simple_bus.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\systemc-2.3.3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus.cpp.obj"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\simple_bus.dir\simple_bus.cpp.obj -c C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus.cpp

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simple_bus.dir/simple_bus.cpp.i"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus.cpp > CMakeFiles\simple_bus.dir\simple_bus.cpp.i

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simple_bus.dir/simple_bus.cpp.s"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus.cpp -o CMakeFiles\simple_bus.dir\simple_bus.cpp.s

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_arbiter.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/flags.make
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_arbiter.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/includes_CXX.rsp
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_arbiter.cpp.obj: ../examples/sysc/simple_bus/simple_bus_arbiter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\systemc-2.3.3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_arbiter.cpp.obj"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\simple_bus.dir\simple_bus_arbiter.cpp.obj -c C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_arbiter.cpp

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_arbiter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simple_bus.dir/simple_bus_arbiter.cpp.i"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_arbiter.cpp > CMakeFiles\simple_bus.dir\simple_bus_arbiter.cpp.i

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_arbiter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simple_bus.dir/simple_bus_arbiter.cpp.s"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_arbiter.cpp -o CMakeFiles\simple_bus.dir\simple_bus_arbiter.cpp.s

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_types.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/flags.make
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_types.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/includes_CXX.rsp
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_types.cpp.obj: ../examples/sysc/simple_bus/simple_bus_types.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\systemc-2.3.3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_types.cpp.obj"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\simple_bus.dir\simple_bus_types.cpp.obj -c C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_types.cpp

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_types.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simple_bus.dir/simple_bus_types.cpp.i"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_types.cpp > CMakeFiles\simple_bus.dir\simple_bus_types.cpp.i

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_types.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simple_bus.dir/simple_bus_types.cpp.s"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_types.cpp -o CMakeFiles\simple_bus.dir\simple_bus_types.cpp.s

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_tools.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/flags.make
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_tools.cpp.obj: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/includes_CXX.rsp
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_tools.cpp.obj: ../examples/sysc/simple_bus/simple_bus_tools.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\systemc-2.3.3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_tools.cpp.obj"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\simple_bus.dir\simple_bus_tools.cpp.obj -c C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_tools.cpp

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_tools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simple_bus.dir/simple_bus_tools.cpp.i"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_tools.cpp > CMakeFiles\simple_bus.dir\simple_bus_tools.cpp.i

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_tools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simple_bus.dir/simple_bus_tools.cpp.s"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\systemc-2.3.3\examples\sysc\simple_bus\simple_bus_tools.cpp -o CMakeFiles\simple_bus.dir\simple_bus_tools.cpp.s

# Object files for target simple_bus
simple_bus_OBJECTS = \
"CMakeFiles/simple_bus.dir/simple_bus_main.cpp.obj" \
"CMakeFiles/simple_bus.dir/simple_bus_master_blocking.cpp.obj" \
"CMakeFiles/simple_bus.dir/simple_bus_master_non_blocking.cpp.obj" \
"CMakeFiles/simple_bus.dir/simple_bus_master_direct.cpp.obj" \
"CMakeFiles/simple_bus.dir/simple_bus.cpp.obj" \
"CMakeFiles/simple_bus.dir/simple_bus_arbiter.cpp.obj" \
"CMakeFiles/simple_bus.dir/simple_bus_types.cpp.obj" \
"CMakeFiles/simple_bus.dir/simple_bus_tools.cpp.obj"

# External object files for target simple_bus
simple_bus_EXTERNAL_OBJECTS =

examples/sysc/simple_bus/simple_bus.exe: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_main.cpp.obj
examples/sysc/simple_bus/simple_bus.exe: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_blocking.cpp.obj
examples/sysc/simple_bus/simple_bus.exe: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_non_blocking.cpp.obj
examples/sysc/simple_bus/simple_bus.exe: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_master_direct.cpp.obj
examples/sysc/simple_bus/simple_bus.exe: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus.cpp.obj
examples/sysc/simple_bus/simple_bus.exe: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_arbiter.cpp.obj
examples/sysc/simple_bus/simple_bus.exe: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_types.cpp.obj
examples/sysc/simple_bus/simple_bus.exe: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/simple_bus_tools.cpp.obj
examples/sysc/simple_bus/simple_bus.exe: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/build.make
examples/sysc/simple_bus/simple_bus.exe: src/libsystemc.a
examples/sysc/simple_bus/simple_bus.exe: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/linklibs.rsp
examples/sysc/simple_bus/simple_bus.exe: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/objects1.rsp
examples/sysc/simple_bus/simple_bus.exe: examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\systemc-2.3.3\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable simple_bus.exe"
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\simple_bus.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/build: examples/sysc/simple_bus/simple_bus.exe

.PHONY : examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/build

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/clean:
	cd /d C:\systemc-2.3.3\build\examples\sysc\simple_bus && $(CMAKE_COMMAND) -P CMakeFiles\simple_bus.dir\cmake_clean.cmake
.PHONY : examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/clean

examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\systemc-2.3.3 C:\systemc-2.3.3\examples\sysc\simple_bus C:\systemc-2.3.3\build C:\systemc-2.3.3\build\examples\sysc\simple_bus C:\systemc-2.3.3\build\examples\sysc\simple_bus\CMakeFiles\simple_bus.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/sysc/simple_bus/CMakeFiles/simple_bus.dir/depend
