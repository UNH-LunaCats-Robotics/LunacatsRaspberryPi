#include "../Headers/ArduinoSerial.h"

//-------------------------------// INITIALIZATION //-------------------------------//
/*
string ArduinoSerial::ports[RS232_PORTNR]  = 
	{"/dev/ttyS0",	"/dev/ttyS1",	"/dev/ttyS2",	"/dev/ttyS3",	
	"/dev/ttyS4",	"/dev/ttyS5",	"/dev/ttyS6",	"/dev/ttyS7",	
	"/dev/ttyS8",	"/dev/ttyS9",	"/dev/ttyS10",	"/dev/ttyS11",
	"/dev/ttyS12",	"/dev/ttyS13",	"/dev/ttyS14",	"/dev/ttyS15",	
	"/dev/ttyUSB0", "/dev/ttyUSB1",	"/dev/ttyUSB2",	"/dev/ttyUSB3",	
	"/dev/ttyUSB4",	"/dev/ttyUSB5",
	"/dev/ttyAMA0",	"/dev/ttyAMA1",	
	"/dev/ttyACM0",	"/dev/ttyACM1",
	"/dev/rfcomm0",	"/dev/rfcomm1",	
	"/dev/ircomm0",	"/dev/ircomm1",
	"/dev/cuau0",	"/dev/cuau1",	"/dev/cuau2",	"/dev/cuau3",
	"/dev/cuaU0",	"/dev/cuaU1",	"/dev/cuaU2",	"/dev/cuaU3"};
*/

//list of all possible baud rates given from <termios.h>
unordered_map<double, speed_t> BaudRate::baudRateList = {
	{0, 	B0},     //Hang up
	{50, 	B50},    //50 baud
	{110, 	B110},   //110 baud
	{134.5, B134},   //134.5 baud
	{150, 	B150},   //150 baud
	{200, 	B200},   //200 baud
	{300, 	B300},   //300 baud
	{600, 	B600},   //600 baud
	{1200, 	B1200},  //1200 baud
	{1800, 	B1800},  //1800 baud
	{2400, 	B2400},  //2400 baud
	{4800, 	B4800},  //4800 baud
	{9600, 	B9600},  //9600 baud
	{19200, B19200}, //19200 baud
	{38400, B38400}  //38400 baud
};

/** ArduinoSerial Constructor (Port Only)
 * @Port p - the port where the arduino is connected
 * @speed_t baud - the baud rate for communication.
 * 
 * - Establish the port location and baud rate 
 * 	 	with a default timeout of two seconds
 * - Calibrate the settings of the serial port
 */
ArduinoSerial::ArduinoSerial(Port p, speed_t baud): baudRate(baud) {
	port = ports[p];

	printf("Port: %s\n", port.c_str());
}

/** ArduinoSerial Constructor (Port Only)
 * @Port p - the port where the arduino is connected
 * @speed_t baud - the baud rate for communication.
 * 
 * - Establish the port location, baud rate, and timeout
 * - Calibrate the settings of the serial port
 
ArduinoSerial::ArduinoSerial(Port p, speed_t baud, chrono::seconds tout): timeout(tout), baudRate(baud){
	port = ports[p]; 
}
*/

/**
 * Re-establish the previous port settings on destruction.
 */
ArduinoSerial::~ArduinoSerial(){
	resetPort();
}

/** Initialize the Port
 * @bool force - force reinitialization after already initialized. 
 *  
 * Set the terminal serial port settings to allow us to perform 
 * reads and writes
 */
bool ArduinoSerial::initializePort(bool force) {
	//do not initialize port if already done unless forced
	if(!force && !isNotInitialized()) return false;

	printf("Port: %s\n", port.c_str());

	USB = open( port.c_str(), O_RDWR| O_NOCTTY );
	
	if(USB == -1) {
		throw invalid_argument("Cannot find serial port to open\n");
	}

	termios tty;
	memset (&tty, 0, sizeof tty);

	if(flock(USB, LOCK_EX | LOCK_NB) != 0) {
		close(USB);
		throw invalid_argument("Another process is using the port\n");
	}

	// Error Handling 
	if ( tcgetattr ( USB, &tty ) != 0 ) {
	   //std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
		close(USB);
		flock(USB, LOCK_UN); 
		throw invalid_argument("Error getting port settings\n");
	}

	// Save old tty parameters 
	if(initialized != true) tty_old = tty;

	// Set Baud Rate 
	cfsetospeed (&tty, baudRate);
	cfsetispeed (&tty, baudRate);

	// Make 8n1
	int cpar = 0, bstop = 0;
	tty.c_cflag = CS8 | cpar | bstop | CLOCAL | CREAD;
	tty.c_iflag = IGNPAR;
	tty.c_oflag = 0;
	tty.c_lflag &= ~(ICANON|ECHO);

	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cc[VMIN]   =  0;                  // read doesn't block
	tty.c_cc[VTIME]  =  0.5;                // 0.5 seconds read timeout
	//tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	// Make raw 
	cfmakeraw(&tty);

	if ( tcsetattr ( USB, TCSAFLUSH, &tty ) != 0) {
	   //std::cout << "Error " << errno << " from tcsetattr" << std::endl;
		close(USB);
		flock(USB, LOCK_UN);
		throw invalid_argument("Error setting new port settings");
	}
	/*
	//Set the modem to data terminal ready and ready to send
	if(ioctl(USB, TIOCMGET, &status_old) == -1) {
		tcsetattr(USB, TCSANOW, &tty_old);
		flock(USB, LOCK_UN);
		throw invalid_argument("Error Setting Port Status");
	}
	
	printf("Status is %x\n", status_old & TIOCM_RNG);
	
	
	int status = status_old;
	status |= TIOCM_DTR;    // turn on DTR 
	status |= TIOCM_RTS;    // turn on RTS 
	
	
	if(ioctl(USB, TIOCMSET, &status) == -1) {
		tcsetattr(USB, TCSANOW, &tty_old);
		flock(USB, LOCK_UN);
		throw invalid_argument("Error Setting Port Status");
	}
	*/
	
	tcflush(USB, TCIOFLUSH);
	
	return true;
}

/** Reset the Port
 *  - Set the port back to its original configuration
 */
bool ArduinoSerial::resetPort() {
	// Make raw 
	cfmakeraw(&tty_old);

	// Flush Port, then applies attributes 
	tcflush( USB, TCIOFLUSH );
	if ( tcsetattr ( USB, TCSANOW, &tty_old ) != 0) {
	   //std::cout << "Error " << errno << " from tcsetattr" << std::endl;
#ifdef DEBUG
		printf("Error Setting Old Port Settings\n");
#endif
	}
	
	/*
	// Set the Port Status back to before
	if(ioctl(USB, TIOCMSET, &status_old) == -1) {
		printf("Error Setting Old Port Status");
	}
	*/
	close(USB);
	flock(USB, LOCK_UN);
	
	initialized = false;
	return true;
}

//-------------------------------// READING / WRITING //-------------------------------//

/** Read an array of bytes from the serial port
 * @int USBB		- Serial port to read from. 
 * @char* response 	- character array to read into
 * @int buf_size 	- max size of the responce character array
 * @char terminator - the terminating character to end the array at(\n, \r, etc)
 * @return int		- return length of string
 *  
 *  Keep reading characters from the serial port until 
 *  the terminating character has been reached. 
 */ 
int ArduinoSerial::readBytes( int USBB, char* response, int buf_size, char terminator) {
	//read 
	int n = 0, spot = 0;
	char buf = '\0';
	
	do {
		n = read( USBB, &buf, 1 );
		sprintf( &response[spot], "%c", buf );
		spot += n;
	} while( buf != terminator && n > 0);

	if(n < 0) return -1;

	return spot;
}

/** Performs readBytes in another thread with timeout
 * @char* response 	- character array to read into
 * @int buf_size 	- max size of the responce character array
 * @char terminator - the terminating character to end the array at(\n, \r, etc)
 * @return int		- return length of string
 *  
 *  Start the readBytes function in another thread until terminator is reached
 *  or if timeout is reached of which the thread is killed. 
 */ 
int ArduinoSerial::readBytes_wrapper( char* response, int buf_size, char terminator) {
	mutex m;
	condition_variable cv;

	int n = 0, usbTemp = USB;
	auto func = &ArduinoSerial::readBytes;

	thread t( [&n, &response, &buf_size, &terminator, &usbTemp, func, &cv ] {
		n = func(usbTemp, response, buf_size, terminator);
		cv.notify_one();
	});
	
	t.detach();

	{
		unique_lock<mutex> l(m);
		if(cv.wait_for(l, timeout) == cv_status::timeout) 
			throw runtime_error("Timeout");
	}

	return n;
}

/** Read a String sent from the Arduino
 * @char* response 	- character array to read into
 * @int buf_size 	- max size of the responce character array
 * @char terminator - the terminating character to end the array at(\n, \r, etc)
 * @return int		- return length of string
 *  
 *  Reads a character at a time from the serial port into the responce array
 *  until the terminator character is reached or it has reached the end of the array.
 */
int ArduinoSerial::readString( char* response, int buf_size, char terminator ) {
	if(!isInitialized()) return 0;
	
	int n = 0;

	try {
		n = readBytes_wrapper(response, buf_size, terminator);
	} catch(runtime_error &e) {
#ifdef DEBUG
		printf("Read Request Timed Out\n");
#endif
		return n;
	}
	
	if (n < 0) {
		//std::cout << "Error reading: " << strerror(errno) << std::endl;
		printf("Error Reading.\n");
	}
	else if (n == 0) {
		//std::cout << "Read nothing!" << std::endl;
		printf("Read nothing! \n");
	}
	else {
		printf("Received %i bytes: '%s'\n", n, (char *)response);
		//std::cout << "Response: " << response << std::endl;
	}

	return n;
}

/** Read a Byte
 * @int USBB 		Port to read from
 * @return char 	char read from serial
 * 
 * Start another thread and try to read a byte.
 * Timeout after x declared seconds, and kill the thread.
*/
char ArduinoSerial::readByte( int USBB ) {
	mutex m;
	condition_variable cv;

	char c;
	auto func = &ArduinoSerial::readByte;

	thread t( [ USBB, &c, func, &cv ] {
		read( USBB, &c, 1);
		cv.notify_one();
	});
	
	t.detach();

	{
		unique_lock<mutex> l(m);
		if(cv.wait_for(l, timeout) == cv_status::timeout)
			throw runtime_error("Timeout");
	}

	return c;
}

/** Read a Character
 * @return char 	char read from serial
 * 
 * Read a character from the serial port with
 * a timeout of x given seconds. 
 */
char ArduinoSerial::readChar() {
	if(!isInitialized()) return '\0';

	try {
		return readByte(USB);
	} catch(runtime_error &e) {
#ifdef DEBUG
		printf("Read Request Timed Out\n");
#endif
		return '\0';
	}
}

/** Write a String to the Arduino 
 * @const unsigned char* cmd - command string to be sent to the arduino
 * @return write string success or fail
 * 
 * Write a string to the serial port for the arduino to recieve. 
 */
bool ArduinoSerial::writeString( const unsigned char* cmd  ) {
	if(!isInitialized()) return false;
	
	int n_written = 0, spot = 0;

#ifdef DEBUG
	printf("Sending the message '%s'\n", (char *)cmd);
#endif

	do {
		n_written = write( USB, &cmd[spot], 1 );
		spot += n_written;
	} while (cmd[spot-1] != '\0' && n_written > 0 );

	return true;
}

/** Write a Character
 * Write a character sent to the aduino
 */
void ArduinoSerial::writeChar(char c) {
	if(!isInitialized()) return;
	
	write( USB, &c, 1 );
}

//-------------------------------// PRIVATE FUNCTIONS //-------------------------------//

/**
 * Check if the status of the serial port is initialized. (different error msg)
 */
bool ArduinoSerial::isInitialized() {
#ifdef DEBUG
	if(!initialized) printf("Port Not Initialized\n");
#endif
	return initialized;
}

/**
 * Check if the status of the serial port is not initialized. (different error msg)
 */
bool ArduinoSerial::isNotInitialized() {
#ifdef DEBUG
	if(initialized) printf("Port Already Initialized\n");
#endif
	return !initialized;
}

//-------------------------------// DESCRIPTOR FUNCTIONS //-------------------------------//

/** Get the status of the Arduino Serial Port */
bool ArduinoSerial::getInitialized() {
	return initialized;
}

/** Get the number representing the port */
int ArduinoSerial::getUSB(){
	return USB;
}

/** Get the string path to the port */
string ArduinoSerial::getPort(){
	return port;
}

/** Get the baud rate used to establish a connection */
speed_t ArduinoSerial::getBaudRate(){
	return baudRate;
}

/** Get the integer value of the baud rate used to establish a connection */
int ArduinoSerial::getBaudRate_int(){
	return BaudRate::getBaudRate_int(baudRate);
}

/** Get the double value of the baud rate used to establish a connection */
double ArduinoSerial::getBaudRate_double(){
	return BaudRate::getBaudRate_double(baudRate);
}

//-------------------------------// BAUD RATE FUNCTIONS //-------------------------------// 

/** Get the baud rate value when given an integer */
speed_t BaudRate::getBaudRate(int baud) {
	return getBaudRate((double) baud);
}

/** Get the baud rate value when given a double */
speed_t BaudRate::getBaudRate(double baud) {
	unordered_map<double, speed_t>::const_iterator got = baudRateList.find(baud);

	if( got == baudRateList.end())
		throw invalid_argument("Baud Rate not valid\n");
	
	return got->second;
}

/** Get the integer value when given a baud rate */
int BaudRate::getBaudRate_int(speed_t baud) {
	return (int) getBaudRate_double(baud);
}

/** Get the double value when given a baud rate */
double BaudRate::getBaudRate_double(speed_t baud) {
	for(unordered_map<double, speed_t>::const_iterator it = baudRateList.begin(); 
		it != baudRateList.end(); ++it) {
		
		if(it->second == baud) return it->first;
	}
	return -1;
}

