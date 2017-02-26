/* 
* TapTempo.cpp
*
* Created: 3/28/2015 9:17:56 AM
* Author: huszty
*/

#include "TapTempo.h"
#include "Uart.h"

TapTempo::TapTempo(TapTempoHandler *newTapTempoHandler): SoftTimerHandler(true, false, false),
                                                              lastTapTime(TAPTEMPOTIMEOUT),
                                                              tapTempoHandler(newTapTempoHandler) {
}

TapTempo::~TapTempo() {
}

void TapTempo::buttonPressed() {
	PUTS("TapTempo::buttonPressed"); NL();
  myTimer.set(TAPTEMPOTIMEOUT);
  tapTempoHandler->handleTapTempo(lastTapTime);
}

unsigned short TapTempo::handleTimerSet( unsigned short oldValue, unsigned short newValue ) {
  if(oldValue)
    lastTapTime = (lastTapTime + TAPTEMPOTIMEOUT - oldValue) / 2;

	PUTS("TapTempo::handleTimerSet: "); PUTI(lastTapTime); NL();
  return newValue;
}
