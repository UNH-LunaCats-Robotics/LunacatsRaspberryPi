#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../Headers/PathPlanning.h"

using namespace std; 

vertex* findPath(double x1, double y1, double x2, double y2, int** field) {

    terrain* grid = buildTerrain(field);

    vertex** vertices = constructRoadmap(x1, y1, x2, y2, grid);
    
    vertex* path =  dijkstra(vertices, NUM_POINTS);

    //Print path, testing only
    vertex* pathp = path;
    printf("path\n");
    while(pathp != nullptr) {
	printf("%f:%f\n", pathp->x, pathp->y);
	pathp = pathp->next;
    }

    return path;
}

int main() {
    //findPath(3.0, 3.0, 97.0, 97.0);
}
