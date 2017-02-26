/* 
* AntiPrell.cpp
*
* Created: 3/27/2015 9:19:15 PM
* Author: huszty
*/

#include "AntiPrell.h"
#include "Usart.h"

AntiPrell::AntiPrell(volatile void *newPort,
                     unsigned char newMask,
                     AntiPrellUser *newUser): SoftTimerHandler(true, false, true),
                                              port((volatile unsigned char *)newPort),
                                              mask(newMask),
                                              user(newUser) {
  lastInputState = *port & mask;
  currentInputState = lastInputState;
  //PUTS("AntiPrell::AntiPrell "); PUTI(lastInputState); PUTI(currentInputState); NL();
}

AntiPrell::~AntiPrell() {
}

void AntiPrell::handleTimeout() {
	//PUTS("AntiPrell::handleTimeout "); PUTI(lastInputState); PUTI(currentInputState); NL();
  lastInputState = currentInputState;
}

unsigned short AntiPrell::handleTimerSet(unsigned short oldValue, unsigned short newValue) {
  //PUTS("AntiPrell::handleTimerSet "); PUTI(lastInputState); PUTI(currentInputState); NL();
  if(lastInputState && !currentInputState) {
    //PUTS("AntiPrell::handleSet calling user"); NL();
    lastInputState = currentInputState;
    user->buttonPressed();
  }    
  return newValue;
}

void AntiPrell::inputChanged(){
  currentInputState = *port & mask;
  //PUTS("AntiPrell::inputChanged "); PUTI(lastInputState); PUTI(currentInputState); NL();
  if(!myTimer.get())
    myTimer.set(ANTI_PRELL_TIMEOUT);
}
