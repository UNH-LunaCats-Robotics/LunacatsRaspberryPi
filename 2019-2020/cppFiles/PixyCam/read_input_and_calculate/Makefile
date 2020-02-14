CXX=g++
CPPFLAGS=-g -fpermissive -I/usr/include/libusb-1.0 -I ../host/libpixyusb2/include -I ../host/arduino/libraries/Pixy2 -I ../common/inc
LDLIBS=../../build/libRobotSourceCode.a -lusb-1.0

SRCS=get_position.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: get_position

clean:
	rm -f *.o get_position

get_position: $(OBJS)
	$(CXX) $(LDFLAGS) -o get_position $(OBJS) $(LDLIBS)
