#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "RS-232/rs232.h"
 
#define BUF_SIZE 128
#define ACM0 24
#define ACM1 25
 
 /*
  * this method is time dependent and therefore not 
  * something we should use.
  */ 
 
int main()
{
  int i=0;
  int cport_nr=ACM0;
  int bdrate=57600; /* 57600 baud */
 
  char mode[]={'8','N','1',0}; // 8 data bits, no parity, 1 stop bit
  char str_send[2][BUF_SIZE]; // send data buffer
  unsigned char str_recv[BUF_SIZE]; // recv data buffer
  
  strcpy(str_send[0], "This is a test string.");
  strcpy(str_send[1], "This is another test string.");
  
  if(RS232_OpenComport(cport_nr, bdrate, mode, 0))
  {
    printf("Can not open comport\n");
    return(0);
  }
 
  usleep(20000);  /* waits 2000ms for stable condition */
  while(1)
  {
    RS232_cputs(cport_nr, str_send[i]); // sends string on serial
	printf("Sent to Arduino: '%s'\n", str_send[i]);
	
	usleep(1000000);  //waits for reply 1000ms 
	
	int n = RS232_PollComport(cport_nr, str_recv, (int)BUF_SIZE);
	if(n > 0){
      str_recv[n] = 0;   // always put a "null" at the end of a string! 
      printf("Received %i bytes: '%s'\n", n, (char *)str_recv);
	}
	i++;
    i %= 2;
    usleep(1000000);  // sleep for 5 Second 
   
  }
  return(0);
}
