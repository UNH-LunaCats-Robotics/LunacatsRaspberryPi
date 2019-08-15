CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -Wformat-nonliteral -Wformat-security -Wtype-limits -o2

objects = rs232.o

all: writeSerial

writeSerial: $(objects) writeSerial.o
	$(CC) $(objects) writeSerial.o -o writeSerial
	
writeSerial.o: writeSerial.cpp rs232.h
	$(CC) $(CFLAGS) -c writeSerial.cpp -o writeSerial.o

rs232.o : rs232.h rs232.c
	$(CC) $(CFLAGS) -c rs232.c -o rs232.o

clean :
	$(RM) writeSerial $(objects) writeSerial.o rs232.o