/* 
* SoftTimerSet.cpp
*
* Created: 3/27/2015 8:25:43 PM
* Author: huszty
*/

#include "SoftTimerSet.h"
#include "Usart.h"

SoftTimerSet::SoftTimerSet() {
}

SoftTimerSet::~SoftTimerSet() {
}

void SoftTimerSet::tick() {
	for(int i=0; i<used; i++) {
    timers[i]->tick();
  }
}

void SoftTimerSet::add(SoftTimerHandler* handler) {
	if(used<TIMERSETSIZE) {
    PUTS("SoftTimerSet::add added: "); PUTI(used); NL();
    timers[used++] = handler->getTimer();
  } else {
    PUTS("SoftTimerSet::add ALREADY FULL"); NL();
  }    
}
