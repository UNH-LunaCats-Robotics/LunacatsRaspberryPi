//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//

#include <signal.h>
#include "libpixyusb2.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>


//the actual size of the placard we use
#define PLACARD_WIDTH  76
#define PLACARD_HEIGHT  56

#define FOCAL_LENGTH  275 //Calculated
#define ROBOT_MAX_SPEED  1 //unit = m/s

Pixy2        pixy;
static bool  run_flag = true;


void handle_SIGINT(int unused)
{
  // On CTRL+C - abort! //

  run_flag = false;
}

// calculate the distance between new location and the previous one,
// and compare it with the max possible distance (calculate from moving speed)
// too many bad values to filter out at present
bool is_bad_result(){
	return true;
}

//assume the robot only moves horizontally, so we could use the vertical side to
//calculate the direct distance
std::string cal_location(Block block){
  //size of the placard on the captured image
  double width_p = block.m_width;
  double height_p = block.m_height;
  
  //width if look at it right in front 
  double width_p_front = height_p * PLACARD_WIDTH / PLACARD_HEIGHT;
  double angle = acos(width_p/width_p_front) /M_PI * 180;
  
  //direct distance
  double dist = (PLACARD_HEIGHT * FOCAL_LENGTH) / height_p;
  //calculate x, y
  double y =  dist * (width_p * PLACARD_HEIGHT/PLACARD_WIDTH)/ height_p;
  double x = sqrt(dist * dist - y * y);
  
  //remove some bad results
  if(isnan(x)){
	//printf("error\n");
	return "";
  }
  printf ("width: %.f, height: %.f\nDirect distance: %.f mm (x: %.f, y: %.f)\n", width_p, height_p, dist, x, y);
  printf("angle: %.5f\n*************\n", angle);
  
  std::ostringstream s;
  s << x << ","<< y;
  return s.str();
} 

//return a string "x, y"
std::string get_location(){
  int  Block_Index;

  // Query Pixy for blocks //
  // get sig 1, (set our placard to signature 1 in advance)
  pixy.ccc.getBlocks(true, 1);

  // Were blocks detected? //
  if (pixy.ccc.numBlocks)
  {
    // Blocks detected - print them! //

    //printf ("Detected %d block(s)\n", pixy.ccc.numBlocks);

    for (Block_Index = 0; Block_Index < pixy.ccc.numBlocks; ++Block_Index)
    {
      //printf ("  Block %d: ", Block_Index + 1);
      //pixy.ccc.blocks[Block_Index].print();
      std::string tmp = cal_location(pixy.ccc.blocks[Block_Index]);
      return tmp;
    }
  }
  return "";
}


int main()
{
  int  Result;

  // Catch CTRL+C (SIGINT) signals //
  signal (SIGINT, handle_SIGINT);

  printf ("=============================================================\n");
  printf ("= PIXY2 Get Blocks                                          =\n");
  printf ("=============================================================\n");

  printf ("Connecting to Pixy2...");

  // Initialize Pixy2 Connection //
  {
    Result = pixy.init();

    if (Result < 0)
    {
      printf ("Error\n");
      printf ("pixy.init() returned %d\n", Result);
      return Result;
    }

    printf ("Success\n");
  }

  // Get Pixy2 Version information //
  {
    Result = pixy.getVersion();

    if (Result < 0)
    {
      printf ("pixy.getVersion() returned %d\n", Result);
      return Result;
    }

    pixy.version->print();
  }

  // Set Pixy2 to color connected components program //
  pixy.changeProg("color_connected_components");
  
  // FPS
  {
    Result = pixy.getFPS();
  
    printf("FPS: %d\n", Result);
  }

  while(1)
  {
  	get_location();
  	  
  	  if (run_flag == false)
    {
      // Exit program loop //
      break;
    }
    
  }

  printf ("Exit\n");
}
