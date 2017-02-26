/* 
* AnalogInputSource.h
*
* Created: 3/29/2015 11:27:12 AM
* Author: huszty
*/

#ifndef __ANALOGINPUTSOURCE_H__
#define __ANALOGINPUTSOURCE_H__

#include "SoftTimer.h"

#ifndef ANALOG_INPUT_AMOUNT
  #define ANALOG_INPUT_AMOUNT 3
#endif

#ifndef ANALOG_INPUT_UPDATE_TIME
  #define ANALOG_INPUT_UPDATE_TIME 100
#endif

#ifndef ANALOG_INPUT_HIST
  #define ANALOG_INPUT_HIST 10
#endif

#define LOWEST_INPUT_VALUE 0
#define HIGHEST_INPUT_VALUE 1023

class AnalogInputHandler {
public:
  virtual void handlePotChange(unsigned short value) = 0;
};

class AnalogInputSource: public SoftTimerHandler {
  static bool exists;
  unsigned char used;
  AnalogInputHandler* handlers[ANALOG_INPUT_AMOUNT];
  short lastInputValues[ANALOG_INPUT_AMOUNT];
	AnalogInputSource( const AnalogInputSource &c );
	AnalogInputSource& operator=( const AnalogInputSource &c );
  unsigned short get(unsigned char index);
public:
	AnalogInputSource();
	~AnalogInputSource();
  void add(AnalogInputHandler* handler);
  void handleTimeout();
};

#endif //__ANALOGINPUTSOURCE_H__
