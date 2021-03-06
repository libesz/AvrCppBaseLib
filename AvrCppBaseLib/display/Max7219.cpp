/* MAX7219 Interaction Code
 * ---------------------------
 * For more information see
 * http://www.adnbr.co.uk/articles/max7219-and-7-segment-displays
 *
 * Changed to C++ by Gergo Huszty
 */

// Outputs, pin definitions
#define PIN_SCK                   PORTB5
#define PIN_MOSI                  PORTB3

#define ON                        1
#define OFF                       0

#define MAX7219_MODE_DECODE       0x09
#define MAX7219_MODE_INTENSITY    0x0A
#define MAX7219_MODE_SCAN_LIMIT   0x0B
#define MAX7219_MODE_POWER        0x0C
#define MAX7219_MODE_TEST         0x0F
#define MAX7219_MODE_NOOP         0x00

#define MAX7219_CHAR_BLANK        0
#define MAX7219_CHAR_NEGATIVE     0b0000001

#include <avr/io.h>
#include <string.h>
#include "Max7219.h"

Max7219::Max7219(uint8_t newDigitsInUse,
                 uint8_t newSsPin,
                 uint8_t newRefreshTime): SoftTimerHandler(false, false, true),
                                          digitsInUse(newDigitsInUse), SsPin(newSsPin), refreshTime(newRefreshTime),
                                          content(), prevContent() {
    init();
    if(refreshTime) {
      myTimer.set(refreshTime);
    }      
}

void Max7219::handleTimeout() {
  applyContent();
  myTimer.set(refreshTime);
}

void Max7219::setNumber(int32_t number, uint8_t offset, uint8_t minimumDigits) {
    offset = 7-offset;
    if(offset>digitsInUse)
      return;
    bool negative = false;
    if (number < 0) {
      negative = true;
      number *= -1;
    }
    
    uint8_t i = offset;
    do {
      uint8_t data = pgm_read_byte(&SevenSegmentASCII[(number % 10)+'0'-32]);
      content[i--] = data;
      number /= 10;
      if(minimumDigits) {
        minimumDigits--;
      }
    } while (number && i);
    
    while(minimumDigits && i) {
      content[i--] = pgm_read_byte(&SevenSegmentASCII['0'-32]);
      minimumDigits--;
    }
    
    if (negative && i) {
      content[i] = MAX7219_CHAR_NEGATIVE;
    }
}

void Max7219::setRawChar(int8_t data, uint8_t offset) {
  content[7-offset] = data;
}

void Max7219::setString(const char *str, uint8_t startAt) {
  uint8_t i = 0;
  while(((startAt + i) < 8) && i < strlen(str)) {
    content[startAt+i] = pgm_read_byte(&SevenSegmentASCII[str[i]-32]);
    i++;
  }
}

void Max7219::setDot(uint8_t place, bool state) {
  if(state) {
    content[place] |= (1<<7);
  } else {
    content[place] &= ~(1<<7);
  }    
}

void Max7219::spiSendByte(uint8_t databyte) {
    // Copy data into the SPI data register
    SPDR = databyte;
    // Wait until transfer is complete
    while (!(SPSR & (1 << SPIF)));
}

void Max7219::writeData(uint8_t data_register, uint8_t data) {  
  PORTB &= ~(1<<SsPin);
  // Send the register where the data will be stored
  spiSendByte(data_register);
  // Send the data to be stored
  spiSendByte(data);
  PORTB |= (1<<SsPin);
}

void Max7219::clearDisplay(uint8_t start, uint8_t len) {
  memset(&(content[start]), MAX7219_CHAR_BLANK, ((start+len)>digitsInUse)?(digitsInUse):(len));
}

void Max7219::applyContent() {
    uint8_t i = 0;
    do {
      uint8_t item = content[i];
      if(prevContent[i] != item) {
        writeData((9 - ++i), item);
      } else {
        i++;
      }
    } while (i<digitsInUse);
    memcpy(prevContent, content, digitsInUse);
}

void Max7219::init() {
	// SCK MOSI CS/LOAD/SS
  DDRB |= (1 << PIN_SCK) | (1 << PIN_MOSI) | (1 << SsPin);

  // SPI Enable, Master mode
  SPCR |= (1 << SPE) | (1 << MSTR)| (1<<SPR1);

  // Decode mode to "No Decode"
  writeData(MAX7219_MODE_DECODE, 0x00);
  // Scan limit runs from 0.
  writeData(MAX7219_MODE_SCAN_LIMIT, digitsInUse - 1);
  writeData(MAX7219_MODE_INTENSITY, 4);
  writeData(MAX7219_MODE_POWER, ON);
	clearDisplay();
	for(uint8_t i=0; i<digitsInUse; i++) {
	  writeData(i+1, MAX7219_CHAR_BLANK);
	}
}

