#include <gtest/gtest.h>
#include "../../Headers/ArduinoSerial.h"

#include <stdlib.h>

ArduinoSerial s = ArduinoSerial( ttyACM0, (speed_t)B9600 );

bool selfUploadArduinoCode = true;

//An arduino file that only writes Pong every 1 second. 
void writeArduinoFile_w() {
    uploadChanges();
}

//An arduino file that writes what it reads
void writeArduinoFile_rw() {
    uploadChanges();
}

//---------------------------// NOTE //---------------------------//
//  ***DO NOT USE THIS FUNCTION OUTSIDE OF THE TEST DIRECTORY***  //   
//                                                                //
// It is not a stable function to depend on, and our code should  //
// not be dependent on this method. There is no garuntee this     //
// method will even work since the thread terminates as soon as   //
// 'make' is called, and is dependent on the file directory       //
// structure.                                                     //
//----------------------------------------------------------------//
void uploadChanges() {
    //kind of a dangerous way to perform this task
    //no way to really check to see if it worked or not
    if(fork() == 0) {
        if(execl("/usr/bin/make", 
                "make", 
                "--directory=../../Testing/ArduinoSerialTests/ArduinoCode/",  
                "upload", NULL) == -1) 
        {
            printf("ERROR: did not use execl right\n");
            exit(-1);
        }
    }

    //wait for make to finish
    printf("\n\nWriting to Arduino...\n\n");
    usleep(5000000); //sleep for 5 seconds
    printf("\nFinished writing to arduino!\n\n");
}
//----------------------------------------------------------------//

void waitForUser(string reason) {
    printf("%s\n\nPress any key to continue...", reason.c_str());
    char c = getchar();
    printf("\n");
}

TEST(ArduinoSerialTest, ConnectToArduino) {
    if(selfUploadArduinoCode) {
        //dangerous way to perform changes
        writeArduinoFile_w();
    }
    else { //have the user perform the changes 
        printf("Hello! Welcome to the Arduino Serial Tests.\n");
        printf("There are two ways to run this code: \n\t1. Through User Interactions(current)\n");
        printf("\t2. Have the test suite upload the correct file contents (DANGEROUS)\n\n");
        waitForUser("Please change the function in loop() to test_w() in ArduinoRead/ArduinoRead.ino, and upload the changes");    
    }
    try {
        s.initializePort();
    } catch( const exception &e) {
        FAIL() << e.what();
    }
}

