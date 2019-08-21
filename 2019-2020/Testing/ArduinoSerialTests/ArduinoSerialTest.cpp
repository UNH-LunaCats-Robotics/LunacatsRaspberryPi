#include <gtest/gtest.h>
#include "../../Headers/ArduinoSerial.h"

#include <stdlib.h>
#include <fstream>

typedef struct ArduinoSettings ArduinoSettings;

struct ArduinoSettings {
    Port port;
    speed_t baudRate;
    chrono::seconds timeout;
};

ArduinoSettings settings{ ttyACM0, (speed_t)B9600, 2s };
ArduinoSerial serial = ArduinoSerial( settings.port, settings.baudRate );

void resetPort() {
    serial.resetPort();
}

bool selfUploadArduinoCode = true;

//helper functions 
//try to minimize uploads to the arduino if you can.
void writeArduinoFile_w( int speed = 1000 );
void writeArduinoFile_wr( int speed = 0 ); 
void writeArduinoFile( string funcName, int delay );
void uploadChanges();
void waitForUser(string reason);

//-----------------------------------------------------------------//
//                              TESTS                              //
//-----------------------------------------------------------------//
TEST(ArduinoSerialTest_Initialization, ConnectToArduino) {
    try {
        serial.initializePort();
    } catch( const exception &e) {
        printf("ERROR: %s\n", e.what());

        FAIL() << e.what();
    }

    ASSERT_TRUE(serial.getInitialized());
}

TEST(ArduinoSerialTest_Initialization, CantChangeSettingsWhenInitialized) {
    ASSERT_FALSE(serial.setBaudRate((speed_t)B1152000));
    assert( serial.getBaudRate() != (speed_t)B1152000);

    ASSERT_FALSE(serial.setPort(ttyACM1));
    assert( serial.getPort() != ttyACM1 );
}

TEST(ArduinoSerialTest_Initialization, DisconnectFromArduino) {
    serial.resetPort();

    ASSERT_FALSE(serial.getInitialized());
}

TEST(ArduinoSerialTest_Initialization, CanChangeSettingsWhenNotInitialized) {
    ASSERT_TRUE(serial.setBaudRate( (speed_t)B1152000));
    assert( serial.getBaudRate() == (speed_t)B1152000);

    ASSERT_TRUE(serial.setPort(ttyACM1));
    assert( serial.getPort() == ttyACM1 );

    serial.setTimeout(10s);
    assert( serial.getTimeout() == 10s );
}

TEST(ArduinoSerialTest_Initialization, FailToConnectWithWrongPort) {
    try {
        serial.initializePort();
    } catch( const exception &e) {
        printf("Successfully failed with reason: %s", e.what());
        ASSERT_FALSE(serial.getInitialized());
        return;
    }

    FAIL() << "Initialized with wrong settings";
}

TEST(ArduinoSerialTest_Initialization, ConnectWithCorrectSettings) {
    serial.setBaudRate(settings.baudRate);
    serial.setPort(settings.port);
    serial.setTimeout(settings.timeout);

    try {
        serial.initializePort();
    } catch( const exception &e) {
        FAIL() << e.what();
    }

    ASSERT_TRUE(serial.getInitialized());
}

//--------------------------- READING -----------------------------//

TEST(ArduinoSerialTest_Reading, ReadSingleByteFromArduino) {
    //writeArduinoFile_w();

    usleep(1000000);

    ASSERT_TRUE(serial.getInitialized());

    char c = 0;
    c = serial.readChar();
    assert(c != 0);
}

//-----------------------------------------------------------------//

//-----------------------------------------------------------------//
/*
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
*/

void waitForUser(string reason) {
    printf("%s\n\nPress any key to continue...", reason.c_str());
    char c = getchar();
    printf("\n");
}

//An arduino file that only writes Pong every 1 second. 
void writeArduinoFile_w( int speed ) {
    writeArduinoFile( "test_w", speed );
    uploadChanges();
}

//An arduino file that writes what it reads
void writeArduinoFile_rw( int speed ) {
    writeArduinoFile( "test_wr", speed );
    uploadChanges();
}

void writeArduinoFile( string funcName, int delay ) {
    ofstream ardFile;

    ardFile.open(
        "../../Testing/ArduinoSerialTests/ArduinoCode/ArduinoCode.ino", 
        fstream::trunc
    );

    if(!ardFile.is_open()) {
        printf("ERROR: Could not write to arduino file");
        exit(-1);
    }

    ardFile <<  "void setup() {\n"                                  << 
                "    Serial.begin( "<< BaudRate::getBaudRate_int(settings.baudRate) <<" );\n"  <<
                "    Serial.setTimeout(20);\n"                      <<
                "}\n\n"                                             <<

                "void test_w() {\n"                                 <<
                "    Serial.println(\"Pong\");\n"                   <<
                "    delay( "<< delay << " );\n"                    <<
                "}\n\n"                                             <<

                "void test_wr() {\n"                                <<
                "    if (Serial.available() > 0) {\n"               <<
                "        Serial.println(Serial.readString());\n"    <<
                "        delay( "<< delay << " );\n"                <<
                "    }\n"                                           <<
                "}\n\n"                                             <<

                "void loop() {\n"                                   <<
                "    " << funcName << "();\n"                       <<
                "}";

    ardFile.close();
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
    
    serial.resetPort();
    
    //kind of a dangerous way to perform this task
    //no way to really check to see if it worked or not
    if(fork() == 0) {
        if(execl("/usr/bin/make", 
                "make", 
                "--directory=../../Testing/ArduinoSerialTests/ArduinoCode/",  
                "upload", NULL) == -1) 
        {
            printf("ERROR: did not use execl right\n");
        }

        exit(-1);
    }
    printf("\n\nWriting to Arduino...\n\n");
    int status;
    wait(&status);
    printf("\nFinished writing to arduino with exit status: %d\n\n", status);

    try {
        serial.initializePort();
    } catch( const exception &e ) {
        printf("Failed to reinitialize the port: %s", e.what());
    }

}
//----------------------------------------------------------------//
