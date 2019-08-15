#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

//https://stackoverflow.com/questions/18108932/reading-and-writing-to-serial-port-in-c-on-linux

int main() {
	//open the port
	int USB = open( "/dev/ttyACM0", O_RDWR| O_NOCTTY );
	
	//set the parameters
	struct termios tty;
	struct termios tty_old;
	memset (&tty, 0, sizeof tty);

	// Error Handling 
	if ( tcgetattr ( USB, &tty ) != 0 ) {
	   //std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
		printf("Error opening port");
	}

	// Save old tty parameters 
	tty_old = tty;

	// Set Baud Rate 
	cfsetospeed (&tty, (speed_t)B9600);
	cfsetispeed (&tty, (speed_t)B9600);

	// Setting other Port Stuff 
	tty.c_cflag     &=  ~PARENB;            // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cc[VMIN]   =  0;                  // read doesn't block
	tty.c_cc[VTIME]  =  0.5;                  // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	// Make raw 
	cfmakeraw(&tty);

	// Flush Port, then applies attributes 
	tcflush( USB, TCIFLUSH );
	if ( tcsetattr ( USB, TCSANOW, &tty ) != 0) {
	   //std::cout << "Error " << errno << " from tcsetattr" << std::endl;
		printf("Error from tcsetattr");
	}
	
	//read 
	int n = 0, spot = 0;
	char buf = '\0';

	/* Whole response*/
	char response[1024];
	memset(response, '\0', sizeof response);
	
	unsigned char cmd[] = "Lets test this messenger!";
	int n_written = 0;
			
	while(1) {
		//write
		
		n_written = 0, spot = 0;
		printf("Sending the message '%s'\n", (char *)cmd);
	
		do {
			n_written = write( USB, &cmd[spot], 1 );
			spot += n_written;
		} while (cmd[spot-1] != '\0' && n_written > 0);
		
		n = 0, spot = 0;
		
		do {
			n = read( USB, &buf, 1 );
			sprintf( &response[spot], "%c", buf );
			spot += n;
		} while( buf != '\n' && n > 0);

		if (n < 0) {
			//std::cout << "Error reading: " << strerror(errno) << std::endl;
			printf("Error Reading.");
			return 0;
		}
		else if (n == 0) {
			//std::cout << "Read nothing!" << std::endl;
			printf("read nothing!");
		}
		else {
			printf("Received %i bytes: '%s'\n\n", spot, (char *)response);
			//std::cout << "Response: " << response << std::endl;
		}
		//usleep(1000000);  // sleep for 5 Second 

	}
	return 0;
}

