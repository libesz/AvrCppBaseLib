/* 
* AntiPrell.h
*
* Created: 3/27/2015 9:19:15 PM
* Author: huszty
*/


#ifndef __DEBOUNCER_H__
#define __DEBOUNCER_H__

#include "SoftTimer.h"
#include <stdint.h>
#define ANTI_PRELL_TIMEOUT 10

class DebouncerUser {
public:
  virtual void buttonPressed() = 0;
};

class Debouncer: public SoftTimerHandler {
  DebouncerUser *user;
  uint8_t currentInputState;
  uint8_t lastInputState;
  uint8_t repeat;
	Debouncer( const Debouncer &c );
	Debouncer& operator=( const Debouncer &c );
public:
	Debouncer(DebouncerUser *newUser);
	~Debouncer();
  void inputChanged(uint8_t);
  void handleTimeout();
  unsigned short handleTimerSet(uint16_t oldValue, uint16_t newValue);
};

#endif //__DEBOUNCER_H__
