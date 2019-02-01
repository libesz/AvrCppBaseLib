/* 
* RotaryEncoder.cpp
*
* Created: 2019. 02. 01. 21:00:22
* Author: Huszty Gergo
*/


#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(RotaryHandler * const newHandler): handler(newHandler) {
}

RotaryEncoder::~RotaryEncoder() {
}

void RotaryEncoder::clkChangedHighToLow(bool dt) {
  if(dt) {
    handler->HandleCCW();
  } else {
    handler->HandleCW();
  }
}
