#-----------------------# NOTE #-----------------------#
# if you wish to create an executable for only testing
#   one class, you can use the `add_executable` command
#   to create a new executable. 
#
# Make sure to clean it up after you are done, though, and 
#   add the tests to the main testing executable. 
#
# Testing Executables can be found after calling cmake in 
#   the folder `Testing`.
#------------------------------------------------------#
cmake_minimum_required (VERSION "3.10")

#title the project
project("AllTests" CXX)

#create testing executable
add_executable(${PROJECT_NAME} 
    ArduinoSerialTest.cpp
#   [className]Test.cpp
)

#target libraries to test and for testing
target_link_libraries(${PROJECT_NAME} PUBLIC
    gtest_main 
    RobotSourceCode
    Threads::Threads
)

#add the executable as a test
add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

#[[  create a single class test executable example 

add_executable(${TEST_NAME}  #replace ${TEST_NAME} with executable name
#   TestFile1.cpp
#   TestFile2.cpp
#   ...
)

target_link_libraries(${TEST_NAME} PUBLIC 
    gtest_main 
    RobotSourceCode
    Threads::Threads
)

add_test(
    NAME ${TEST_NAME}
    COMMAND ${TEST_NAME}
)

]]
