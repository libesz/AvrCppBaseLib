/* 
* ShiftIn.h
*
* Created: 2019. 02. 02. 11:14:39
* Author: Huszty Gergo
*/

#ifndef __SHIFTIN_H__
#define __SHIFTIN_H__

#include "CppStubs.h"
#include "avr/io.h"

template<uint8_t ldPin> class ShiftIn {
	ShiftIn( const ShiftIn &c );
	ShiftIn& operator=( const ShiftIn &c );
public:
	ShiftIn() {
    PORTB |= (1<<ldPin);
  }
	~ShiftIn();
  uint8_t get() {
    PORTB &= ~(1<<ldPin);
    PORTB |= (1<<ldPin);
    SPDR = 0;
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
  }
};

#endif //__SHIFTIN_H__
