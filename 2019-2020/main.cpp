  
#include "Headers/ArduinoSerial.h"

#define BUF_SIZE 1024

int main() {
    try {
	    ArduinoSerial serial(ttyACM0, B9600);

        unsigned char cmd[] = "Lets test this messenger!";
	
        /* Whole response*/
        char response[BUF_SIZE];
        memset(response, '\0', sizeof response);
        
        while(true) {
            serial.writeString(cmd);
            serial.readString(response, BUF_SIZE);
        }
        
    } catch( invalid_argument e ) {
        printf("Error: %s", e.what());
    }

	return 0;
}
