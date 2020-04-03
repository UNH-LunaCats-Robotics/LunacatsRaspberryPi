#include "../Headers/Autonomous.h"

bool closeTo(double x, double y) {
    return robotX - x <= 1 && robotX - x >= -1 && robotY - y <= 1 && robotY - y >= -1;
}

int adjustAngle() {
    //Calculate angle difference
    //Turn until at the correct angle
    return -1;
}

int moveTo(double x, double y) {
    if(adjustAngle() == -1)
	return -1;

    //Turn on wheels

    while(!closeTo(x, y)) {
	if(!doAutonomous) {
	    //Turn off wheels
	    return -1;
	}
    }

    //Turn off wheels
}

int runAutonomous() {
    while(true) {
        //Need way to find goal position, replace 97s
        //Need to render field
        /*vertex* path = findPath(robotX, robotY, 97, 97, field); 

        while(path != nullptr) {
            if(moveTo(path->x, path->y) == -1)
            break;
            path = path->next;
        }*/
    }
}
