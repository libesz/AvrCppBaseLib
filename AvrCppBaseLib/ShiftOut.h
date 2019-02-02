/* 
* ShiftOut.h
*
* Created: 2019. 02. 01. 23:14:51
* Author: Huszty Gergo
*/


#ifndef __SHIFTOUT_H__
#define __SHIFTOUT_H__

#include "CppStubs.h"

template<uint8_t SsPin> class ShiftOut {
	ShiftOut( const ShiftOut &c );
	ShiftOut& operator=( const ShiftOut &c );
  uint8_t data;
public:
	ShiftOut(): data(0) {
  apply();
  }
	~ShiftOut() {}
  void set(uint8_t index, bool state) {
    if(state) {
      data |= (1<<index);
    } else {
      data &= ~(1<<index);
    }
  }
  void apply() {
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
    PORTB |= (1<<SsPin);
    PORTB &= ~(1<<SsPin);
  }
};

#endif //__SHIFTOUT_H__
