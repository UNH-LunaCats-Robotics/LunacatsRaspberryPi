CC = gcc

all: termiosSerial

termiosSerial: termiosSerial.o
	$(CC) termiosSerial.o -o termiosSerial 

termiosSerial.o: termiosSerial.cpp
	$(CC) -c termiosSerial.cpp -o termiosSerial.o

clear: 
	$(RM) termiosSerial termiosSerial.o

