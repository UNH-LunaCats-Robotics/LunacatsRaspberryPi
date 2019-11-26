#include "ofApp.cpp"
#include <math.h>

//--------------------------------------------------------------
void node::node(long x, long y, long z, int lidarpoint);{
	botx = x;
  boty = y;
  botheight = z;
	stridis = 0;
	whichLidar = lidarpoint;
}

//setup for the lidar
void node::setup(bool fasti2c, int i2c){
	cout << "Here is the start of file" << endl;
	myLidarLite = LidarLite();
	myLidarLite.begin(0, fasti2c, true, i2c);

	// Exit if the lidar lite didn't initialize properly
	if (!myLidarLite.hasBegun()) ofApp::exit();

	// Print the hardware version of the Lidar Lite
	cout << "LIDAR Lite hardware version: " << myLidarLite.hardwareVersion() << endl;
	cout << "LIDAR Lite software version: " << myLidarLite.softwareVersion() << endl;

	wDistance = -1;
	myLidarLite.start();
}

//--------------------------------------------------------------
long node::getdistance(){
	int desread = myLidarLite.distance(true,true);
	if(desread >= 0) {
		cout << "myLidarLite reads a correct value" << endl;
		return desread;
	}
	else{
		cout << "Wrong number" << endl;
		return -1;
	}
}

void node::update(long x, long y){
	botx = x;
	boty = y;
}

int node::gettypeofobstacle(long angle){
	int dis = getdistance();
	double strightdis = getXlength(angle, dis);
	stridis = strightdis;
	double height = getHeight(angle, dis);
	if(height < botheight){
		cout << "This is a rock" << endl;
		//return height;
	}
	else if(height >= botheight){
		cout << "This is a hole" << endl;
		//return height;
	}
	return height;
}

long * node::getobstacle(long angle, int ulur){
	int dis = getdistance();
	if(ulur == 1){//upleft

	}

}
