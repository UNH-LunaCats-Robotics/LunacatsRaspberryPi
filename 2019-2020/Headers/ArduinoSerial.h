#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <stdexcept>
#include <cstdio>      // standard input / output functions
#include <string>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

using namespace std;
typedef struct termios termios;

enum Port {ttyACM0 = 0, ttyACM1 = 1};

class ArduinoSerial{
private: 
	//all current possible ports to select from
	string ports[2] = { "/dev/ttyACM0", "/dev/ttyACM1"};
	
	//port descriptors
	int USB = -1; 				//port integer value
	string port;				//port location
	speed_t baudRate;           //baud rate used
	termios tty_old; 			//old port settings
	bool initialized = false;   //if initializaion has happened

	//prints error msg if in debug mode.
	bool isInitialized(); 	   
	bool isNotInitialized(); 
	
public:
	/** Baud Rate Conversion Class
	 *  - Shows the list of possible baud rates (in cpp file)
	 *  - Converts between integers/doubles and speed_t, the type used for baud rates.
	 */
	struct BaudRate {
		//all possible baud rate options
		static unordered_map<double, speed_t> baudRateList;
		
		//get baud rate - throws exception on fail
		static speed_t 	getBaudRate(int baud);
		static speed_t 	getBaudRate(double baud);
		
		//get baud rate value - returns -1 on fail
		static int 		getBaudRate_int(speed_t baud);
		static double 	getBaudRate_double(speed_t baud);
	};

	//create the connection
	ArduinoSerial(Port p); //default baud: 9600
	ArduinoSerial(Port p, double baud);
	ArduinoSerial(Port p, int baud);
	ArduinoSerial(Port p, speed_t baud);
	~ArduinoSerial();

	//initialize the arduino serial connection port
	bool initializePort( bool force = false );

	//restore previous port settings on destruction
	bool resetPort();
	
	//perform read/write operations with arduino
	void readString( char* response, int buf_size, char terminator = '\n' );
	char readChar();
	void writeString( const unsigned char* cmd );
	void writeChar(char c);
	
	//get descriptor information 
	bool getInitialized();
	int getUSB();
	string getPort();
	speed_t getBaudRate();
	int getBaudRate_int();
	double getBaudRate_double();
};
