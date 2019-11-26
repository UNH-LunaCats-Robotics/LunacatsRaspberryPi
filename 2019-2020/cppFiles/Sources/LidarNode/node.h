#pragma once

#include "ofMain.h"
#include "LidarLite.hpp"
#include "ofApp.cpp"

class ofApp : public ofBaseApp{
	public:
    long botx;
    long boty;
    long botheight;
		long stridis;

		void setup(bool fasti2c, char i2c);
		void node(long x, long y, long z);
		void getdistance();
		void update(long x, long y);
		//void draw();

    int gettypeofobstacle(long angle);
    long getobstacle(long angle);

		ofApp myApp;
		LidarLite myLidarLite;
		int wDistance;
};
