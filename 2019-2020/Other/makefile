CC = g++
CFLAGS = -Wno-psabi

objects = ArduinoSerial.o

all: ArduinoSerialTest

ArduinoSerialTest: $(objects) ArduinoSerialTest.o
	$(CC) $(objects) ArduinoSerialTest.o -o ArduinoSerialTest

ArduinoSerialTest.o: ArduinoSerialTest.cpp ArduinoSerial.h 
	$(CC) $(CFLAGS) -c ArduinoSerialTest.cpp -o ArduinoSerialTest.o

ArduinoSerial.o: ArduinoSerial.cpp ArduinoSerial.h
	$(CC) $(CFLAGS) -c ArduinoSerial.cpp -o ArduinoSerial.o

clean:
	$(RM) ArduinoSerial.o ArduinoSerialTest.o