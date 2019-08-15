#-----------------------# NOTE #-----------------------#
# make sure you build the project in a folder called 'build'.
# if you change the name of the build folder, add it to .gitignore

# if you plan on making changes to this file as well that are  
# only for local use, add this file to .gitignore as well

# if you make platform-specific changes, add them in the 
# appropriate if statement as to not mess with other platforms
#------------------------------------------------------#

#define the min version of cmake
cmake_minimum_required (VERSION "3.10")

#title the project
project("LunaCats")

#The directories are included privately since they are in
#the source directory. 

#list of sources (src) - ONLY CPP FILES TO COMPILE GO HERE
set( SOURCES 
    Sources/ArduinoSerial.cpp
    main.cpp
)

set( HEADERS
    Headers/ArduinoSerial.h
)

add_compile_options("-Wno-psabi")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#create the executable for the project
add_executable(main ${SOURCES} ${HEADERS})

target_link_libraries(main Threads::Threads)

#check if linux (includes raspberry pi)
if(UNIX AND NOT APPLE)
    #Check Build_Instructions/Linux.txt for how to run this project
    #Linux specific commands can go here
endif()

#check if windows
if(WIN32)
    # Check Build_Instructions/Windows.txt for how to run this project
	# Windows specific commands can go here
endif()

#check if mac
if(APPLE)
    # Check Build_Instructions/Mac.txt for how to run this project
	# Windows specific commands can go here
endif()
