
#ifndef POINT
#define POINT

//we can expand on this class later
class Point {
public:
    Point();
    Point(float x, float y, float z);
    void set(float x, float y, float z);
    
    float X();
    float Y();
    float Z();
private:
    float x_;
    float y_;
    float z_;
};

#endif