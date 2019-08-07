#include "./ArduinoSerial.h"

unordered_map<double, speed_t> ArduinoSerial::BaudRate::baudRateList = {
	{0, 	B0},     //Hand up
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

ArduinoSerial::ArduinoSerial(Port p) {
	port = ports[p];
	baudRate = (speed_t)B9600;
	initialized = initializePort();
	printf("Port is %s, baud rate is 9600, initialized is %d\n", port.c_str(), initialized);
}

ArduinoSerial::ArduinoSerial(Port p, double baud){
	port = ports[p];
	baudRate = BaudRate::getBaudRate(baud);
	initialized = initializePort(); 
}

ArduinoSerial::ArduinoSerial(Port p, int baud){
	port = ports[p];
	baudRate =  BaudRate::getBaudRate(baud);
	initialized = initializePort();
}

ArduinoSerial::ArduinoSerial(Port p, speed_t baud){
	port = ports[p];
	baudRate = baud;
	initialized = initializePort();  
}

ArduinoSerial::~ArduinoSerial(){
	resetPort();
}

bool ArduinoSerial::initializePort(bool force) {
	//do not initialize port if already done unless forced
	if(!force && !isNotInitialized()) return false;

	USB = open( port.c_str(), O_RDWR| O_NOCTTY );
	
	termios tty;
	memset (&tty, 0, sizeof tty);

	// Error Handling 
	if ( tcgetattr ( USB, &tty ) != 0 ) {
	   //std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
		throw invalid_argument("Error opening port\n");
	}

	// Save old tty parameters 
	if(initialized != true) tty_old = tty;

	// Set Baud Rate 
	cfsetospeed (&tty, baudRate);
	cfsetispeed (&tty, baudRate);

	// Setting other Port Stuff 
	tty.c_cflag     &=  ~PARENB;            // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cc[VMIN]   =  0;                  // read doesn't block
	tty.c_cc[VTIME]  =  0.5;                // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	// Make raw 
	cfmakeraw(&tty);

	// Flush Port, then applies attributes 
	tcflush( USB, TCIFLUSH );
	if ( tcsetattr ( USB, TCSANOW, &tty ) != 0) {
	   //std::cout << "Error " << errno << " from tcsetattr" << std::endl;
		printf("Error from tcsetattr\n");
		return false;
	}
	
	return true;
}

bool ArduinoSerial::resetPort() {
	// Make raw 
	cfmakeraw(&tty_old);

	// Flush Port, then applies attributes 
	tcflush( USB, TCIFLUSH );
	if ( tcsetattr ( USB, TCSANOW, &tty_old ) != 0) {
	   //std::cout << "Error " << errno << " from tcsetattr" << std::endl;
		printf("Error from tcsetattr\n");
		return false;
	}
	initialized = false;
	return true;
}

void ArduinoSerial::readString( char* response, int buf_size, char terminator ) {
	if(!isInitialized()) return;
	
	//read 
	int n = 0, spot = 0;
	char buf = '\0';
	
	do {
		n = read( USB, &buf, 1 );
		sprintf( &response[spot], "%c", buf );
		spot += n;
	} while( buf != terminator && n > 0);

	if (n < 0) {
		//std::cout << "Error reading: " << strerror(errno) << std::endl;
		printf("Error Reading.\n");
	}
	else if (n == 0) {
		//std::cout << "Read nothing!" << std::endl;
		printf("Read nothing! \n");
	}
	else {
		printf("Received %i bytes: '%s'\n", spot, (char *)response);
		//std::cout << "Response: " << response << std::endl;
	}
}

char ArduinoSerial::readChar() {
	char r = '\0';
	if(!isInitialized()) return r;

	return read( USB, &r, 1);
}

void ArduinoSerial::writeString( const unsigned char* cmd  ) {
	if(!isInitialized()) return;
	
	int n_written = 0, spot = 0;
	printf("Sending the message '%s'\n", (char *)cmd);

	do {
		n_written = write( USB, &cmd[spot], 1 );
		spot += n_written;
	} while (cmd[spot-1] != '\0' && n_written > 0);
}

void ArduinoSerial::writeChar(char c) {
	if(!isInitialized()) return;
	
	write( USB, &c, 1 );
}

bool ArduinoSerial::isInitialized() {
	if(!initialized) printf("Port Not Initialized\n");
	return initialized;
}

bool ArduinoSerial::isNotInitialized() {
	if(initialized) printf("Port Already Initialized\n");
	return !initialized;
}

bool ArduinoSerial::getInitialized() {
	return initialized;
}

int ArduinoSerial::getUSB(){
	return USB;
}

string ArduinoSerial::getPort(){
	return port;
}

speed_t ArduinoSerial::getBaudRate(){
	return baudRate;
}

int ArduinoSerial::getBaudRate_int(){
	return BaudRate::getBaudRate_int(baudRate);
}

double ArduinoSerial::getBaudRate_double(){
	return BaudRate::getBaudRate_double(baudRate);
}

speed_t ArduinoSerial::BaudRate::getBaudRate(int baud) {
	return getBaudRate((double) baud);
}

speed_t ArduinoSerial::BaudRate::getBaudRate(double baud) {
	unordered_map<double, speed_t>::const_iterator got = baudRateList.find(baud);
	
	if( got == baudRateList.end())
		throw invalid_argument("Baud Rate not valid\n");
	
	return got->second;
}

int ArduinoSerial::BaudRate::getBaudRate_int(speed_t baud) {
	return (int) getBaudRate_double(baud);
}

double ArduinoSerial::BaudRate::getBaudRate_double(speed_t baud) {
	for(unordered_map<double, speed_t>::const_iterator it = baudRateList.begin(); 
		it != baudRateList.end(); ++it) {
		
		if(it->second == baud) return it->first;
	}
	return -1;
}

