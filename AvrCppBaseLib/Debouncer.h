/* 
* Debouncer.h
*
* Created: 3/27/2015 9:19:15 PM
* Author: huszty
*/


#ifndef __DEBOUNCER_H__
#define __DEBOUNCER_H__

#include "CppStubs.h"
#include "SoftTimer.h"
#include <stdint.h>
#define DEBOUNCER_DEFAULT_TIMEOUT 3
#define DEBOUNCER_DEFAULT_REPEAT_FIRST_TIMEOUT 100
#define DEBOUNCER_DEFAULT_REPEAT_TIMEOUT 20

class DebouncerUser {
public:
  virtual void buttonPressed() const = 0;
  virtual void buttonRepeat() const = 0;
};

class Debouncer: public SoftTimerHandler {
  enum repeatStates {None, First, Nth};
  const DebouncerUser *user;
  uint8_t currentInputState;
  uint8_t lastInputState;
  uint8_t timeout;
  uint8_t repeatFirstTimeout;
  uint8_t repeatTimeout;
  repeatStates repeatState;
	Debouncer( const Debouncer &c );
	Debouncer& operator=( const Debouncer &c );
public:
	Debouncer(const DebouncerUser *newUser,
            uint8_t newTimeout = DEBOUNCER_DEFAULT_TIMEOUT,
            uint8_t newRepeatFirstTimeout = DEBOUNCER_DEFAULT_REPEAT_FIRST_TIMEOUT,
            uint8_t newRepeatTimeout = DEBOUNCER_DEFAULT_REPEAT_TIMEOUT);
	~Debouncer();
  void inputChanged(uint8_t);
  void handleTimeout();
  unsigned short handleTimerSet(uint16_t oldValue, uint16_t newValue);
};

#endif //__DEBOUNCER_H__
