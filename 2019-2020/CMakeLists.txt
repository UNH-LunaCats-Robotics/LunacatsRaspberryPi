#-----------------------# NOTE #-----------------------#
# Make sure you build the project in a folder called 'build'.
#   If you change the name of the build folder, add it to .gitignore
#
# This file will be on the .gitignore after you clone it. 
#   If you wish to make global changes to this file, remove it from
#   .gitignore. 
#
# If you make platform-specific changes, add them in the 
#   appropriate if statement as to not mess with other platforms
#------------------------------------------------------#

#define the min version of cmake
cmake_minimum_required (VERSION "3.10")

#title the project
project("LunaCats" CXX)

#enable testing
option(PACKAGE_TESTS "Build the tests" ON)

include(FetchContent)

#add compiler flags
add_compile_options("-Wno-psabi")

#require cmake to be aware of pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#allows us to run tests
enable_testing()

#create the libraries used by the main file.
add_library( RobotSourceCode STATIC 
    Sources/ArduinoSerial.cpp	Headers/ArduinoSerial.h
#   Sources/[className].cpp     Headers/[className].h
#                               Headers/[declarations].h
)

#create the executable for the project
add_executable(main main.cpp)

#add linked libraries to the compiled result 
target_link_libraries(main PUBLIC 
    RobotSourceCode
    Threads::Threads
)

#check if linux (includes raspberry pi)
if(UNIX AND NOT APPLE)
    #Check Build_Instructions/Linux/Linux.txt for how to run this project
    	#Linux specific commands can go here
endif()

#check if windows
if(WIN32)
    # Check Build_Instructions/Windows/Windows.txt for how to run this project
	# Windows specific commands can go here
endif()

#check if mac
if(APPLE)
    # Check Build_Instructions/Mac/Mac.txt for how to run this project
	# Mac specific commands can go here
endif()

#includes the googletest directory and Testing Directory
if(PACKAGE_TESTS)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.8.0
    )
    
    FetchContent_GetProperties(googletest)
    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    endif()
  
    add_subdirectory(Testing)

endif()

#keeps cache cleaner
mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

#keeping IDEs that support folders clean
set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

