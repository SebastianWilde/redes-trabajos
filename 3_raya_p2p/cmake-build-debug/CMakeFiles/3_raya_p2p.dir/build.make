# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /opt/clion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zafiron/8semestre/redes/sockets/3_raya_p2p

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zafiron/8semestre/redes/sockets/3_raya_p2p/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/3_raya_p2p.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/3_raya_p2p.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/3_raya_p2p.dir/flags.make

CMakeFiles/3_raya_p2p.dir/client.cpp.o: CMakeFiles/3_raya_p2p.dir/flags.make
CMakeFiles/3_raya_p2p.dir/client.cpp.o: ../client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zafiron/8semestre/redes/sockets/3_raya_p2p/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/3_raya_p2p.dir/client.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/3_raya_p2p.dir/client.cpp.o -c /home/zafiron/8semestre/redes/sockets/3_raya_p2p/client.cpp

CMakeFiles/3_raya_p2p.dir/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/3_raya_p2p.dir/client.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zafiron/8semestre/redes/sockets/3_raya_p2p/client.cpp > CMakeFiles/3_raya_p2p.dir/client.cpp.i

CMakeFiles/3_raya_p2p.dir/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/3_raya_p2p.dir/client.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zafiron/8semestre/redes/sockets/3_raya_p2p/client.cpp -o CMakeFiles/3_raya_p2p.dir/client.cpp.s

CMakeFiles/3_raya_p2p.dir/client.cpp.o.requires:

.PHONY : CMakeFiles/3_raya_p2p.dir/client.cpp.o.requires

CMakeFiles/3_raya_p2p.dir/client.cpp.o.provides: CMakeFiles/3_raya_p2p.dir/client.cpp.o.requires
	$(MAKE) -f CMakeFiles/3_raya_p2p.dir/build.make CMakeFiles/3_raya_p2p.dir/client.cpp.o.provides.build
.PHONY : CMakeFiles/3_raya_p2p.dir/client.cpp.o.provides

CMakeFiles/3_raya_p2p.dir/client.cpp.o.provides.build: CMakeFiles/3_raya_p2p.dir/client.cpp.o


CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o: CMakeFiles/3_raya_p2p.dir/flags.make
CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o: ../DieWithError.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zafiron/8semestre/redes/sockets/3_raya_p2p/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o -c /home/zafiron/8semestre/redes/sockets/3_raya_p2p/DieWithError.cpp

CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zafiron/8semestre/redes/sockets/3_raya_p2p/DieWithError.cpp > CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.i

CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zafiron/8semestre/redes/sockets/3_raya_p2p/DieWithError.cpp -o CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.s

CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o.requires:

.PHONY : CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o.requires

CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o.provides: CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o.requires
	$(MAKE) -f CMakeFiles/3_raya_p2p.dir/build.make CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o.provides.build
.PHONY : CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o.provides

CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o.provides.build: CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o


CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o: CMakeFiles/3_raya_p2p.dir/flags.make
CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o: ../TCPEchoServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zafiron/8semestre/redes/sockets/3_raya_p2p/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o -c /home/zafiron/8semestre/redes/sockets/3_raya_p2p/TCPEchoServer.cpp

CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zafiron/8semestre/redes/sockets/3_raya_p2p/TCPEchoServer.cpp > CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.i

CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zafiron/8semestre/redes/sockets/3_raya_p2p/TCPEchoServer.cpp -o CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.s

CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o.requires:

.PHONY : CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o.requires

CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o.provides: CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o.requires
	$(MAKE) -f CMakeFiles/3_raya_p2p.dir/build.make CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o.provides.build
.PHONY : CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o.provides

CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o.provides.build: CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o


# Object files for target 3_raya_p2p
3_raya_p2p_OBJECTS = \
"CMakeFiles/3_raya_p2p.dir/client.cpp.o" \
"CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o" \
"CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o"

# External object files for target 3_raya_p2p
3_raya_p2p_EXTERNAL_OBJECTS =

3_raya_p2p: CMakeFiles/3_raya_p2p.dir/client.cpp.o
3_raya_p2p: CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o
3_raya_p2p: CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o
3_raya_p2p: CMakeFiles/3_raya_p2p.dir/build.make
3_raya_p2p: CMakeFiles/3_raya_p2p.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zafiron/8semestre/redes/sockets/3_raya_p2p/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable 3_raya_p2p"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/3_raya_p2p.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/3_raya_p2p.dir/build: 3_raya_p2p

.PHONY : CMakeFiles/3_raya_p2p.dir/build

CMakeFiles/3_raya_p2p.dir/requires: CMakeFiles/3_raya_p2p.dir/client.cpp.o.requires
CMakeFiles/3_raya_p2p.dir/requires: CMakeFiles/3_raya_p2p.dir/DieWithError.cpp.o.requires
CMakeFiles/3_raya_p2p.dir/requires: CMakeFiles/3_raya_p2p.dir/TCPEchoServer.cpp.o.requires

.PHONY : CMakeFiles/3_raya_p2p.dir/requires

CMakeFiles/3_raya_p2p.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/3_raya_p2p.dir/cmake_clean.cmake
.PHONY : CMakeFiles/3_raya_p2p.dir/clean

CMakeFiles/3_raya_p2p.dir/depend:
	cd /home/zafiron/8semestre/redes/sockets/3_raya_p2p/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zafiron/8semestre/redes/sockets/3_raya_p2p /home/zafiron/8semestre/redes/sockets/3_raya_p2p /home/zafiron/8semestre/redes/sockets/3_raya_p2p/cmake-build-debug /home/zafiron/8semestre/redes/sockets/3_raya_p2p/cmake-build-debug /home/zafiron/8semestre/redes/sockets/3_raya_p2p/cmake-build-debug/CMakeFiles/3_raya_p2p.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/3_raya_p2p.dir/depend

