#pragma once

#include "ofMain.h"
#include "LidarLite.hpp"
#include "ofApp.cpp"

class ofApp : public ofBaseApp{
	public:
    long botx;
    long boty;
    long botheight;

		void node(long x, long y, long z);
		void update(long x, long y);
		void draw();

    long gettypeofobstacle(long angle);
    long getobstacle(long angle);

		ofApp myApp;
		int wDistance;
};
