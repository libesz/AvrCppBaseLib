/* 
* BlinkingLed.h
*
* Created: 3/28/2015 9:18:40 PM
* Author: huszty
*/

#ifndef __BLINKINGLED_H__
#define __BLINKINGLED_H__

#include "SoftTimer.h"

class BlinkingLed: public SoftTimerHandler {
  volatile unsigned char *port;
  unsigned char mask;
  unsigned char lightTime;
  BlinkingLed( const BlinkingLed &c );
  BlinkingLed& operator=( const BlinkingLed &c );
public:
  BlinkingLed(volatile void *newPort,
              unsigned char newMask,
              unsigned short newLightTime);
  ~BlinkingLed();
  void start();
  void handleTimeout();
};

#endif //__BLINKINGLED_H__
