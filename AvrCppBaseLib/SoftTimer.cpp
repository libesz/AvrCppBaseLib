/* 
* SoftTimer.cpp
*
* Created: 3/28/2015 2:57:59 PM
* Author: huszty
*/

#include "SoftTimer.h"
#include "Usart.h"

SoftTimer::SoftTimer(SoftTimerHandler *newHandler,
                     bool useSet,
                     bool useReset,
                     bool useTimeout): remaining(0),
                                       handler(newHandler),
                                       subscriptions(0) {
  subscriptions |= useSet ? SET_EVENT_MASK : 0;
  subscriptions |= useReset ? RESET_EVENT_MASK : 0;
  subscriptions |= useTimeout ? TIMEOUT_EVENT_MASK : 0;
}

SoftTimer::SoftTimer() {
}

void SoftTimer::set(unsigned short newValue) {
  if(subscriptions & SET_EVENT_MASK)
    remaining = handler->handleTimerSet(remaining, newValue);
  else
    remaining = newValue;
}

void SoftTimer::reset() {
  if(subscriptions & RESET_EVENT_MASK)
    handler->handleTimerReset(remaining);
  remaining = 0;
}

unsigned short SoftTimer::get() {
  return remaining;
}

void SoftTimer::tick() {
  if(remaining)
    if(!--remaining)
      if(subscriptions & TIMEOUT_EVENT_MASK)
        handler->handleTimeout();
}

SoftTimerHandler::SoftTimerHandler(bool useSet,
                                   bool useReset,
                                   bool useTimeout): myTimer(this, useSet, useReset, useTimeout) {
}                                     

unsigned short SoftTimerHandler::handleTimerSet(unsigned short oldValue, unsigned short newValue) {
  PUTS("SoftTimerHandler::handleTimerSet NOT IMPLEMENTED"); NL();
  return newValue;
}

void SoftTimerHandler::handleTimerReset(unsigned short oldValue) {
  PUTS("SoftTimerHandler::handleTimerReset NOT IMPLEMENTED"); NL();
}

void SoftTimerHandler::handleTimeout() {
  PUTS("SoftTimerHandler::handleTimeout NOT IMPLEMENTED"); NL();
}

SoftTimer* SoftTimerHandler::getTimer() {
	return &myTimer;
}
