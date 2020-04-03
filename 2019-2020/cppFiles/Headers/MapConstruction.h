#include "Dijkstra.h"
#include "Terrain.h"

static const int NUM_POINTS = 500;
static const int KNN = 10;
static const double PRECISION = 0.05;

vertex** constructRoadmap(double sx, double sy, double gx, double gy, terrain* grid);
