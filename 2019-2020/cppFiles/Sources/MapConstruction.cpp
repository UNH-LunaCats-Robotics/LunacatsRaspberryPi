#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "../Headers/MapConstruction.h"

using namespace std;

vertex** merge(vertex** vertices, int i, int k, int j, vertex* v);
vertex** mergesort(vertex** vertices, int i, int j, vertex* v);
double distance(vertex* v1, vertex* v2);
double distance(double x1, double y1, double x2, double y2);
bool isValidEdge(vertex* v1, vertex* v2, terrain* grid);
double angleTo(vertex* v1, vertex* v2);
double angleTo(double x1, double y1, double x2, double y2);
void printMap(vertex** vertices);

int terrain [100][100];

vertex** samplePoints(struct terrain* grid) {
    vertex** vertices = new vertex*[NUM_POINTS];

    //Pick points
    srand(time(NULL));
    for(int i = 0; i < NUM_POINTS; i++) {
        vertex* v = newVertex(i);
        v->x = rand() % grid->width;
        v->y = rand() % grid->height;
        while(!isValidPoint(v->x, v->y, grid)) {
            v->x = rand() % grid->width;
	    v->y = rand() % grid->height;
        }
        vertices[i] = v;
    }

    return vertices;
}

vertex** constructRoadmap(double sx, double sy, double gx, double gy, struct terrain* grid) {

    //Pick points
    vertex** vertices = samplePoints(grid);

    //First point is start point
    vertices[0]->x = sx;
    vertices[0]->y = sy;

    //Second point is goal point
    vertices[1]->x = gx;
    vertices[1]->y = gy;

    //Copy to keep things in order
    vertex** vertcopy = new vertex*[NUM_POINTS];
    for(int i = 0; i < NUM_POINTS; i++)
    	vertcopy[i] = vertices[i];

    //Construct edges
    for(int i = 0; i < NUM_POINTS; i++) {
        vertex* v = vertcopy[i];

	    //Sort by distance to v
        vertex** svertices = mergesort(vertices, 0, NUM_POINTS - 1, v);
        int count = 0;
        for(int j = 0; j < NUM_POINTS; j++) {
	        if(svertices[j] == v)
		        continue;

	        //Try to connect KNN vertices to v
            if(count < KNN && isValidEdge(v, svertices[j], grid)) {
                edge* edge = v->edges;
                bool exists = false;
                while(edge != nullptr) {
                    if(edge->dest == svertices[j]) {
                        exists = true;
                        break;
                    }
		            edge = edge->next;
                }
                if(!exists) {
                    addedge(v, svertices[j], distance(v, svertices[j]));
                    addedge(svertices[j], v, distance(svertices[j], v));
                    count++;
                }
            }
        }
    }

    printMap(vertcopy);

    return vertcopy;
}

vertex** merge(vertex** vertices, int i, int k, int j, vertex* v) {

    vertex** copy = new vertex*[j - i + 1];
    unsigned int ipt = i;
    unsigned int jpt = k + 1;

    for(unsigned int pt = 0; pt < j - i + 1; pt++) {
	if(jpt > j || (ipt < k + 1 && distance(vertices[ipt], v) < distance(vertices[jpt], v)))
            copy[pt] = vertices[ipt++];
        else
            copy[pt] = vertices[jpt++];   
    }

    for(int x = 0; x < j - i + 1; x++)
        vertices[x + i] = copy[x];
    delete[] copy;
    return vertices;
}

vertex** mergesort(vertex** vertices, int i, int j, vertex* v) {
    if(i >= j)
        return vertices;
    unsigned int k = (i + j) / 2;
    vertices = mergesort(vertices, i, k, v);
    vertices = mergesort(vertices, k + 1, j, v);
    return merge(vertices, i, k, j, v);
}

double distance(vertex* v1, vertex* v2) {
    if(v1 == nullptr || v2 == nullptr)
        return 10000000;
    return distance(v1->x, v1->y, v2->x, v2->y);
}

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool isValidEdge(vertex* v1, vertex* v2, struct terrain* grid) {
    double dist = distance(v1, v2);
    double vx = (v2->x - v1->x) / dist;
    double vy = (v2->y - v1->y) / dist;

    int hole = 0;
    if(grid->grid[(int)v1->x][(int)v1->y] == -1 || grid->grid[(int)v2->x][(int)v2->y] == -1)
	    hole = 1;

    for(double i = 0; i < dist; i += PRECISION) {
        double px = v1->x + (i * vx);
        double py = v1->y + (i * vy);
        if(!isValidEdgePoint(px, py, grid, hole)) 
            return false;
    }
    return true; 
}

double angleTo(vertex* v1, vertex* v2) {
    return angleTo(v1->x, v1->y, v2->x, v2->y);
}

double angleTo(double x1, double y1, double x2, double y2) {
    return atan((y2 - y1) / (x2 - x1));
}

void printMap(vertex** vertices) {
    printf("points\n");
    for(int i = 0; i < NUM_POINTS; i++) {
        vertex* v = vertices[i];
        printf("%f:%f\n", v->x, v->y);
    }
    printf("edges\n");
    for(int i = 0; i < NUM_POINTS; i++) {
        vertex* v = vertices[i];
        //printf("Point %i (%f, %f)\n", v->id, v->x, v->y);
        edge* edge = v->edges;
        while(edge != nullptr) {
	    if(edge->valid) {
                printf("%f:%f:%f:%f\n", v->x, v->y, edge->dest->x, edge->dest->y);
		edge->valid = false;
	    }
	    edge = edge->next;
	}
    }
}

/*void buildTerrain() {
	for(int x = 0; x < 100; x++) {
		for(int y = 0; y < 100; y++)
			terrain[x][y] = 0;
	}
	for(int x = 10; x < 80; x++) {
		for(int y = 10; y < 20; y++)
			terrain[x][y] = 1;
	}
	for(int x = 10; x < 15; x++) {
		for(int y = 20; y < 80; y++)
			terrain[x][y] = 1;
	}
	for(int x = 35; x < 90; x++) {
		for(int y = 35; y < 65; y++)
			terrain[x][y] = 1;
	}
	for(int x = 0; x < 80; x++) {
		for(int y = 80; y < 100; y++)
			terrain[x][y] = 1;
	}
	for(int x = 90; x < 100; x++) {
		for(int y = 30; y < 70; y++)
			terrain[x][y] = 1;
	}
}*/

/*int main() {
	//buildTerrain();
    findPath(3.0, 3.0, 97.0, 97.0);
}*/
