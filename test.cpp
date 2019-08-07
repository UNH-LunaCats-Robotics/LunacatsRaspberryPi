#include <iostream>
#include <fstream>      // std::fstream


using namespace std;



// Where arduino is plugged in:
// /dev/cu.usbmodem146201/


int main()
{
    ifstream arduino("/dev/tty/ACM0");
    // arduino.open("/dev/cu.usbmodem146201/", fstream::in);

    if(arduino.is_open()) {
        cout<<"File is open"<<endl;

        char c = arduino.get();
        while (arduino.good()) {
            std::cout << c;
            c = arduino.get();
        }
    }
    else {
        cout<<"File is closed"<<endl;
    }

    arduino.close();
}
