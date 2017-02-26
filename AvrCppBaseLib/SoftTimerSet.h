/* 
* SoftTimerSet.h
*
* Created: 3/27/2015 8:25:43 PM
* Author: huszty
*/


#ifndef __SOFTTIMERSET_H__
#define __SOFTTIMERSET_H__

#include "SoftTimer.h"

#ifndef TIMERSETSIZE
  #define TIMERSETSIZE 5
#endif

class SoftTimerSet {
private:
  unsigned char used;
  SoftTimer *timers[TIMERSETSIZE];
  SoftTimerSet( const SoftTimerSet &c );
	SoftTimerSet& operator=( const SoftTimerSet &c );

public:
	SoftTimerSet();
	~SoftTimerSet();
  void add(SoftTimerHandler* handler);
  void tick();
};

#endif //__SOFTTIMERSET_H__
