/* 
* TapTempo.h
*
* Created: 3/28/2015 9:17:57 AM
* Author: huszty
*/


#ifndef __TAPTEMPO_H__
#define __TAPTEMPO_H__

#include "AntiPrell.h"
#include "SoftTimer.h"

#ifndef TAPTEMPOTIMEOUT
  #define TAPTEMPOTIMEOUT 1000
#endif

class TapTempoHandler {
public:
  virtual void handleTapTempo(unsigned short value);
};

class TapTempo: public AntiPrellUser, public SoftTimerHandler {
  unsigned short lastTapTime;
  TapTempoHandler *tapTempoHandler;
	TapTempo( const TapTempo &c );
	TapTempo& operator=( const TapTempo &c );
public:
	TapTempo(TapTempoHandler *newTapTempoHandler);
	~TapTempo();
  void buttonPressed();
  unsigned short handleTimerSet(unsigned short oldValue, unsigned short newValue);
};

#endif //__TAPTEMPO_H__
