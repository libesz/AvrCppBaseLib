/* 
* SoftTimerSet.h
*
* Created: 3/27/2015 8:25:43 PM
* Author: huszty
*/


#ifndef __SOFTTIMERSET_H__
#define __SOFTTIMERSET_H__

#include "SoftTimer.h"
#include "Uart.h"

template<unsigned char T_SIZE> class SoftTimerSet {
private:
  unsigned char used;
  SoftTimer *timers[T_SIZE];
  SoftTimerSet( const SoftTimerSet &c );
	SoftTimerSet& operator=( const SoftTimerSet &c );

public:
	SoftTimerSet() = default;
	~SoftTimerSet(){}
  void add(SoftTimerHandler* handler) {
    if(used<T_SIZE) {
      PUTS("SoftTimerSet::add added: "); PUTI(used); NL();
      timers[used++] = handler->getTimer();
    } else {
      PUTS("SoftTimerSet::add ALREADY FULL"); NL();
    }
  }

  void tick() {
    for(int i=0; i<used; i++)
      timers[i]->tick();
  }
};

#endif //__SOFTTIMERSET_H__
