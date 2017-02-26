/* 
* BlinkingLed.cpp
*
* Created: 3/28/2015 9:18:40 PM
* Author: huszty
*/

#include "BlinkingLed.h"
#include "Usart.h"

BlinkingLed::BlinkingLed(volatile void *newPort,
                         unsigned char newMask,
                         unsigned short newLightTime): SoftTimerHandler(false, false, true),
                                                       port((volatile unsigned char *)newPort),
                                                       mask(newMask),
                                                       lightTime(newLightTime) {
  PUTS("BlinkingLed::BlinkingLed()");NL();
}

BlinkingLed::~BlinkingLed() {
}

void BlinkingLed::start() {
  //PUTS("BlinkingLed::start()");NL();
  *port |= mask;
  myTimer.set(lightTime);
}

void BlinkingLed::handleTimeout() {
  //PUTS("BlinkingLed::handleTimeout()");NL();
  *port &= ~mask;
}
