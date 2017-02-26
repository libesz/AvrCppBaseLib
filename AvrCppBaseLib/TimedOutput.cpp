/* 
* TimedOutput.cpp
*
* Created: 3/28/2015 9:18:40 PM
* Author: huszty
*/

#include "TimedOutput.h"
#include "Uart.h"

TimedOutput::TimedOutput(volatile void *newPort,
                         unsigned char newMask,
                         unsigned short newLightTime): SoftTimerHandler(false, false, true),
                                                       port((volatile unsigned char *)newPort),
                                                       mask(newMask),
                                                       lightTime(newLightTime) {
  PUTS("TimedOutput::TimedOutput()");NL();
}

TimedOutput::~TimedOutput() {
}

void TimedOutput::start() {
  //PUTS("TimedOutput::start()");NL();
  *port |= mask;
  myTimer.set(lightTime);
}

void TimedOutput::handleTimeout() {
  //PUTS("TimedOutput::handleTimeout()");NL();
  *port &= ~mask;
}
