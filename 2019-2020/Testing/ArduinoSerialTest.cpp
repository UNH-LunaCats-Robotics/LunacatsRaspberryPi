#include "ArduinoSerial.h"

#define BUF_SIZE 1024


int main() {
	ArduinoSerial serial(ttyACM0);
	
	unsigned char cmd[] = "Lets test this messenger!";
	
	/* Whole response*/
	char response[BUF_SIZE];
	memset(response, '\0', sizeof response);
	
	while(true) {
		serial.writeString(cmd);
		serial.readString(response, BUF_SIZE);
		
		//usleep(2000000);  // sleep for 2 Seconds
	}
	
	return 0;
}
