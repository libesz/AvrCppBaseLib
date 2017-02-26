/* 
* TimedOutput.h
*
* Created: 3/28/2015 9:18:40 PM
* Author: huszty
*/

#ifndef __TIMEDOUTPUT_H__
#define __TIMEDOUTPUT_H__

#include "SoftTimer.h"

class TimedOutput: public SoftTimerHandler {
  volatile unsigned char *port;
  unsigned char mask;
  unsigned char lightTime;
  TimedOutput( const TimedOutput &c );
  TimedOutput& operator=( const TimedOutput &c );
public:
  TimedOutput(volatile void *newPort,
              unsigned char newMask,
              unsigned short newLightTime);
  ~TimedOutput();
  void start();
  void handleTimeout();
};

#endif //__TIMEDOUTPUT_H__
