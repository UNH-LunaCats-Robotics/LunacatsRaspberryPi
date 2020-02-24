/*------------------------------------------------------------------------------
  This example illustrates how to use the LIDAR-Lite library to gain quick
  access to the basic functions of LIDAR-Lite via the Raspberry Pi interface.
  Additionally, it provides users of any platform with a template for their
  own application code.

  Copyright (c) 2019 Garmin Ltd. or its subsidiaries.
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at
  http://www.apache.org/licenses/LICENSE-2.0
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
------------------------------------------------------------------------------*/

#include <linux/types.h>
#include <cstdio>
#include <time.h>
#include <iostream>
#include <include/lidarlite_v3.h>
#include <unistd.h>
#include <math.h>

using namespace std;

LIDARLite_v3 myLidarLite;

//void sleeps(int milsecond){
	//clock_t timeend = clock() + milsecond + CLOCKS_PER_SEC/1000;
//}



int main()
{
    __u16 distance;
    __u8  busyFlag;

    // Initialize i2c peripheral in the cpu core
    myLidarLite.i2c_init();
	//unsigned int ms1000 = 1000000;
    // Optionally configure LIDAR-Lite
    myLidarLite.configure(0);
	//sleeps(1000);
    while(1)
    {
        // Each time through the loop, check BUSY
        busyFlag = myLidarLite.getBusyFlag();

        if (busyFlag == 0x00)
        {
            // When no longer busy, immediately initialize another measurement
            // and then read the distance data from the last measurement.
            // This method will result in faster I2C rep rates.
            myLidarLite.takeRange();
            distance = myLidarLite.readDistance();
			      //printf("here\n");
            printf("%4d\n", distance);
            usleep(1000000);
        }
        // sleeps(100000);
        //Sleep(1000);
        //usleep(ms1000);
    }
}


/*
 * ================================================================
 * The set of instructions below illustrates one method of setting
 * an alternate I2C device address in the LIDAR-Lite v3. See the
 * operator manual and C++ libraries for further details.
 * ================================================================
 */
 // Get the straight distance
 double ofApp::getXlength(double angle, double straightDistance){
 	double pi = 3.14159265;
 	double sinangle = sin (angle * pi / 180);
 	cout << "The sin of angle is " << sinangle << " for strightDistance";
 	double xlength = sinangle * straightDistance;
 	return xlength;
 }

 // Get the straight distance
 double ofApp::getHeight(double angle, double straightDistance){
 	double pi = 3.14159265;
 	double sinangle = cos (angle * pi / 180);
 	cout << "The cos of angle is " << sinangle << " for strightDistance";
 	double hlength = sinangle * straightDistance;
 	return hlength;
 }

 // straightDistance is the distance from the lidar to the rock
 // HereY is the Y of the current position
 // UR means up right
 double ofApp::getYforUR(double angle, double straightDistance, double hereY){
 	double pi = 3.14159265;
 	double result, cosnum;
 	if(angle == 0 || angle == 360){
 		result = straightDistance + hereY;
 	}
 	else if(angle < 90 && angle > 0){
 		cosnum = cos(angle * pi /180);
 		result = cosnum * straightDistance;
 		result = result + hereY;
 	}
 	else if(angle == 90 || angle == 270){
 		result = hereY;
 	}
 	else if(angle > 270 && angle < 360){
 		angle = angle - 270;
 		cosnum = cos(angle * pi /180);
 		result = cosnum * straightDistance;
 		result = result + hereY;
 	}
 	else if(angle > 90 && angle < 180){
 		cosnum = cos(angle * pi /180);
 		result = cosnum * straightDistance;
 		result = hereY + result;
 	}
 	else{
 		result = -1;
 	}
 	return result;
 }

 // straightDistance is the distance from the lidar to the rock
 // HereX is the X of the current position
 // UR means up right
 double ofApp::getXforUR(double angle, double straightDistance, double hereX){
 	double pi = 3.14159265;
 	double result, cosnum;
 	if(angle == 0 || angle == 360 || ngle == 180){
 		result = hereX;
 	}
 	else if(angle < 90 && angle > 0){
 		cosnum = sin(angle * pi /180);
 		result = cosnum * straightDistance;
 		result = result + hereX;
 	}
 	else if(angle == 90){
 		result = hereX + straightDistance;
 	}
 	else if(angle == 270){
 		result = hereX - straightDistance;
 	}
 	else if(angle > 270 && angle < 360){
 		angle = angle - 270;
 		cosnum = sin(angle * pi /180);
 		result = cosnum * straightDistance;
 		result = hereX - result;
 	}
 	else if(angle > 90 && angle < 180){
 		cosnum = sin(angle * pi /180);
 		result = cosnum * straightDistance;
 		result = result - hereX;
 	}
 	else{
 		result = -1;
 	}
 	return result;
 }

 // straightDistance is the distance from the lidar to the rock
 // HereX is the X of the current position
 // UL means up Left
 double ofApp::getXforUL(double angle, double straightDistance, double hereX){
 	double pi = 3.14159265;
 	double result, cosnum;
 	if(angle == 0 || angle == 360 || angle == 180){
 		result = hereX;
 	}
 	else if(angle < 90 && angle > 0){
 		cosnum = sin(angle * pi /180);
 		result = cosnum * straightDistance;
 		result = result + hereX;
 	}
 	else if(angle == 90){
 		result = hereX + straightDistance;
 	}
 	else if(angle == 270){
 		result = hereX - straightDistance;
 	}
 	else if(angle > 270 && angle < 360){
 		angle = angle - 270;
 		cosnum = sin(angle * pi /180);
 		result = cosnum * straightDistance;
 		result = hereX - result;
 	}
 	else if(angle > 180 && angle < 270){
 		angle = angle - 180;
 		cosnum = sin(angle * pi /180);
 		result = cosnum * straightDistance;
 		result = hereX - result;
 	}
 	else{
 		result = -1;
 	}
 	return result;
 }

 // straightDistance is the distance from the lidar to the rock
 // HereY is the Y of the current position
 // UL means up Left
 double ofApp::getYforUL(double angle, double straightDistance, double hereY){
 	double pi = 3.14159265;
 	double result, cosnum;
 	if(angle == 0 || angle == 360){
 		result = straightDistance + hereY;
 	}
 	else if(angle < 90 && angle > 0){
 		cosnum = cos(angle * pi /180);
 		result = cosnum * straightDistance;
 		result = result + hereY;
 	}
 	else if(angle == 90 || angle == 270){
 		result = hereY;
 	}
 	else if(angle > 270 && angle < 360){
 		angle = angle - 270;
 		cosnum = cos(angle * pi /180);
 		result = cosnum * straightDistance;
 		result = result + hereY;
 	}
 	else if(angle > 180 && angle < 270){
 		cosnum = cos(angle * pi /180);
 		result = cosnum * straightDistance;
 		result = hereY - result;
 	}
 	else{
 		result = -1;
 	}
 	return result;
 }
/*
#define i2cSecondaryAddr 0x44  // Set I2C address of LIDAR-Lite v3 to 0x44

int main()
{
    __u16 distance;

    // Initialize i2c peripheral in the cpu core
    myLidarLite.i2c_init();

    // Set an alternate i2c address in the LIDAR-Lite
    // The 2nd argument, if non-zero, disables the default addr 0x62
    myLidarLite.setI2Caddr(i2cSecondaryAddr, true);

    while(1)
    {
        myLidarLite.waitForBusy(i2cSecondaryAddr);
        myLidarLite.takeRange(i2cSecondaryAddr);
        distance      = myLidarLite.readDistance(i2cSecondaryAddr);

        printf("%4d\n", distance);
    }
}
*/
