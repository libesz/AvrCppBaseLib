/* 
* AnalogInputSource.cpp
*
* Created: 3/29/2015 11:27:12 AM
* Author: huszty
*/

#include <avr/io.h>
#include "AnalogInputSource.h"
#include "Uart.h"

bool AnalogInputSource::exists = false;

/*void AnalogInputHandler::handlePotChange( unsigned short value ) {
	PUTS("AnalogInputHandler::handlePotChange NOT IMPLEMENTED");
}*/

AnalogInputSource::AnalogInputSource(): SoftTimerHandler(false, false, true),
                                        used(0) {
  if(!exists) {
    exists = true;
    PUTS("AnalogInputSource::AnalogInputSource"); NL();
    ADMUX = (1<<REFS0);
    ADCSRA |= ((1<<ADEN) | (1<<ADPS2) | (1<<ADPS1));
    myTimer.set(ANALOG_INPUT_UPDATE_TIME);
  }
}

AnalogInputSource::~AnalogInputSource() {
}

void AnalogInputSource::add( AnalogInputHandler* handler ) {
	if(used<ANALOG_INPUT_AMOUNT) {
  	PUTS("AnalogInputSource::add added: "); PUTI(used); NL();
  	handlers[used++] = handler;
  } else {
  	PUTS("AnalogInputSource::add ALREADY FULL"); NL();
	}
}

void AnalogInputSource::handleTimeout() {
  for(unsigned char i=0; i<used; i++) {
    short newInputValue = get(i);
    if( ( lastInputValues[ i ] > ( newInputValue + ANALOG_INPUT_HIST ) ) ||
        ( lastInputValues[ i ] < ( newInputValue - ANALOG_INPUT_HIST ) ) ||
        ( ( lastInputValues[ i ] != LOWEST_INPUT_VALUE ) && ( newInputValue == LOWEST_INPUT_VALUE ) ) ||
        ( ( lastInputValues[ i ] != HIGHEST_INPUT_VALUE ) && ( newInputValue == HIGHEST_INPUT_VALUE ) ) ) {
      handlers[i]->handlePotChange((unsigned short)newInputValue);
      lastInputValues[i] = newInputValue;
    }      
  }    
	myTimer.set(ANALOG_INPUT_UPDATE_TIME);
}

unsigned short AnalogInputSource::get( unsigned char index ) {
   unsigned short value;
   ADMUX &= 0xF0;
   ADMUX |= index;
   ADCSRA |= (1<<ADSC);
   while((ADCSRA&(1<<ADSC)));
   value = ADCL;
   value += (ADCH*256);
   return value;
}
