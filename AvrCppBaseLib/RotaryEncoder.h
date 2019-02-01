/* 
* RotaryEncoder.h
*
* Created: 2019. 02. 01. 21:00:22
* Author: Huszty Gergo
*/


#ifndef __ROTARYENCODER_H__
#define __ROTARYENCODER_H__

#include "CppStubs.h"

class RotaryHandler {
public:
  virtual void HandleCW() = 0;
  virtual void HandleCCW() = 0;
};

class RotaryEncoder {
	RotaryEncoder( const RotaryEncoder &c );
	RotaryEncoder& operator=( const RotaryEncoder &c );
  RotaryHandler * const handler;
public:
	RotaryEncoder(RotaryHandler * const newHandler);
	~RotaryEncoder();
  void clkChangedHighToLow(bool dt);
};

#endif //__ROTARYENCODER_H__
