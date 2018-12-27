/* 
* AntiPrell.cpp
*
* Created: 3/27/2015 9:19:15 PM
* Author: huszty
*/

#include "Debouncer.h"
#include "Uart.h"

Debouncer::Debouncer(DebouncerUser *newUser): SoftTimerHandler(true, false, true),
                                              user(newUser),
											                        repeat(0) {
  lastInputState = 1;
  currentInputState = lastInputState;
  //PUTS("AntiPrell::AntiPrell "); PUTI(lastInputState); PUTI(currentInputState); NL();
}

Debouncer::~Debouncer() {
}

void Debouncer::handleTimeout() {
	//PUTS("AntiPrell::handleTimeout "); PUTI(lastInputState); PUTI(currentInputState); NL();
  lastInputState = currentInputState;
  if(repeat) {
    user->buttonPressed();
  }
  if(!lastInputState) {
    myTimer.set(100);
    repeat = 1;
  }
}

unsigned short Debouncer::handleTimerSet(uint16_t oldValue, uint16_t newValue) {
  //PUTS("AntiPrell::handleTimerSet "); PUTI(lastInputState); PUTI(currentInputState); NL();
  if(!repeat && lastInputState && !currentInputState) {
    //PUTS("AntiPrell::handleSet calling user"); NL();
    user->buttonPressed();
  }
  if(!lastInputState && currentInputState) {
    repeat = 0;
  }
  return newValue;
}

void Debouncer::inputChanged(uint8_t newCurrentInputState){
  currentInputState = newCurrentInputState;
  //PUTS("AntiPrell::inputChanged "); PUTI(lastInputState); PUTI(currentInputState); NL();
  if(!myTimer.get() || repeat)
    myTimer.set(ANTI_PRELL_TIMEOUT);
}
