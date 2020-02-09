#include "../Headers/RoadMap.h"

static const int NUM_POINTS = 100;
static const int KNN = 5;
static const double PRECISION = 0.05;
static const int LENGTH = 100;
static const int WIDTH = 100;

vertex** constructRoadmap(double sx, double sy, double gx, double gy);
