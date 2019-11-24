#include <string>

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

    operator auto() const {
        std::string res = "{\"x\":" + std::to_string(x_)
               +", \"y\":"+std::to_string(y_)
               +", \"z\":"+std::to_string(z_)+"}";
        return res;
    }
private:
    float x_;
    float y_;
    float z_;
};

#endif