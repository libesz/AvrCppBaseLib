/*
 * max7219.h
 *
 * Created: 2018. 12. 23. 15:33:10
 *  Author: Gergo Huszty
 */ 


#ifndef MAX7219_H_
#define MAX7219_H_

#include "CppStubs.h"
#include "SoftTimer.h"

#include "7-Segment-ASCII_SYM.txt"

class Max7219: public SoftTimerHandler {
  uint8_t digitsInUse;
  uint8_t SsPin;
  uint8_t refreshTime;
  uint8_t content[8];
  uint8_t prevContent[8];
  inline void spiSendByte(uint8_t);
  inline void writeData(uint8_t, uint8_t);
public:
  Max7219(uint8_t newDigitsInUse, uint8_t newSsPin, uint8_t newRefreshTime);
  void handleTimeout();
  void init();
  void applyContent();
  void clearDisplay();
  void setNumber(int32_t newNumber, uint8_t offset = 0, uint8_t newDotPlace = 9);
  void setRawChar(int8_t data, uint8_t offset = 0);
  void setString(char *str, uint8_t startAt = 0);
};

#endif /* MAX7219_H_ */