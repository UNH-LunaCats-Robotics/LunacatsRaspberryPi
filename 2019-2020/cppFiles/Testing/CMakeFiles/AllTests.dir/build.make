# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles

# Include any dependencies generated for this target.
include Testing/CMakeFiles/AllTests.dir/depend.make

# Include the progress variables for this target.
include Testing/CMakeFiles/AllTests.dir/progress.make

# Include the compile flags for this target's objects.
include Testing/CMakeFiles/AllTests.dir/flags.make

Testing/CMakeFiles/AllTests.dir/ArduinoSerialTest.cpp.o: Testing/CMakeFiles/AllTests.dir/flags.make
Testing/CMakeFiles/AllTests.dir/ArduinoSerialTest.cpp.o: Testing/ArduinoSerialTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Testing/CMakeFiles/AllTests.dir/ArduinoSerialTest.cpp.o"
	cd /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles/Testing && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AllTests.dir/ArduinoSerialTest.cpp.o -c /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles/Testing/ArduinoSerialTest.cpp

Testing/CMakeFiles/AllTests.dir/ArduinoSerialTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AllTests.dir/ArduinoSerialTest.cpp.i"
	cd /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles/Testing && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles/Testing/ArduinoSerialTest.cpp > CMakeFiles/AllTests.dir/ArduinoSerialTest.cpp.i

Testing/CMakeFiles/AllTests.dir/ArduinoSerialTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AllTests.dir/ArduinoSerialTest.cpp.s"
	cd /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles/Testing && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles/Testing/ArduinoSerialTest.cpp -o CMakeFiles/AllTests.dir/ArduinoSerialTest.cpp.s

# Object files for target AllTests
AllTests_OBJECTS = \
"CMakeFiles/AllTests.dir/ArduinoSerialTest.cpp.o"

# External object files for target AllTests
AllTests_EXTERNAL_OBJECTS =

Testing/AllTests: Testing/CMakeFiles/AllTests.dir/ArduinoSerialTest.cpp.o
Testing/AllTests: Testing/CMakeFiles/AllTests.dir/build.make
Testing/AllTests: libRobotSourceCode.a
Testing/AllTests: _deps/googletest-build/googlemock/gtest/libgtest.a
Testing/AllTests: _deps/googletest-build/googlemock/libgmock.a
Testing/AllTests: _deps/googletest-build/googlemock/gtest/libgtest_main.a
Testing/AllTests: _deps/googletest-build/googlemock/gtest/libgtest.a
Testing/AllTests: Testing/CMakeFiles/AllTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AllTests"
	cd /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles/Testing && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AllTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Testing/CMakeFiles/AllTests.dir/build: Testing/AllTests

.PHONY : Testing/CMakeFiles/AllTests.dir/build

Testing/CMakeFiles/AllTests.dir/clean:
	cd /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles/Testing && $(CMAKE_COMMAND) -P CMakeFiles/AllTests.dir/cmake_clean.cmake
.PHONY : Testing/CMakeFiles/AllTests.dir/clean

Testing/CMakeFiles/AllTests.dir/depend:
	cd /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles/Testing /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles/Testing /Users/cathysandstrom/Desktop/Lunacats/LunacatsRaspberryPi/2019-2020/cppFiles/Testing/CMakeFiles/AllTests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Testing/CMakeFiles/AllTests.dir/depend
