#include <cstring>		// string function definitions
#include <unordered_map>
#include <sys/file.h>
#include <cstdio>       // standard input / output functions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

#include <chrono>
#include <thread> 
#include <mutex>
#include <condition_variable>

using namespace std;
typedef struct termios termios;

#define RS232_PORTNR  38

enum Port {
	ttyS0 = 0,   ttyS1 = 1,   ttyS2 = 2,   ttyS3 = 3,   
	ttyS4 = 4,   ttyS5 = 5,   ttyS6 = 6,   ttyS7 = 7,   
	ttyS8 = 8,   ttyS9 = 9,   ttyS10 = 10, ttyS11 = 11,
	ttyS12 = 12, ttyS13 = 13, ttyS14 = 14, ttyS15 = 15,
	ttyUSB0 = 16, ttyUSB1 = 17, ttyUSB2 = 18, tyUSB3 = 19, 
	ttyUSB4 = 20, ttyUSB5 = 21,
	ttyAMA0 = 22, ttyAMA1 = 23,
	ttyACM0 = 24, ttyACM1 = 25,
	rfcomm0 = 26, rfcomm1 = 27,
	ircomm0 = 28, ircomm1 = 29,
	cuau0 = 30, cuau1 = 31, cuau2 = 32, cuau3 = 33,
	cuaU0 = 30, cuaU1 = 31, cuaU2 = 32, cuaU3 = 33};

/** Baud Rate Conversion Class
 *  - Shows the list of possible baud rates (in cpp file)
 *  - Converts between integers/doubles and speed_t, the type used for baud rates.
 */
struct BaudRate {
	//get baud rate - throws exception on fail
	static speed_t 	getBaudRate(int baud);
	static speed_t 	getBaudRate(double baud);
	
	//get baud rate value - returns -1 on fail
	static int 		getBaudRate_int(speed_t baud);
	static double 	getBaudRate_double(speed_t baud);

private:
	//all possible baud rate options
	static unordered_map<double, speed_t> baudRateList;
};

class ArduinoSerial{
private: 
	//all current possible ports to select from
	static string ports[RS232_PORTNR]; 
                       
	//port descriptors
	int USB = -1; 				//port integer value
	string port;				//port location
	speed_t baudRate;           //baud rate used
	termios tty_old; 			//old port settings
	int status_old = 0;			//old modem settings	
	bool initialized = false;   //if initializaion has happened
	
	//timeout for readBytes
	chrono::seconds timeout = 2s;
	int static readBytes( int USBB, char* response, int buf_size, char terminator);
	int readBytes_wrapper( char* response, int buf_size, char terminator);

	char readByte( int USBB );

	//prints error msg if in debug mode.
	bool isInitialized(); 	   
	bool isNotInitialized(); 
public:
	//create the connection
	ArduinoSerial(Port p, speed_t baud); //default timeout = 2s
	ArduinoSerial(Port p, speed_t baud, chrono::seconds tout);
	~ArduinoSerial();

	//initialize the arduino serial connection port
	bool initializePort( bool force = false );

	//restore previous port settings on destruction
	bool resetPort();
	
	//perform read/write operations with arduino
	int readString( char* response, int buf_size, char terminator = '\n' );
	char readChar();
	bool writeString( const unsigned char* cmd );
	void writeChar(char c);
	
	//set descriptor information
	void setTimeout(chrono::seconds s);

	//get descriptor information 
	bool getInitialized();
	int getUSB();
	string getPort();
	speed_t getBaudRate();
	int getBaudRate_int();
	double getBaudRate_double();
	chrono::seconds getTimeout();
};
