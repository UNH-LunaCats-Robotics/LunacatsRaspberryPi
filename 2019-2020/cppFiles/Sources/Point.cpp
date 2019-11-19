#include "../Headers/Point.h"

/*
Point();
Point(float x, float y, float z);
void set(int x, int y, float z);

float X();
float Y();
float Z();
*/

Point::Point() {
    x_ = 0.0f;
    y_ = 0.0f;
    z_ = 0.0f;
}

Point::Point(float x, float y, float z) {
    x_ = x;
    y_ = y;
    z_ = z;
}

void Point::set(float x, float y, float z) {
    x_ = x;
    y_ = y;
    z_ = z;
}

float Point::X() { return x_; }
float Point::Y() { return y_; }
float Point::Z() { return z_; }