/*
 * max7219.h
 *
 * Created: 2018. 12. 23. 15:33:10
 *  Author: Gergo Huszty
 */ 


#ifndef MAX7219_H_
#define MAX7219_H_

#include "SoftTimer.h"

class Max7219: public SoftTimerHandler {
  uint8_t digitsInUse;
  uint8_t SsPin;
  uint8_t refreshTime;
  uint8_t content[8];
  uint8_t prevContent[8];
  inline void spiSendByte(char);
  inline void writeData(char, char);
public:
  Max7219(uint8_t newDigitsInUse, uint8_t newSsPin, uint8_t newRefreshTime);
  void handleTimeout();
  void init();
  void applyContent();
  void clearDisplay();
  void setNumber(int32_t newNumber, uint8_t newDotPlace = 8);
};

#endif /* MAX7219_H_ */