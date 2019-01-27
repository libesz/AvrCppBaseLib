/* 
* Debouncer.cpp
*
* Created: 3/27/2015 9:19:15 PM
* Author: huszty
*/

#include "Debouncer.h"
#include "Uart.h"

Debouncer::Debouncer(const DebouncerUser *newUser,
                     uint8_t newTimeout,
                     uint8_t newRepeatFirstTimeout,
                     uint8_t newRepeatTimeout): SoftTimerHandler(false, false, true),
                                                user(newUser),
                                                timeout(newTimeout),
                                                repeatFirstTimeout(newRepeatFirstTimeout),
                                                repeatTimeout(newRepeatTimeout),
                                                repeatState(None) {
  lastInputState = 1;
  currentInputState = lastInputState;
  //PUTS("AntiPrell::AntiPrell "); PUTI(lastInputState); PUTI(currentInputState); NL();
}

Debouncer::~Debouncer() {
}

void Debouncer::handleTimeout() {
	//PUTS("AntiPrell::handleTimeout "); PUTI(lastInputState); PUTI(currentInputState); NL();
  lastInputState = currentInputState;
  if(!lastInputState) {
    if(repeatState == None) {
      repeatState = First;
      myTimer.set(repeatFirstTimeout);
    } else {
      user->buttonPressed();
      repeatState = Nth;
      myTimer.set(repeatTimeout);
    }
  }
}

void Debouncer::inputChanged(uint8_t newCurrentInputState){
  currentInputState = newCurrentInputState;
  //PUTS("AntiPrell::inputChanged "); PUTI(lastInputState); PUTI(currentInputState); NL();
  if(currentInputState != lastInputState) {
    if(!currentInputState && !myTimer.get()) {
      user->buttonPressed();
    }      
    repeatState = None;
    myTimer.set(timeout);
  }
}
