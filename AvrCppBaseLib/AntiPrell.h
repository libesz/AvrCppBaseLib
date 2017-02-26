/* 
* AntiPrell.h
*
* Created: 3/27/2015 9:19:15 PM
* Author: huszty
*/


#ifndef __ANTIPRELL_H__
#define __ANTIPRELL_H__

#include "SoftTimer.h"
#define ANTI_PRELL_TIMEOUT 10

class AntiPrellUser {
public:
  virtual void buttonPressed() = 0;
};

class AntiPrell: public SoftTimerHandler {
  volatile unsigned char *port;
  unsigned char mask;
  AntiPrellUser *user;
  unsigned char currentInputState;
  unsigned char lastInputState;
	AntiPrell( const AntiPrell &c );
	AntiPrell& operator=( const AntiPrell &c );
public:
	AntiPrell(volatile void *newPort, unsigned char newMask, AntiPrellUser *newUser);
	~AntiPrell();
  void inputChanged();
  void handleTimeout();
  unsigned short handleTimerSet(unsigned short oldValue, unsigned short newValue);
};

#endif //__ANTIPRELL_H__
