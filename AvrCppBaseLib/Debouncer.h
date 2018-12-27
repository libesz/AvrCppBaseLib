/* 
* AntiPrell.h
*
* Created: 3/27/2015 9:19:15 PM
* Author: huszty
*/


#ifndef __DEBOUNCER_H__
#define __DEBOUNCER_H__

#include "SoftTimer.h"
#define ANTI_PRELL_TIMEOUT 10

class DebouncerUser {
public:
  virtual void buttonPressed() = 0;
};

class Debouncer: public SoftTimerHandler {
  volatile unsigned char *port;
  unsigned char mask;
  DebouncerUser *user;
  unsigned char currentInputState;
  unsigned char lastInputState;
  unsigned char repeat;
	Debouncer( const Debouncer &c );
	Debouncer& operator=( const Debouncer &c );
public:
	Debouncer(volatile void *newPort, unsigned char newMask, DebouncerUser *newUser);
	~Debouncer();
  void inputChanged();
  void handleTimeout();
  unsigned short handleTimerSet(unsigned short oldValue, unsigned short newValue);
};

#endif //__DEBOUNCER_H__
