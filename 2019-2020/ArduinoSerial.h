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
	string ports[2] = { "/dev/ttyACM0", "/dev/ttyACM1"};
	
	int USB = -1;
	string port;
	speed_t baudRate;
	termios tty_old;
	bool initialized = false;
	//prints error msg if in debug mode.
	bool isInitialized(); 	 
	bool isNotInitialized(); 
	
public:
	ArduinoSerial(Port p); //default baud: 9600
	ArduinoSerial(Port p, double baud);
	ArduinoSerial(Port p, int baud);
	ArduinoSerial(Port p, speed_t baud);
	~ArduinoSerial();
	bool initializePort( bool force = false );
	bool resetPort();
	
	void readString( char* response, int buf_size, char terminator = '\n' );
	char readChar();
	void writeString( const unsigned char* cmd );
	void writeChar(char c);
	
	bool getInitialized();
	int getUSB();
	string getPort();
	speed_t getBaudRate();
	int getBaudRate_int();
	double getBaudRate_double();
	
	struct BaudRate {
		static unordered_map<double, speed_t> baudRateList;
		
		//throws exception on fail
		static speed_t 	getBaudRate(int baud);
		static speed_t 	getBaudRate(double baud);
		
		//returns -1 on fail
		static int 		getBaudRate_int(speed_t baud);
		static double 	getBaudRate_double(speed_t baud);
	};
};
